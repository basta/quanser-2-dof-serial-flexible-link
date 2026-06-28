// ============================================================================
//  B(E)3M35ORR — Optimal and Robust Control, semestral project
//  Tip-angle tracking of a flexible link: LQG / output-MPC / H-infinity
//
//  Build:  typst compile --root .. report.typ
//  Template: charged-ieee (two-column IEEE).  Wide content (the A/B matrices,
//  the MPC program, and the comparison plots) is placed as full-width floats.
//  Figures: the model diagram is embedded directly. The five comparison
//  figures are produced by analysis/compare_methods_output.py (marimo);
//  export each to report/figs/<name>.png (checklist in the Appendix) and the
//  figslot(..) placeholders will pick them up.
// ============================================================================

#import "@preview/charged-ieee:0.1.3": ieee
#import "hinf_diagram.typ": hinf-diagram

// --- helpers ----------------------------------------------------------------
#let th(x) = table.cell(fill: luma(238))[#strong(x)]

// full-width (both-column) floats; label goes on the element inside the block
#let wfloat(body) = place(top, scope: "parent", float: true, body)
#let wfloatb(body) = place(bottom, scope: "parent", float: true, body)

// placeholder for a figure to be exported from the marimo notebook
#let figslot(path) = block(
  width: 100%, stroke: 0.5pt + luma(160), inset: 14pt, radius: 3pt, fill: luma(248),
)[
  #set align(center)
  #set text(size: 8.5pt, fill: luma(90))
  #text(weight: "bold")[figure slot] \
  export from marimo → #raw("report/figs/" + path)
]

#show: ieee.with(
  title: [Robust Tip-Angle Tracking of a Flexible Link: A Comparison of LQG, Output-Feedback MPC, and $H_infinity$ Control],
  abstract: none,
  authors: (
    (
      name: "Ondřej Baštař",
      department: [B(E)3M35ORR — Optimal and Robust Control],
      organization: [Czech Technical University in Prague],
      email: "bastaond@fel.cvut.cz",
    ),
  ),
  index-terms: ("Flexible-link control", "Robust control", "H-infinity", "Model predictive control", "LQG", "Vibration damping"),
  paper-size: "a4",
)

// nicer bundled fonts (TeX Gyre is not installed)
#set text(font: "New Computer Modern")
#show raw: set text(font: "DejaVu Sans Mono")

// charged-ieee leaves pages unnumbered; add centred page numbers
#set page(numbering: "1", number-align: center)

// ============================================================================
= The Laboratory Model and the Control Task
// ============================================================================

== The apparatus

The Quanser 2-DOF Serial Flexible Link is a planar two-link manipulator whose
links are thin beams that visibly bend under motion. Each joint is
driven by a DC motor through; each link carries a base strain
gauge that measures its elastic deflection, and each joint carries an optical
encoder. This project addresses the inner link only (the outer
link and its motor are locked and treated as a rigid tip load), which already
exhibits the essential difficulty of the full machine, a lightly-damped
structural resonance in the loop, while remaining a single-input model
suitable for a controlled comparison.

@fig-model defines the geometry. The motor applies a torque at the hub; the hub
rotates by the encoder angle $theta_h$, and the beam bends by the additional
strain-gauge angle $theta_t$, so the quantity a downstream task actually cares
about (the #emph[absolute tip angle]) is $theta_"tip" = theta_h + theta_t$.

#wfloat[
  #figure(
    image("../analysis/figures/model_diagram.png", width: 78%),
    caption: [Stage-1 variables. Input: motor current $u$. Measured: hub angle
    $theta_h$ (encoder) and link deflection $theta_t$ (strain gauge). The
    controlled output is the absolute tip angle
    $theta_"tip" = theta_h + theta_t$.],
  ) <fig-model>
]

== Mathematical model

Lumping the link as a two-inertia system (hub inertia $J_(11)$, tip inertia
$J_(12)$) joined by a torsional spring of stiffness $K_s$ and hub damping
$B_(11)$, the linearised Stage-1 dynamics in the state
$x = [theta_h, theta_t, dot(theta)_h, dot(theta)_t]^top$ are
$dot(x) = A x + B u$ with $A$, $B$ as in @eq-ab, where
$K_(t g) = 0.75 K_m K_g$ is the motor-torque constant reflected through the
gearbox. The controlled output and the two measurements are
$
y_"ctrl" = underbrace(mat(1,1,0,0), C_"tip") x, quad
y_"meas" = underbrace(mat(1,0,0,0; 0,1,0,0), C_"pos") x .
$ <eq-c>

