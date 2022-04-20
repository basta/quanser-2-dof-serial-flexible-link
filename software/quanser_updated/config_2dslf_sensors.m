function [K1_strain_b, K1_defl_b, K2_strain_b, K2_defl_b, KE_D1, KE_D2] = config_2dslf_sensors(L1, T1, L2, T2, Kg1, Kg2)
% estimated base strain gauge calibration constant (strain/V)
K1_strain_b = 1.286e-4;
% base strain to angular tip deflection conversion constant (rad/strain)
K1_defl_b = 2 / 3 * L1 / T1;
% estimated base strain gauge calibration constant (strain/V)
K2_strain_b = 1.235e-4;
% base strain to angular tip deflection conversion constant (rad/strain)
K2_defl_b = 2 / 3 * L2 / T2;
% Motor (#1 and #2) Encoder Resolution (before gear ratios) (rad/count)
K_ENC = 2 * pi / ( 4 * 1024 ); % = 0.0015 rad/count
% Drive #1 (after gearbox) Encoder Sensitivity (rad/count)
KE_D1 = K_ENC / Kg1; % = 1.5340e-005
% Drive #2 (after gearbox) Encoder Sensitivity (rad/count)
KE_D2 = K_ENC / Kg2; % = 1.9175e-005
%