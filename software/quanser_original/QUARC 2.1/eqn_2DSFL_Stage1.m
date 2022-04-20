% Matlab equation file: "eqn_2DSFL_Stage1.m"
% Open-Loop State-Space Matrices: A, B, C, and D
% for the Quanser 2-DOF Serial Flexible Link Robot (First Stage) Experiment.

A( 1, 1 ) = 0;
A( 1, 2 ) = 0;
A( 1, 3 ) = 1;
A( 1, 4 ) = 0;
A( 2, 1 ) = 0;
A( 2, 2 ) = 0;
A( 2, 3 ) = 0;
A( 2, 4 ) = 1;
A( 3, 1 ) = 0;
A( 3, 2 ) = Ks1/J11;
A( 3, 3 ) = -B11/J11;
A( 3, 4 ) = B12/J11;
A( 4, 1 ) = 0;
A( 4, 2 ) = -(J11+J12)/J11/J12*Ks1;
A( 4, 3 ) = B11/J11;
A( 4, 4 ) = -B12*(J11+J12)/J11/J12;

B( 1, 1 ) = 0;
B( 2, 1 ) = 0;
B( 3, 1 ) = Ktg1/J11;
B( 4, 1 ) = -Ktg1/J11;

C( 1, 1 ) = 1;
C( 1, 2 ) = 0;
C( 1, 3 ) = 0;
C( 1, 4 ) = 0;
C( 2, 1 ) = 0;
C( 2, 2 ) = 1;
C( 2, 3 ) = 0;
C( 2, 4 ) = 0;
C( 3, 1 ) = 0;
C( 3, 2 ) = 0;
C( 3, 3 ) = 1;
C( 3, 4 ) = 0;
C( 4, 1 ) = 0;
C( 4, 2 ) = 0;
C( 4, 3 ) = 0;
C( 4, 4 ) = 1;

D( 1, 1 ) = 0;
D( 2, 1 ) = 0;
D( 3, 1 ) = 0;
D( 4, 1 ) = 0;
