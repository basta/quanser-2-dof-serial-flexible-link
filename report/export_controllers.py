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
sio.savemat(OUT, dict(
    Ts_ctrl=float(mf.Ts),
    C_TIP=mf.C_TIP.reshape(1, -1),
    C_POS=mf.C_POS,
    lqg=lqg, hinf=hinf, mpc=mpc,
), do_compression=True)

print(f"[export] wrote {os.path.abspath(OUT)}")
print(f"         Ts_ctrl = {mf.Ts*1e3:.0f} ms,  H-inf order {mf.HINF_ORDER}, "
      f"gamma = {mf.GAMMA:.3f},  MPC Np = {Np}")
print("         LQG: K(1x4), L(4x2);  H-inf: A%s;  MPC: Hqp%s"
      % (mf.Hk.shape, Hqp.shape))