#wfloat[
  $
  A = mat(
    0, 0, 1, 0;
    0, 0, 0, 1;
    0, K_s\/J_(11), -B_(11)\/J_(11), 0;
    0, -(J_(11)+J_(12))/(J_(11) J_(12)) K_s, B_(11)\/J_(11), 0;
  ), quad
  B = mat(0; 0; K_(t g)\/J_(11); -K_(t g)\/J_(11))
  $ <eq-ab>
]

The nominal parameters (from the Quanser configuration files) and the resulting
modal properties are collected in @tab-params. Two facts drive every design
decision below. First, $A$ has a #emph[rigid-body integrator]: a pole at exactly
the origin (rotary-arm torque integrates to angle), which is what lets a setpoint
be tracked with zero steady-state error. Second, the structural mode at
$omega_n = 16.9$~rad/s ($2.69$~Hz) is #emph[very lightly damped] ($zeta = 0.33$):
in open loop the tip rings for seconds, and any controller that pushes loop gain
through this frequency risks exciting it.
#figure(
  table(
    columns: (auto, 1fr, auto, auto),
    align: (left, left, right, left),
    stroke: none,
    inset: (x: 5pt, y: 2.6pt),
    table.hline(stroke: 0.7pt),
    th[Symbol], th[Quantity], th[Value], th[Unit],
    table.hline(stroke: 0.4pt),
    $K_s$,        [link torsional stiffness], [$39.96$], [N·m/rad],
    $J_(11)$,     [hub equiv. inertia],   [$0.0635$], [kg·m²],
    $J_(12)$,     [tip equiv. inertia],   [$0.1704$], [kg·m²],
    $B_(11)$,     [hub viscous damping],      [$4.0$],    [N·m·s/rad],
    $K_(t g)$,    [motor const. @ load],    [$8.925$],  [N·m/A],
    $K_g$,        [gear ratio],               [$100$],    [--],
    table.hline(stroke: 0.4pt),
    [poles], [eigenvalues of $A$], table.cell(colspan: 2)[$0;-51.8;-5.58 plus.minus 15.9 j$],
    $omega_n$, [flexible-mode freq.], [$16.9$], [rad/s],
    $zeta$,    [flexible-mode damping],   [$0.33$], [--],
    table.hline(stroke: 0.7pt),
  ),
  caption: [Nominal Stage-1 parameters and modal properties.],
) <tab-params>

== Variables: inputs, states, outputs

The two positions $theta_h, theta_t$ are the #emph[only] signals available for
feedback (as on the real rig), matching @eq-c; the two velocities are estimated.
Sampling is at $T_s = 10$~ms. @tab-vars lists every variable with its operating
range and unit.

