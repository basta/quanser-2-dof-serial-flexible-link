# Deploying the Python controllers on the rig

Goal: run the *exact* LQG / output-MPC / H∞ designs from
`analysis/compare_methods_output.py` on the Quanser 2-DOF Serial Flexible Link,
log step responses, and verify them against the Python prediction
(`report/make_hw_figures.py`).

The controllers are discrete at **`Ts_ctrl = 10 ms`** and use **only the two
measured positions** (hub encoder `θ_hub`, base strain gauge `θ_tip`) — the
velocities are reconstructed by a Kalman observer *inside* the block, exactly as
in simulation. The rig's own 40 Hz derivative filters are therefore **not**
used by these blocks.

## 0. One-time export (on the analysis machine)

```bash
.venv/bin/python report/export_controllers.py   # writes orr_controllers.mat
```

Re-run this whenever the designs change, then re-run `setup_orr_controllers.m`.

## 1. Load designs (MATLAB)

```matlab
setup_2dsfl                 % Quanser plant params + LQR baseline (required)
setup_orr_controllers       % loads lqg / hinf / mpc structs + Ts_ctrl
```

## 2. Edit `q_2dsfl_pos_cntrl.slx` (stage-1 loop only)

The stock model feeds the stage-1 state into `K1` (full-state feedback) and the
reference in as a state setpoint. Replace that path with one MATLAB Function
block:

1. Delete the `K1`-gain feedback path (keep the current-command output, the
   saturation, and all safety/limit-switch logic downstream untouched).
2. Drop in a **MATLAB Function** block and point it at `orr_ctrl_lqg`
   (or `orr_ctrl_hinf` / `orr_ctrl_mpc`).
3. Wire its inputs:
   - `yhub` ← stage-1 hub angle `θ11` [rad]
   - `ytip` ← stage-1 tip deflection `θ12` [rad]
   - `ref`  ← the stage-1 hub reference [rad] (the Repeating-Sequence-Stair
     output that `run_lab_experiments.m` configures)
   - the remaining arguments are **Parameters** — see step 3.
4. Connect the block output `u` into the existing current-command saturation
   (`±0.94 A` firmware clip) → motor.
5. Set the block **Sample time** to `Ts_ctrl` (`0.01`). Insert a **Rate
   Transition** between the 10 ms block and the 500 ms... the 500 Hz (`0.002`)
   plant I/O so the multirate model compiles.

## 3. Mark the matrix arguments as Parameters

Open the block → **Edit Data** (Ports and Data Manager). For every argument
*after* `ref`, set **Scope = Parameter** and **Name** = the workspace field:

| block | parameter arguments → workspace field |
|---|---|
| `orr_ctrl_lqg`  | `K`→`lqg.K`, `L`→`lqg.L`, `Ad`→`lqg.Ad`, `Bd`→`lqg.Bd`, `C_POS`→`lqg.C_POS`, `umax`→`lqg.umax` |
| `orr_ctrl_hinf` | `A`→`hinf.A`, `B`→`hinf.B`, `C`→`hinf.C`, `D`→`hinf.D`, `umax`→`hinf.umax`, `Ts`→`Ts_ctrl` |
| `orr_ctrl_mpc`  | `Ad`→`mpc.Ad`, `Bd`→`mpc.Bd`, `C_POS`→`mpc.C_POS`, `L`→`mpc.L`, `Hqp`→`mpc.Hqp`, `M_f`→`mpc.M_f`, `w_f`→`mpc.w_f`, `Gth`→`mpc.Gth`, `Pth`→`mpc.Pth`, `umax`→`mpc.umax`, `defl_lim`→`mpc.defl_lim`, `rho`→`mpc.rho` |

Simulink bakes these in at compile time → codegen-safe for QUARC.

> **MPC note.** `orr_ctrl_mpc` calls `mpcActiveSetSolver` (Model Predictive
> Control Toolbox). It solves an 80-variable QP every 10 ms; this is feasible on
> the QUARC real-time kernel, but verify timing on the first run (External Mode
> shows overruns). If the toolbox is unavailable, deploy **LQG + H∞ only** and
> keep MPC as the simulation reference — the report's hardware section is
> written to degrade gracefully to two controllers.

## 4. Collect data (per controller)

In `run_lab_experiments.m` set `controller_name` to `'lqg'`, `'hinf'`, or
`'mpc'` (matching the block you wired), run the **PREP** cell, set the External
Mode duration it prints, **Monitor & Tune**, then run the **SAVE** cell. This
writes `data/<name>_step_<amp>deg_run01.mat` in the same format as the existing
`lqr_*` runs.

Suggested matched set (same as the report figures): steps to
`±5, ±10, ±20 °`, `u_max = 0.6 A`, MPC deflection limit `2 °`.

## 5. Make the report figures

```bash
.venv/bin/python report/make_hw_figures.py    # overlays measured vs Python sim
cd report && typst compile --root .. report.typ
```
