%
%% SETUP_2DSFL_ROBOT
%
% Controller Design File for Quanser's 2-DOF Serial Flexible Link (2DSFL)
% Plant.
% SETUP_2DSFL_ROBOT sets the system parameters.
% It also designs two LQR controllers to minimize both flexible link
% oscillations. A decoupled approach is used.
%
% Copyright (C) 2011 Quanser Consulting Inc.
% Quanser Consulting Inc.
%
clear all
%
%% Watchdogs
% Turn on or off all four limit switches of the system. When enabled, it
% makes the controller stop as soon as one limit switch gets triggered.
% set it to 1 (to enable), or 0 (to disable)
LIMIT_SWITCHES_ENABLE = 1;  % all four limit switches are enabled
% LIMIT_SWITCHES_ENABLE = 0; % CAUTION: all four limit switches are disabled
% Turn on or off the safety watchdog on the oscillations of the first flexible link: 
% set it to 1 (to enable), or 0 (to disable)
DTH1_LIM_ENABLE = 1;       % safety watchdog #1 turned ON
% DTH1_LIM_ENABLE = 0;      % safety watchdog #1 turned OFF
% Safety Limits on the oscillations of the first flexible link (deg)
DTH1_MAX = 5.0;            % first flexible link maximum safety oscillation
DTH1_MIN = - DTH1_MAX;        % first flexible link minimum safety oscillation
% Turn on or off the safety watchdog on the oscillations of the second flexible link: 
% set it to 1 (to enable), or 0 (to disable)
DTH2_LIM_ENABLE = 1;       % safety watchdog #2 turned ON
% DTH2_LIM_ENABLE = 0;      % safety watchdog #2 turned OFF
% Safety Limits on the oscillations of the second flexible link (deg)
DTH2_MAX = 7.5;            % second flexible link maximum safety oscillation
DTH2_MIN = - DTH2_MAX;        % second flexible link minimum safety oscillation
%
%% System Analysis
% flag to carry out some system analysis for stage #1
SYS_ANALYSIS_1 = 'NO';
% SYS_ANALYSIS_1 = 'YES';
% flag to carry out some system analysis for stage #2
SYS_ANALYSIS_2 = 'NO';
% SYS_ANALYSIS_2 = 'YES';
%
%% Modeling
% Load 2DSLF model parameters
[L1, T1, J11, J12, B11, B12, Ks1, Ktg1, Kg1, L2, T2, J22, J21, B22, B21, Ks2, Ktg2, Kg2  ] = config_2dslf();
% Load sensor calibration gains
[K1_strain_b, K1_defl_b, K2_strain_b, K2_defl_b, KE_D1, KE_D2] = config_2dslf_sensors(L1, T1, L2, T2, Kg1, Kg2);
% For the following state vector: X1 = [ theta11; theta12; theta11_dot; theta12_dot ]
% State-Space Matrices for Stage 1: A1, B1, C1, and D1
eqn_2DSFL_Stage1;
A1 = A; B1 = B; C1 = eye( 4 ); D1 = zeros( 4, 1 );
% For the following state vector: X2 = [ theta21; theta22; theta21_dot; theta22_dot ]
% State-Space Matrices for Stage 2: A2, B2, C2, and D2
eqn_2DSFL_Stage2
A2 = A; B2 = B; C2 = eye( 4 ); D2 = zeros( 4, 1 );
%
%% Control Design
% Second-order low-pass filter (to obtain the angular speed)
wcf = 2 * pi * 40; % encoder signal filter cutting frequency (rad/s)
wcfa = 2 * pi * 2; % analog signal filter cutting frequency (rad/s)
zetaf = 0.9;        % filter damping ratio
% LQR Controller Tuning Parameters For The First Stage Of The 2DSFL Robot
% Q1 = diag([2500 1500 1.0 5.0 ]);
Q1 = diag([2500 1 1 100 ]);
R1 = 10;
% LQR Controller Tuning Parameters For The Second Stage Of The 2DSFL Robot
% Q2 = diag([2000 1500 0.75 7.0 ]);
Q2 = diag([2500 1 1 50 ]);
R2 = 10;
% calculate the LQR gain vector, K1
[ K1, S1, E1 ] = lqr( A1, B1, Q1, R1 );
% calculate the LQR gain vector, K2
[ K2, S2, E2 ] = lqr( A2, B2, Q2, R2 );
%
%% Display / System Analysis
% Display the calculated gains
disp( ' ' )
disp( [ 'K1(1) = ' num2str( K1(1) ) ' A/rad' ] )
disp( [ 'K1(2) = ' num2str( K1(2) ) ' A/rad' ] )
disp( [ 'K1(3) = ' num2str( K1(3) ) ' A.s/rad' ] )
disp( [ 'K1(4) = ' num2str( K1(4) ) ' A.s/rad' ] )
% Display the calculated gains
disp( ' ' )
disp( [ 'K2(1) = ' num2str( K2(1) ) ' A/rad' ] )
disp( [ 'K2(2) = ' num2str( K2(2) ) ' A/rad' ] )
disp( [ 'K2(3) = ' num2str( K2(3) ) ' A.s/rad' ] )
disp( [ 'K2(4) = ' num2str( K2(4) ) ' A.s/rad' ] )
%
% System Analysis
if strcmp( SYS_ANALYSIS_1, 'YES' ) || strcmp( SYS_ANALYSIS_2, 'YES' )
    d_2dsfl_sys_analysis
end