#figure(
  table(
    columns: (auto, 1fr, auto, auto),
    align: (left, left, left, left),
    stroke: none,
    inset: (x: 5pt, y: 2.6pt),
    table.hline(stroke: 0.7pt),
    th[Symbol], th[Meaning], th[Range], th[Unit],
    table.hline(stroke: 0.4pt),
    table.cell(colspan: 4, fill: luma(248))[#emph[Input (manipulated)]],
    $u$, [motor current command], [$|u| <= 0.94$], [A],
    table.hline(stroke: 0.3pt),
    table.cell(colspan: 4, fill: luma(248))[#emph[States]],
    $theta_h$, [hub joint angle], [$plus.minus 30$ cmd], [deg],
    $theta_t$, [link tip deflection], [$|theta_t| <= 5$], [deg],
    $dot(theta)_h$, [hub rate], [est.], [deg/s],
    $dot(theta)_t$, [deflection rate], [est.], [deg/s],
    table.hline(stroke: 0.3pt),
    table.cell(colspan: 4, fill: luma(248))[#emph[Measured outputs]],
    $y_1=theta_h$, [hub encoder], [res. $8.8 e^(-4)$], [deg],
    $y_2=theta_t$, [base strain gauge], [$plus.minus 5$], [deg],
    table.hline(stroke: 0.3pt),
    table.cell(colspan: 4, fill: luma(248))[#emph[Controlled output]],
    $theta_"tip"$, [$=theta_h+theta_t$], [$plus.minus 30$], [deg],
    table.hline(stroke: 0.7pt),
  ),
  caption: [Input, state, and output variables. Current is hard-limited at
  $0.94$~A in firmware; simulations clip at $plus.minus u_max$. The $5 degree$ deflection limit is a safety trip; controllers target
  a tighter $approx 2 degree$. Velocities are reconstructed by the observer.],
) <tab-vars>

== Characterisation of uncertainty

The nominal model in @eq-ab is not an exact model. This makes it a good fit for testing robustness of
a controller designed on the theoretical model. The main differences are:

- Parametric stiffness $K_s$: The resonance measured on the rig ($approx 1.8$~Hz,
  §6) sits #emph[below] the modelled $2.69$~Hz. I bracket this
  with a multiplier $K_s in [0.3, 1.5] times$ nominal.

- Unmodelled dynamics: The single-mode model omits higher bending modes and any
  actuator/communication lag. These are unstructured, so no parameter in
  @eq-ab represents them. I test two representatives in §4: a residual second
  flexible mode (spillover) and a pure input delay (phase lag).


== Control requirements

The task is to drive the absolute tip angle $theta_"tip"$ to a commanded set
point (steps up to $plus.minus 30 degree$), subject to:

+ Zero steady-state error to a step.
+ $|u| <= u_"max"$~A actuator limit at all times.
+ Keeping the tip deflection small,
  $|theta_t| lt.tilde 2 degree$, to bound beam stress.
+ Settle the lightly-damped mode quickly, no
  sustained ringing.
+ Remain stable under the uncertainties above,
  especially the unstructured high-frequency dynamics.

// ============================================================================
= The Three Control Methods
// ============================================================================

All three controllers share the #emph[same] nominal discrete model
($A_d, B_d$ from a zero-order-hold of @eq-ab at $T_s = 10$~ms), the #emph[same]
output set $C_"pos"$, and (to achieve a fair comparison) the #emph[same]
state estimator. Only the control law differs. Where a controller needs the
unmeasured velocities, they come from one common steady-state Kalman predictor
$
hat(x)_(k+1) = A_d hat(x)_k + B_d u_k + L (y_k - C_"pos" hat(x)_k),
$ <eq-kalman>
with $L$ from #raw("dlqe") on process covariance $Q_n = q_n B_d B_d^top$
($q_n=10$) and measurement covariance $R_n = r_n I$ ($r_n = 10^(-6)$, i.e. the
positions are trusted).

== LQG

The simplest controller of the bunch, which will serve as a baseline benchmark. An infinite-horizon LQR gain $K$ is computed once by solving the
discrete algebraic Riccati equation (#raw("dlqr")) for the cost
$
J = sum_(k=0)^infinity (x_k - x_"ss")^top Q (x_k - x_"ss") + R u_k^2,
$ <eq-lqr>
with $Q = q_y C_"tip"^top C_"tip" + 10^(-3) I$ ($q_y = 50$, i.e. penalise tip
#emph[angle] error) and $R = 0.5$. The control is static feedback on the
estimate, with the reference injected as a state setpoint
$x_"ss" = [r, 0, 0, 0]^top$ (the plant's own integrator gives offset-free
tracking):
$
u_k = "sat"_(plus.minus u_max) (-K (hat(x)_k - x_"ss")).
$ <eq-lqg>
LQG is fast and cheap, and on a well-modelled plant near-optimal; but its loop
has no guaranteed gain/phase margin, a fact §4 shows clearly.

== Output-feedback MPC

Same estimator, same $Q, R$, but the control is recomputed online by solving, at
every step, a finite-horizon ($N_p = 40$, i.e. $0.4$~s) constrained quadratic
program seeded from the current estimate, @eq-mpc. The terminal cost $P$ is the
LQR Riccati solution (so that the MPC is identical to LQG and to achieve a better comparison), and the deflection limit $|theta_t| <= theta_"max"$ is
imposed as a #emph[soft] constraint (slack $sigma$, penalty $rho = 10^4$) to keep
the QP always feasible. Solved with Clarabel. The
distinguishing capability is the #emph[state constraint]: MPC is the only one of
the three that can actively cap the tip deflection.

#wfloat[
  $
  min_(U, X, sigma) quad & sum_(j=0)^(N_p-1) [(x_j - x_"ss")^top Q (x_j - x_"ss") + R u_j^2 + rho sigma_j] + (x_(N_p)-x_"ss")^top P (x_(N_p)-x_"ss") \
  "s.t." quad & x_(j+1) = A_d x_j + B_d u_j, quad x_0 = hat(x)_k, \
  & |u_j| <= u_max, quad |theta_(t,j)| <= theta_"max" + sigma_j, quad sigma_j >= 0
  $ <eq-mpc>
]

== $H_infinity$ output feedback (Ch. 11--12)

A two-measurement mixed-sensitivity design synthesised with #raw("hinfsyn")
(@fig-hinf). Two issues make this plant awkward and shape the design:

- The rigid-body pole on the imaginary axis breaks the synthesis rank
  conditions, so it is regularised off-axis, $A arrow.l A - epsilon I$
  ($epsilon = 10^(-3)$). But that same nudge hides the integrator from the
  synthesis, which then causes tracking with a large offset. I restore integral action
  explicitly with a tracking-error integrator state
  $dot(x)_i = r - theta_"tip"$ fed to the controller, recovering offset-free
  tracking.
- The regulated outputs are $z = [W_i x_i, " " W_2 u]$. The control-effort weight
  $W_2$ is a high-pass with its corner placed #emph[low], at $omega_c = 8$~rad/s
  (lower than the flexible mode) so the synthesis penalises
  high-frequency control effort androlls the loop off before the
  resonance. This buys the robustness margin of §4 at the cost of a little
  nominal speed.

#wfloatb[
  #figure(
    box(inset: (y: 4pt), hinf-diagram),
    caption: [Integral-augmented $H_infinity$ output-feedback loop. The plant
    integrator is regularised off-axis for synthesis, so integral action is
    restored #emph[explicitly]: the tracking error $e = r - theta_"tip"$ is
    integrated to a state $x_i$ that is handed to the controller alongside the
    two measurements $y = [theta_h, theta_t]$. The synthesis minimises the
    weighted regulated outputs $z_1 = W_i x_i$ (tracking) and $z_2 = W_2(s) u$
    (control effort, rolled off above $omega_c = 8$~rad/s).],
  ) <fig-hinf>
]

The synthesis returns a 6th-order controller with $gamma = 0.31$. Because the
integral augmentation adds a second imaginary-axis pole the synthesis is
numerically delicate (about a quarter of the weight grid collapses to a
degenerate controller), so the weights were difficult to select. Through trial-and-error I reached($epsilon=10^(-3)$, $W_i=1.0$, $W_2$ DC gain $0.1$) but manual tuning proved unwieldy.


// ============================================================================
= Nominal Performance on the Theoretical Model
// ============================================================================

On the nominal plant the three methods are, as expected, close.
@fig-nominal overlays the closed-loop step to $+20 degree$ and @tab-nominal
quantifies it.

#figure(
  table(
    columns: (1.2fr, auto, auto, auto, auto),
    align: (left, center, center, center, center),
    stroke: none,
    inset: (x: 5pt, y: 3pt),
    table.hline(stroke: 0.7pt),
    th[Method], th[rise [s]], th[OS [%]], th[pk $|u|$ [A]], th[max $|theta_t|$ [°]],
    table.hline(stroke: 0.4pt),
    [LQG],          [$0.30$], [$1.5$], [$0.60$], [$3.56$],
    [output-MPC],   [$0.35$], [$2.9$], [$0.60$], [#strong[$2.00$]],
    [$H_infinity$], [$0.49$], [$0.7$], [$0.46$], [$2.25$],
    table.hline(stroke: 0.7pt),
  ),
  caption: [Nominal metrics (step to $+20 degree$). All three offset-free
  (steady-state error $< 0.01 degree$). LQG is fastest but its deflection
  ($3.56 degree$) exceeds the $2 degree$ limit; MPC trades $0.05$~s of rise to
  hold it at exactly $2.00 degree$; $H_infinity$ is slowest but uses least
  current.],
) <tab-nominal>

#wfloat[
  #figure(
    image("figs/compare_nominal.png", width: 66%),
    caption: [Nominal closed-loop response to a $+20 degree$ tip-angle step
    ($u_max = 0.6$~A, MPC deflection limit $2 degree$). Top: tip angle; middle:
    tip deflection $theta_t$ with the MPC limit; bottom: motor current. All three
    track offset-free; only MPC holds the deflection at its constraint.],
  ) <fig-nominal>
]

