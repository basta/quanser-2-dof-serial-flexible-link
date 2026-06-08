function u = orr_ctrl_lqg(yhub, ytip, ref, K, L, Ad, Bd, C_POS, umax) %#codegen
% ORR_CTRL_LQG  Python-designed LQG, as a Simulink MATLAB Function block.
%
%   Replaces Quanser's stage-1 full-state-feedback gain. Inputs are the two
%   MEASURED positions (encoder hub angle, strain-gauge tip deflection) and
%   the tip-angle reference [rad]. A steady-state Kalman PREDICTOR reconstructs
%   the velocities (the rig's filtered derivatives are NOT used, so the loop is
%   identical to the design in compare_methods_output.py); the LQR gain K acts
%   on the estimate with the reference injected as a state setpoint.
%
%   Mark K, L, Ad, Bd, C_POS, umax as *Parameter* arguments in the block's
%   Ports-and-Data-Manager and point them at the fields of the workspace
%   struct built by setup_orr_controllers.m  (lqg.K, lqg.L, ...). Set the
%   block sample time to Ts_ctrl (10 ms) and feed it through a Rate Transition
%   into the 500 Hz model.
%
%   See: report/export_controllers.py (writes orr_controllers.mat).

persistent xh
if isempty(xh)
    xh = zeros(4, 1);
end

ym  = [yhub; ytip];                       % the two measured positions
xss = [ref; 0; 0; 0];                     % state setpoint (offset-free via the
                                          %   plant's own rigid-body integrator)
u = -K * (xh - xss);
u = max(min(u, umax), -umax);             % same hard clip as the simulation

% steady-state Kalman predictor (eq. "eq-kalman" in the report)
xh = Ad * xh + Bd * u + L * (ym - C_POS * xh);
end
