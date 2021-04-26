%% Data Files
% rm: comment out the data files you don't want to view
% Full-State Feedback
load('data_fsf_th11.mat');
load('data_fsf_th12.mat');
load('data_fsf_th21.mat');
load('data_fsf_th22.mat');
load('data_fsf_Im1.mat');
load('data_fsf_Im2.mat');
%
% Partial-State Feedback
% load('data_psf_th11.mat');
% load('data_psf_th12.mat');
% load('data_psf_th21.mat');
% load('data_psf_th22.mat');
% load('data_psf_Im1.mat');
% load('data_psf_Im2.mat');
%
%% Load data
% Stage 1
t = data_th11(:,1);
th11_r = data_th11(:,2); % stage 1 reference angle
th11 = data_th11(:,3); % stage 1 measured angle
th12 = data_th12(:,3); % link 1 measured angle
Im1_r = data_Im1(:,2); % reference motor #1 current
Im1 = data_Im1(:,3); % measured motor #1 current
%
% Stage 2
th21_r = data_th21(:,2); % stage 2 reference angle
th21 = data_th21(:,3); % stage 2 measured angle
th22 = data_th22(:,3); % link 2 measured angle
Im2_r = data_Im2(:,2); % reference motor #2 current
Im2 = data_Im2(:,3); % measured motor #2 current

%% Plot
% Stage 1
figure(1)
subplot(3,1,1)
plot(t,th11_r,'b-.',t,th11,'r-');
ylabel('\theta_{11} (deg)');
subplot(3,1,2)
plot(t,th12,'r-');
axis([0 20 -2.5 2.5]);
ylabel('\theta_{12} (deg)');
subplot(3,1,3)
plot(t,Im1_r,'b-.',t,Im1,'r-');
ylabel('I_{m1} (A)');
xlabel('time (s)');
%
% Stage 2
figure(2)
subplot(3,1,1)
plot(t,th21_r,'b-.',t,th21,'r-');
axis([0 20 -12.5 12.5]);
ylabel('\theta_{21} (deg)');
subplot(3,1,2)
plot(t,th22,'r-');
axis([0 20 -2.5 2.5]);
ylabel('\theta_{22} (deg)');
subplot(3,1,3)
plot(t,Im2_r,'b-.',t,Im2,'r-');
ylabel('I_{m2} (A)');
xlabel('time (s)');
