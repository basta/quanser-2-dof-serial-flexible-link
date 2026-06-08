#!/usr/bin/env python
"""Export every figure used by report.typ into report/figs/.

This is a standalone, non-interactive port of the designs and simulations in
``analysis/compare_methods_output.py`` (the marimo notebook). The controllers
(LQG, output-MPC, H-infinity) are designed ONCE on the nominal model; each
figure then simulates them against a perturbed *truth* plant. Edit the CONFIG
block below, rerun, and recompile the report:

    .venv/bin/python report/make_figures.py
    cd report && typst compile --root .. report.typ

Outputs (report/figs/): compare_nominal.png, hinf_sensitivity.png,
robust_spillover.png, robust_delay.png, robust_ks_sweep.png
"""
from __future__ import annotations

import os
import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import control
import cvxpy as cp
from scipy.linalg import expm

# ============================================================================
#  CONFIG  — tweak these, rerun, recompile
# ============================================================================
OUT_DIR = os.path.join(os.path.dirname(__file__), "figs")
DPI = 150

REF_DEG = 20.0        # tip-angle step reference [deg]   (design + all figures)
UMAX = 0.6            # current clip ±u_max [A]
DEFL_DEG = 2.0        # MPC tip-deflection limit [deg]

# robustness scenarios
SPILL_F2 = 3.0        # scenario A: 2nd-mode freq as a multiple of the modelled mode
SPILL_COUT = 1.0      # scenario A: 2nd-mode coupling into the tip output
SPILL_Z2 = 0.02       # scenario A: 2nd-mode damping
DELAY_MS = 60.0       # scenario B: input delay [ms]
KS_SWEEP = np.linspace(0.3, 1.5, 13)   # §5 parametric stiffness multipliers

# colours / styles per method
STYLE = {
    "LQG":        dict(color="#1f77b4", ls="-"),
    "output-MPC": dict(color="#ff7f0e", ls="--"),
    r"H$\infty$": dict(color="#2ca02c", ls="-."),
}

# ============================================================================
#  NOMINAL MODEL  (Stage-1 parameters from config_2dslf.m)
# ============================================================================
K_IN2M = 0.0254
Me = 2.068427e11
Xb1, Tb1, L1 = 3.0 * K_IN2M, 0.050 * K_IN2M, 0.202
KS1_NOM = Me * Xb1 * Tb1 ** 3 / (4 * L1)
B11, Kg1, Km1 = 4.0, 100, 0.119
KTG1 = 0.75 * Km1 * Kg1
Jm1 = 6.28e-6
J11 = Kg1 ** 2 * Jm1 + 0.00073616
M12 = 1.578
J12 = 0.18028257 - M12 * 0.079 ** 2

C_TIP = np.array([1.0, 1.0, 0.0, 0.0])
C_POS = np.array([[1.0, 0, 0, 0], [0, 1.0, 0, 0]])
Ts, Np, Nsim = 0.01, 40, 500


def build_AB(Ks):
    A = np.array([
        [0.0, 0.0, 1.0, 0.0],
        [0.0, 0.0, 0.0, 1.0],
        [0.0, Ks / J11, -B11 / J11, 0.0],
        [0.0, -(J11 + J12) / (J11 * J12) * Ks, B11 / J11, 0.0],
    ])
    B = np.array([[0.0], [0.0], [KTG1 / J11], [-KTG1 / J11]])
    return A, B


def discretize(Ks):
    A, B = build_AB(Ks)
    Mx = expm(np.block([[A, B], [np.zeros((1, 5))]]) * Ts)
    return Mx[:4, :4], Mx[:4, 4:5]


# ============================================================================
#  CONTROLLER DESIGN  (once, on the nominal model)
# ============================================================================
A0, B0 = build_AB(KS1_NOM)
Ad0, Bdc0 = discretize(KS1_NOM)

# --- LQR gain + DARE terminal cost ---
Qy, Ru = 50.0, 0.5
Q = Qy * np.outer(C_TIP, C_TIP) + 1e-3 * np.eye(4)
R = np.array([[Ru]])
K, P, _ = control.dlqr(Ad0, Bdc0, Q, R)
K = np.asarray(K)

# --- Kalman predictor from the two positions ---
qn, rn = 10.0, 1e-6
Qn = Bdc0 @ Bdc0.T * qn + 1e-9 * np.eye(4)
Rn = rn * np.eye(2)
L, _, _ = control.dlqe(Ad0, np.eye(4), C_POS, Qn, Rn)
L = np.asarray(L)