How to read this? MPC's value is the state constraint (Interestingly, pure
input saturation does not separate it from a clipped LQR for this single move,
but the deflection cap does, and only MPC can impose it.) $H_infinity$ looks
merely "slower" here; the next section shows what that slowness is buying.

To see the loop-shaping explicitly, @fig-sens plots the closed-loop sensitivity
$S$ and complementary sensitivity $T$ of the $H_infinity$ design. $S$ rolls off
to a small value at DC (offset-free tracking) and $T$ rolls off #emph[before] the
flexible mode, with modest peaks.

#wfloat[
  #figure(
    image("figs/hinf_sensitivity.png", width: 72%),
    caption: [Sensitivity $S$ and complementary sensitivity $T$ of the
    $H_infinity$ loop (controlled output $theta_"tip"$). $|S(0)|$ small
    $arrow.r$ offset-free; $|T|$ rolls off below the flexible mode (dotted)
    $arrow.r$ no spillover; low $norm(S)_infinity, norm(T)_infinity$ peaks
    $arrow.r$ margins.],
  ) <fig-sens>
]

// ============================================================================
= Robustness of $H_infinity$
// ============================================================================

The conclusion from §3 is that on a well-modelled, minimum-phase plant
$H_infinity$ has no visible advantage. Its margin only shows once the truth plant
differs from the design model in ways no quadratic cost accounts for. We
keep every controller exactly as designed (each still uses the nominal four-state
model and the same Kalman estimate) and perturb only the simulated truth
plant.

