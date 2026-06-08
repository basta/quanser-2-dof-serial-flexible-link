%% SETUP_ORR_CONTROLLERS
%  Load the Python-designed LQG / output-MPC / H-infinity controllers into the
%  base workspace so the MATLAB Function blocks orr_ctrl_*.m can reference their
%  matrices as Parameter arguments. Run this AFTER setup_2dsfl (which loads the
%  plant parameters and the Quanser LQR baseline).
%
%  The .mat is produced by:  .venv/bin/python report/export_controllers.py
%  Re-run that whenever the designs in compare_methods_output.py change, then
%  re-run this script.
%
%  Workspace variables created:
%     Ts_ctrl            controller sample time [s]  (10 ms)
%     C_TIP, C_POS       output maps
%     lqg.{K,L,Ad,Bd,C_POS,umax}
%     hinf.{A,B,C,D,umax,gamma}
%     mpc.{Ad,Bd,C_POS,L,Hqp,M_f,w_f,Gth,Pth,umax,defl_lim,rho,Np}

here = fileparts(mfilename('fullpath'));
S = load(fullfile(here, 'orr_controllers.mat'));

Ts_ctrl = S.Ts_ctrl;
C_TIP   = S.C_TIP;
C_POS   = S.C_POS;
lqg     = S.lqg;
hinf    = S.hinf;
mpc     = S.mpc;

fprintf('[orr] controllers loaded.  Ts_ctrl = %g ms\n', Ts_ctrl * 1e3);
fprintf('[orr]   LQG  : K(%dx%d), L(%dx%d)\n', size(lqg.K,1),size(lqg.K,2), size(lqg.L,1),size(lqg.L,2));
fprintf('[orr]   Hinf : order %d, gamma = %.3f\n', size(hinf.A,1), hinf.gamma);
fprintf('[orr]   MPC  : Np = %d, defl_lim = %.2f deg\n', mpc.Np, rad2deg(mpc.defl_lim));
fprintf('[orr] Wire ONE orr_ctrl_* block into q_2dsfl_pos_cntrl.slx (see WIRING.md),\n');
fprintf('[orr] set its sample time to Ts_ctrl, then run run_lab_experiments.m\n');
fprintf('[orr] with controller_name = ''lqg'' | ''hinf'' | ''mpc''.\n');
