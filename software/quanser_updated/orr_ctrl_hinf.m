function u = orr_ctrl_hinf(yhub, ytip, ref, A, B, C, D, umax, Ts) %#codegen
% ORR_CTRL_HINF  Python-designed H-infinity output-feedback controller.
%
%   Integral-augmented mixed-sensitivity design (hinfsyn), Tustin-discretised
%   to the controller rate. The controller consumes meas = [hub, tip, xi],
%   where xi is the integral of the tracking error r - theta_tip that restores
%   offset-free tracking (the plant integrator is regularised off-axis for the
%   synthesis -- see the H-infinity design note in the report).
%
%   Mark A, B, C, D, umax, Ts as *Parameter* arguments and point them at the
%   workspace struct fields hinf.A, hinf.B, hinf.C, hinf.D, hinf.umax, Ts_ctrl.
%   Run at Ts_ctrl (10 ms) behind a Rate Transition, same as the LQG block.

persistent xc xi
if isempty(xc)
    xc = zeros(size(A, 1), 1);
    xi = 0;
end

tip  = yhub + ytip;                       % controlled output theta_tip = hub + defl
meas = [yhub; ytip; xi];

u = C * xc + D * meas;
u = max(min(u, umax), -umax);

xc = A * xc + B * meas;                   % controller state update (discrete)
xi = xi + Ts * (ref - tip);               % integral of tracking error
end