== Scenario A: unmodelled second flexible mode

A real beam has more bending modes than the one-mode design model. I append a
residual lightly-damped mode at $3 times$ the modelled frequency, coupled into
the tip output. The nominal-designed LQG and MPC push loop gain into the
unmodelled mode and ring / destabilise, while the $H_infinity$ loop, deliberately rolled off
above the modelled mode, stays clean. Only an explicit high-frequency
roll-off guarantees this; a quadratic cost provides none. See @fig-spill.

#wfloat[
  #figure(
    image("figs/robust_spillover.png", width: 66%),
    caption: [Scenario A: with an unmodelled second flexible mode in the truth
    plant, nominal LQG/MPC excite it and ring (control spillover) while the
    rolled-off $H_infinity$ loop tracks cleanly.],
  ) <fig-spill>
]

== Scenario B: input delay

A few tens of milliseconds of actuator/communication delay (modelled as a
discrete shift register at the plant input) eats phase margin. LQG loses stability around $approx 50$~m, whereas $H_infinity$, which bounds the
sensitivity peaks, tolerates substantially more ($80$~ms+). See
@fig-delay.

#wfloat[
  #figure(
    image("figs/robust_delay.png", width: 66%),
    caption: [Scenario B: a pure input delay. LQG destabilises near $50$~ms; the
    $H_infinity$ loop, with bounded $norm(S)_infinity$, keeps stable margins well
    past $80$~ms.],
  ) <fig-delay>
]

The price $H_infinity$ pays for this is exactly the slower nominal response and
the higher-order (6th vs static) controller seen in §3.

// ============================================================================
= Empirical Robustness Verification
// ============================================================================

The unstructured uncertainties of §4 are where $H_infinity$ had great results.
Out of interest I also sweep the one structured uncertainty the model
exposes: the link stiffness $K_s$, whose true value is the least certain
parameter (§1.4). Holding each controller fixed at its nominal design, we
re-simulate the $+20 degree$ step while scaling the truth-plant stiffness over
$K_s in [0.3, 1.5] times$ nominal and record tracking error, overshoot, and peak
deflection. See @fig-ks.

#wfloat[
  #figure(
    image("figs/robust_ks_sweep.png", width: 66%),
    caption: [Parametric robustness: steady-state error, overshoot, and peak
    deflection versus a truth-plant stiffness multiplier
    $K_s\/K_s^"nom" in [0.3,1.5]$, all controllers fixed at nominal design.],
  ) <fig-ks>
]

The instructive (and slightly counter-intuitive) result is that this axis
does not favour $H_infinity$: all three controllers remain robustly stable
across the whole stiffness range, because $K_s$ only moves the resonance, it does
not introduce dynamics outside the model's structure. The integral action keeps
LQG and MPC offset-free throughout; $H_infinity$ too, apart from a small residual
at the softest plants ($K_s lt.tilde 0.4 times$ nominal), where its deliberate
roll-off makes the loop slow enough that the integrator has not fully settled
within the $5$~s window. My takeaway is robustness is not a scalar. A controller can be
robust to large
#emph[parametric] error and yet fragile to small #emph[unstructured] error (LQG,
§4), or vice versa.

