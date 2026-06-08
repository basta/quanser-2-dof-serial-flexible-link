"""
sim_vs_meas.jl — overlay measured LQR step responses against a Julia
simulation of the same linearized model.

Stage-1 model is ported from `software/quanser_updated/config_2dslf.m` and
`software/quanser_updated/eqn_2DSFL_Stage1.m`. LQR gain uses the same
weights as `setup_2dsfl.m` (`Q1 = diag([2500 1 1 100])`, `R1 = 10`).

For each measured segment we simulate closed-loop from the same initial
state with a constant reference equal to the segment's setpoint, then
overlay hub angle (theta11) and tip deflection (theta12) for measured
vs simulated.

Stage 2: the .mat files already contain Simulink-generated X2_sim, so
we overlay X2_meas vs X2_sim directly without re-simulating.
"""

using MAT
using Plots
using ControlSystems
using OrdinaryDiffEq
using LinearAlgebra
using Printf

const DATA_DIR = joinpath(@__DIR__, "..", "software", "quanser_updated", "data")
const FIG_DIR  = joinpath(@__DIR__, "figures")
isdir(FIG_DIR) || mkpath(FIG_DIR)

# ---------- Stage-1 plant parameters (from config_2dslf.m) ----------
const Me      = 2.068427e11              # Young's modulus (Pa)
const K_IN2M  = 0.0254
const Xb1     = 3.0  * K_IN2M            # beam width  (m)
const Tb1     = 0.050 * K_IN2M           # beam thickness (m)
const L1      = 0.202                    # beam length (m)
const Ks1     = Me * Xb1 * Tb1^3 / (4 * L1)  # torsional stiffness
const B11     = 4.0                      # hub damping
const B12     = 0.0                      # tip damping (neglected)
const Kg1     = 100                      # gear ratio
const Km1     = 0.119                    # back-EMF
const Kt1     = Km1                      # torque constant
const Ktg1    = 0.75 * Kt1 * Kg1         # torque at load shaft per amp
const Jm1     = 6.28e-6
const Jeqm1   = Kg1^2 * Jm1
const J1fix   = 0.00073616
const J11     = Jeqm1 + J1fix
const M12     = 1.578
const J12_cad = 0.18028257
const J12     = J12_cad - M12 * 0.079^2

# ---------- Stage-1 SS matrices (from eqn_2DSFL_Stage1.m) ----------
const A1 = [0.0  0.0                              1.0       0.0;
            0.0  0.0                              0.0       1.0;
            0.0  Ks1/J11                          -B11/J11  B12/J11;
            0.0  -(J11+J12)/(J11*J12)*Ks1         B11/J11   -B12*(J11+J12)/(J11*J12)]

const B1 = reshape([0.0; 0.0; Ktg1/J11; -Ktg1/J11], 4, 1)

# ---------- LQR design (same weights as setup_2dsfl.m) ----------
const Q1 = diagm([2500.0, 1.0, 1.0, 100.0])
const R1 = 10.0
const K1 = lqr(Continuous, A1, B1, Q1, R1)   # 1x4
println("Julia LQR gain K1 = ", K1)

# Closed-loop A. Reference enters as: u = K1[1] * r - K1 * x
const Acl = A1 - B1 * K1

"""Closed-loop ODE: dx/dt = Acl * x + B1 * K1[1] * r"""
function closedloop!(dx, x, p, t)
    r = p
    dx .= Acl * x .+ B1 * (K1[1] * r)
    return nothing
end

"Simulate stage-1 closed loop from x0, constant reference r_rad, over time vector t."
function simulate_stage1(x0::AbstractVector, r_rad::Real, t::AbstractVector)
    prob = ODEProblem(closedloop!, collect(float.(x0)), (t[1], t[end]), float(r_rad))
    sol  = solve(prob, Tsit5(); saveat = t, reltol = 1e-8, abstol = 1e-10)
    X    = reduce(hcat, sol.u)'   # N x 4
    return X
end

