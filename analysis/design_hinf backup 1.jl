### A Pluto.jl notebook ###
# v0.20.25

using Markdown
using InteractiveUtils

# ╔═╡ 00000000-0000-0000-0000-000000000001
md"""
# H∞ mixed-sensitivity design — 2DOF flexible link (stage 1)

Stage-1 plant ported from `software/quanser_updated/config_2dslf.m` +
`eqn_2DSFL_Stage1.m`. SISO: input = motor command, output = hub angle θ₁₁.

**Goal:** design a robust controller via mixed-sensitivity H∞, comparable
against the stock LQR (`Q = diag(2500, 1, 1, 100)`, `R = 10`).

Incremental — first inspect open-loop modes, then pick weights based on
where the tip-flex mode sits.
"""

# ╔═╡ 00000000-0000-0000-0000-000000000002
begin
	using ControlSystems
	using RobustAndOptimalControl
	using LinearAlgebra
	using Plots
	using PlutoUI
	using Printf
end

# ╔═╡ 00000000-0000-0000-0000-000000000003
md"## Plant parameters"

# ╔═╡ 00000000-0000-0000-0000-000000000004
plant_params = (
	Me      = 2.068427e11,   # Young's modulus [Pa]
	K_IN2M  = 0.0254,
	L1      = 0.202,         # beam length [m]
	B11     = 4.0,           # hub damping
	B12     = 0.0,           # tip damping (neglected)
	Kg1     = 100,           # gear ratio
	Km1     = 0.119,         # back-EMF / torque constant
	Jm1     = 6.28e-6,
	J1fix   = 0.00073616,
	M12     = 1.578,
	J12_cad = 0.18028257,
)

# ╔═╡ 00000000-0000-0000-0000-000000000005
derived = let p = plant_params
	Xb1   = 3.0   * p.K_IN2M
	Tb1   = 0.050 * p.K_IN2M
	Ks1   = p.Me * Xb1 * Tb1^3 / (4 * p.L1)
	Ktg1  = 0.75 * p.Km1 * p.Kg1
	Jeqm1 = p.Kg1^2 * p.Jm1
	J11   = Jeqm1 + p.J1fix
	J12   = p.J12_cad - p.M12 * 0.079^2
	(; Ks1, Ktg1, J11, J12)
end

# ╔═╡ 00000000-0000-0000-0000-000000000006
md"## State-space plant — SISO, output = θ₁₁ (hub angle)"

# ╔═╡ 00000000-0000-0000-0000-000000000007
G1 = let p = plant_params, d = derived
	A = [0.0  0.0                                  1.0          0.0;
	     0.0  0.0                                  0.0          1.0;
	     0.0  d.Ks1/d.J11                          -p.B11/d.J11 p.B12/d.J11;
	     0.0  -(d.J11+d.J12)/(d.J11*d.J12)*d.Ks1   p.B11/d.J11  -p.B12*(d.J11+d.J12)/(d.J11*d.J12)]
	B = reshape([0.0, 0.0, d.Ktg1/d.J11, -d.Ktg1/d.J11], 4, 1)
	C = [1.0 0.0 0.0 0.0]
	D = 0.0
	ss(A, B, C, D)
end

# ╔═╡ 00000000-0000-0000-0000-000000000008
md"""
## Open-loop modes

Look for the lightly-damped pair — that's the tip-flex mode. It tells us
where `W_T` (the robustness weight) has to start rolling up.
"""

# ╔═╡ 00000000-0000-0000-0000-000000000009
modes_table = let
	pol = eigvals(G1.A)
	wn  = abs.(pol)
	ζ   = [iszero(w) ? 0.0 : -real(p)/w for (p, w) in zip(pol, wn)]
	fHz = wn ./ (2π)
	[(; pole = pol[i], ωn = wn[i], fHz = fHz[i], ζ = ζ[i]) for i in eachindex(pol)]
end

# ╔═╡ 00000000-0000-0000-0000-00000000000a
bodeplot(G1; label = "θ₁₁/u", size = (800, 500), title = "Open-loop Bode — stage 1")

# ╔═╡ 00000000-0000-0000-0000-00000000000b
md"""
**Next:** pick W_S bandwidth (well below the tip mode) and W_T corner
(above it) based on the mode frequencies above, then synthesize.
"""

# ╔═╡ Cell order:
# ╟─00000000-0000-0000-0000-000000000001
# ╠═00000000-0000-0000-0000-000000000002
# ╟─00000000-0000-0000-0000-000000000003
# ╠═00000000-0000-0000-0000-000000000004
# ╠═00000000-0000-0000-0000-000000000005
# ╟─00000000-0000-0000-0000-000000000006
# ╠═00000000-0000-0000-0000-000000000007
# ╟─00000000-0000-0000-0000-000000000008
# ╠═00000000-0000-0000-0000-000000000009
# ╠═00000000-0000-0000-0000-00000000000a
# ╟─00000000-0000-0000-0000-00000000000b