// ============================================================================
= Hardware Verification on the Physical Rig
// ============================================================================

Sections 3--5 are simulation. To verify that the conclusions survive contact
with the apparatus, the two linear designs (LQG and $H_infinity$) are deployed on
the Quanser rig and their measured step responses compared against the Python
prediction they were designed from. (MPC, which needs an online QP solver on the
real-time target, was not deployed; I didn't have enough time.)

== Experimental protocol

Each controller drives the automated stair sequence of
#raw("run_lab_experiments.m") (steps to $plus.minus 5, plus.minus 10,
plus.minus 20, plus.minus 30 degree$ at $u_max = 0.9$~A) logging the full
state at $500$~Hz; each segment steps from the previous stair level, not from
zero. The rig shapes every commanded step through a smoothing sigmoid, so
I run the Python prediction with the
logged reference: the residual between measured and predicted then
reflects plant--model mismatch, not the command shape. @fig-hw-lqg and
@fig-hw-hinf show the $+20 degree$ step; @tab-hw collects the
measured-vs-predicted metrics.

#figure(
  table(
    columns: (1.1fr, auto, auto, auto, auto),
    align: (left, center, center, center, center),
    stroke: none,
    inset: (x: 5pt, y: 3pt),
    table.hline(stroke: 0.7pt),
    th[Method], th[rise m/p [s]], th[OS m/p [%]], th[max $|theta_t|$ [°]], th[sse [°]],
    table.hline(stroke: 0.4pt),
    [LQG],          [$0.76\/0.70$], [$3.5\/0.0$],  [#strong[$1.64$]], [$0.04$],
    [$H_infinity$], [$0.93\/0.96$], [$16.8\/0.5$], [$1.91$],          [$0.52$],
    table.hline(stroke: 0.7pt),
  ),
  caption: [Hardware metrics, measured (m) vs. predicted (p), step to
  $+20 degree$ (from #raw("make_hw_figures.py")). LQG matches its prediction
  closely; $H_infinity$ overshoots $5 times$ more than predicted. Across the
  $plus.minus 20\/30 degree$ steps the residual tip ring is $0.2$--$0.5 degree$
  for LQG but $1.8$--$3.0 degree$ for $H_infinity$.],
) <tab-hw>

#wfloat[
  #figure(
    image("figs/hw_lqg.png", width: 80%),
    caption: [LQG on the rig (red) vs. the logged-reference Python prediction
    (blue), $+20 degree$ step. Angle and deflection track the design closely; the
    small residual ring ($approx 0.2 degree$) is the lightly-damped structural
    mode, actively damped by the high-gain state feedback.],
  ) <fig-hw-lqg>
]

#wfloat[
  #figure(
    image("figs/hw_hinf.png", width: 80%),
    caption: [$H_infinity$ on the rig (red) vs. prediction (blue), $+20 degree$.
    The measured loop overshoots and rings at $approx 1.8$~Hz with $1.8$--$3 degree$
    of deflection --- far more than predicted --- because its deliberately
    low-authority loop adds little active damping at the true resonance.],
  ) <fig-hw-hinf>
]

== Results on the experimental setup

The rig is not the nominal model, so we can look at how the two controllers handled it.

=== Measured rise tracks the prediction within
$approx 0.1$~s across every amplitude, steady-state error stays under
$approx 0.6 degree$, and the structural mode is actively damped to a
$0.2$--$0.5 degree$ residual. The design transfers to hardware essentially as
@fig-nominal promised.

=== $H_infinity$
It rings hard on the large steps ($16$--$48%$ overshoot, $1.8$--$3 degree$ of
sustained deflection at $approx 1.8$~Hz) and #emph[stalls] on the small ones
($plus.minus 5, +10 degree$ end $3$--$4.6 degree$ short, static friction the
low-authority loop never overcomes). Two real-plant effects, both named in §1.4,
likely drive this: hub stiction (a nonlinearity no linear design models) and a
true resonance at $approx 1.8$~Hz (not the modelled $2.69$~Hz, and
right where the $H_infinity$ loop was deliberately given little gain. Its
roll-off, which bought margin against the unstructured high-frequency
uncertainty of §4, leaves it without the authority to actively damp the
structural mode or to break stiction. LQG's higher loop gain makes it work better here.
