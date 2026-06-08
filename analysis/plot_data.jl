"""
plot_data.jl — inspect LQR step-response data captured by run_lab_experiments.m

Usage (from this directory):

    julia --project=<your env> plot_data.jl

The script loads every `lqr_step_*.mat` file in ../software/quanser_updated/data/,
plots hub angle and tip deflection per amplitude, and writes PNGs into ./figures/.

Dependencies: MAT, Plots. Add to your env with:
    using Pkg; Pkg.add(["MAT", "Plots"])
"""

using MAT
using Plots
using Printf

const DATA_DIR = joinpath(@__DIR__, "..", "software", "quanser_updated", "data")
const FIG_DIR  = joinpath(@__DIR__, "figures")
isdir(FIG_DIR) || mkpath(FIG_DIR)

"Load a single .mat segment and return a NamedTuple with the fields we care about."
function load_segment(path::AbstractString)
    f = matread(path)
    t  = vec(f["time"])
    th11 = vec(f["theta11"])      # hub angle [rad]
    th12 = vec(f["theta12"])      # tip deflection [rad]
    th21 = vec(f["theta21"])
    th22 = vec(f["theta22"])
    X1ref = f["X1_ref"]           # Nx4
    ref_deg = Float64(f["ref_deg"])
    fs = Float64(f["sample_rate_Hz"])
    return (; t, th11, th12, th21, th22, X1ref, ref_deg, fs, path)
end

"Per-segment two-panel plot: hub vs time + tip vs time."
function plot_segment(seg)
    label = @sprintf("ref = %+g°", seg.ref_deg)
    p1 = plot(seg.t, rad2deg.(seg.th11);
              label = "θ₁₁ (hub)",
              xlabel = "time [s]",
              ylabel = "angle [°]",
              lw = 1.5,
              legend = :bottomright,
              title = "Stage 1 hub — $label")
    hline!(p1, [seg.ref_deg]; label = "reference", linestyle = :dash, color = :red)

    p2 = plot(seg.t, rad2deg.(seg.th12);
              label = "θ₁₂ (tip defl.)",
              xlabel = "time [s]",
              ylabel = "deflection [°]",
              lw = 1.5,
              legend = :bottomright,
              title = "Stage 1 tip — $label")
    hline!(p2, [0.0]; label = nothing, linestyle = :dot, color = :gray)

    plot(p1, p2; layout = (2, 1), size = (900, 600))
end

"Overlay all amplitudes on a single hub/tip plot for the same controller."
function plot_overlay(segs; outpath)
    p1 = plot(; xlabel = "time [s]", ylabel = "θ₁₁ hub [°]",
              title = "Hub angle — all amplitudes", legend = :outerright)
    p2 = plot(; xlabel = "time [s]", ylabel = "θ₁₂ tip [°]",
              title = "Tip deflection — all amplitudes", legend = :outerright)
    for seg in sort(segs; by = s -> s.ref_deg)
        lab = @sprintf("%+g°", seg.ref_deg)
        plot!(p1, seg.t, rad2deg.(seg.th11); label = lab, lw = 1.2)
        plot!(p2, seg.t, rad2deg.(seg.th12); label = lab, lw = 1.2)
    end
    fig = plot(p1, p2; layout = (2, 1), size = (1000, 700))
    savefig(fig, outpath)
    return fig
end

function main()
    files = filter(endswith(".mat"), readdir(DATA_DIR; join = true))
    files = filter(f -> startswith(basename(f), "lqr_step_"), files)
    isempty(files) && error("No lqr_step_*.mat files found in $DATA_DIR")

    println("Found $(length(files)) files.")
    segs = load_segment.(files)

    # Per-amplitude plots
    for seg in segs
        base = splitext(basename(seg.path))[1]
        fig = plot_segment(seg)
        out = joinpath(FIG_DIR, base * ".png")
        savefig(fig, out)
        println("wrote ", relpath(out))
    end

    # Overlay
    out = joinpath(FIG_DIR, "lqr_overlay.png")
    plot_overlay(segs; outpath = out)
    println("wrote ", relpath(out))

    return segs
end

# Run when executed as a script. Returns the loaded segments for REPL inspection.
segs = main()