# --- 2-measurement H-infinity (integral-augmented, fixed weights) ---
eps, Wi, w2g, wc, nz = 1e-3, 1.0, 0.1, 8.0, 1e-2
s = control.tf("s")
Ae = A0 - eps * np.eye(4)
W2 = control.tf2ss((s / wc + 1) / (s / 3000 + 1) * w2g)
Aw2, Bw2, Cw2, Dw2 = [np.atleast_2d(x) for x in (W2.A, W2.B, W2.C, W2.D)]
n2 = Aw2.shape[0]
n = 4 + 1 + n2
Ap = np.zeros((n, n)); Ap[:4, :4] = Ae; Ap[4, :4] = -C_TIP; Ap[5:, 5:] = Aw2
Bp = np.zeros((n, 5)); Bp[4, 0] = 1.0; Bp[:4, 4:5] = B0; Bp[5:, 4:5] = Bw2
Cp = np.zeros((5, n)); Cp[0, 4] = Wi; Cp[1, 5:] = Cw2.ravel()
Cp[2, :4] = C_POS[0]; Cp[3, :4] = C_POS[1]; Cp[4, 4] = 1.0
Dp = np.zeros((5, 5)); Dp[1, 4] = Dw2[0, 0]
Dp[2, 1] = nz; Dp[3, 2] = nz; Dp[4, 3] = nz
_hinf = control.hinfsyn(control.ss(Ap, Bp, Cp, Dp), 3, 1)
Kc_hinf = _hinf[0]
GAMMA = float(np.ravel(np.asarray(_hinf[2], dtype=float))[0])
Kd = control.sample_system(Kc_hinf, Ts, method="tustin")
HB = np.atleast_2d(np.asarray(Kd.B)); HC = np.atleast_2d(np.asarray(Kd.C))
HD = np.atleast_2d(np.asarray(Kd.D)); Hk = np.atleast_2d(np.asarray(Kd.A))
HINF_ORDER = np.asarray(Kc_hinf.A).shape[0]
print(f"[design] H-inf gamma={GAMMA:.3f}, controller order {HINF_ORDER}")

# nominal design point shared by every simulation
r = np.deg2rad(REF_DEG)
x_ss = np.array([r, 0.0, 0.0, 0.0])
Bd = Bdc0.ravel()
Kf = K.ravel()


# ============================================================================
#  TRUTH-PLANT BUILDER  (controllers never see these perturbations)
# ============================================================================
W1_MODE = float(np.max(np.abs(np.linalg.eigvals(A0).imag)))   # ~16.9 rad/s
GIN = float(B0[2, 0])                                          # modal input gain


def make_truth(ks_mult=1.0, mode_on=False, f2=SPILL_F2, z2d=SPILL_Z2,
               cout=SPILL_COUT, ndelay=0):
    """Discrete truth plant: perturbed Ks, optional 2nd mode, optional delay."""
    A, B = build_AB(KS1_NOM * ks_mult)
    if mode_on:
        w2 = f2 * W1_MODE
        A2 = np.array([[0.0, 1.0], [-w2 ** 2, -2 * z2d * w2]])
        Aa = np.zeros((6, 6)); Aa[:4, :4] = A; Aa[4:, 4:] = A2
        Ba = np.vstack([B, np.array([[0.0], [GIN]])])
        cy = np.array([1.0, 1.0, 0, 0, cout, 0])
        cm = np.array([[1.0, 0, 0, 0, 0, 0], [0, 1.0, 0, 0, cout, 0]])
    else:
        Aa, Ba = A, B
        cy = np.array([1.0, 1.0, 0, 0])
        cm = np.array([[1.0, 0, 0, 0], [0, 1.0, 0, 0]])
    nx = Aa.shape[0]
    Mx = expm(np.block([[Aa, Ba], [np.zeros((1, nx + 1))]]) * Ts)
    Adt, Bdt = Mx[:nx, :nx], Mx[:nx, nx:nx + 1]
    if ndelay > 0:
        N = nx + ndelay
        Af = np.zeros((N, N)); Af[:nx, :nx] = Adt; Af[:nx, nx] = Bdt.ravel()
        for i in range(ndelay - 1):
            Af[nx + i, nx + i + 1] = 1.0
        Bf = np.zeros((N, 1)); Bf[-1, 0] = 1.0
        cy = np.concatenate([cy, np.zeros(ndelay)])
        cm = np.hstack([cm, np.zeros((2, ndelay))])
        return Af, Bf, cy, cm
    return Adt, Bdt, cy, cm


