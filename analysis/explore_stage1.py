import marimo

__generated_with = "0.23.9"
app = marimo.App(width="medium")


@app.cell
def _():
    import marimo as mo
    import numpy as np
    import matplotlib.pyplot as plt
    import scipy.io as sio
    import control
    from pathlib import Path

    DATA_DIR = Path(__file__).resolve().parent.parent / "software" / "quanser_updated" / "data"
    return DATA_DIR, control, mo, np, plt, sio


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    # Stage-1 grey-box exploration

    Overlay measured LQR step responses against the **physics model** from
    `config_2dslf.m` / `eqn_2DSFL_Stage1.m`. The controller gain is held fixed
    at the deployed nominal value; the **plant** parameters are tunable so you
    can fit the model to the measured flexible-mode ringing.

    The control command is **saturated at `±u_max`** (motor-current limit) and the
    loop runs in discrete time at 500 Hz, matching the deployed controller — so the
    rate-limited rise of large steps is reproduced.

    State: `x = [θ₁₁ (hub), θ₁₂ (tip), θ̇₁₁, θ̇₁₂]` (rad, rad/s).
    """)
    return


@app.cell(hide_code=True)
def _(np):
    # ---- Nominal Stage-1 parameters (from config_2dslf.m) ----
    K_IN2M = 0.0254
    Me = 2.068427e11          # Young's modulus (Pa)
    Xb1 = 3.0 * K_IN2M        # beam width (m)
    Tb1 = 0.050 * K_IN2M      # beam thickness (m)
    L1 = 0.202                # beam length (m)
    KS1_NOM = Me * Xb1 * Tb1 ** 3 / (4 * L1)   # torsional stiffness

    B11_NOM = 4.0             # hub damping
    B12 = 0.0                 # tip damping (neglected)

    Kg1 = 100                 # gear ratio
    Km1 = 0.119               # back-EMF
    Kt1 = Km1                 # torque constant
    KTG1 = 0.75 * Kt1 * Kg1   # load-shaft torque per amp

    Jm1 = 6.28e-6
    Jeqm1 = Kg1 ** 2 * Jm1
    J1fix = 0.00073616
    J11_NOM = Jeqm1 + J1fix
    M12 = 1.578
    J12_cad = 0.18028257
    J12_NOM = J12_cad - M12 * 0.079 ** 2

    def build_AB(Ks, B11, J11, J12):
        """Stage-1 A, B from eqn_2DSFL_Stage1.m (B12 = 0)."""
        A = np.array([
            [0.0, 0.0,            1.0,        0.0],
            [0.0, 0.0,            0.0,        1.0],
            [0.0, Ks / J11,      -B11 / J11,  0.0],
            [0.0, -(J11 + J12) / (J11 * J12) * Ks,  B11 / J11, 0.0],
        ])
        B = np.array([[0.0], [0.0], [KTG1 / J11], [-KTG1 / J11]])
        return A, B

    return B11_NOM, J11_NOM, J12_NOM, KS1_NOM, build_AB


@app.cell
def _(B11_NOM, J11_NOM, J12_NOM, KS1_NOM, build_AB, control, np):
    # ---- Fixed deployed LQR gain (from nominal plant + setup_2dsfl.m weights) ----
    A_nom, B_nom = build_AB(KS1_NOM, B11_NOM, J11_NOM, J12_NOM)
    Q1 = np.diag([2500.0, 1.0, 1.0, 100.0])
    R1 = np.array([[10.0]])
    K_LQR, _, _ = control.lqr(A_nom, B_nom, Q1, R1)   # 1x4, held fixed below
    K_LQR = np.asarray(K_LQR)
    return (K_LQR,)


@app.cell
def _(DATA_DIR, np, sio):
    def load_segments():
        segs = {}
        for f in sorted(DATA_DIR.glob("lqr_step_*.mat")):
            m = sio.loadmat(f)
            segs[f.stem] = dict(
                name=f.stem,
                t=np.ravel(m["time"]),
                X1_meas=m["X1_meas"],            # N x 4 (rad, rad/s)
                ref_deg=float(np.squeeze(m["ref_deg"])),
            )
        return segs

    SEGMENTS = load_segments()
    return (SEGMENTS,)


@app.cell(hide_code=True)
def _(B11_NOM, J11_NOM, J12_NOM, KS1_NOM, SEGMENTS, mo):
    seg_select = mo.ui.dropdown(
        options=list(SEGMENTS.keys()),
        value="lqr_step_20deg_run01",
        label="segment",
    )
    Ks_slider = mo.ui.slider(10.0, 80.0, value=round(KS1_NOM, 2), step=0.25,
                             label="Ks  (torsional stiffness)", show_value=True)
    B11_slider = mo.ui.slider(0.0, 15.0, value=B11_NOM, step=0.1,
                              label="B11 (hub damping)", show_value=True)
    J11_slider = mo.ui.slider(0.02, 0.20, value=round(J11_NOM, 4), step=0.0005,
                              label="J11 (hub inertia)", show_value=True)
    J12_slider = mo.ui.slider(0.05, 0.30, value=round(J12_NOM, 4), step=0.0005,
                              label="J12 (link inertia)", show_value=True)
    umax_slider = mo.ui.slider(0.25, 20.0, value=2.0, step=0.25,
                               label="u_max (motor current limit) [A]", show_value=True)
    mo.vstack([seg_select, Ks_slider, B11_slider, J11_slider, J12_slider, umax_slider])
    return (
        B11_slider,
        J11_slider,
        J12_slider,
        Ks_slider,
        seg_select,
        umax_slider,
    )


@app.cell(hide_code=True)
def _(
    B11_slider,
    J11_slider,
    J12_slider,
    K_LQR,
    Ks_slider,
    SEGMENTS,
    build_AB,
    np,
    seg_select,
    umax_slider,
):
    from scipy.linalg import expm

    seg = SEGMENTS[seg_select.value]
    A, B = build_AB(Ks_slider.value, B11_slider.value, J11_slider.value, J12_slider.value)

    t = seg["t"]
    dt = float(t[1] - t[0])
    r_rad = np.deg2rad(seg["ref_deg"])
    umax = umax_slider.value

    # Exact zero-order-hold discretization of the open-loop plant.
    # A is singular (integrator row), so use the augmented-matrix exponential.
    Maug = expm(np.block([[A, B], [np.zeros((1, 5))]]) * dt)
    Ad = Maug[:4, :4]
    Bd = Maug[:4, 4:5].ravel()

    # Discrete closed loop at 500 Hz (matches the deployed controller), with the
    # FIXED deployed gain and a SATURATED current command:
    #   u[k] = clip(K[0]*r - K @ x[k], -umax, +umax)
    N = len(t)
    Xsim = np.empty((N, 4))
    Ucmd = np.empty(N)   # commanded (pre-saturation)
    Usat = np.empty(N)   # applied (post-saturation)
    x = seg["X1_meas"][0, :].astype(float).copy()
    Kv = K_LQR.ravel()          # 1-D gain so (Kv @ x) is a scalar
    k0 = float(Kv[0])
    for k in range(N):
        Xsim[k] = x
        uc = k0 * r_rad - float(Kv @ x)
        us = float(np.clip(uc, -umax, umax))
        Ucmd[k] = uc
        Usat[k] = us
        x = Ad @ x + Bd * us

    # Flexible-mode natural frequency from current open-loop A
    eigs = np.linalg.eigvals(A)
    flex = eigs[np.argmax(np.abs(eigs.imag))]
    f_n = abs(flex) / (2 * np.pi)
    zeta = -flex.real / abs(flex) if abs(flex) > 0 else float("nan")
    return Ucmd, Usat, Xsim, f_n, seg, t, umax, zeta


@app.cell(hide_code=True)
def _(Ucmd, Usat, Xsim, f_n, mo, np, plt, seg, t, umax, zeta):
    th11_m = np.rad2deg(seg["X1_meas"][:, 0])
    th12_m = np.rad2deg(seg["X1_meas"][:, 1])
    th11_s = np.rad2deg(Xsim[:, 0])
    th12_s = np.rad2deg(Xsim[:, 1])

    fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(9, 8), sharex=True)
    ax1.plot(t, th11_m, lw=1.5, label="θ₁₁ measured")
    ax1.plot(t, th11_s, lw=1.5, ls="--", label="θ₁₁ model")
    ax1.axhline(seg["ref_deg"], color="r", ls=":", lw=1, label="reference")
    ax1.set_ylabel("hub angle [°]")
    ax1.legend(loc="lower right")
    ax1.set_title(f"{seg['name']}  (ref = {seg['ref_deg']:+g}°,  u_max = {umax:g} A)")

    ax2.plot(t, th12_m, lw=1.5, label="θ₁₂ measured")
    ax2.plot(t, th12_s, lw=1.5, ls="--", label="θ₁₂ model")
    ax2.set_ylabel("tip deflection [°]")
    ax2.legend(loc="lower right")

    ax3.plot(t, Ucmd, lw=1.0, color="0.6", label="commanded u")
    ax3.plot(t, Usat, lw=1.5, color="C3", label="applied u (saturated)")
    ax3.axhline(umax, color="k", ls=":", lw=1)
    ax3.axhline(-umax, color="k", ls=":", lw=1)
    ax3.set_ylabel("motor current [A]")
    ax3.set_xlabel("time [s]")
    ax3.legend(loc="upper right")
    fig.tight_layout()

    sat_frac = float(np.mean(np.abs(Ucmd) > umax + 1e-9)) * 100
    mo.vstack([
        mo.md(
            f"**Open-loop flexible mode:** fₙ ≈ **{f_n:.2f} Hz**, ζ ≈ **{zeta:.3f}**"
            f"  ·  command saturated **{sat_frac:.0f}%** of the time"
            f"  ·  peak demand **{np.max(np.abs(Ucmd)):.1f} A**"
        ),
        fig,
    ])
    return


if __name__ == "__main__":
    app.run()