function load_segment(path::AbstractString)
    f = matread(path)
    return (
        t       = vec(f["time"]),
        X1_meas = f["X1_meas"],        # N x 4 (rad, rad/s)
        X1_ref  = f["X1_ref"],
        X2_meas = f["X2_meas"],
        X2_sim  = f["X2_sim"],
        ref_deg = Float64(f["ref_deg"]),
        fs      = Float64(f["sample_rate_Hz"]),
        path    = path,
    )
end

"Per-segment overlay: stage-1 measured vs Julia-simulated."
function plot_stage1_overlay(seg)
    x0     = seg.X1_meas[1, :]                # initial state from measurement
    r_rad  = deg2rad(seg.ref_deg)
    Xsim   = simulate_stage1(x0, r_rad, seg.t)

    th11_m = rad2deg.(seg.X1_meas[:, 1])
    th12_m = rad2deg.(seg.X1_meas[:, 2])
    th11_s = rad2deg.(Xsim[:, 1])
    th12_s = rad2deg.(Xsim[:, 2])

    title_label = @sprintf("ref = %+g°", seg.ref_deg)

    p1 = plot(seg.t, th11_m; label = "θ₁₁ measured", lw = 1.5,
              xlabel = "time [s]", ylabel = "hub angle [°]",
              legend = :bottomright, title = "Hub — $title_label")
    plot!(p1, seg.t, th11_s; label = "θ₁₁ simulated", lw = 1.5, linestyle = :dash)
    hline!(p1, [seg.ref_deg]; label = "reference", linestyle = :dot, color = :red)

    p2 = plot(seg.t, th12_m; label = "θ₁₂ measured", lw = 1.5,
              xlabel = "time [s]", ylabel = "tip deflection [°]",
              legend = :bottomright, title = "Tip — $title_label")
    plot!(p2, seg.t, th12_s; label = "θ₁₂ simulated", lw = 1.5, linestyle = :dash)

    plot(p1, p2; layout = (2, 1), size = (1000, 700))
end

"Per-segment stage-2 overlay using the Simulink-generated X2_sim."
function plot_stage2_overlay(seg)
    th21_m = rad2deg.(seg.X2_meas[:, 1])
    th22_m = rad2deg.(seg.X2_meas[:, 2])
    th21_s = rad2deg.(seg.X2_sim[:, 1])
    th22_s = rad2deg.(seg.X2_sim[:, 2])

    title_label = @sprintf("ref = %+g° (stage 1)", seg.ref_deg)

    p1 = plot(seg.t, th21_m; label = "θ₂₁ measured", lw = 1.5,
              xlabel = "time [s]", ylabel = "hub angle [°]",
              legend = :bottomright, title = "Stage 2 hub — $title_label")
    plot!(p1, seg.t, th21_s; label = "θ₂₁ Simulink sim", lw = 1.5, linestyle = :dash)

    p2 = plot(seg.t, th22_m; label = "θ₂₂ measured", lw = 1.5,
              xlabel = "time [s]", ylabel = "tip deflection [°]",
              legend = :bottomright, title = "Stage 2 tip — $title_label")
    plot!(p2, seg.t, th22_s; label = "θ₂₂ Simulink sim", lw = 1.5, linestyle = :dash)

    plot(p1, p2; layout = (2, 1), size = (1000, 700))
end

function main()
    files = filter(endswith(".mat"), readdir(DATA_DIR; join = true))
    files = filter(f -> startswith(basename(f), "lqr_step_"), files)
    isempty(files) && error("No lqr_step_*.mat files in $DATA_DIR")

    segs = load_segment.(files)
    println("Loaded ", length(segs), " segments.")

    for seg in segs
        base = splitext(basename(seg.path))[1]

        fig1 = plot_stage1_overlay(seg)
        out1 = joinpath(FIG_DIR, base * "_sim_stage1.png")
        savefig(fig1, out1)
        println("wrote ", relpath(out1))

        fig2 = plot_stage2_overlay(seg)
        out2 = joinpath(FIG_DIR, base * "_sim_stage2.png")
        savefig(fig2, out2)
        println("wrote ", relpath(out2))
    end

    return segs
end

segs = main()