# ============================================================================
#  SIMULATION  (nominal observer; controllers fixed at design)
# ============================================================================
umax = UMAX
defl_lim = np.deg2rad(DEFL_DEG)


def observe(xh, u, ym):
    return Ad0 @ xh + Bd * u + L @ (ym - C_POS @ xh)


def sim_lqg(At, Bt, Cy, Cm, nt):
    x = np.zeros(nt); xh = np.zeros(4)
    y = np.empty(Nsim); d = np.empty(Nsim); u = np.empty(Nsim)
    for k in range(Nsim):
        ym = Cm @ x
        uk = float(np.clip(-Kf @ (xh - x_ss), -umax, umax))
        y[k] = np.rad2deg(Cy @ x); d[k] = np.rad2deg(ym[1]); u[k] = uk
        xh = observe(xh, uk, ym); x = At @ x + Bt.ravel() * uk
    return y, d, u


# MPC problem built once (depends only on the nominal design point)
_x0 = cp.Parameter(4)
_U = cp.Variable((1, Np)); _X = cp.Variable((4, Np + 1)); _Sl = cp.Variable(Np, nonneg=True)
_cost = 0; _cons = [_X[:, 0] == _x0]
for k in range(Np):
    _cost += cp.quad_form(_X[:, k] - x_ss, cp.psd_wrap(Q)) + Ru * cp.square(_U[0, k]) + 1e4 * _Sl[k]
    _cons += [_X[:, k + 1] == Ad0 @ _X[:, k] + Bd * _U[0, k],
              cp.abs(_U[0, k]) <= umax, cp.abs(_X[1, k + 1]) <= defl_lim + _Sl[k]]
_cost += cp.quad_form(_X[:, Np] - x_ss, cp.psd_wrap(P))
_mpc = cp.Problem(cp.Minimize(_cost), _cons)


def sim_mpc(At, Bt, Cy, Cm, nt):
    x = np.zeros(nt); xh = np.zeros(4)
    y = np.empty(Nsim); d = np.empty(Nsim); u = np.empty(Nsim)
    for k in range(Nsim):
        ym = Cm @ x
        _x0.value = xh
        _mpc.solve(solver=cp.CLARABEL, warm_start=True)
        uk = float(np.clip(_U.value[0, 0], -umax, umax)) if _U.value is not None else 0.0
        y[k] = np.rad2deg(Cy @ x); d[k] = np.rad2deg(ym[1]); u[k] = uk
        xh = observe(xh, uk, ym); x = At @ x + Bt.ravel() * uk
    return y, d, u


def sim_hinf(At, Bt, Cy, Cm, nt):
    x = np.zeros(nt); xi = 0.0; xc = np.zeros(Hk.shape[0])
    y = np.empty(Nsim); d = np.empty(Nsim); u = np.empty(Nsim)
    for k in range(Nsim):
        ym = Cm @ x
        meas = np.array([ym[0], ym[1], xi])
        uu = (HC @ xc + HD @ meas).reshape(-1)[0]
        uk = float(np.clip(uu, -umax, umax))
        yk = float(Cy @ x)
        y[k] = np.rad2deg(yk); d[k] = np.rad2deg(ym[1]); u[k] = uk
        xc = Hk @ xc + HB @ meas.reshape(-1)
        xi = xi + Ts * (r - yk)
        x = At @ x + Bt.ravel() * uk
    return y, d, u


SIMS = {"LQG": sim_lqg, "output-MPC": sim_mpc, r"H$\infty$": sim_hinf}
T = np.arange(Nsim) * Ts


def run(**truth):
    At, Bt, Cy, Cm = make_truth(**truth)
    nt = At.shape[0]
    return {nm: f(At, Bt, Cy, Cm, nt) for nm, f in SIMS.items()}


