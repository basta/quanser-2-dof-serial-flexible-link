#!/usr/bin/env python
"""Hardware-verification figures: measured rig runs vs the Python prediction.

For each controller deployed on the rig (LQG / output-MPC / H-infinity), this
loads the logged step segments produced by ``run_lab_experiments.m`` and
overlays the MEASURED tip-angle / deflection against the closed-loop response
predicted by the *same* Python design (the one in
``report/make_figures.py`` / ``compare_methods_output.py``), simulated from the
segment's own initial state and setpoint on the nominal model. It also prints a
measured-vs-predicted metrics table.

    .venv/bin/python report/make_hw_figures.py

Outputs (report/figs/): hw_lqg.png, hw_hinf.png, hw_mpc.png  (only for the
controllers that have data). Controllers with no <name>_step_*.mat are skipped.

Data search: software/quanser_updated/data/  and  data/.  File naming follows
``run_lab_experiments.m``:  <controller>_step_[neg_]<deg>deg_run<NN>.mat, each a
struct with X1_meas (Nx4, rad: [hub, tip_defl, hub_dot, tip_dot]), ref_deg,
sample_rate_Hz. NOTE: the existing ``lqr_*`` runs are Quanser's continuous
full-state LQR, not the Python LQG — they are shown (if present) only as an
illustrative baseline; the genuine verification uses lqg/hinf/mpc runs.
"""
from __future__ import annotations

import glob
import os
import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import cvxpy as cp

import make_figures as mf   # identical designs (Ad0, Bd, K, L, Hk.., Q, P, ...)

OUT_DIR = mf.OUT_DIR
_QSU = os.path.join(os.path.dirname(__file__), "..", "software", "quanser_updated")
DATA_DIRS = [
    os.path.join(_QSU, "data"),       # H-inf runs (hinf_step_*.mat)
    os.path.join(_QSU, "lqg_data"),   # LQG runs   (lqg_step_*.mat)
    os.path.join(os.path.dirname(__file__), "..", "data"),
]
# step to feature in each controller's figure (falls back to the largest run)
FEATURE_DEG = 20.0
# which logged controllers to process -> Python predictor used for the overlay
PREDICTOR = {"lqg": "lqg", "hinf": "hinf", "mpc": "mpc",
             "lqr": "lqg"}   # 'lqr' = Quanser baseline, overlaid on LQG prediction
LABEL = {"lqg": "LQG", "hinf": r"H$\infty$", "mpc": "output-MPC",
         "lqr": "Quanser LQR (baseline)"}


# --------------------------------------------------------------------------
#  Per-segment Python prediction: closed loop of (nominal plant + controller),
#  started from the measured initial state x0 and driven by the *logged*
#  reference r_series[k] (rad, at the 10 ms controller rate). Using the recorded
#  reference -- which the rig smooths through a sigmoid -- means the residual
#  reflects plant/model mismatch (friction, true resonance), not the step shape.
# --------------------------------------------------------------------------
Ad, Bd, C_POS, C_TIP = mf.Ad0, mf.Bd, mf.C_POS, mf.C_TIP
Kf, L = mf.Kf, mf.L


def _observe(xh, u, ym):
    return Ad @ xh + Bd * u + L @ (ym - C_POS @ xh)


def predict_lqg(r_series, x0, umax):
    n = len(r_series)
    x = x0.copy(); xh = x0.copy()
    y = np.empty(n); d = np.empty(n)
    for k in range(n):
        ym = C_POS @ x
        xss = np.array([r_series[k], 0.0, 0.0, 0.0])
        u = float(np.clip(-Kf @ (xh - xss), -umax, umax))
        y[k] = np.rad2deg(C_TIP @ x); d[k] = np.rad2deg(x[1])
        xh = _observe(xh, u, ym); x = Ad @ x + Bd * u
    return y, d


