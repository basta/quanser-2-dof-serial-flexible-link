function [L1, T1, J11, J12, B11, B12, Ks1, Ktg1, Kg1, L2, T2, J22, J21, B22, B21, Ks2, Ktg2, Kg2 ] = config_2dslf()

% AMPAQ maximum output voltage (V)
V_MAX = 28;
% Me: modulus of elasticity (a.k.a. Young's modulus) for steel (Pa=N/m^2)
% 30e6 PSI = 2.068427e+011 Pa
Me = 2.068427e11;
% from Inch to Meter conversion factor (m/in)
K_IN2M = 0.0254;
% amplifier strain gauge calibration constant (strain/V)
K_strain = 1.35e-4;
%
%% Stage 1 Stiffness and Damping
% first flexible link specifications: width = 3.0", thickness = 0.050"
% link width = 3.0 in, thickness = 0.050 in
% beam width (m)
X1 = 3.0 * K_IN2M;
% beam thickness (m)
T1 = 0.050 * K_IN2M;
% beam length: distance from tip load to base strain gauge (m)
L1 = 0.202;
% First Flexible Link Torsional Stiffness (N.m/rad)
Ks1_th = Me * X1 * T1^3 / (4 * L1); % = 40.0
% Ks1_exp = 27.0; % from torque impulse test - old
% Ks1 = Ks1_exp;
Ks1 = Ks1_th;
% Equivalent Viscous Damping Coefficient as seen at the drive #1 output shaft (N.m.s/rad)
B11 = 4.0;  % adjusted from open-loop step response 
% First Flexible Link (with full load) Equivalent Viscous Damping Coefficient
% as seen at its rotation axis (N.m.s/rad)
B12 = 0; % neglected
% 
%% Stage 2 Stiffness and Damping
% second flexible link specifications: width = 1.5", thickness = 0.035"
% link width = 1.5 in, thickness = 0.035 in
% beam width (m)
X2 = 1.5 * K_IN2M;
% beam thickness (m)
T2 = 0.035 * K_IN2M;
% beam length: distance from tip load to base strain gauge (m)
L2 = 0.20185;
% Second Flexible Link Torsional Stiffness (N.m/rad)
Ks2_th = Me * X2 * T2^3 / (4 * L2); % = 6.9
% Ks2_exp = 2.5;
% Ks2 = Ks2_exp;
Ks2 = Ks2_th;
% Equivalent Viscous Damping Coefficient as seen at the drive #2 output shaft (N.m.s/rad)
B21 = 1.5; % adjusted from open-loop step response 
% Second Flexible Link Equivalent Viscous Damping Coefficient
% as seen at its rotation axis (N.m.s/rad)
B22 = 0.085608; % from torque impulse test
%
%% Stage 1 Specifications
% Harmonic drive #1 gear ratio
Kg1 = 100;
% Motor #1 back-EMF constant (V.s/rad)
Km1 = 0.119;
% Motor #2 torque constant (N.m/A)
Kt1 = Km1;
% Motor #1 torque constant at the harmonic drive #1 shaft output (N.m/A)
Ktg1 = 0.75 * Kt1 * Kg1; % < Kt1 * Kg1 == 8.925
% Rotor Moment Of Inertia at the motor #1 shaft (kg.m^2)
Jm1 = 6.28e-6;
% Equivalent Rotor Moment Of Inertia at the harmonic drive #1 shaft output (kg.m^2)
Jeqm1 = Kg1^2 * Jm1;
% Moment Of Inertia of the motor fixture assembly (kg.m^2)
J1fix = 0.00073616; % obtained from CAD model
% Equivalent Inertia of the loaded drive #1 system (kg.m^2)
J11 = Jeqm1 + J1fix; % = 0.0109
% link #1 end-effector mass (kg)
M12 = 1.578;
% Equivalent Inertia of the First Flexible Link end-effector loaded with
% the second serial link mechanism (kg.m^2)
J12_cad = 0.18028257; % obtained from CAD model (wrt Z1)
J12 = J12_cad - M12 * 0.079^2; % = 0.17043
% drive #1 maximum allowable velocity at the load shaft (rad/s)
W1_MAX = V_MAX / Km1 / Kg1; % = 2.35 = 134.6 deg/s^2
% drive #1 maximum allowable torque at the load shaft (N.m)
% corresponding to a maximum joint deflection DTHETA1_MAX (rad)
DTHETA1_MAX = 2 * pi / 180;
T1_MAX = Ks1 * DTHETA1_MAX;
% drive #1 maximum allowable acceleration at the load shaft (rad/s^2)
W1DOT_MAX = T1_MAX / J12; % from dtheta1_max: = 4.45 rad/s^2
%
%% Stage 2 Specifications
% Harmonic drive #2 gear ratio
Kg2 = 50;
% Motor #2 back-EMF constant (V.s/rad)
Km2 = 0.0232;
% Motor #2 torque constant (N.m/A)
Kt2 = Km2;
% Motor #2 torque constant at the harmonic drive #2 shaft output (N.m/A)
Ktg2 = 0.75 * Kt2 * Kg2; % < Kt2 * Kg2
% Rotor Moment Of Inertia at the motor #2 shaft (kg.m^2)
Jm2 = 1.03e-6;
% Equivalent Rotor Moment Of Inertia at the harmonic drive #2 shaft output (kg.m^2)
Jeqm2 = Kg2^2 * Jm2;
% Moment Of Inertia of the motor fixture assembly (kg.m^2)
J2fix = 0.00044455; % obtained from CAD model
% Equivalent Inertia of the loaded drive #2 system (kg.m^2)
J21 = Jeqm2 + J2fix; % = 0.0090
% link #2 end-effector mass (kg)
M22 = 0.157;
% Equivalent Inertia of the Second Flexible Link end-effector system (kg.m^2)
J22_cad = 0.00750070;  % obtained from CAD model (wrt Z2)
J22_cad = J22_cad - M22 * 0.079^2; % = 0.0065
L22 = 0.202;
% link #2 end-effector heigth (m)
a22 = 44.5e-3;
% link #2 end-effector thickness (m)
b22 = 22.4e-3;
J22_meas = M22 * (a22^2 + b22^2) / 12 + M22 * L22^2;
J22 = J22_meas; % = 0.0064
% drive #2 maximum allowable velocity at the load shaft (rad/s)
W2_MAX = V_MAX / Km2 / Kg2; % = 14.96
% drive #2 maximum allowable torque at the load shaft (N.m)
% corresponding to a maximum joint deflection DTHETA2_MAX (rad)
DTHETA2_MAX = DTHETA1_MAX;
T2_MAX = Ks2 * DTHETA2_MAX;
% drive #2 maximum allowable acceleration at the load shaft (rad/s^2)
W2DOT_MAX = T2_MAX / J22; % from dtheta2_max: = 37.23 rad/s^2
%