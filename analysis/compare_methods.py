import marimo

__generated_with = "0.23.9"
app = marimo.App(width="medium")


@app.cell
def _():
    import marimo as mo
    import numpy as np
    import matplotlib.pyplot as plt
    import control
    import cvxpy as cp
    from scipy.linalg import expm

    return control, cp, expm, mo, np, plt


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    # Tip-tracking: method comparison (Stage 1)

    Track the **tip angle** `y = θ_hub + θ_tip` to a step reference. Controllers are
    **designed on the nominal plant**; perturb the *true* plant's `Ks` to test robustness.

    * **LQR-servo** (Ch 3/9) — infinite-horizon optimal full-state feedback; output saturation by clipping.
    * **MPC** (Ch 2/5) — finite-horizon QP; shares the LQR cost + **DARE terminal cost** (so unconstrained
      **MPC ≡ LQR**), and additionally enforces `±u_max` **and** a tip-deflection limit `|θ_tip| ≤ defl_max`.
    * **H∞** (Ch 11) — mixed-sensitivity (`S/KS/T`) dynamic output-feedback on the tip error;
      explicitly robust to the resonance-frequency uncertainty. Current applied with the same `±u_max` clip.
    """)
    return


@app.cell(hide_code=True)
def _(np):
    # ---- Stage-1 nominal parameters (config_2dslf.m) ----
    K_IN2M = 0.0254
    Me = 2.068427e11
    Xb1 = 3.0 * K_IN2M
    Tb1 = 0.050 * K_IN2M
    L1 = 0.202
    KS1_NOM = Me * Xb1 * Tb1 ** 3 / (4 * L1)
    B11 = 4.0
    Kg1 = 100
    Km1 = 0.119
    KTG1 = 0.75 * Km1 * Kg1
    Jm1 = 6.28e-6
    J11 = Kg1 ** 2 * Jm1 + 0.00073616
    M12 = 1.578
    J12 = 0.18028257 - M12 * 0.079 ** 2

    C_TIP = np.array([1.0, 1.0, 0.0, 0.0])   # tip absolute angle = hub + deflection
    Ts = 0.01
    Np = 40
    Nsim = 400

    def build_AB(Ks):
        A = np.array([
            [0.0, 0.0,        1.0,       0.0],
            [0.0, 0.0,        0.0,       1.0],
            [0.0, Ks / J11,  -B11 / J11, 0.0],
            [0.0, -(J11 + J12) / (J11 * J12) * Ks, B11 / J11, 0.0],
        ])
        B = np.array([[0.0], [0.0], [KTG1 / J11], [-KTG1 / J11]])
        return A, B

    return C_TIP, KS1_NOM, Np, Nsim, Ts, build_AB


@app.cell(hide_code=True)
def _(C_TIP, KS1_NOM, Ts, build_AB, control, np):
    # ---- H-infinity mixed-sensitivity controller (designed once, nominal plant) ----
    # Integrator nudged off the jw-axis (eps) so the H-inf rank conditions hold.
    A0, B0 = build_AB(KS1_NOM)
    Gdes = control.ss(A0 - 0.1 * np.eye(4), B0, C_TIP.reshape(1, 4), 0.0)
    s = control.tf("s")
    Aw = 1e-3
    wb, wbc, M3, w2g = 6.0, 30.0, 3.0, 0.1     # "moderate" design (gamma~1.06)
    W1 = (s / 2.0 + wb) / (s + wb * Aw)        # performance / tracking (on S)
    W2 = (s / 80 + 1) / (s / 4000 + 1) * w2g   # control effort (on KS)
    W3 = (s + wbc / M3) / (Aw * s + wbc)       # robustness / roll-off (on T)

    Khinf, _, info = control.mixsyn(Gdes, W1, W2, W3)
    gamma_hinf = float(np.ravel(info[0])[0])
    Kd = control.sample_system(Khinf, Ts, method="tustin")   # discretize the controller
    Adk = np.atleast_2d(np.asarray(Kd.A))
    Bdk = np.asarray(Kd.B).reshape(-1)
    Cdk = np.asarray(Kd.C).reshape(-1)
    Ddk = float(np.asarray(Kd.D).reshape(-1)[0])
    return Adk, Bdk, Cdk, Ddk, gamma_hinf


@app.cell(hide_code=True)
def _(mo):
    umax_slider = mo.ui.slider(0.25, 5.0, value=0.6, step=0.05,
                               label="u_max (current limit) [A]", show_value=True)
    ref_slider = mo.ui.slider(-30, 30, value=20, step=1,
                              label="tip reference [deg]", show_value=True)
    defl_slider = mo.ui.slider(0.5, 8.0, value=2.0, step=0.25,
                               label="MPC tip-deflection limit |θ_tip| [deg]", show_value=True)
    defl_switch = mo.ui.switch(value=True, label="enforce deflection limit (MPC)")
    kspert_slider = mo.ui.slider(0.3, 1.5, value=1.0, step=0.05,
                                 label="true-plant Ks multiplier (robustness)", show_value=True)
    mo.vstack([umax_slider, ref_slider, defl_slider, defl_switch, kspert_slider])
    return defl_slider, defl_switch, kspert_slider, ref_slider, umax_slider


@app.cell(hide_code=True)
def _(
    Adk,
    Bdk,
    C_TIP,
    Cdk,
    Ddk,
    KS1_NOM,
    Np,
    Nsim,
    Ts,
    build_AB,
    control,
    cp,
    defl_slider,
    defl_switch,
    expm,
    kspert_slider,
    np,
    ref_slider,
    umax_slider,
):
    umax = float(umax_slider.value)
    r = np.deg2rad(float(ref_slider.value))
    defl_lim = np.deg2rad(float(defl_slider.value)) if defl_switch.value else 1e3

    def discretize(Ks):
        A, B = build_AB(Ks)
        M = expm(np.block([[A, B], [np.zeros((1, 5))]]) * Ts)
        return M[:4, :4], M[:4, 4:5]

    Ad, Bdc = discretize(KS1_NOM)                                  # nominal (design)
    Bd = Bdc.ravel()
    Adp, Bdpc = discretize(KS1_NOM * float(kspert_slider.value))   # true plant
    Bdp = Bdpc.ravel()

    # ---- shared cost + LQR gain + DARE terminal cost ----
    Qy, Ru = 50.0, 0.5
    Q = Qy * np.outer(C_TIP, C_TIP) + 1e-3 * np.eye(4)
    R = np.array([[Ru]])
    K, P, _ = control.dlqr(Ad, Bdc, Q, R)
    K = np.asarray(K).ravel()
    x_ss = np.array([r, 0.0, 0.0, 0.0])

    def sim_lqr(Adt, Bdt):
        x = np.zeros(4); y = np.empty(Nsim); d = np.empty(Nsim); u = np.empty(Nsim)
        for k in range(Nsim):
            uk = float(np.clip(-K @ (x - x_ss), -umax, umax))
            y[k] = np.rad2deg(C_TIP @ x); d[k] = np.rad2deg(x[1]); u[k] = uk
            x = Adt @ x + Bdt * uk
        return y, d, u

    # ---- MPC: same cost + terminal cost; input box + soft deflection limit ----
    x0 = cp.Parameter(4)
    U = cp.Variable((1, Np)); X = cp.Variable((4, Np + 1)); S = cp.Variable(Np, nonneg=True)
    cost = 0; cons = [X[:, 0] == x0]
    for k in range(Np):
        cost += cp.quad_form(X[:, k] - x_ss, cp.psd_wrap(Q)) + Ru * cp.square(U[0, k]) + 1e4 * S[k]
        cons += [X[:, k + 1] == Ad @ X[:, k] + Bd * U[0, k],
                 cp.abs(U[0, k]) <= umax, cp.abs(X[1, k + 1]) <= defl_lim + S[k]]
    cost += cp.quad_form(X[:, Np] - x_ss, cp.psd_wrap(P))
    mpc = cp.Problem(cp.Minimize(cost), cons)

    def sim_mpc(Adt, Bdt):
        x = np.zeros(4); y = np.empty(Nsim); d = np.empty(Nsim); u = np.empty(Nsim)
        for k in range(Nsim):
            x0.value = x
            mpc.solve(solver=cp.CLARABEL, warm_start=True)
            uk = float(np.clip(U.value[0, 0], -umax, umax)) if U.value is not None else 0.0
            y[k] = np.rad2deg(C_TIP @ x); d[k] = np.rad2deg(x[1]); u[k] = uk
            x = Adt @ x + Bdt * uk
        return y, d, u

    # ---- H-infinity: dynamic controller on tip error e = r - y ----
    def sim_hinf(Adt, Bdt):
        x = np.zeros(4); xc = np.zeros(Adk.shape[0])
        y = np.empty(Nsim); d = np.empty(Nsim); u = np.empty(Nsim)
        for k in range(Nsim):
            yk = float(C_TIP @ x); e = r - yk
            uu = float(Cdk @ xc) + Ddk * e
            uk = float(np.clip(uu, -umax, umax))
            y[k] = np.rad2deg(yk); d[k] = np.rad2deg(x[1]); u[k] = uk
            xc = Adk @ xc + Bdk * e
            x = Adt @ x + Bdt * uk
        return y, d, u

    t = np.arange(Nsim) * Ts
    y_lqr, d_lqr, u_lqr = sim_lqr(Adp, Bdp)
    y_mpc, d_mpc, u_mpc = sim_mpc(Adp, Bdp)
    y_hinf, d_hinf, u_hinf = sim_hinf(Adp, Bdp)
    return (
        d_hinf,
        d_lqr,
        d_mpc,
        defl_lim,
        t,
        u_hinf,
        u_lqr,
        u_mpc,
        umax,
        y_hinf,
        y_lqr,
        y_mpc,
    )


@app.cell(hide_code=True)
def _(
    d_hinf,
    d_lqr,
    d_mpc,
    defl_lim,
    defl_switch,
    gamma_hinf,
    mo,
    np,
    plt,
    ref_slider,
    t,
    u_hinf,
    u_lqr,
    u_mpc,
    umax,
    y_hinf,
    y_lqr,
    y_mpc,
):
    rdeg = float(ref_slider.value)
    defl_deg = np.rad2deg(defl_lim)
    lim_y = 3 * abs(rdeg) if rdeg != 0 else 30.0   # clip diverging (unstable) traces for display

    def metrics(y, d, u):
        if not np.all(np.isfinite(y)) or np.abs(y).max() > 5 * abs(rdeg) + 5:
            return None
        s = np.sign(rdeg) if rdeg != 0 else 1.0
        hit = (s * y) >= abs(0.9 * rdeg)
        rise = t[np.argmax(hit)] if hit.any() else np.nan
        ov = ((s * y).max() - abs(rdeg)) / abs(rdeg) * 100 if rdeg != 0 else 0.0
        return rise, ov, np.abs(u).max(), np.abs(d).max()

    series = [("LQR-servo", y_lqr, d_lqr, u_lqr, "C0", "-"),
              ("MPC",       y_mpc, d_mpc, u_mpc, "C1", "--"),
              ("H∞",        y_hinf, d_hinf, u_hinf, "C2", "-.")]

    fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(9, 8.5), sharex=True)
    for nm, y, d, u, c, ls in series:
        ax1.plot(t, np.clip(y, -lim_y, lim_y), lw=1.5, ls=ls, color=c, label=nm)
        ax2.plot(t, np.clip(d, -lim_y, lim_y), lw=1.3, ls=ls, color=c, label=nm)
        ax3.plot(t, u, lw=1.1, ls=ls, color=c, label=nm)
    ax1.axhline(rdeg, color="r", ls=":", lw=1, label="reference")
    ax1.set_ylabel("tip angle [°]"); ax1.legend(loc="lower right", ncol=2)
    ax1.set_title(f"Tip tracking  (ref={rdeg:+g}°,  u_max={umax:g} A,  H∞ γ={gamma_hinf:.2f})")
    if defl_switch.value:
        ax2.axhline(defl_deg, color="k", ls=":", lw=1, label="MPC limit"); ax2.axhline(-defl_deg, color="k", ls=":", lw=1)
    ax2.set_ylabel("tip deflection θ_tip [°]"); ax2.legend(loc="upper right", ncol=2)
    ax3.axhline(umax, color="k", ls=":", lw=1); ax3.axhline(-umax, color="k", ls=":", lw=1)
    ax3.set_ylabel("current u [A]"); ax3.set_xlabel("time [s]"); ax3.legend(loc="upper right", ncol=3)
    fig.tight_layout()

    rows = ""
    for nm, y, d, u, _c, _ls in series:
        m = metrics(y, d, u)
        rows += (f"| {nm} | UNSTABLE | – | – | – |\n" if m is None
                 else f"| {nm} | {m[0]:.2f} | {m[1]:.1f} | {m[2]:.2f} | {m[3]:.2f} |\n")
    table = ("| method | rise [s] | overshoot [%] | peak \\|u\\| [A] | max \\|θ_tip\\| [°] |\n"
             "|---|---|---|---|---|\n" + rows)
    mo.vstack([mo.md(table), fig])
    return


if __name__ == "__main__":
    app.run()
