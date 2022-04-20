% SISO
C1siso = [ 0 1 0 0 ]; % Y = [ theta12 ]
D1siso = [ 0 ];
% SISO
C2siso = [ 0 1 0 0 ]; % Y = [ theta22 ]
D2siso = [ 0 ];
%
% Reference gains
Kr1 = K1(1) + K1(2); % corresponds to the two first states
Kr2 = K2(1) + K2(2); % corresponds to the two first states
% or:
%Kr = - 1 / ( Csiso * inv( A_CL_FS ) * B );
% Closed-Loop State-Space Model for stage #1
A1_CL_FS = A1 - B1 * K1;
B1_CL_FS = B1 * Kr1; 
C1_CL = eye(4);
D1_CL = zeros(4, 1);
% Closed-Loop State-Space Model for stage #2
A2_CL_FS = A2 - B2 * K2;
B2_CL_FS = B2 * Kr2; 
C2_CL = eye(4);
D2_CL = zeros(4, 1);

% Open-Loop system for stage #1
TDSFL_1_SIMO_OL_SYS = ss( A1, B1, C1, D1, 'statename', ...
    { 'theta11' 'theta12' 'theta11_dot' 'theta12_dot' }, 'inputname', 'Im1', ...
    'outputname', { 'theta11' 'theta12' 'theta11_dot' 'theta12_dot' } );
TDSFL_1_SISO_OL_SYS = ss( A1, B1, C1siso, D1siso, 'statename', ...
    { 'theta11' 'theta12' 'theta11_dot' 'theta12_dot' }, 'inputname', 'Im1', ...
    'outputname', { 'theta12' } );
% Open-Loop system for stage #2
TDSFL_2_SIMO_OL_SYS = ss( A2, B2, C2, D2, 'statename', ...
    { 'theta21' 'theta22' 'theta21_dot' 'theta22_dot' }, 'inputname', 'Im2', ...
    'outputname', { 'theta21' 'theta22' 'theta21_dot' 'theta22_dot' } );
TDSFL_2_SISO_OL_SYS = ss( A2, B2, C2siso, D2siso, 'statename', ...
    { 'theta21' 'theta22' 'theta21_dot' 'theta22_dot' }, 'inputname', 'Im2', ...
    'outputname', { 'theta22' } );
% Closed-Loop System for stage #1: Full-State Feedback
TDSFL_1_SIMO_CL_SYS_FS = ss( A1_CL_FS, B1_CL_FS, C1_CL, D1_CL, ...
    'statename', { 'theta11' 'theta12' 'theta11_dot' 'theta12_dot' }, ...
    'inputname', 'Im1', 'outputname', { 'theta11' 'theta12' 'theta11_dot' 'theta12_dot' } );
% Closed-Loop System for stage #1: Partial-State Feedback
K1_PS = [ K1(1) 0 K1(3) 0 ];
A1_CL_PS = A1 - B1 * K1_PS;
B1_CL_PS = B1 * K1_PS(1);
TDSFL_1_SIMO_CL_SYS_PS = ss( A1_CL_PS, B1_CL_PS, C1_CL, D1_CL, ...
    'statename', { 'theta11' 'theta12' 'theta11_dot' 'theta12_dot' }, ...
    'inputname', 'Im1', 'outputname', { 'theta11' 'theta12' 'theta11_dot' 'theta12_dot' } );
% Closed-Loop System for stage #2: Full-State Feedback
TDSFL_2_SIMO_CL_SYS_FS = ss( A2_CL_FS, B2_CL_FS, C2_CL, D2_CL, ...
    'statename', { 'theta21' 'theta22' 'theta21_dot' 'theta22_dot' }, ...
    'inputname', 'Im2', 'outputname', { 'theta21' 'theta22' 'theta21_dot' 'theta22_dot' } );
% Closed-Loop System for stage #2: Partial-State Feedback
K2_PS = [ K2(1) 0 K2(3) 0 ];
A2_CL_PS = A2 - B2 * K2_PS;
B2_CL_PS = B2 * K2_PS(1);
TDSFL_2_SIMO_CL_SYS_PS = ss( A2_CL_PS, B2_CL_PS, C2_CL, D2_CL, ...
    'statename', { 'theta21' 'theta22' 'theta21_dot' 'theta22_dot' }, ...
    'inputname', 'Im2', 'outputname', { 'theta21' 'theta22' 'theta21_dot' 'theta22_dot' } );

% carry out some additional system analysis for stage #1
if strcmp( SYS_ANALYSIS_1, 'YES' )
    disp( ' ' )
    disp( '2DSFL Stage #1 System Analysis:' )
    disp( ' ' )
    % SISO models
    ULABELS = [ 'I_m_1' ];
    XLABELS = [ 'theta11 theta12 theta11_dot theta12_dot' ];
    YLABELS = [ 'theta12' ];
    % print the Open-Loop State-Space Matrices
    disp( 'Open-Loop System: stage #1' )
    printsys( A1, B1, C1siso, D1siso, ULABELS, YLABELS, XLABELS )
    % open-loop pole-zero locations: SIMO
    z_ol_1 = ss2zp( A1, B1, C1, D1, 1 )
    [ wn_ol_1, zeta_ol_1, p_ol_1 ] = damp(TDSFL_1_SIMO_OL_SYS )
    %disp( eig( A1 )' )
    % print the Closed-Loop State-Space Matrices
    disp( 'Closed-Loop System: stage #1' )
    printsys( A1_CL_FS, B1_CL_FS, C1siso, D1siso, ULABELS, YLABELS, XLABELS )
    % closed-loop pole-zero locations: SIMO
    z_cl_1 = ss2zp( A1_CL_FS, B1_CL_FS, C1, D1, 1 )
    [ wn_cl_fs_1, zeta_cl_fs_1, p_cl_fs_1 ] = damp(TDSFL_1_SIMO_CL_SYS_FS)
    % or: Closed-Loop eigenvalues
    CL_poles_1 = eig( A1_CL_FS )'; % = EIG_CL
end

% carry out some additional system analysis for stage #2
if strcmp( SYS_ANALYSIS_2, 'YES' )
    disp( ' ' )
    disp( '2DSFL Stage #2 System Analysis:' )
    disp( ' ' )
    % SISO models
    ULABELS = [ 'I_m_2' ];
    XLABELS = [ 'theta21 theta22 theta21_dot theta22_dot' ];
    YLABELS = [ 'theta22' ];
    % print the Open-Loop State-Space Matrices
    disp( 'Open-Loop System: stage #2' )
    printsys( A2, B2, C2siso, D2siso, ULABELS, YLABELS, XLABELS )
    % open-loop pole-zero locations: SIMO
    z_ol_2 = ss2zp( A2, B2, C2, D2, 1 )
    [ wn_ol_2, zeta_ol_2, p_ol_2 ] = damp(TDSFL_2_SIMO_OL_SYS )
    %disp( eig( A2 )' )
    % print the Closed-Loop State-Space Matrices
    disp( 'Closed-Loop System: stage #2' )
    printsys( A2_CL_FS, B2_CL_FS, C2siso, D2siso, ULABELS, YLABELS, XLABELS )
    % closed-loop pole-zero locations: SIMO
    z_cl_2 = ss2zp( A2_CL_FS, B2_CL_FS, C2, D2, 1 )
    [ wn_cl_fs_2, zeta_cl_fs_2, p_cl_fs_2 ] = damp(TDSFL_2_SIMO_CL_SYS_FS)
    % or: Closed-Loop eigenvalues
    CL_poles_2 = eig( A2_CL_FS )'; % = EIG_CL
end