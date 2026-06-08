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
    # Tip-tracking: OUTPUT-feedback comparison (Stage 1)

    Fair comparison: **all three controllers use only the two measured positions**
    `y = [θ_hub, θ_tip]` (encoder + strain gauge, as on the real rig) and estimate the
    velocities. Perturb the true plant (`Ks`, an **unmodelled 2nd mode**, **input delay**)
    to test robustness — see the robustness demo near the bottom for where H∞ shines.

    * **LQG** (Ch 9) — LQR gain on a Kalman estimate from the two positions.
    * **output-MPC** (Ch 2/5) — MPC on the Kalman estimate; the tip-deflection limit
      `|θ̂_tip| ≤ defl_max` is imposed on the *estimate* (θ_tip is measured, so it's accurate).
    * **H∞** (Ch 11/12) — 2-measurement output-feedback (`hinfsyn`) with an explicit
      integral-of-error state for offset-free tracking (see the H∞ cell for why).

    Current applied with the same `±u_max` clip (no anti-windup).
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

    C_TIP = np.array([1.0, 1.0, 0.0, 0.0])           # tip absolute angle
    C_POS = np.array([[1.0, 0, 0, 0], [0, 1.0, 0, 0]])  # measured: hub, tip deflection
    Ts = 0.01
    Np = 40
    Nsim = 500

    def build_AB(Ks):
        A = np.array([
            [0.0, 0.0,        1.0,       0.0],
            [0.0, 0.0,        0.0,       1.0],
            [0.0, Ks / J11,  -B11 / J11, 0.0],
            [0.0, -(J11 + J12) / (J11 * J12) * Ks, B11 / J11, 0.0],
        ])
        B = np.array([[0.0], [0.0], [KTG1 / J11], [-KTG1 / J11]])
        return A, B

    return C_POS, C_TIP, KS1_NOM, Np, Nsim, Ts, build_AB


@app.cell(hide_code=True)
def _(C_POS, C_TIP, KS1_NOM, Ts, build_AB, control, expm, np):
    # ---- LQR gain + DARE terminal cost + Kalman predictor gain (designed once) ----
    A0, B0 = build_AB(KS1_NOM)
    M0 = expm(np.block([[A0, B0], [np.zeros((1, 5))]]) * Ts)
    Ad0, Bdc0 = M0[:4, :4], M0[:4, 4:5]
    Qy, Ru = 50.0, 0.5
    Q = Qy * np.outer(C_TIP, C_TIP) + 1e-3 * np.eye(4)
    R = np.array([[Ru]])
    K, P, _ = control.dlqr(Ad0, Bdc0, Q, R)
    K = np.asarray(K)

    # Kalman (predictor) from the two positions
    qn, rn = 10.0, 1e-6
    Qn = Bdc0 @ Bdc0.T * qn + 1e-9 * np.eye(4)
    Rn = rn * np.eye(2)
    L, _, _ = control.dlqe(Ad0, np.eye(4), C_POS, Qn, Rn)
    L = np.asarray(L)
    return B0, K, L, P, Q, Ru


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### H∞ design note — why the weights are *fixed*, not live-tuned

    The plant has a rigid-body **integrator on the jω-axis**, which breaks `hinfsyn`'s
    rank conditions, so it must be regularized off-axis (`A − eps·I`). But that same
    regularization *hides the integrator from the synthesis*: the resulting controller
    satisfies the spec with feed-forward and **zero DC feedback gain**, so it tracks with
    a large steady-state offset. We restore integral action **explicitly** with an
    integral-of-tracking-error state `ẋᵢ = r − y` fed to the controller — giving exact
    offset-free tracking that's even robust to `Ks` mismatch.

    The price: that extra integrator adds a *second* jω-axis pole, making the synthesis
    numerically delicate — across the weight grid ~¼ of combinations collapse to a
    degenerate controller. So rather than expose a fragile live-tuning slider, the design
    is **frozen at a validated operating point** (`eps=1e-3`, `Wᵢ=1.0`, `W₂=0.1`).
    LQG/MPC need none of this: they inject the reference as a state setpoint and exploit
    the plant's own integrator directly.

    The `W₂` corner is placed **low (`wc≈8 rad/s`)** so the loop deliberately rolls off
    above the modelled flexible mode — trading a little nominal speed for a robustness
    margin against *unmodelled* high-frequency dynamics. The robustness demo at the
    bottom shows what that margin buys (and what LQG/MPC lack).
    """)
    return


@app.cell(hide_code=True)
def _(B0, C_POS, C_TIP, KS1_NOM, Ts, build_AB, control, np):
    # ---- 2-measurement output-feedback H-infinity (integral-augmented, fixed) ----
    # See the design-note cell above for the rationale. Generalized-plant states are
    #   [xp(4), xi(1), xw2(n2)]  with  xi = integral of the tracking error (ẋᵢ = r − y).
    # Exogenous inputs [r, nA, nB, nC]; control u (nin=5, u last).
    # Regulated z = [Wᵢ·xi, W₂·u];  measurements = [yhub, ytip, xi] (nmeas=3, ncon=1).
    eps = 1e-3      # rigid-body integrator regularized off the jω-axis (for hinfsyn)
    Wi = 1.0        # integral-error penalty  (tracking aggressiveness)
    w2g = 0.1       # control-effort weight   (on KS)
    wc = 8.0        # W2 corner [rad/s]: ROLL the loop off above here, well below any
                    # unmodelled high-frequency dynamics -> robustness (see demo below)
    nz = 1e-2       # measurement-noise floor (gives D21 full row rank)
    s = control.tf("s")

    Ah, _Bh = build_AB(KS1_NOM)
    Ae = Ah - eps * np.eye(4)
    # W2 rises from w2g (DC) and keeps rising past wc, so the synthesis penalizes
    # high-frequency control effort -> the loop gain rolls off before the unmodelled
    # 2nd flexible mode (no spillover). This is exactly what LQG/MPC cannot guarantee.
    W2 = control.tf2ss((s / wc + 1) / (s / 3000 + 1) * w2g)
    Aw2, Bw2, Cw2, Dw2 = [np.atleast_2d(x) for x in (W2.A, W2.B, W2.C, W2.D)]
    n2 = Aw2.shape[0]
    n = 4 + 1 + n2

    Ap = np.zeros((n, n)); Ap[:4, :4] = Ae
    Ap[4, :4] = -C_TIP                       # ẋᵢ = −y_tip  (+ r via Bp)
    Ap[5:, 5:] = Aw2
    Bp = np.zeros((n, 5))
    Bp[4, 0] = 1.0                           # r  -> xi
    Bp[:4, 4:5] = B0                         # u  -> plant
    Bp[5:, 4:5] = Bw2                        # u  -> W2
    Cp = np.zeros((5, n))
    Cp[0, 4] = Wi                            # z1 = Wᵢ·xi
    Cp[1, 5:] = Cw2.ravel()                  # z2 = W₂·u
    Cp[2, :4] = C_POS[0]; Cp[3, :4] = C_POS[1]; Cp[4, 4] = 1.0   # meas: yhub, ytip, xi
    Dp = np.zeros((5, 5))
    Dp[1, 4] = Dw2[0, 0]
    Dp[2, 1] = nz; Dp[3, 2] = nz; Dp[4, 3] = nz                  # noise on the 3 meas

    out = control.hinfsyn(control.ss(Ap, Bp, Cp, Dp), 3, 1)
    gamma_hinf = float(np.ravel(np.asarray(out[2], dtype=float))[0])
    Kc_hinf = out[0]                                             # continuous controller
    Kd = control.sample_system(Kc_hinf, Ts, method="tustin")     # for the discrete sim
    HB = np.atleast_2d(np.asarray(Kd.B)); HC = np.atleast_2d(np.asarray(Kd.C))
    HD = np.atleast_2d(np.asarray(Kd.D)); Hk = np.atleast_2d(np.asarray(Kd.A))
    hinf_status = (f"**H∞** — γ = {gamma_hinf:.2f}, controller order "
                   f"{np.asarray(Kc_hinf.A).shape[0]} (integral-augmented, fixed weights)")
    return HB, HC, HD, Hk, Kc_hinf, gamma_hinf, hinf_status


@app.cell(hide_code=True)
def _(
    C_POS,
    C_TIP,
    KS1_NOM,
    Kc_hinf,
    build_AB,
    control,
    gamma_hinf,
    mo,
    np,
    plt,
):
    # ---- Sensitivity S and complementary sensitivity T of the H∞ loop ----
    # Build the continuous closed loop (nominal plant + controller + integral state) and
    # read off T = (r -> tip angle).  At the controlled output, S = 1 - T.
    A_st, B_st = build_AB(KS1_NOM); B_st = B_st.ravel()
    Ac = np.atleast_2d(np.asarray(Kc_hinf.A)); Bc = np.atleast_2d(np.asarray(Kc_hinf.B))
    Cc = np.atleast_2d(np.asarray(Kc_hinf.C)); Dc = np.atleast_2d(np.asarray(Kc_hinf.D))
    nc = Ac.shape[0]; Nst = 4 + 1 + nc
    # state z = [xp(4), xi(1), xc(nc)] ; meas = [yhub, ytip, xi] = Cmst z ; u = Cc·xc + Dc·meas
    Cmst = np.zeros((3, Nst)); Cmst[0, :4] = C_POS[0]; Cmst[1, :4] = C_POS[1]; Cmst[2, 4] = 1.0
    Acl = np.zeros((Nst, Nst)); Bcl = np.zeros((Nst, 1))
    Du = Dc @ Cmst
    Acl[:4, :4] = A_st
    Acl[:4, :] += np.outer(B_st, Du.ravel())
    Acl[:4, 5:5 + nc] += B_st.reshape(-1, 1) @ Cc
    Acl[4, :4] = -C_TIP; Bcl[4, 0] = 1.0           # ẋᵢ = r − y_tip
    Acl[5:, :] = Bc @ Cmst; Acl[5:, 5:5 + nc] += Ac
    Ccl = np.zeros((1, Nst)); Ccl[0, :4] = C_TIP
    sysT = control.ss(Acl, Bcl, Ccl, 0.0)

    w = np.logspace(-2, 3, 500)
    db = lambda x: 20 * np.log10(np.maximum(np.abs(x), 1e-12))
    T = np.array([sysT(1j * wi) for wi in w]).reshape(-1)
    S = 1.0 - T
    w_flex = 16.9   # nominal flexible-mode frequency [rad/s]

    figST, (axS, axT) = plt.subplots(2, 1, figsize=(9, 7), sharex=True)
    axS.semilogx(w, db(S), lw=1.8, color="C0", label="|S| sensitivity")
    axS.axvline(w_flex, color="r", ls=":", lw=1, label="flex mode")
    axS.axhline(0, color="0.7", lw=0.8)
    axS.set_ylabel("|S| [dB]"); axS.legend(loc="lower right")
    axS.set_title(f"H∞ loop sensitivities  (γ = {gamma_hinf:.2f})")

    axT.semilogx(w, db(T), lw=1.8, color="C1", label="|T| (complementary)")
    axT.axvline(w_flex, color="r", ls=":", lw=1)
    axT.axhline(0, color="0.7", lw=0.8)
    axT.set_ylabel("|T| [dB]"); axT.set_xlabel("ω [rad/s]"); axT.legend(loc="lower left")
    figST.tight_layout()

    mo.vstack([
        mo.md(f"**S(DC) = {abs(S[0]):.4f}** (steady-state tracking error)  ·  "
              f"‖S‖∞ = {db(S).max():.1f} dB  ·  ‖T‖∞ = {db(T).max():.1f} dB "
              f"(lower peaks ⇒ bigger stability margins)"),
        figST,
    ])
    return


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
def _(mo):
    # ---- Robustness demo: perturbations the controllers were NOT designed for ----
    mode_switch = mo.ui.switch(value=False, label="add UNMODELLED 2nd flexible mode (spillover test)")
    f2_slider = mo.ui.slider(2.0, 6.0, value=3.0, step=0.25,
                             label="    2nd-mode frequency  [× modelled mode]", show_value=True)
    cout_slider = mo.ui.slider(0.0, 2.0, value=1.0, step=0.1,
                               label="    2nd-mode coupling into the tip output", show_value=True)
    delay_slider = mo.ui.slider(0.0, 100.0, value=0.0, step=5.0,
                                label="input delay  [ms]  (actuator / loop lag)", show_value=True)
    mo.vstack([
        mo.md("**Robustness perturbations** — flip these on to see who survives "
              "*unstructured* uncertainty (spillover / phase lag), H∞'s home ground:"),
        mode_switch, f2_slider, cout_slider, delay_slider,
    ])
    return cout_slider, delay_slider, f2_slider, mode_switch


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    #### Where H∞ earns its keep — two *unstructured* uncertainties

    On the nominal, well-modelled plant the three methods are near-identical — that is
    LQR/MPC's home turf, and H∞'s robustness margin is invisible. Its advantage only
    shows once the *truth plant differs from the design model* in ways no quadratic cost
    accounts for:

    * **Scenario A — unmodelled 2nd flexible mode (spillover).** A real beam has more
      bending modes than the 1-mode design model. Switch it on: the nominal **LQG/MPC
      push loop gain into the unmodelled mode and ring/destabilise** (control spillover),
      while the H∞ loop — deliberately rolled off above the modelled mode — **stays
      clean**. Only an explicit high-frequency roll-off *guarantees* this, and quadratic
      cost gives none.
    * **Scenario B′ — input delay (phase lag).** A few tens of ms of actuator/loop delay
      eats phase margin. The margin-blind **LQG loses stability around ~50 ms** (Doyle:
      *“LQG has no guaranteed margins”*), while H∞, which bounds the sensitivity peaks,
      **tolerates far more**.

    *Fairness note:* both controllers are tuned to comparable nominal speed first, so this
    is robustness bought by design, not by detuning. The price H∞ pays is a slightly
    slower nominal response (the roll-off) and a higher-order controller.
    """)
    return


