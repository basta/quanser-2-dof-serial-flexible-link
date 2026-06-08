%% BUILD_ORR_MODELS
%  Generate ready-to-run rig models for the Python-designed LQG and H-infinity
%  controllers by surgically swapping Quanser's stage-1 LQR gain for a single
%  Discrete State-Space block (observer + gain + integrator folded into one A/B
%  /C/D, exported by report/export_controllers.py and verified there against the
%  report simulation). Stage-2 and ALL safety / HIL / scope wiring is untouched.
%
%  Produces, next to the original model:
%     q_2dsfl_orr_lqg.slx
%     q_2dsfl_orr_hinf.slx
%
%  Usage:
%     setup_2dsfl            % plant params + safety limits (REQUIRED first)
%     build_orr_models       % writes the two models
%  then open one, set the Repeating Sequence Stair (run_lab_experiments.m PREP),
%  Build, Monitor & Tune. (MPC needs the online QP solver -- see WIRING.md.)
%
%  The swap, by exact block name (discovered from the .slx):
%     Mux1            -> [theta11; theta12; theta11_dot; theta12_dot]  (state)
%     Stage 1 Setpoint-> [r; r; 0; 0]                                  (ref)
%   We tap both, Mux them into v=[state(4); setpoint(4)], feed the SS block, and
%   route its output into 'Im_r1: Saturation' in place of 'LQR Gain 1'.

here = fileparts(mfilename('fullpath'));
src  = fullfile(here, 'q_2dsfl_pos_cntrl.slx');
S    = load(fullfile(here, 'orr_controllers.mat'));
assert(isfile(src), 'q_2dsfl_pos_cntrl.slx not found next to this script.');

designs = struct( ...
    'name', {'lqg', 'hinf'}, ...
    'ss',   {S.lqg_ss, S.hinf_ss});

for di = 1:numel(designs)
    name = designs(di).name;
    ss   = designs(di).ss;
    mdl  = sprintf('q_2dsfl_orr_%s', name);
    dst  = fullfile(here, [mdl '.slx']);

    if bdIsLoaded(mdl), close_system(mdl, 0); end
    if isfile(dst), delete(dst); end
    copyfile(src, dst);
    load_system(dst);

    % --- new blocks -------------------------------------------------------
    muxPath = [mdl '/ORR Mux'];
    ssPath  = [mdl '/ORR ' upper(name)];
    add_block('simulink/Signal Routing/Mux', muxPath, ...
        'Inputs', '2', 'Position', [330 20 335 80]);
    add_block('simulink/Discrete/Discrete State-Space', ssPath, ...
        'A', mat2str(ss.A, 16), 'B', mat2str(ss.B, 16), ...
        'C', mat2str(ss.C, 16), 'D', mat2str(ss.D, 16), ...
        'X0', '0', 'SampleTime', mat2str(S.Ts_ctrl), ...
        'Position', [380 25 460 75]);

    % --- rewire -----------------------------------------------------------
    % drop the old gain -> saturation link and terminate the dangling gain out
    delete_line(mdl, 'LQR Gain 1/1', 'Im_r1: Saturation/1');
    add_block('simulink/Sinks/Terminator', [mdl '/ORR Old Gain Term'], ...
        'Position', [330 120 350 140]);
    add_line(mdl, 'LQR Gain 1/1', 'ORR Old Gain Term/1', 'autorouting', 'on');

    % tap the existing state + setpoint signals (branches), feed the SS block
    add_line(mdl, 'Mux1/1',           'ORR Mux/1', 'autorouting', 'on');
    add_line(mdl, 'Stage 1 Setpoint/1','ORR Mux/2', 'autorouting', 'on');
    add_line(mdl, 'ORR Mux/1',        ['ORR ' upper(name) '/1'], 'autorouting', 'on');
    add_line(mdl, ['ORR ' upper(name) '/1'], 'Im_r1: Saturation/1', 'autorouting', 'on');

    % --- multirate: 10 ms controller inside the 2 ms (ode1) model --------
    % The stock model is multi-tasking with MultiTaskRateTransMsg=error, so a
    % 10 ms -> 2 ms transition (controller out -> saturation -> continuous
    % plant) is rejected. Single-tasking handles the transfer automatically
    % (the controller simply runs every 5th base step); also auto-insert any
    % discrete-discrete rate transitions.
    set_param(mdl, 'AutoInsertRateTranBlk', 'on');
    try
        set_param(mdl, 'EnableMultiTasking', 'off');   % single-tasking
    catch
        set_param(mdl, 'SolverMode', 'SingleTasking'); % older Simulink
    end

    save_system(mdl);
    close_system(mdl, 0);
    fprintf('[orr] wrote %s.slx  (%s, %d controller states)\n', ...
        mdl, name, size(ss.A, 1));
end

fprintf(['\n[orr] Done. Open q_2dsfl_orr_lqg.slx, set the Repeating Sequence ' ...
         'Stair\n      inside ''Stage 1 Setpoint'' per run_lab_experiments.m, ' ...
         'then Build + Monitor & Tune.\n']);