# ============================================================================
#  FIGURE 1 — nominal three-method comparison
# ============================================================================
def fig_nominal():
    res = run()
    lim = 3 * abs(REF_DEG)
    fig, (a1, a2, a3) = plt.subplots(3, 1, figsize=(7.0, 6.4), sharex=True)
    for nm, (y, d, u) in res.items():
        st = STYLE[nm]
        a1.plot(T, np.clip(y, -lim, lim), lw=1.5, label=nm, **st)
        a2.plot(T, np.clip(d, -lim, lim), lw=1.3, **st)
        a3.plot(T, u, lw=1.1, **st)
    a1.axhline(REF_DEG, color="r", ls=":", lw=1, label="reference")
    a1.set_ylabel("tip angle [°]"); a1.legend(loc="lower right", ncol=2, fontsize=8)
    a1.set_title(f"Nominal output feedback  (ref = +{REF_DEG:g}°, "
                 f"$u_{{max}}$ = {UMAX:g} A, H$\\infty$ γ = {GAMMA:.2f})")
    a2.axhline(DEFL_DEG, color="k", ls=":", lw=1, label="MPC limit")
    a2.axhline(-DEFL_DEG, color="k", ls=":", lw=1)
    a2.set_ylabel(r"tip deflection $\theta_t$ [°]")
    a2.legend(loc="upper right", fontsize=8)
    a3.axhline(UMAX, color="k", ls=":", lw=1); a3.axhline(-UMAX, color="k", ls=":", lw=1)
    a3.set_ylabel("current $u$ [A]"); a3.set_xlabel("time [s]")
    save(fig, "compare_nominal.png")


# ============================================================================
#  FIGURE 2 — H-infinity sensitivity S and complementary sensitivity T
# ============================================================================
def fig_sensitivity():
    A_st, B_st = build_AB(KS1_NOM); B_st = B_st.ravel()
    Ac = np.atleast_2d(np.asarray(Kc_hinf.A)); Bc = np.atleast_2d(np.asarray(Kc_hinf.B))
    Cc = np.atleast_2d(np.asarray(Kc_hinf.C)); Dc = np.atleast_2d(np.asarray(Kc_hinf.D))
    nc = Ac.shape[0]; Nst = 4 + 1 + nc
    Cmst = np.zeros((3, Nst)); Cmst[0, :4] = C_POS[0]; Cmst[1, :4] = C_POS[1]; Cmst[2, 4] = 1.0
    Acl = np.zeros((Nst, Nst)); Bcl = np.zeros((Nst, 1))
    Du = Dc @ Cmst
    Acl[:4, :4] = A_st
    Acl[:4, :] += np.outer(B_st, Du.ravel())
    Acl[:4, 5:5 + nc] += B_st.reshape(-1, 1) @ Cc
    Acl[4, :4] = -C_TIP; Bcl[4, 0] = 1.0
    Acl[5:, :] = Bc @ Cmst; Acl[5:, 5:5 + nc] += Ac
    Ccl = np.zeros((1, Nst)); Ccl[0, :4] = C_TIP
    sysT = control.ss(Acl, Bcl, Ccl, 0.0)

    w = np.logspace(-2, 3, 500)
    db = lambda x: 20 * np.log10(np.maximum(np.abs(x), 1e-12))
    Tv = np.array([sysT(1j * wi) for wi in w]).reshape(-1)
    Sv = 1.0 - Tv
    w_flex = W1_MODE

    fig, (axS, axT) = plt.subplots(2, 1, figsize=(7.0, 5.2), sharex=True)
    axS.semilogx(w, db(Sv), lw=1.8, color="#1f77b4", label="|S| sensitivity")
    axS.axvline(w_flex, color="r", ls=":", lw=1, label="flex mode")
    axS.axhline(0, color="0.7", lw=0.8)
    axS.set_ylabel("|S| [dB]"); axS.legend(loc="lower right", fontsize=8)
    axS.set_title(f"H$\\infty$ loop sensitivities  (γ = {GAMMA:.2f})")
    axT.semilogx(w, db(Tv), lw=1.8, color="#ff7f0e", label="|T| complementary")
    axT.axvline(w_flex, color="r", ls=":", lw=1)
    axT.axhline(0, color="0.7", lw=0.8)
    axT.set_ylabel("|T| [dB]"); axT.set_xlabel("ω [rad/s]")
    axT.legend(loc="lower left", fontsize=8)
    save(fig, "hinf_sensitivity.png")