def predict_hinf(r_series, x0, umax):
    n = len(r_series)
    Hk, HB, HC, HD = mf.Hk, mf.HB, mf.HC, mf.HD
    x = x0.copy(); xi = 0.0; xc = np.zeros(Hk.shape[0])
    y = np.empty(n); d = np.empty(n)
    for k in range(n):
        ym = C_POS @ x
        meas = np.array([ym[0], ym[1], xi])
        u = float(np.clip((HC @ xc + HD @ meas).reshape(-1)[0], -umax, umax))
        yk = float(C_TIP @ x)
        y[k] = np.rad2deg(yk); d[k] = np.rad2deg(x[1])
        xc = Hk @ xc + HB @ meas; xi += mf.Ts * (r_series[k] - yk); x = Ad @ x + Bd * u
    return y, d


# MPC with a parametric setpoint (the report's QP is fixed at one reference)
_xss = cp.Parameter(4); _x0p = cp.Parameter(4)
_U = cp.Variable((1, mf.Np)); _X = cp.Variable((4, mf.Np + 1)); _Sl = cp.Variable(mf.Np, nonneg=True)
_cost = 0; _cons = [_X[:, 0] == _x0p]
for _k in range(mf.Np):
    _cost += cp.quad_form(_X[:, _k] - _xss, cp.psd_wrap(mf.Q)) + mf.Ru * cp.square(_U[0, _k]) + 1e4 * _Sl[_k]
    _cons += [_X[:, _k + 1] == Ad @ _X[:, _k] + Bd * _U[0, _k],
              cp.abs(_U[0, _k]) <= mf.UMAX, cp.abs(_X[1, _k + 1]) <= np.deg2rad(mf.DEFL_DEG) + _Sl[_k]]
_cost += cp.quad_form(_X[:, mf.Np] - _xss, cp.psd_wrap(mf.P))
_mpc = cp.Problem(cp.Minimize(_cost), _cons)


def predict_mpc(r_series, x0, umax):
    n = len(r_series)
    x = x0.copy(); xh = x0.copy()
    y = np.empty(n); d = np.empty(n)
    for k in range(n):
        ym = C_POS @ x
        _xss.value = np.array([r_series[k], 0.0, 0.0, 0.0])
        _x0p.value = xh
        _mpc.solve(solver=cp.CLARABEL, warm_start=True)
        u = float(np.clip(_U.value[0, 0], -umax, umax)) if _U.value is not None else 0.0
        y[k] = np.rad2deg(C_TIP @ x); d[k] = np.rad2deg(x[1])
        xh = _observe(xh, u, ym); x = Ad @ x + Bd * u
    return y, d


PREDICT = {"lqg": predict_lqg, "hinf": predict_hinf, "mpc": predict_mpc}


def _predict_seg(pred, seg, umax):
    """Run a predictor on the controller-rate grid for one logged segment.
    Returns (t_ctrl, y_pred_deg, d_pred_deg)."""
    t = seg["t"] - seg["t"][0]
    t_c = np.arange(0.0, t[-1] + mf.Ts / 2, mf.Ts)
    r_c = np.interp(t_c, t, seg["ref_series"])          # logged ref at 10 ms
    yp, dp = pred(r_c, seg["X"][0, :].copy(), umax)
    return t_c, yp, dp


# --------------------------------------------------------------------------
def _load(path):
    from scipy.io import loadmat
    m = loadmat(path)
    Xr = np.asarray(m["X1_ref"], float)          # logged reference, col 0 = r [rad]
    return dict(t=np.ravel(m["time"]), X=np.asarray(m["X1_meas"], float),
                ref_series=Xr[:, 0],
                ref=float(np.ravel(m["ref_deg"])[0]),
                fs=float(np.ravel(m["sample_rate_Hz"])[0]))


def _runs(ctrl):
    found = []
    for d in DATA_DIRS:
        found += glob.glob(os.path.join(d, f"{ctrl}_step_*deg_run*.mat"))
    return sorted(set(found))


