# Deploying the Python controllers on the rig

Goal: run the *exact* LQG / H∞ / output-MPC designs from
`analysis/compare_methods_output.py` on the Quanser 2-DOF Serial Flexible Link,
log step responses, and verify them against the Python prediction
(`report/make_hw_figures.py`).

The controllers are discrete at **`Ts_ctrl = 10 ms`** and use **only the two
measured positions** (hub encoder `θ_hub`, base strain gauge `θ_tip`); the
velocities are reconstructed by a Kalman observer *inside* the controller,
exactly as in simulation. The rig's own 40 Hz derivative filters are **not**
used.

## LQG and H∞ — fully automatic (no Simulink hand-editing)

Each linear controller folds (observer + gain + integrator) into a single
Discrete State-Space block, so a script builds the rig models for you.

```bash
# 1. (analysis machine) export + self-verify the controllers
.venv/bin/python report/export_controllers.py     # writes orr_controllers.mat
```
```matlab
% 2. (rig machine, in software/quanser_updated)
setup_2dsfl          % Quanser plant params + safety limits  (REQUIRED first)
build_orr_models     % writes q_2dsfl_orr_lqg.slx and q_2dsfl_orr_hinf.slx
```

`build_orr_models` copies `q_2dsfl_pos_cntrl.slx`, swaps Quanser's `LQR Gain 1`
for the state-space controller, and leaves every safety / HIL / scope block
untouched. The state and setpoint are tapped from the existing `Mux1` and
`Stage 1 Setpoint` blocks; the output replaces the old gain into
`Im_r1: Saturation`.

## Run an experiment

1. Open `q_2dsfl_orr_lqg.slx`.
2. **First move — small and safe.** Before the full stair, drive a single
   **+5°** step and **Monitor & Tune** with a hand on the E-stop. It should rise
   in ≈0.3 s, deflection stays small, current well under 0.94 A. The 5°
   deflection watchdog (`setup_2dsfl`) is your safety net. Runaway / immediate
   trip ⇒ a sign issue — stop and tell me.
3. **Matched set.** In `run_lab_experiments.m` set `controller_name = 'lqg'` and
   `amps_deg = [0 5 -5 10 -10 20 -20 0]`. Run the **PREP** cell; it prints the
   Repeating-Sequence-Stair values and the External-Mode duration. Set the Stair
   (inside `Stage 1 Setpoint`) and the duration, **Monitor & Tune** for the full
   run, then run the **SAVE** cell → `data/lqg_step_*deg_run01.mat`.
4. Repeat with `q_2dsfl_orr_hinf.slx` and `controller_name = 'hinf'`.

## MPC — one manual step (needs the online QP solver)

MPC solves a QP every step, so it can't be a state-space block. Check the solver
exists first: `exist('mpcActiveSetSolver','file')` must return `2` (Model
Predictive Control Toolbox). Then, in a copy of the model, replace `LQR Gain 1`
with a **MATLAB Function** block running `orr_ctrl_mpc` (3 inputs
`yhub, ytip, ref`; mark the matrix arguments as *Parameter* → `mpc.Ad`,
`mpc.Bd`, `mpc.C_POS`, `mpc.L`, `mpc.Hqp`, `mpc.M_f`, `mpc.w_f`, `mpc.Gth`,
`mpc.Pth`, `mpc.umax`, `mpc.defl_lim`, `mpc.rho`; sample time `Ts_ctrl`).
`setup_orr_controllers` loads those. On the first run watch External Mode for
**overruns** (the 80-var QP must finish inside 10 ms); if it overruns, tell me
and we'll shorten the horizon or drop the rate. Set `controller_name = 'mpc'`.
If the toolbox is unavailable, deploy **LQG + H∞ only** — the report degrades
gracefully to two controllers.

> `orr_ctrl_lqg.m` / `orr_ctrl_hinf.m` are kept as reference implementations of
> the same laws; the automatic state-space build supersedes them.

## Make the report figures

```bash
.venv/bin/python report/make_hw_figures.py    # overlays measured vs Python sim
cd report && typst compile --root .. report.typ
```