@app.cell(hide_code=True)
def _(
    C_POS,
    HB,
    HC,
    HD,
    Hk,
    K,
    KS1_NOM,
    L,
    Np,
    Nsim,
    P,
    Q,
    Ru,
    Ts,
    build_AB,
    cout_slider,
    cp,
    defl_slider,
    defl_switch,
    delay_slider,
    expm,
    f2_slider,
    kspert_slider,
    mode_switch,
    np,
    ref_slider,
    umax_slider,
):
    umax = float(umax_slider.value)
    r = np.deg2rad(float(ref_slider.value))
    defl_lim = np.deg2rad(float(defl_slider.value)) if defl_switch.value else 1e3

    def discretize(Ks):
        A, B = build_AB(Ks)
        Mx = expm(np.block([[A, B], [np.zeros((1, 5))]]) * Ts)
        return Mx[:4, :4], Mx[:4, 4:5]

    Ad, Bdc = discretize(KS1_NOM)                                  # nominal (design/observer)
    Bd = Bdc.ravel()
    Kf = K.ravel()
    x_ss = np.array([r, 0.0, 0.0, 0.0])

    # ---- TRUTH plant: perturbed Ks, optional UNMODELLED 2nd mode, optional input delay ----
    # The controllers/observers only ever use the nominal 4-state model (Ad, Bd, C_POS).
    W1_MODE = float(np.max(np.abs(np.linalg.eigvals(build_AB(KS1_NOM)[0]).imag)))  # ~16.9 rad/s
    GIN = float(build_AB(KS1_NOM)[1][2, 0])      # modal input gain (= KTG1/J11)

    def make_truth(Ks, mode_on, f2, z2d, cout, ndelay):
        A, B = build_AB(Ks)
        if mode_on:                              # append a residual lightly-damped mode
            w2 = f2 * W1_MODE
            A2 = np.array([[0.0, 1.0], [-w2 ** 2, -2 * z2d * w2]])
            Aa = np.zeros((6, 6)); Aa[:4, :4] = A; Aa[4:, 4:] = A2
            Ba = np.vstack([B, np.array([[0.0], [GIN]])])
            cy = np.array([1.0, 1.0, 0, 0, cout, 0])               # tip angle (controlled)
            cm = np.array([[1.0, 0, 0, 0, 0, 0], [0, 1.0, 0, 0, cout, 0]])  # [yhub, ytip]
        else:
            Aa, Ba = A, B
            cy = np.array([1.0, 1.0, 0, 0])
            cm = np.array([[1.0, 0, 0, 0], [0, 1.0, 0, 0]])
        nx = Aa.shape[0]
        Mx = expm(np.block([[Aa, Ba], [np.zeros((1, nx + 1))]]) * Ts)
        Adt, Bdt = Mx[:nx, :nx], Mx[:nx, nx:nx + 1]
        if ndelay > 0:                           # discrete input shift-register (delay)
            N = nx + ndelay
            Af = np.zeros((N, N)); Af[:nx, :nx] = Adt; Af[:nx, nx] = Bdt.ravel()
            for i in range(ndelay - 1):
                Af[nx + i, nx + i + 1] = 1.0
            Bf = np.zeros((N, 1)); Bf[-1, 0] = 1.0
            cy = np.concatenate([cy, np.zeros(ndelay)])
            cm = np.hstack([cm, np.zeros((2, ndelay))])
            return Af, Bf, cy, cm
        return Adt, Bdt, cy, cm

    ndelay = int(round(float(delay_slider.value) / 1000.0 / Ts))
    At, Btc, Cy, Cm = make_truth(KS1_NOM * float(kspert_slider.value),
                                 mode_switch.value, float(f2_slider.value),
                                 0.02, float(cout_slider.value), ndelay)
    Bt = Btc.ravel()
    nt = At.shape[0]

    def observe(xh, u, ymeas):
        return Ad @ xh + Bd * u + L @ (ymeas - C_POS @ xh)

    def sim_lqg():
        x = np.zeros(nt); xh = np.zeros(4)
        y = np.empty(Nsim); d = np.empty(Nsim); u = np.empty(Nsim)
        for k in range(Nsim):
            ym = Cm @ x
            uk = float(np.clip(-Kf @ (xh - x_ss), -umax, umax))
            y[k] = np.rad2deg(Cy @ x); d[k] = np.rad2deg(ym[1]); u[k] = uk
            xh = observe(xh, uk, ym); x = At @ x + Bt * uk
        return y, d, u

    # MPC problem (predicts from the estimate; deflection limit on predicted estimate)
    x0 = cp.Parameter(4)
    U = cp.Variable((1, Np)); X = cp.Variable((4, Np + 1)); Sl = cp.Variable(Np, nonneg=True)
    cost = 0; cons = [X[:, 0] == x0]
    for k in range(Np):
        cost += cp.quad_form(X[:, k] - x_ss, cp.psd_wrap(Q)) + Ru * cp.square(U[0, k]) + 1e4 * Sl[k]
        cons += [X[:, k + 1] == Ad @ X[:, k] + Bd * U[0, k],
                 cp.abs(U[0, k]) <= umax, cp.abs(X[1, k + 1]) <= defl_lim + Sl[k]]
    cost += cp.quad_form(X[:, Np] - x_ss, cp.psd_wrap(P))
    mpc = cp.Problem(cp.Minimize(cost), cons)

    def sim_mpc():
        x = np.zeros(nt); xh = np.zeros(4)
        y = np.empty(Nsim); d = np.empty(Nsim); u = np.empty(Nsim)
        for k in range(Nsim):
            ym = Cm @ x
            x0.value = xh
            mpc.solve(solver=cp.CLARABEL, warm_start=True)
            uk = float(np.clip(U.value[0, 0], -umax, umax)) if U.value is not None else 0.0
            y[k] = np.rad2deg(Cy @ x); d[k] = np.rad2deg(ym[1]); u[k] = uk
            xh = observe(xh, uk, ym); x = At @ x + Bt * uk
        return y, d, u

    def sim_hinf():
        x = np.zeros(nt); xi = 0.0; xc = np.zeros(Hk.shape[0])
        y = np.empty(Nsim); d = np.empty(Nsim); u = np.empty(Nsim)
        for k in range(Nsim):
            ym = Cm @ x
            meas = np.array([ym[0], ym[1], xi])        # [yhub, ytip, ∫(r−y)]
            uu = (HC @ xc + HD @ meas).reshape(-1)[0]
            uk = float(np.clip(uu, -umax, umax))
            yk = float(Cy @ x)
            y[k] = np.rad2deg(yk); d[k] = np.rad2deg(ym[1]); u[k] = uk
            xc = Hk @ xc + HB @ meas.reshape(-1)
            xi = xi + Ts * (r - yk)                     # integral of tracking error
            x = At @ x + Bt * uk
        return y, d, u

    t = np.arange(Nsim) * Ts
    y_lqg, d_lqg, u_lqg = sim_lqg()
    y_mpc, d_mpc, u_mpc = sim_mpc()
    y_hinf, d_hinf, u_hinf = sim_hinf()
    return (
        d_hinf,
        d_lqg,
        d_mpc,
        defl_lim,
        t,
        u_hinf,
        u_lqg,
        u_mpc,
        umax,
        y_hinf,
        y_lqg,
        y_mpc,
    )


