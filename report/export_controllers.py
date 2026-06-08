#!/usr/bin/env python
"""Export the Python-designed controllers for deployment on the real rig.

The three controllers in ``analysis/compare_methods_output.py`` /
``report/make_figures.py`` are designed in Python (discrete, ``Ts = 10 ms``,
two measured positions + a Kalman observer). To *verify* them on the Quanser
rig they must run inside the Simulink/QUARC model. This script re-uses the
exact same designs (it imports them from ``make_figures``) and writes a single
``orr_controllers.mat`` that the MATLAB-side blocks load.

    .venv/bin/python report/export_controllers.py

Output: software/quanser_updated/orr_controllers.mat  with, for each method,
everything the corresponding MATLAB Function block in
``software/quanser_updated/orr_ctrl_*.m`` needs. All matrices are at the
controller rate ``Ts_ctrl`` (= the design rate, 10 ms); run the blocks at that
sample time inside the 500 Hz model (a Rate Transition handles the multirate).
"""
from __future__ import annotations

import os
import numpy as np
import scipy.io as sio

# Re-use the *identical* designs the report figures are built from. Importing
# make_figures runs the one-shot design (dlqr / dlqe / hinfsyn); it does NOT
# generate any figures (those are under its __main__ guard).
import make_figures as mf

OUT = os.path.join(os.path.dirname(__file__), "..", "software",
                   "quanser_updated", "orr_controllers.mat")

# ---------------------------------------------------------------------------
# Condense the MPC into a dense QP in z = [U (Np); slack (Np)] so it can be
# solved on the target by mpcActiveSetSolver (codegen-safe, MPC Toolbox).
# Prediction over k = 1..Np:   Xstack = Phi x0 + Gamma U,  Xstack = [X_1;..;X_Np]
# ---------------------------------------------------------------------------
Ad, Bd = mf.Ad0, mf.Bdc0          # nominal discrete model used for prediction
Np, Q, P, Ru = mf.Np, mf.Q, mf.P, mf.Ru
nx = 4

Phi = np.zeros((Np * nx, nx))
Gamma = np.zeros((Np * nx, Np))
Apow = np.eye(nx)
for k in range(Np):                # builds rows for X_{k+1}
    Apow = Ad @ Apow               # = Ad^(k+1)
    Phi[k * nx:(k + 1) * nx, :] = Apow
    for j in range(k + 1):         # X_{k+1} += Ad^(k-j) Bd U_j
        Gamma[k * nx:(k + 1) * nx, j:j + 1] = np.linalg.matrix_power(Ad, k - j) @ Bd

# stage weights over X_1..X_Np : Q on 1..Np-1, terminal P on Np
Qbar = np.zeros((Np * nx, Np * nx))
for k in range(Np - 1):
    Qbar[k * nx:(k + 1) * nx, k * nx:(k + 1) * nx] = Q
Qbar[(Np - 1) * nx:, (Np - 1) * nx:] = P

# setpoint stack:  xss = r * e_r  (e_r selects the hub angle / tip reference)
e_r = np.array([1.0, 0.0, 0.0, 0.0])
Er = np.tile(e_r, Np)                                    # (Np*nx,)

# cost in U:  Hqp = 2(Gamma' Qbar Gamma + Ru I);  f = M_f x0 + w_f r
Hqp = 2.0 * (Gamma.T @ Qbar @ Gamma + Ru * np.eye(Np))
M_f = 2.0 * Gamma.T @ Qbar @ Phi                         # (Np, nx)
w_f = -2.0 * Gamma.T @ Qbar @ Er                         # (Np,)

# deflection rows: theta_tip = state index 1 of each X_k
sel = np.zeros((Np, Np * nx))
for k in range(Np):
    sel[k, k * nx + 1] = 1.0
Gth = sel @ Gamma                                        # (Np, Np)  theta_tip = Gth U + Pth x0
Pth = sel @ Phi                                          # (Np, nx)

mpc = dict(
    Ad=Ad, Bd=Bd, Np=float(Np),
    Hqp=Hqp, M_f=M_f, w_f=w_f.reshape(-1, 1),
    Gth=Gth, Pth=Pth,
    umax=float(mf.UMAX), defl_lim=float(np.deg2rad(mf.DEFL_DEG)),
    rho=1e4,                                             # soft-constraint penalty
)

# ---------------------------------------------------------------------------
# LQG : Kalman predictor (Ad, Bd, C_POS, L) + static gain K, state setpoint.
# ---------------------------------------------------------------------------
lqg = dict(Ad=mf.Ad0, Bd=mf.Bdc0, C_POS=mf.C_POS, L=mf.L,
           K=mf.K, umax=float(mf.UMAX))

# ---------------------------------------------------------------------------
# H-infinity : discrete (Tustin) integral-augmented controller. Takes
# meas = [theta_hub, theta_tip, xi]; xi integrates the tracking error r - tip.
# ---------------------------------------------------------------------------
hinf = dict(A=mf.Hk, B=mf.HB, C=mf.HC, D=mf.HD,
            umax=float(mf.UMAX), gamma=float(mf.GAMMA))

