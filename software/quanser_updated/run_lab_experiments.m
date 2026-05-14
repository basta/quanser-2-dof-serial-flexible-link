%% =====================================================================
%  Flexible Link -- Automated experiment runner
%  ---------------------------------------------------------------------
%  WORKFLOW:
%    1) Open q_2dsfl_pos_cntrl.slx and replace the stage-1 hub reference
%       block with a "Repeating Sequence Stair" (Sources library).
%       Configure it as the PREP section below prints.
%    2) In each scope you want to log:
%         settings -> Logging -> tick "Log data to workspace"
%         Save format: "Structure With Time"
%         Variable names (exactly):
%           data_theta11   data_theta12   data_strain1   data_strain2
%    3) Run setup_2dsfl  (Quanser's parameter script). Required.
%    4) Run the PREP cell of this script. It will tell you the External
%       Mode Duration in samples and the Repeating Sequence values.
%    5) Set External Mode -> Signal & Triggering -> Duration to the
%       printed number of samples.
%    6) Click Monitor & Tune. Wait for the run to finish naturally.
%    7) Run the SAVE cell. It validates the recording, slices it into
%       per-amplitude .mat files in ./data/, named with controller_name.
%
%  This script is safe to re-run: PREP only prints, SAVE only writes
%  inside out_dir.
%  =====================================================================

%% ---------- CONFIG (edit me) ----------
amps_deg        = [0 5 -5 10 -10 20 -20 30 -30 0];   % step targets [deg]
seg_dur         = 4;                                  % seconds per segment
sample_rate_Hz  = 1000;                               % match Simulink fixed step
controller_name = 'lqr';                              % 'lqr' | 'hinf' | 'mpc'
out_dir         = fullfile(pwd, 'data');              % output directory
% --------------------------------------


%% ---------- PREP: pre-run checks + instructions ----------
fprintf('\n===== PREP =====\n');

% sanity check the config
assert(isnumeric(amps_deg) && ~isempty(amps_deg), 'amps_deg must be a non-empty numeric vector.');
assert(isnumeric(seg_dur)  && isscalar(seg_dur)  && seg_dur > 0,  'seg_dur must be a positive scalar.');
assert(isnumeric(sample_rate_Hz) && sample_rate_Hz > 0,           'sample_rate_Hz must be positive.');
assert(ischar(controller_name) || isstring(controller_name),     'controller_name must be a string.');

total_dur_s   = numel(amps_deg) * seg_dur;
duration_samp = round(total_dur_s * sample_rate_Hz);

% Check: setup_2dsfl outputs present
required_vars = {'A1','B1','K1','A2','B2','K2'};
missing = {};
for vi = 1:numel(required_vars)
    if ~evalin('base', sprintf('exist(''%s'',''var'')==1', required_vars{vi}))
        missing{end+1} = required_vars{vi}; %#ok<SAGROW>
    end
end
if ~isempty(missing)
    fprintf('[WARN] Missing workspace vars: %s\n', strjoin(missing, ', '));
    fprintf('       Run  >> setup_2dsfl  before launching the experiment.\n');
else
    fprintf('[OK]   setup_2dsfl outputs present.\n');
end

% Safety: amplitude bounds
if max(abs(amps_deg)) > 35
    warning('Amplitudes exceed 35 deg. Verify this is safe on the rig.');
end
fprintf('[OK]   Amplitude vector: %s deg\n', mat2str(amps_deg));

% Output dir
if ~exist(out_dir, 'dir')
    mkdir(out_dir);
    fprintf('[OK]   Created output dir: %s\n', out_dir);
else
    fprintf('[OK]   Output dir exists : %s\n', out_dir);
end

% Print instructions for the Simulink side
fprintf('\n--- Configure Repeating Sequence Stair (stage-1 hub reference) ---\n');
fprintf('  Vector of output values : deg2rad(%s)\n', mat2str(amps_deg));
fprintf('  Sample time             : %g\n', seg_dur);
fprintf('\n--- Configure External Mode ---\n');
fprintf('  Signal & Triggering -> Duration : %d samples (at %d Hz)\n', ...
    duration_samp, sample_rate_Hz);