@app.cell(hide_code=True)
def _(
    d_hinf,
    d_lqg,
    d_mpc,
    defl_lim,
    defl_switch,
    gamma_hinf,
    hinf_status,
    mo,
    np,
    plt,
    ref_slider,
    t,
    u_hinf,
    u_lqg,
    u_mpc,
    umax,
    y_hinf,
    y_lqg,
    y_mpc,
):
    rdeg = float(ref_slider.value)
    defl_deg = np.rad2deg(defl_lim)
    lim_y = 3 * abs(rdeg) if rdeg != 0 else 30.0

    def metrics(y, d, u):
        if not np.all(np.isfinite(y)) or np.abs(y).max() > 5 * abs(rdeg) + 5:
            return None
        sgn = np.sign(rdeg) if rdeg != 0 else 1.0
        hit = (sgn * y) >= abs(0.9 * rdeg)
        rise = t[np.argmax(hit)] if hit.any() else np.nan
        ov = ((sgn * y).max() - abs(rdeg)) / abs(rdeg) * 100 if rdeg != 0 else 0.0
        return rise, ov, np.abs(u).max(), np.abs(d).max()

    series = [("LQG",        y_lqg, d_lqg, u_lqg, "C0", "-"),
              ("output-MPC", y_mpc, d_mpc, u_mpc, "C1", "--"),
              ("H∞",         y_hinf, d_hinf, u_hinf, "C2", "-.")]

    fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(9, 8.5), sharex=True)
    for nm, y, d, u, c, ls in series:
        ax1.plot(t, np.clip(y, -lim_y, lim_y), lw=1.5, ls=ls, color=c, label=nm)
        ax2.plot(t, np.clip(d, -lim_y, lim_y), lw=1.3, ls=ls, color=c, label=nm)
        ax3.plot(t, u, lw=1.1, ls=ls, color=c, label=nm)
    ax1.axhline(rdeg, color="r", ls=":", lw=1, label="reference")
    ax1.set_ylabel("tip angle [°]"); ax1.legend(loc="lower right", ncol=2)
    ax1.set_title(f"Output feedback  (ref={rdeg:+g}°, u_max={umax:g} A, H∞ γ={gamma_hinf:.2f})")
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
    mo.vstack([mo.md(hinf_status), mo.md(table), fig])
    return


if __name__ == "__main__":
    app.run()