def _metrics(t, tip, ref):
    if ref == 0 or not np.all(np.isfinite(tip)):
        return None
    sgn = np.sign(ref)
    hit = (sgn * tip) >= abs(0.9 * ref)
    rise = t[np.argmax(hit)] - t[0] if hit.any() else np.nan
    ov = max(0.0, ((sgn * tip).max() - abs(ref)) / abs(ref) * 100)
    sse = abs(tip[-1] - ref)
    return rise, ov, sse


def make_one(ctrl):
    runs = _runs(ctrl)
    if not runs:
        return None
    pred = PREDICT[PREDICTOR[ctrl]]
    # choose the featured run (closest |ref| to FEATURE_DEG, positive preferred)
    segs = [_load(p) for p in runs]
    feat = min(segs, key=lambda s: (abs(abs(s["ref"]) - FEATURE_DEG), -s["ref"]))

    t = feat["t"] - feat["t"][0]
    tip_m = np.rad2deg(feat["X"][:, 0] + feat["X"][:, 1])
    defl_m = np.rad2deg(feat["X"][:, 1])
    tc, yp, dp = _predict_seg(pred, feat, mf.UMAX)

    fig, (a1, a2) = plt.subplots(2, 1, figsize=(7.0, 5.0), sharex=True)
    a1.plot(t, tip_m, lw=1.6, color="#d62728", label="measured (rig)")
    a1.plot(tc, yp, lw=1.5, ls="--", color="#1f77b4", label="Python prediction")
    a1.axhline(feat["ref"], color="r", ls=":", lw=1, label="reference")
    a1.set_ylabel("tip angle [°]")
    a1.set_title(f"Hardware verification — {LABEL[ctrl]}  (step to {feat['ref']:+g}°)")
    a1.legend(loc="lower right", fontsize=8)
    a2.plot(t, defl_m, lw=1.6, color="#d62728", label="measured")
    a2.plot(tc, dp, lw=1.5, ls="--", color="#1f77b4", label="predicted")
    if ctrl == "mpc":
        a2.axhline(mf.DEFL_DEG, color="k", ls=":", lw=1); a2.axhline(-mf.DEFL_DEG, color="k", ls=":", lw=1)
    a2.set_ylabel(r"tip deflection $\theta_t$ [°]"); a2.set_xlabel("time [s]")
    a2.legend(loc="upper right", fontsize=8)
    fig.tight_layout()
    out = os.path.join(OUT_DIR, f"hw_{ctrl}.png")
    fig.savefig(out, dpi=mf.DPI, bbox_inches="tight"); plt.close(fig)

    # metrics across all runs of this controller (prediction driven by logged ref)
    print(f"\n[{LABEL[ctrl]}]  measured vs predicted   ({len(segs)} runs)")
    print(f"  {'ref°':>5} | {'rise meas/pred':>15} | {'OS% m/p':>11} | {'sse°m/p':>11}")
    for s in sorted(segs, key=lambda s: s["ref"]):
        tt = s["t"] - s["t"][0]
        tm = np.rad2deg(s["X"][:, 0] + s["X"][:, 1])
        tcp, yp2, _ = _predict_seg(pred, s, mf.UMAX)
        mm, mp = _metrics(tt, tm, s["ref"]), _metrics(tcp, yp2, s["ref"])
        if mm and mp:
            print(f"  {s['ref']:>5g} | {mm[0]:6.2f} /{mp[0]:6.2f} | "
                  f"{mm[1]:4.1f}/{mp[1]:4.1f} | {mm[2]:5.2f}/{mp[2]:5.2f}")
    print(f"  -> saved {out}")
    return out


def main():
    os.makedirs(OUT_DIR, exist_ok=True)
    made = [c for c in ("lqg", "hinf", "mpc", "lqr") if make_one(c)]
    if not made:
        print("No <controller>_step_*.mat runs found. Deploy a controller "
              "(see software/quanser_updated/WIRING.md) and collect data first.")
    else:
        print("\nFigures written to", OUT_DIR, "->", made)


if __name__ == "__main__":
    main()
