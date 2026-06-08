#import "@preview/fletcher:0.5.8" as fletcher: diagram, node, edge

// Standalone preview. When #include-d into the report, the trailing
// `#align(center, hinf-diagram)` is what gets shown; wrap as you like there.
#set page(width: auto, height: auto, margin: 6mm)
#set text(font: "New Computer Modern", size: 9pt)

#let hinf-diagram = diagram(
  spacing: (9mm, 10mm),
  node-stroke: 0.6pt,
  node-inset: 6pt,
  mark-scale: 60%,

  // ---- main forward path (y = 0, x increasing to the right) ----------------
  node((0, 0), text(10pt)[$r$], stroke: none),
  node((1, 0), [], shape: circle, radius: 3.4mm, name: <sum>),
  node((1, 0), text(10pt)[$+$], stroke: none),
  node((2, 0), [$ display(integral) $], name: <int>),
  node((3.4, 0), align(center)[$K_infinity$\ #text(7pt)[6th order]], name: <K>),
  node((5, 0), align(center)[Plant $G$\ #text(7pt)[4 states]], name: <G>),
  node((6.3, 0), text(10pt)[$theta_"tip"$], stroke: none, name: <out>),

  edge((0, 0), <sum>, "->"),
  edge(<sum>, <int>, "->", label: text(7pt)[$e$], label-pos: 0.5, label-side: left),
  edge(<int>, <K>, "->", label: text(7pt)[$x_i$], label-pos: 0.55, label-side: left),
  edge(<K>, <G>, "->", label: text(7pt)[$u$], label-pos: 0.4, label-side: left),
  edge(<G>, <out>, "->"),

  // tap dots on the x_i and u wires
  node((2.7, 0), [], shape: circle, radius: 0.7mm, fill: black, name: <tapxi>),
  node((4.2, 0), [], shape: circle, radius: 0.7mm, fill: black, name: <tapu>),

  // ---- measurement feedback  y = [θ_h, θ_t]  into K from below -------------
  edge(<G>, (5, 1.15), (3.4, 1.15), <K>, "->",
       label: text(7pt)[$y=[theta_h, theta_t]$], label-pos: 0.12, label-side: right),

  // ---- tip-angle feedback into the summing junction (lowest lane) ----------
  edge(<out>, (6.3, 2.0), (1, 2.0), <sum>, "->",
       label: text(8pt)[$-$], label-pos: 0.97, label-side: left),

  // ---- performance outputs z (minimised by the H∞ synthesis), upper lane ---
  node((2.7, -1.15), [$W_i$], fill: luma(245), name: <Wi>),
  node((4.2, -1.15), align(center)[$W_2(s)$\ #text(6pt)[roll-off ($omega_c = 8$)]], fill: luma(245), name: <W2>),
  node((2.7, -2.05), text(8pt)[$z_1$], stroke: none, name: <z1>),
  node((4.2, -2.05), text(8pt)[$z_2$], stroke: none, name: <z2>),

  edge(<tapxi>, <Wi>, "->"),
  edge(<Wi>, <z1>, "->"),
  edge(<tapu>, <W2>, "->"),
  edge(<W2>, <z2>, "->"),
)

#align(center, hinf-diagram)