# ---------------------------------------------------------------------------
# SINGLE-BLOCK realizations for Simulink (built by build_orr_models.m).
#
# Each linear controller is folded into ONE Discrete State-Space block driven
# by the 8-vector  v = [ x(1..4) ; xref(1..4) ]  taken straight off the model's
# existing Mux1 (the stage-1 state) and Stage-1-Setpoint (= [r;r;0;0]) signals.
# Only v1=theta_hub, v2=theta_tip and v5=r are used; the rig's filtered
# velocities (v3,v4) are deliberately ignored so the loop matches the design.
#   u = Css x_c + Dss v ,   x_c[k+1] = Ass x_c + Bss v
# ---------------------------------------------------------------------------
C_POS, C_TIP, Ts = mf.C_POS, mf.C_TIP, mf.Ts
e_r = np.array([1.0, 0.0, 0.0, 0.0])

# ---- LQG single block (controller state = the Kalman estimate, 4) ----
Kf = mf.K.reshape(1, -1)              # 1x4
Lg = mf.L                            # 4x2
Kr = float((Kf @ e_r).item())        # hub-angle feedforward gain
A_lqg = mf.Ad0 - mf.Bdc0 @ Kf - Lg @ C_POS
B_lqg = np.zeros((4, 8))
B_lqg[:, 0] = Lg[:, 0]; B_lqg[:, 1] = Lg[:, 1]
B_lqg[:, 4] = mf.Bdc0.ravel() * Kr
C_lqg = -Kf
D_lqg = np.zeros((1, 8)); D_lqg[0, 4] = Kr
lqg_ss = dict(A=A_lqg, B=B_lqg, C=C_lqg, D=D_lqg, umax=float(mf.UMAX))

# ---- H-infinity single block (state = [xc(6); xi(1)] = 7) ----
Hk, HB, HC, HD = mf.Hk, mf.HB, mf.HC, mf.HD
nh = Hk.shape[0]
A_h = np.zeros((nh + 1, nh + 1))
A_h[:nh, :nh] = Hk; A_h[:nh, nh] = HB[:, 2]      # xc <- xi
A_h[nh, nh] = 1.0                                # xi integrator
B_h = np.zeros((nh + 1, 8))
B_h[:nh, 0] = HB[:, 0]; B_h[:nh, 1] = HB[:, 1]   # xc <- yhub, ytip
B_h[nh, 0] = -Ts; B_h[nh, 1] = -Ts; B_h[nh, 4] = Ts   # xi <- (r - hub - tip)
C_h = np.zeros((1, nh + 1)); C_h[0, :nh] = HC.ravel(); C_h[0, nh] = HD[0, 2]
D_h = np.zeros((1, 8)); D_h[0, 0] = HD[0, 0]; D_h[0, 1] = HD[0, 1]
hinf_ss = dict(A=A_h, B=B_h, C=C_h, D=D_h, umax=float(mf.UMAX))

# ---- self-check: the single-block realization must reproduce make_figures ----
def _closed_loop(css):
    Ad_, Bd_ = mf.Ad0, mf.Bdc0
    x = np.zeros(4); c = np.zeros(css["A"].shape[0])
    s = np.array([mf.r, mf.r, 0.0, 0.0])
    y = np.empty(mf.Nsim)
    for k in range(mf.Nsim):
        v = np.concatenate([x, s])
        u = float(np.clip((css["C"] @ c + css["D"] @ v)[0], -mf.UMAX, mf.UMAX))
        y[k] = np.rad2deg(C_TIP @ x)
        c = css["A"] @ c + css["B"] @ v
        x = Ad_ @ x + Bd_.ravel() * u
    return y

y_lqg_ref = mf.sim_lqg(*mf.make_truth(), 4)[0]
y_hinf_ref = mf.sim_hinf(*mf.make_truth(), 4)[0]
e_lqg = np.max(np.abs(_closed_loop(lqg_ss) - y_lqg_ref))
e_hinf = np.max(np.abs(_closed_loop(hinf_ss) - y_hinf_ref))
print(f"[self-check] single-block vs notebook sim: "
      f"LQG max|Δtip| = {e_lqg:.2e}°,  H-inf = {e_hinf:.2e}°")
# LQG differs only while the current saturates (the single block updates its
# observer from the UNSATURATED command, whereas the notebook feeds back the
# clipped one). The gap is sub-millidegree -- negligible vs hardware effects.
# A gross bug (e.g. a sign error) would show degrees of error, so:
assert e_lqg < 1e-2 and e_hinf < 1e-6, "single-block realization mismatch!"

# ---------------------------------------------------------------------------
sio.savemat(OUT, dict(
    Ts_ctrl=float(mf.Ts),
    C_TIP=mf.C_TIP.reshape(1, -1),
    C_POS=mf.C_POS,
    lqg=lqg, hinf=hinf, mpc=mpc,
    lqg_ss=lqg_ss, hinf_ss=hinf_ss,
), do_compression=True)

print(f"[export] wrote {os.path.abspath(OUT)}")
print(f"         Ts_ctrl = {mf.Ts*1e3:.0f} ms,  H-inf order {mf.HINF_ORDER}, "
      f"gamma = {mf.GAMMA:.3f},  MPC Np = {Np}")
print("         LQG: K(1x4), L(4x2);  H-inf: A%s;  MPC: Hqp%s"
      % (mf.Hk.shape, Hqp.shape))