fprintf('\nTotal run length        : %.1f s\n', total_dur_s);
fprintf('Controller label        : %s\n', controller_name);
fprintf('\nReady? Click Monitor & Tune and wait for the full run.\n');
fprintf('================\n\n');


%% ---------- SAVE: run AFTER experiment ends ----------
fprintf('\n===== SAVE =====\n');

% Check logged variables exist
required_scope_vars = {'data_theta11','data_theta12','data_strain1','data_strain2'};
missing = {};
for vi = 1:numel(required_scope_vars)
    if ~evalin('base', sprintf('exist(''%s'',''var'')==1', required_scope_vars{vi}))
        missing{end+1} = required_scope_vars{vi}; %#ok<SAGROW>
    end
end
if ~isempty(missing)
    error(['Missing scope variables: %s\n' ...
           'In each scope:  settings -> Logging -> tick "Log data to workspace",\n' ...
           'set the variable name accordingly, and Save format "Structure With Time".'], ...
           strjoin(missing, ', '));
end

% Pull signals (Structure With Time)
try
    t   = data_theta11.time;
    y11 = data_theta11.signals.values;
    y12 = data_theta12.signals.values;
    s1  = data_strain1.signals.values;
    s2  = data_strain2.signals.values;
catch ME
    error(['Could not read .time / .signals.values from a scope variable.\n' ...
           'Make sure scope Save format is "Structure With Time".\n' ...
           'Original error: %s'], ME.message);
end

% Sanity: lengths consistent
N = numel(t);
lens = [numel(y11), numel(y12), numel(s1), numel(s2)];
if any(lens ~= N)
    error('Logged signals have mismatched lengths: t=%d, others=%s', N, mat2str(lens));
end
if N < 10
    error('Only %d samples logged. Did External Mode Duration get set?', N);
end

% Sanity: captured the whole run
captured_dur = t(end) - t(1);
if captured_dur < 0.95 * total_dur_s
    warning('Captured %.2f s but expected %.2f s. Signal & Triggering Duration likely too small.', ...
        captured_dur, total_dur_s);
end

% Slice and save, handling repeated amplitudes by suffixing run index
run_count = containers.Map('KeyType','int32','ValueType','int32');
n_saved   = 0;

for k = 1:numel(amps_deg)
    t0  = (k-1) * seg_dur;
    t1  = k * seg_dur;
    idx = (t >= t0) & (t < t1);

    if nnz(idx) < 10
        warning('Segment %d (%d deg) has only %d samples -- skipping.', ...
            k, amps_deg(k), nnz(idx));
        continue;
    end

    amp_key = int32(amps_deg(k));
    if isKey(run_count, amp_key)
        run_count(amp_key) = run_count(amp_key) + 1;
    else
        run_count(amp_key) = 1;
    end
    run_idx = run_count(amp_key);

    seg = struct();
    seg.time            = t(idx) - t0;
    seg.theta11         = y11(idx);
    seg.theta12         = y12(idx);
    seg.strain1         = s1(idx);
    seg.strain2         = s2(idx);
    seg.ref_deg         = amps_deg(k);
    seg.controller      = controller_name;
    seg.sample_rate_Hz  = sample_rate_Hz;
    seg.seg_dur_s       = seg_dur;

    sign_tag = '';
    if amps_deg(k) < 0, sign_tag = 'neg_'; end
    fname = sprintf('%s_step_%s%ddeg_run%02d.mat', ...
        controller_name, sign_tag, abs(amps_deg(k)), run_idx);
    full  = fullfile(out_dir, fname);
    save(full, '-struct', 'seg', '-v7');
    fprintf('saved  %s  (%d samples)\n', fname, nnz(idx));
    n_saved = n_saved + 1;
end

fprintf('Done. %d files written to %s\n', n_saved, out_dir);
fprintf('================\n');
