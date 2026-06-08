function u = orr_ctrl_mpc(yhub, ytip, ref, ...
        Ad, Bd, C_POS, L, Hqp, M_f, w_f, Gth, Pth, umax, defl_lim, rho) %#codegen
% ORR_CTRL_MPC  Python-designed output-feedback MPC, condensed to a dense QP.
%
%   Same Kalman estimate as the LQG block; the distinguishing feature is the
%   SOFT tip-deflection constraint |theta_tip| <= defl_lim (slack s, penalty
%   rho). The horizon QP is condensed offline (report/export_controllers.py)
%   into  min 0.5 z'Hz + f'z  s.t.  Az <= b,  with z = [U(Np); s(Np)], and is
%   solved on the target by mpcActiveSetSolver (MPC Toolbox, codegen-safe).
%
%   Mark every matrix/scalar after `ref` as a *Parameter* argument, pointing
%   at the workspace struct fields mpc.Ad, mpc.Bd, ... built by
%   setup_orr_controllers.m. Run at Ts_ctrl (10 ms) behind a Rate Transition.
%
%   Requires Model Predictive Control Toolbox (mpcActiveSetSolver). If it is
%   unavailable, deploy LQG + H-infinity only and keep MPC as the sim-only
%   reference (the report notes this).

Np = size(Hqp, 1);

persistent xh Linv Acon opt iA
if isempty(xh)
    xh = zeros(4, 1);
    % constant dense-QP Hessian: blkdiag(Hqp, eps*I) (eps keeps it PD for chol)
    H = zeros(2 * Np, 2 * Np);
    H(1:Np, 1:Np) = (Hqp + Hqp') / 2;            % symmetrise
    H(Np + 1:end, Np + 1:end) = 1e-6 * eye(Np);
    Linv = inv(chol(H, 'lower'));
    % constant inequality matrix A (b is rebuilt each step)
    I = eye(Np);
    Acon = [ I,    zeros(Np);                    % U <= umax
            -I,    zeros(Np);                    % -U <= umax
             Gth, -I;                            % Gth U - s <= defl_lim - Pth xh
            -Gth, -I;                            % -Gth U - s <= defl_lim + Pth xh
             zeros(Np), -I];                     % -s <= 0  (s >= 0)
    opt = mpcActiveSetOptions;
    iA  = false(5 * Np, 1);
end

ym  = [yhub; ytip];

% --- QP linear term and right-hand side from the current estimate ---
f = [M_f * xh + w_f * ref;  rho * ones(Np, 1)];
b = [ umax * ones(Np, 1);
      umax * ones(Np, 1);
      defl_lim - Pth * xh;
      defl_lim + Pth * xh;
      zeros(Np, 1)];

[z, status, iA] = mpcActiveSetSolver(Linv, f, Acon, b, ...
                                     zeros(0, 2 * Np), zeros(0, 1), iA, opt);
if status > 0
    u = z(1);                                    % first move of the optimal U
else
    u = -0.0;                                    % infeasible/failed: coast (rare)
end
u = max(min(u, umax), -umax);

% same Kalman predictor as the LQG block
xh = Ad * xh + Bd * u + L * (ym - C_POS * xh);
end