# ============================================================================
#  FIGURES 3 & 4 — robustness scenarios (tip angle + deflection + current)
# ============================================================================
def _scenario_fig(res, title, fname):
    lim = 3 * abs(REF_DEG)
    fig, (a1, a2, a3) = plt.subplots(3, 1, figsize=(7.0, 6.4), sharex=True)
    for nm, (y, d, u) in res.items():
        st = STYLE[nm]
        a1.plot(T, np.clip(y, -lim, lim), lw=1.5, label=nm, **st)
        a2.plot(T, np.clip(d, -lim, lim), lw=1.3, **st)
        a3.plot(T, u, lw=1.1, **st)
    a1.axhline(REF_DEG, color="r", ls=":", lw=1, label="reference")
    a1.set_ylabel("tip angle [°]"); a1.legend(loc="lower right", ncol=2, fontsize=8)
    a1.set_title(title)
    a2.set_ylabel(r"tip deflection $\theta_t$ [°]")
    a3.axhline(UMAX, color="k", ls=":", lw=1); a3.axhline(-UMAX, color="k", ls=":", lw=1)
    a3.set_ylabel("current $u$ [A]"); a3.set_xlabel("time [s]")
    save(fig, fname)


def fig_spillover():
    res = run(mode_on=True, f2=SPILL_F2, cout=SPILL_COUT, z2d=SPILL_Z2)
    _scenario_fig(
        res,
        f"Scenario A — unmodelled 2nd flexible mode at {SPILL_F2:g}× "
        f"(spillover)",
        "robust_spillover.png",
    )


def fig_delay():
    ndelay = int(round(DELAY_MS / 1000.0 / Ts))
    res = run(ndelay=ndelay)
    _scenario_fig(
        res,
        f"Scenario B — input delay {DELAY_MS:g} ms (phase lag)",
        "robust_delay.png",
    )


# ============================================================================
#  FIGURE 5 — parametric K_s robustness sweep
# ============================================================================
def _metrics(y, d):
    if not np.all(np.isfinite(y)) or np.abs(y).max() > 5 * abs(REF_DEG) + 5:
        return np.nan, np.nan, np.nan          # unstable
    ss_err = abs(y[-1] - REF_DEG)
    overshoot = max(0.0, (y.max() - REF_DEG) / abs(REF_DEG) * 100)
    peak_defl = np.abs(d).max()
    return ss_err, overshoot, peak_defl


def fig_ks_sweep():
    data = {nm: {"ss": [], "os": [], "pd": []} for nm in SIMS}
    for ks in KS_SWEEP:
        res = run(ks_mult=float(ks))
        for nm, (y, d, _u) in res.items():
            ss, os_, pd = _metrics(y, d)
            data[nm]["ss"].append(ss); data[nm]["os"].append(os_); data[nm]["pd"].append(pd)
        print(f"[ks-sweep] Ks×{ks:.2f} done")

    fig, axes = plt.subplots(3, 1, figsize=(7.0, 6.4), sharex=True)
    ylabels = ["steady-state error [°]", "overshoot [%]", r"peak $|\theta_t|$ [°]"]
    keys = ["ss", "os", "pd"]
    for ax, key, yl in zip(axes, keys, ylabels):
        for nm in SIMS:
            st = STYLE[nm]
            ax.plot(KS_SWEEP, data[nm][key], marker="o", ms=3.5, lw=1.3, label=nm, **st)
        ax.set_ylabel(yl); ax.grid(True, alpha=0.3)
    axes[0].axvline(1.0, color="0.6", ls=":", lw=1)
    axes[0].set_title("Parametric robustness — truth-plant stiffness sweep "
                      "(controllers fixed at nominal)")
    axes[0].legend(loc="best", fontsize=8, ncol=3)
    axes[-1].set_xlabel(r"stiffness multiplier $K_s / K_s^{\mathrm{nom}}$")
    save(fig, "robust_ks_sweep.png")


# ============================================================================
def save(fig, name):
    fig.tight_layout()
    path = os.path.join(OUT_DIR, name)
    fig.savefig(path, dpi=DPI, bbox_inches="tight")
    plt.close(fig)
    print(f"[saved] {path}")


def main():
    os.makedirs(OUT_DIR, exist_ok=True)
    fig_nominal()
    fig_sensitivity()
    fig_spillover()
    fig_delay()
    fig_ks_sweep()
    print("\nAll figures written to", OUT_DIR)


if __name__ == "__main__":
    main()
