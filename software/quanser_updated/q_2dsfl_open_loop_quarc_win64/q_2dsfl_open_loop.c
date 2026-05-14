/*
 * q_2dsfl_open_loop.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "q_2dsfl_open_loop".
 *
 * Model version              : 28.1
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Thu May 14 15:35:28 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "q_2dsfl_open_loop.h"
#include "q_2dsfl_open_loop_private.h"
#include "q_2dsfl_open_loop_dt.h"

/* Block signals (default storage) */
B_q_2dsfl_open_loop_T q_2dsfl_open_loop_B;

/* Continuous states */
X_q_2dsfl_open_loop_T q_2dsfl_open_loop_X;

/* Block states (default storage) */
DW_q_2dsfl_open_loop_T q_2dsfl_open_loop_DW;

/* Real-time model */
static RT_MODEL_q_2dsfl_open_loop_T q_2dsfl_open_loop_M_;
RT_MODEL_q_2dsfl_open_loop_T *const q_2dsfl_open_loop_M = &q_2dsfl_open_loop_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 20;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  q_2dsfl_open_loop_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/*
 * System initialize for atomic system:
 *    '<S1>/Bias Removal'
 *    '<S2>/Bias Removal'
 */
void q_2dsfl_open_l_BiasRemoval_Init(B_BiasRemoval_q_2dsfl_open_lo_T *localB,
  DW_BiasRemoval_q_2dsfl_open_l_T *localDW, P_BiasRemoval_q_2dsfl_open_lo_T
  *localP)
{
  /* SystemInitialize for Enabled SubSystem: '<S9>/Enabled Moving Average' */
  /* InitializeConditions for UnitDelay: '<S16>/Unit Delay' */
  localDW->UnitDelay_DSTATE = localP->UnitDelay_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S12>/Sum( k=1,n-1, x(k) )' */
  localDW->Sumk1n1xk_DSTATE = localP->Sumk1n1xk_InitialCondition;

  /* End of SystemInitialize for SubSystem: '<S9>/Enabled Moving Average' */

  /* SystemInitialize for IfAction SubSystem: '<S9>/Switch Case Action Subsystem' */
  /* SystemInitialize for Outport: '<S13>/zero' incorporates:
   *  Constant: '<S13>/Constant'
   */
  localB->Constant = localP->zero_Y0;

  /* End of SystemInitialize for SubSystem: '<S9>/Switch Case Action Subsystem' */

  /* SystemInitialize for IfAction SubSystem: '<S9>/Switch Case Action Subsystem1' */
  /* SystemInitialize for Outport: '<S14>/Vbiased' incorporates:
   *  Inport: '<S14>/Vin'
   */
  localB->Vin = localP->Vbiased_Y0;

  /* End of SystemInitialize for SubSystem: '<S9>/Switch Case Action Subsystem1' */

  /* SystemInitialize for IfAction SubSystem: '<S9>/Switch Case Action Subsystem2' */
  /* SystemInitialize for Outport: '<S15>/Vunbiased' incorporates:
   *  Inport: '<S15>/V-Vavg'
   */
  localB->VVavg = localP->Vunbiased_Y0;

  /* End of SystemInitialize for SubSystem: '<S9>/Switch Case Action Subsystem2' */
}

/*
 * Start for atomic system:
 *    '<S1>/Bias Removal'
 *    '<S2>/Bias Removal'
 */
void q_2dsfl_open__BiasRemoval_Start(DW_BiasRemoval_q_2dsfl_open_l_T *localDW)
{
  /* Start for Enabled SubSystem: '<S9>/Enabled Moving Average' */
  localDW->EnabledMovingAverage_MODE = false;

  /* End of Start for SubSystem: '<S9>/Enabled Moving Average' */

  /* Start for SwitchCase: '<S9>/Switch Case' */
  localDW->SwitchCase_ActiveSubsystem = -1;
}

/*
 * Outputs for atomic system:
 *    '<S1>/Bias Removal'
 *    '<S2>/Bias Removal'
 */
void q_2dsfl_open_loop_BiasRemoval(RT_MODEL_q_2dsfl_open_loop_T * const
  q_2dsfl_open_loop_M, real_T rtu_V, real_T rtp_switch_id, real_T rtp_start_time,
  real_T rtp_end_time, B_BiasRemoval_q_2dsfl_open_lo_T *localB,
  DW_BiasRemoval_q_2dsfl_open_l_T *localDW, P_BiasRemoval_q_2dsfl_open_lo_T
  *localP)
{
  real_T rtb_Stepend_time;
  real_T rtb_Sum_o;
  real_T tmp;
  int8_T rtAction;
  int8_T rtPrevAction;

  /* Step: '<S9>/Step: end_time' incorporates:
   *  Step: '<S9>/Step: start_time'
   */
  tmp = q_2dsfl_open_loop_M->Timing.t[1];
  if (tmp < rtp_end_time) {
    rtb_Stepend_time = localP->Stepend_time_Y0;
  } else {
    rtb_Stepend_time = localP->Stepend_time_YFinal;
  }

  /* End of Step: '<S9>/Step: end_time' */

  /* Step: '<S9>/Step: start_time' */
  if (tmp < rtp_start_time) {
    tmp = localP->Stepstart_time_Y0;
  } else {
    tmp = localP->Stepstart_time_YFinal;
  }

  /* Outputs for Enabled SubSystem: '<S9>/Enabled Moving Average' incorporates:
   *  EnablePort: '<S12>/Enable'
   */
  /* Logic: '<S9>/Logical Operator' incorporates:
   *  Logic: '<S9>/Logical Operator1'
   */
  if ((tmp != 0.0) && (!(rtb_Stepend_time != 0.0))) {
    if (!localDW->EnabledMovingAverage_MODE) {
      /* InitializeConditions for UnitDelay: '<S16>/Unit Delay' */
      localDW->UnitDelay_DSTATE = localP->UnitDelay_InitialCondition;

      /* InitializeConditions for UnitDelay: '<S12>/Sum( k=1,n-1, x(k) )' */
      localDW->Sumk1n1xk_DSTATE = localP->Sumk1n1xk_InitialCondition;
      localDW->EnabledMovingAverage_MODE = true;
    }

    /* Sum: '<S16>/Count' incorporates:
     *  Constant: '<S16>/unity'
     *  UnitDelay: '<S16>/Unit Delay'
     */
    localB->Count = localP->unity_Value + localDW->UnitDelay_DSTATE;

    /* Sum: '<S12>/Sum' incorporates:
     *  UnitDelay: '<S12>/Sum( k=1,n-1, x(k) )'
     */
    localB->Sum = rtu_V + localDW->Sumk1n1xk_DSTATE;

    /* Product: '<S12>/div' */
    localB->div = localB->Sum / localB->Count;
    srUpdateBC(localDW->EnabledMovingAverage_SubsysRanB);
  } else {
    localDW->EnabledMovingAverage_MODE = false;
  }

  /* End of Logic: '<S9>/Logical Operator' */
  /* End of Outputs for SubSystem: '<S9>/Enabled Moving Average' */

  /* Sum: '<S9>/Sum' */
  rtb_Sum_o = rtu_V - localB->div;

  /* SwitchCase: '<S9>/Switch Case' incorporates:
   *  Constant: '<S13>/Constant'
   *  Constant: '<S9>/Constant'
   *  Inport: '<S14>/Vin'
   *  Inport: '<S15>/V-Vavg'
   */
  rtPrevAction = localDW->SwitchCase_ActiveSubsystem;
  rtAction = -1;
  if (rtp_switch_id < 0.0) {
    tmp = ceil(rtp_switch_id);
  } else {
    tmp = floor(rtp_switch_id);
  }

  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 4.294967296E+9);
  }

  switch (tmp < 0.0 ? -(int32_T)(uint32_T)-tmp : (int32_T)(uint32_T)tmp) {
   case 1:
    rtAction = 0;
    break;

   case 2:
    rtAction = 1;
    break;

   case 3:
    rtAction = 2;
    break;
  }

  localDW->SwitchCase_ActiveSubsystem = rtAction;
  if (rtPrevAction != rtAction) {
    switch (rtPrevAction) {
     case 0:
      /* Disable for Outport: '<S13>/zero' incorporates:
       *  Constant: '<S13>/Constant'
       * */
      localB->Constant = localP->zero_Y0;
      break;

     case 1:
      /* Disable for Outport: '<S14>/Vbiased' incorporates:
       *  Inport: '<S14>/Vin'
       * */
      localB->Vin = localP->Vbiased_Y0;
      break;

     case 2:
      /* Disable for Outport: '<S15>/Vunbiased' incorporates:
       *  Inport: '<S15>/V-Vavg'
       * */
      localB->VVavg = localP->Vunbiased_Y0;
      break;
    }
  }

  switch (rtAction) {
   case 0:
    /* Outputs for IfAction SubSystem: '<S9>/Switch Case Action Subsystem' incorporates:
     *  ActionPort: '<S13>/Action Port'
     */
    localB->Constant = localP->Constant_Value;
    srUpdateBC(localDW->SwitchCaseActionSubsystem_Subsy);

    /* End of Outputs for SubSystem: '<S9>/Switch Case Action Subsystem' */
    break;

   case 1:
    /* Outputs for IfAction SubSystem: '<S9>/Switch Case Action Subsystem1' incorporates:
     *  ActionPort: '<S14>/Action Port'
     */
    localB->Vin = rtu_V;
    srUpdateBC(localDW->SwitchCaseActionSubsystem1_Subs);

    /* End of Outputs for SubSystem: '<S9>/Switch Case Action Subsystem1' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S9>/Switch Case Action Subsystem2' incorporates:
     *  ActionPort: '<S15>/Action Port'
     */
    localB->VVavg = rtb_Sum_o;
    srUpdateBC(localDW->SwitchCaseActionSubsystem2_Subs);

    /* End of Outputs for SubSystem: '<S9>/Switch Case Action Subsystem2' */
    break;
  }

  /* End of SwitchCase: '<S9>/Switch Case' */

  /* Switch: '<S9>/Switch' incorporates:
   *  Logic: '<S9>/Logical Operator2'
   */
  if (!(rtb_Stepend_time != 0.0)) {
    /* Switch: '<S9>/Switch' incorporates:
     *  Sum: '<S9>/Sum1'
     */
    localB->Switch = (localB->Constant + localB->Vin) + localB->VVavg;
  } else {
    /* Switch: '<S9>/Switch' */
    localB->Switch = rtb_Sum_o;
  }

  /* End of Switch: '<S9>/Switch' */
}

/*
 * Update for atomic system:
 *    '<S1>/Bias Removal'
 *    '<S2>/Bias Removal'
 */
void q_2dsfl_open_BiasRemoval_Update(B_BiasRemoval_q_2dsfl_open_lo_T *localB,
  DW_BiasRemoval_q_2dsfl_open_l_T *localDW)
{
  /* Update for Enabled SubSystem: '<S9>/Enabled Moving Average' incorporates:
   *  EnablePort: '<S12>/Enable'
   */
  if (localDW->EnabledMovingAverage_MODE) {
    /* Update for UnitDelay: '<S16>/Unit Delay' */
    localDW->UnitDelay_DSTATE = localB->Count;

    /* Update for UnitDelay: '<S12>/Sum( k=1,n-1, x(k) )' */
    localDW->Sumk1n1xk_DSTATE = localB->Sum;
  }

  /* End of Update for SubSystem: '<S9>/Enabled Moving Average' */
}

/* Model output function */
void q_2dsfl_open_loop_output(void)
{
  /* local block i/o variables */
  real_T rtb_HILReadAnalog_o2;
  real_T rtb_HILReadAnalog_o1;
  boolean_T rtb_HILReadDigital_o1;
  boolean_T rtb_HILReadDigital_o2;
  boolean_T rtb_HILReadDigital_o3;
  boolean_T rtb_HILReadDigital_o4;
  real_T rtb_DerivativeFilter3;
  real_T rtb_Gain_k;
  real_T rtb_ManualSwitch;
  real_T rtb_undStage2DOFSFJRobotState_0;
  real_T tmp;
  int32_T rtb_undStage2DOFSFJRobotState_1;
  int_T ci;
  if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
    /* set solver stop time */
    if (!(q_2dsfl_open_loop_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&q_2dsfl_open_loop_M->solverInfo,
                            ((q_2dsfl_open_loop_M->Timing.clockTickH0 + 1) *
        q_2dsfl_open_loop_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&q_2dsfl_open_loop_M->solverInfo,
                            ((q_2dsfl_open_loop_M->Timing.clockTick0 + 1) *
        q_2dsfl_open_loop_M->Timing.stepSize0 +
        q_2dsfl_open_loop_M->Timing.clockTickH0 *
        q_2dsfl_open_loop_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(q_2dsfl_open_loop_M)) {
    q_2dsfl_open_loop_M->Timing.t[0] = rtsiGetT(&q_2dsfl_open_loop_M->solverInfo);
  }

  /* Reset subsysRan breadcrumbs */
  srClearBC(q_2dsfl_open_loop_DW.BiasRemoval.EnabledMovingAverage_SubsysRanB);

  /* Reset subsysRan breadcrumbs */
  srClearBC(q_2dsfl_open_loop_DW.BiasRemoval.SwitchCaseActionSubsystem_Subsy);

  /* Reset subsysRan breadcrumbs */
  srClearBC(q_2dsfl_open_loop_DW.BiasRemoval.SwitchCaseActionSubsystem1_Subs);

  /* Reset subsysRan breadcrumbs */
  srClearBC(q_2dsfl_open_loop_DW.BiasRemoval.SwitchCaseActionSubsystem2_Subs);

  /* Reset subsysRan breadcrumbs */
  srClearBC(q_2dsfl_open_loop_DW.PositionWatchdog_SubsysRanBC_b);

  /* Reset subsysRan breadcrumbs */
  srClearBC(q_2dsfl_open_loop_DW.PositionWatchdog_SubsysRanBC);
  if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S1>/HIL Read Encoder Timebase' */

    /* S-Function Block: q_2dsfl_open_loop/1st Stage: 2-DOF SFL Robot + Q8: Actual Plant/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (q_2dsfl_open_loop_DW.HILReadEncoderTimebase_Task, 1,
         &q_2dsfl_open_loop_DW.HILReadEncoderTimebase_Buffer);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
      } else {
        rtb_HILReadAnalog_o2 =
          q_2dsfl_open_loop_DW.HILReadEncoderTimebase_Buffer;
      }
    }
  }

  /* SignalGenerator: '<Root>/Signal Generator' incorporates:
   *  SignalGenerator: '<Root>/Signal Generator1'
   */
  rtb_Gain_k = q_2dsfl_open_loop_M->Timing.t[0];
  rtb_ManualSwitch = q_2dsfl_open_loop_P.SignalGenerator_Frequency * rtb_Gain_k;
  if (rtb_ManualSwitch - floor(rtb_ManualSwitch) >= 0.5) {
    rtb_ManualSwitch = q_2dsfl_open_loop_P.SignalGenerator_Amplitude;
  } else {
    rtb_ManualSwitch = -q_2dsfl_open_loop_P.SignalGenerator_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/Signal Generator' */

  /* Gain: '<Root>/Im_r1' */
  q_2dsfl_open_loop_B.Im_r1 = q_2dsfl_open_loop_P.Im_r1_Gain * rtb_ManualSwitch;
  if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
    /* Gain: '<S1>/Motor #1 Encoder Calib' */
    q_2dsfl_open_loop_B.Motor1EncoderCalib = q_2dsfl_open_loop_P.KE_D1 *
      rtb_HILReadAnalog_o2;
  }

  /* StateSpace: '<Root>/1st Stage: 2-DOF SFJ Robot: State-Space Model' */
  rtb_ManualSwitch = 0.0;
  rtb_undStage2DOFSFJRobotState_0 = 0.0;
  for (ci = 0; ci < 4; ci++) {
    rtb_undStage2DOFSFJRobotState_1 = ci << 2;
    rtb_ManualSwitch += q_2dsfl_open_loop_P.C1[rtb_undStage2DOFSFJRobotState_1] *
      q_2dsfl_open_loop_X.ustStage2DOFSFJRobotStateSpaceM[ci];
    rtb_undStage2DOFSFJRobotState_0 +=
      q_2dsfl_open_loop_P.C1[rtb_undStage2DOFSFJRobotState_1 + 1] *
      q_2dsfl_open_loop_X.ustStage2DOFSFJRobotStateSpaceM[ci];
  }

  /* End of StateSpace: '<Root>/1st Stage: 2-DOF SFJ Robot: State-Space Model' */

  /* Gain: '<S41>/Gain' */
  q_2dsfl_open_loop_B.Gain[0] = q_2dsfl_open_loop_P.Gain_Gain *
    q_2dsfl_open_loop_B.Motor1EncoderCalib;
  q_2dsfl_open_loop_B.Gain[1] = q_2dsfl_open_loop_P.Gain_Gain * rtb_ManualSwitch;
  if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
  }

  /* TransferFcn: '<S1>/Filter3' */
  rtb_ManualSwitch = q_2dsfl_open_loop_P.Filter3_C[0] *
    q_2dsfl_open_loop_X.Filter3_CSTATE[0] + q_2dsfl_open_loop_P.Filter3_C[1] *
    q_2dsfl_open_loop_X.Filter3_CSTATE[1];

  /* Gain: '<S42>/Gain' */
  q_2dsfl_open_loop_B.Gain_a[0] = q_2dsfl_open_loop_P.Gain_Gain_m *
    rtb_ManualSwitch;
  q_2dsfl_open_loop_B.Gain_a[1] = q_2dsfl_open_loop_P.Gain_Gain_m *
    rtb_undStage2DOFSFJRobotState_0;
  if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
    /* S-Function (hil_read_analog_block): '<S1>/HIL Read Analog' */

    /* S-Function Block: q_2dsfl_open_loop/1st Stage: 2-DOF SFL Robot + Q8: Actual Plant/HIL Read Analog (hil_read_analog_block) */
    {
      t_error result = hil_read_analog(q_2dsfl_open_loop_DW.HILInitialize_Card,
        q_2dsfl_open_loop_P.HILReadAnalog_channels, 2,
        &q_2dsfl_open_loop_DW.HILReadAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
      }

      rtb_HILReadAnalog_o2 = q_2dsfl_open_loop_DW.HILReadAnalog_Buffer[0];
      rtb_HILReadAnalog_o1 = q_2dsfl_open_loop_DW.HILReadAnalog_Buffer[1];
    }

    /* UnaryMinus: '<S1>/positive  CCW' */
    q_2dsfl_open_loop_B.positiveCCW = -rtb_HILReadAnalog_o2;

    /* Outputs for Atomic SubSystem: '<S1>/Bias Removal' */
    /* Outputs for Atomic SubSystem: '<S1>/Bias Removal' */
    q_2dsfl_open_loop_BiasRemoval(q_2dsfl_open_loop_M,
      q_2dsfl_open_loop_B.positiveCCW, q_2dsfl_open_loop_P.BiasRemoval_switch_id,
      q_2dsfl_open_loop_P.BiasRemoval_start_time,
      q_2dsfl_open_loop_P.BiasRemoval_end_time, &q_2dsfl_open_loop_B.BiasRemoval,
      &q_2dsfl_open_loop_DW.BiasRemoval, &q_2dsfl_open_loop_P.BiasRemoval);

    /* End of Outputs for SubSystem: '<S1>/Bias Removal' */
    /* End of Outputs for SubSystem: '<S1>/Bias Removal' */

    /* Gain: '<S1>/Volts to Base Strain' */
    q_2dsfl_open_loop_B.VoltstoBaseStrain = q_2dsfl_open_loop_P.K1_strain_b *
      q_2dsfl_open_loop_B.BiasRemoval.Switch;
  }

  /* ManualSwitch: '<Root>/Manual Switch1' incorporates:
   *  Gain: '<S8>/Amplitude (A)'
   *  Sum: '<S8>/Sum'
   */
  if (q_2dsfl_open_loop_P.ManualSwitch1_CurrentSetting == 1) {
    rtb_DerivativeFilter3 = q_2dsfl_open_loop_B.Im_r1;
  } else {
    /* Step: '<S8>/Step' incorporates:
     *  Step: '<S8>/Step1'
     */
    rtb_undStage2DOFSFJRobotState_0 = q_2dsfl_open_loop_M->Timing.t[0];
    if (rtb_undStage2DOFSFJRobotState_0 < q_2dsfl_open_loop_P.Step_Time) {
      tmp = q_2dsfl_open_loop_P.Step_Y0;
    } else {
      tmp = q_2dsfl_open_loop_P.Step_YFinal;
    }

    /* End of Step: '<S8>/Step' */

    /* Step: '<S8>/Step1' */
    if (rtb_undStage2DOFSFJRobotState_0 < q_2dsfl_open_loop_P.Step1_Time) {
      rtb_undStage2DOFSFJRobotState_0 = q_2dsfl_open_loop_P.Step1_Y0;
    } else {
      rtb_undStage2DOFSFJRobotState_0 = q_2dsfl_open_loop_P.Step1_YFinal;
    }

    rtb_DerivativeFilter3 = (tmp + rtb_undStage2DOFSFJRobotState_0) *
      q_2dsfl_open_loop_P.AmplitudeA_Gain;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch1' */

  /* Saturate: '<Root>/Im_r1: Saturation' */
  if (rtb_DerivativeFilter3 > q_2dsfl_open_loop_P.Im_r1Saturation_UpperSat) {
    /* Saturate: '<Root>/Im_r1: Saturation' */
    q_2dsfl_open_loop_B.Im_r1Saturation =
      q_2dsfl_open_loop_P.Im_r1Saturation_UpperSat;
  } else if (rtb_DerivativeFilter3 <
             q_2dsfl_open_loop_P.Im_r1Saturation_LowerSat) {
    /* Saturate: '<Root>/Im_r1: Saturation' */
    q_2dsfl_open_loop_B.Im_r1Saturation =
      q_2dsfl_open_loop_P.Im_r1Saturation_LowerSat;
  } else {
    /* Saturate: '<Root>/Im_r1: Saturation' */
    q_2dsfl_open_loop_B.Im_r1Saturation = rtb_DerivativeFilter3;
  }

  /* End of Saturate: '<Root>/Im_r1: Saturation' */
  if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
    /* Gain: '<S1>/Volts to Amps' */
    q_2dsfl_open_loop_B.VoltstoAmps = q_2dsfl_open_loop_P.VoltstoAmps_Gain *
      rtb_HILReadAnalog_o1;
  }

  /* Gain: '<S1>/Amps to Volts' incorporates:
   *  UnaryMinus: '<S1>/positive dir: CCW'
   */
  q_2dsfl_open_loop_B.AmpstoVolts = q_2dsfl_open_loop_P.AmpstoVolts_Gain *
    -q_2dsfl_open_loop_B.Im_r1Saturation;

  /* Outputs for Enabled SubSystem: '<S1>/Position Watchdog' incorporates:
   *  EnablePort: '<S10>/Enable'
   */
  if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
    /* S-Function (hil_write_analog_block): '<S1>/HIL Write Analog' */

    /* S-Function Block: q_2dsfl_open_loop/1st Stage: 2-DOF SFL Robot + Q8: Actual Plant/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(q_2dsfl_open_loop_DW.HILInitialize_Card,
        &q_2dsfl_open_loop_P.HILWriteAnalog_channels, 1,
        &q_2dsfl_open_loop_B.AmpstoVolts);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
      }
    }

    if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
      /* Constant: '<S1>/Constant' */
      q_2dsfl_open_loop_DW.PositionWatchdog_MODE_k =
        (q_2dsfl_open_loop_P.DTH1_LIM_ENABLE > 0.0);
    }
  }

  /* End of Outputs for SubSystem: '<S1>/Position Watchdog' */

  /* Gain: '<S11>/Gain' */
  rtb_ManualSwitch *= q_2dsfl_open_loop_P.Gain_Gain_n;

  /* Outputs for Enabled SubSystem: '<S1>/Position Watchdog' incorporates:
   *  EnablePort: '<S10>/Enable'
   */
  if (q_2dsfl_open_loop_DW.PositionWatchdog_MODE_k) {
    /* RelationalOperator: '<S10>/Check Maximum Allowed Position' incorporates:
     *  Constant: '<S10>/X MAX'
     */
    q_2dsfl_open_loop_B.CheckMaximumAllowedPosition_a =
      (q_2dsfl_open_loop_P.DTH2_MAX < rtb_ManualSwitch);

    /* RelationalOperator: '<S19>/Compare' incorporates:
     *  Constant: '<S19>/Constant'
     */
    q_2dsfl_open_loop_B.Compare_l =
      (q_2dsfl_open_loop_B.CheckMaximumAllowedPosition_a !=
       q_2dsfl_open_loop_P.Constant_Value);
    if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
      /* Stop: '<S17>/Stop Simulation' */
      if (q_2dsfl_open_loop_B.Compare_l) {
        rtmSetStopRequested(q_2dsfl_open_loop_M, 1);
      }

      /* End of Stop: '<S17>/Stop Simulation' */
    }

    /* RelationalOperator: '<S10>/Check Minimum Allowed Position' incorporates:
     *  Constant: '<S10>/X IN'
     */
    q_2dsfl_open_loop_B.CheckMinimumAllowedPosition_d = (rtb_ManualSwitch <
      q_2dsfl_open_loop_P.DTH2_MIN);

    /* RelationalOperator: '<S20>/Compare' incorporates:
     *  Constant: '<S20>/Constant'
     */
    q_2dsfl_open_loop_B.Compare_b =
      (q_2dsfl_open_loop_B.CheckMinimumAllowedPosition_d !=
       q_2dsfl_open_loop_P.Constant_Value_k);
    if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
      /* Stop: '<S18>/Stop Simulation' */
      if (q_2dsfl_open_loop_B.Compare_b) {
        rtmSetStopRequested(q_2dsfl_open_loop_M, 1);
      }

      /* End of Stop: '<S18>/Stop Simulation' */
    }

    if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
      srUpdateBC(q_2dsfl_open_loop_DW.PositionWatchdog_SubsysRanBC_b);
    }
  }

  /* End of Outputs for SubSystem: '<S1>/Position Watchdog' */
  if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
    /* Gain: '<S1>/Strain to Deflection' */
    q_2dsfl_open_loop_B.StraintoDeflection = q_2dsfl_open_loop_P.K1_defl_b *
      q_2dsfl_open_loop_B.VoltstoBaseStrain;

    /* S-Function (hil_read_encoder_block): '<S2>/HIL Read Encoder' */

    /* S-Function Block: q_2dsfl_open_loop/2nd Stage: 2-DOF SFL Robot + Q8: Actual Plant/HIL Read Encoder (hil_read_encoder_block) */
    {
      t_error result = hil_read_encoder(q_2dsfl_open_loop_DW.HILInitialize_Card,
        &q_2dsfl_open_loop_P.HILReadEncoder_channels, 1,
        &q_2dsfl_open_loop_DW.HILReadEncoder_Buffer);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
      } else {
        rtb_HILReadAnalog_o1 = q_2dsfl_open_loop_DW.HILReadEncoder_Buffer;
      }
    }

    /* Gain: '<S2>/Motor #2 Encoder Calib' */
    q_2dsfl_open_loop_B.Motor2EncoderCalib = q_2dsfl_open_loop_P.KE_D2 *
      rtb_HILReadAnalog_o1;
  }

  /* StateSpace: '<Root>/2nd Stage: 2-DOF SFJ Robot: State-Space Model' */
  rtb_ManualSwitch = 0.0;
  rtb_undStage2DOFSFJRobotState_0 = 0.0;
  for (ci = 0; ci < 4; ci++) {
    rtb_ManualSwitch += q_2dsfl_open_loop_P.C2[ci << 2] *
      q_2dsfl_open_loop_X.undStage2DOFSFJRobotStateSpaceM[ci];
    rtb_undStage2DOFSFJRobotState_0 += q_2dsfl_open_loop_P.C2[(ci << 2) + 1] *
      q_2dsfl_open_loop_X.undStage2DOFSFJRobotStateSpaceM[ci];
  }

  /* End of StateSpace: '<Root>/2nd Stage: 2-DOF SFJ Robot: State-Space Model' */

  /* Gain: '<S43>/Gain' */
  q_2dsfl_open_loop_B.Gain_p[0] = q_2dsfl_open_loop_P.Gain_Gain_m4 *
    q_2dsfl_open_loop_B.Motor2EncoderCalib;
  q_2dsfl_open_loop_B.Gain_p[1] = q_2dsfl_open_loop_P.Gain_Gain_m4 *
    rtb_ManualSwitch;
  if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
  }

  /* TransferFcn: '<S2>/Derivative Filter3' */
  rtb_DerivativeFilter3 = q_2dsfl_open_loop_P.DerivativeFilter3_C[0] *
    q_2dsfl_open_loop_X.DerivativeFilter3_CSTATE[0] +
    q_2dsfl_open_loop_P.DerivativeFilter3_C[1] *
    q_2dsfl_open_loop_X.DerivativeFilter3_CSTATE[1];

  /* Gain: '<S44>/Gain' */
  q_2dsfl_open_loop_B.Gain_m[0] = q_2dsfl_open_loop_P.Gain_Gain_g *
    rtb_DerivativeFilter3;
  q_2dsfl_open_loop_B.Gain_m[1] = q_2dsfl_open_loop_P.Gain_Gain_g *
    rtb_undStage2DOFSFJRobotState_0;
  if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
    /* S-Function (hil_read_analog_block): '<S2>/HIL Read Analog' */

    /* S-Function Block: q_2dsfl_open_loop/2nd Stage: 2-DOF SFL Robot + Q8: Actual Plant/HIL Read Analog (hil_read_analog_block) */
    {
      t_error result = hil_read_analog(q_2dsfl_open_loop_DW.HILInitialize_Card,
        q_2dsfl_open_loop_P.HILReadAnalog_channels_g, 2,
        &q_2dsfl_open_loop_DW.HILReadAnalog_Buffer_d[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
      }

      rtb_HILReadAnalog_o1 = q_2dsfl_open_loop_DW.HILReadAnalog_Buffer_d[0];
      rtb_HILReadAnalog_o2 = q_2dsfl_open_loop_DW.HILReadAnalog_Buffer_d[1];
    }

    /* UnaryMinus: '<S2>/positive  CCW' */
    q_2dsfl_open_loop_B.positiveCCW_l = -rtb_HILReadAnalog_o1;

    /* Outputs for Atomic SubSystem: '<S2>/Bias Removal' */
    /* Outputs for Atomic SubSystem: '<S2>/Bias Removal' */
    q_2dsfl_open_loop_BiasRemoval(q_2dsfl_open_loop_M,
      q_2dsfl_open_loop_B.positiveCCW_l,
      q_2dsfl_open_loop_P.BiasRemoval_switch_id_c,
      q_2dsfl_open_loop_P.BiasRemoval_start_time_k,
      q_2dsfl_open_loop_P.BiasRemoval_end_time_n,
      &q_2dsfl_open_loop_B.BiasRemoval_e, &q_2dsfl_open_loop_DW.BiasRemoval_e,
      &q_2dsfl_open_loop_P.BiasRemoval_e);

    /* End of Outputs for SubSystem: '<S2>/Bias Removal' */
    /* End of Outputs for SubSystem: '<S2>/Bias Removal' */

    /* Gain: '<S2>/Volts to Strain' */
    q_2dsfl_open_loop_B.VoltstoStrain = q_2dsfl_open_loop_P.K2_strain_b *
      q_2dsfl_open_loop_B.BiasRemoval_e.Switch;
  }

  /* SignalGenerator: '<Root>/Signal Generator1' */
  rtb_ManualSwitch = q_2dsfl_open_loop_P.SignalGenerator1_Frequency * rtb_Gain_k;

  /* ManualSwitch: '<Root>/Manual Switch' incorporates:
   *  Gain: '<Root>/Im_r2'
   *  Gain: '<S7>/Amplitude (A)'
   *  Sum: '<S7>/Sum'
   */
  if (q_2dsfl_open_loop_P.ManualSwitch_CurrentSetting == 1) {
    /* SignalGenerator: '<Root>/Signal Generator1' */
    if (rtb_ManualSwitch - floor(rtb_ManualSwitch) >= 0.5) {
      rtb_ManualSwitch = q_2dsfl_open_loop_P.SignalGenerator1_Amplitude;
    } else {
      rtb_ManualSwitch = -q_2dsfl_open_loop_P.SignalGenerator1_Amplitude;
    }

    rtb_ManualSwitch *= q_2dsfl_open_loop_P.Im_r2_Gain;
  } else {
    /* Step: '<S7>/Step' incorporates:
     *  Step: '<S7>/Step1'
     */
    rtb_undStage2DOFSFJRobotState_0 = q_2dsfl_open_loop_M->Timing.t[0];
    if (rtb_undStage2DOFSFJRobotState_0 < q_2dsfl_open_loop_P.Step_Time_f) {
      tmp = q_2dsfl_open_loop_P.Step_Y0_m;
    } else {
      tmp = q_2dsfl_open_loop_P.Step_YFinal_n;
    }

    /* End of Step: '<S7>/Step' */

    /* Step: '<S7>/Step1' */
    if (rtb_undStage2DOFSFJRobotState_0 < q_2dsfl_open_loop_P.Step1_Time_h) {
      rtb_undStage2DOFSFJRobotState_0 = q_2dsfl_open_loop_P.Step1_Y0_g;
    } else {
      rtb_undStage2DOFSFJRobotState_0 = q_2dsfl_open_loop_P.Step1_YFinal_e;
    }

    rtb_ManualSwitch = (tmp + rtb_undStage2DOFSFJRobotState_0) *
      q_2dsfl_open_loop_P.AmplitudeA_Gain_j;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch' */

  /* Saturate: '<Root>/Im_r2: Saturation' */
  if (rtb_ManualSwitch > q_2dsfl_open_loop_P.Im_r2Saturation_UpperSat) {
    /* Saturate: '<Root>/Im_r2: Saturation' */
    q_2dsfl_open_loop_B.Im_r2Saturation =
      q_2dsfl_open_loop_P.Im_r2Saturation_UpperSat;
  } else if (rtb_ManualSwitch < q_2dsfl_open_loop_P.Im_r2Saturation_LowerSat) {
    /* Saturate: '<Root>/Im_r2: Saturation' */
    q_2dsfl_open_loop_B.Im_r2Saturation =
      q_2dsfl_open_loop_P.Im_r2Saturation_LowerSat;
  } else {
    /* Saturate: '<Root>/Im_r2: Saturation' */
    q_2dsfl_open_loop_B.Im_r2Saturation = rtb_ManualSwitch;
  }

  /* End of Saturate: '<Root>/Im_r2: Saturation' */
  if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
    /* Gain: '<S2>/Volts to Amps' */
    q_2dsfl_open_loop_B.VoltstoAmps_h = q_2dsfl_open_loop_P.VoltstoAmps_Gain_g *
      rtb_HILReadAnalog_o2;
  }

  /* Gain: '<S2>/Amps to Volts' incorporates:
   *  UnaryMinus: '<S2>/positive dir: CCW'
   */
  q_2dsfl_open_loop_B.AmpstoVolts_d = q_2dsfl_open_loop_P.AmpstoVolts_Gain_e *
    -q_2dsfl_open_loop_B.Im_r2Saturation;

  /* Outputs for Enabled SubSystem: '<S2>/Position Watchdog' incorporates:
   *  EnablePort: '<S22>/Enable'
   */
  if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
    /* S-Function (hil_write_analog_block): '<S2>/HIL Write Analog' */

    /* S-Function Block: q_2dsfl_open_loop/2nd Stage: 2-DOF SFL Robot + Q8: Actual Plant/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(q_2dsfl_open_loop_DW.HILInitialize_Card,
        &q_2dsfl_open_loop_P.HILWriteAnalog_channels_j, 1,
        &q_2dsfl_open_loop_B.AmpstoVolts_d);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
      }
    }

    if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
      /* Constant: '<S2>/Constant' */
      q_2dsfl_open_loop_DW.PositionWatchdog_MODE =
        (q_2dsfl_open_loop_P.DTH2_LIM_ENABLE > 0.0);
    }
  }

  /* End of Outputs for SubSystem: '<S2>/Position Watchdog' */

  /* Gain: '<S23>/Gain' */
  rtb_Gain_k = q_2dsfl_open_loop_P.Gain_Gain_n5 * rtb_DerivativeFilter3;

  /* Outputs for Enabled SubSystem: '<S2>/Position Watchdog' incorporates:
   *  EnablePort: '<S22>/Enable'
   */
  if (q_2dsfl_open_loop_DW.PositionWatchdog_MODE) {
    /* RelationalOperator: '<S22>/Check Maximum Allowed Position' incorporates:
     *  Constant: '<S22>/X MAX'
     */
    q_2dsfl_open_loop_B.CheckMaximumAllowedPosition =
      (q_2dsfl_open_loop_P.DTH2_MAX < rtb_Gain_k);

    /* RelationalOperator: '<S31>/Compare' incorporates:
     *  Constant: '<S31>/Constant'
     */
    q_2dsfl_open_loop_B.Compare =
      (q_2dsfl_open_loop_B.CheckMaximumAllowedPosition !=
       q_2dsfl_open_loop_P.Constant_Value_p);
    if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
      /* Stop: '<S29>/Stop Simulation' */
      if (q_2dsfl_open_loop_B.Compare) {
        rtmSetStopRequested(q_2dsfl_open_loop_M, 1);
      }

      /* End of Stop: '<S29>/Stop Simulation' */
    }

    /* RelationalOperator: '<S22>/Check Minimum Allowed Position' incorporates:
     *  Constant: '<S22>/X IN'
     */
    q_2dsfl_open_loop_B.CheckMinimumAllowedPosition = (rtb_Gain_k <
      q_2dsfl_open_loop_P.DTH2_MIN);

    /* RelationalOperator: '<S32>/Compare' incorporates:
     *  Constant: '<S32>/Constant'
     */
    q_2dsfl_open_loop_B.Compare_p =
      (q_2dsfl_open_loop_B.CheckMinimumAllowedPosition !=
       q_2dsfl_open_loop_P.Constant_Value_o);
    if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
      /* Stop: '<S30>/Stop Simulation' */
      if (q_2dsfl_open_loop_B.Compare_p) {
        rtmSetStopRequested(q_2dsfl_open_loop_M, 1);
      }

      /* End of Stop: '<S30>/Stop Simulation' */
    }

    if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
      srUpdateBC(q_2dsfl_open_loop_DW.PositionWatchdog_SubsysRanBC);
    }
  }

  /* End of Outputs for SubSystem: '<S2>/Position Watchdog' */
  if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
    /* Gain: '<S2>/Strain to Deflection' */
    q_2dsfl_open_loop_B.StraintoDeflection_g = q_2dsfl_open_loop_P.K2_defl_b *
      q_2dsfl_open_loop_B.VoltstoStrain;

    /* S-Function (hil_write_digital_block): '<S3>/HIL Write Digital' incorporates:
     *  Constant: '<S3>/Enable: Active Low'
     *  Constant: '<S3>/Master Enable: Active High'
     */

    /* S-Function Block: q_2dsfl_open_loop/Enable AMPAQ/HIL Write Digital (hil_write_digital_block) */
    {
      t_error result;
      q_2dsfl_open_loop_DW.HILWriteDigital_Buffer[0] =
        (q_2dsfl_open_loop_P.EnableActiveLow_Value[0] != 0);
      q_2dsfl_open_loop_DW.HILWriteDigital_Buffer[1] =
        (q_2dsfl_open_loop_P.EnableActiveLow_Value[1] != 0);
      q_2dsfl_open_loop_DW.HILWriteDigital_Buffer[2] =
        (q_2dsfl_open_loop_P.MasterEnableActiveHigh_Value != 0);
      result = hil_write_digital(q_2dsfl_open_loop_DW.HILInitialize_Card,
        q_2dsfl_open_loop_P.HILWriteDigital_channels, 3,
        &q_2dsfl_open_loop_DW.HILWriteDigital_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
      }
    }

    /* S-Function (hil_read_digital_block): '<S4>/HIL Read Digital' */

    /* S-Function Block: q_2dsfl_open_loop/Limit Switches/HIL Read Digital (hil_read_digital_block) */
    {
      t_error result = hil_read_digital(q_2dsfl_open_loop_DW.HILInitialize_Card,
        q_2dsfl_open_loop_P.HILReadDigital_channels, 4,
        &q_2dsfl_open_loop_DW.HILReadDigital_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
      } else {
        rtb_HILReadDigital_o1 = q_2dsfl_open_loop_DW.HILReadDigital_Buffer[0];
        rtb_HILReadDigital_o2 = q_2dsfl_open_loop_DW.HILReadDigital_Buffer[1];
        rtb_HILReadDigital_o3 = q_2dsfl_open_loop_DW.HILReadDigital_Buffer[2];
        rtb_HILReadDigital_o4 = q_2dsfl_open_loop_DW.HILReadDigital_Buffer[3];
      }
    }

    /* Logic: '<S4>/Logical Operator4' incorporates:
     *  Constant: '<S4>/Constant'
     *  Logic: '<S4>/Logical Operator2'
     */
    q_2dsfl_open_loop_B.LogicalOperator4 =
      ((q_2dsfl_open_loop_P.LIMIT_SWITCHES_ENABLE != 0.0) &&
       (!rtb_HILReadDigital_o1));

    /* Stop: '<S33>/Stop Simulation' incorporates:
     *  Constant: '<S37>/Constant'
     *  RelationalOperator: '<S37>/Compare'
     */
    if (q_2dsfl_open_loop_B.LogicalOperator4 !=
        q_2dsfl_open_loop_P.Constant_Value_n) {
      rtmSetStopRequested(q_2dsfl_open_loop_M, 1);
    }

    /* End of Stop: '<S33>/Stop Simulation' */

    /* Logic: '<S4>/Logical Operator5' incorporates:
     *  Constant: '<S4>/Constant'
     *  Logic: '<S4>/Logical Operator3'
     */
    q_2dsfl_open_loop_B.LogicalOperator5 =
      ((q_2dsfl_open_loop_P.LIMIT_SWITCHES_ENABLE != 0.0) &&
       (!rtb_HILReadDigital_o2));

    /* Stop: '<S34>/Stop Simulation' incorporates:
     *  Constant: '<S38>/Constant'
     *  RelationalOperator: '<S38>/Compare'
     */
    if (q_2dsfl_open_loop_B.LogicalOperator5 !=
        q_2dsfl_open_loop_P.Constant_Value_g) {
      rtmSetStopRequested(q_2dsfl_open_loop_M, 1);
    }

    /* End of Stop: '<S34>/Stop Simulation' */

    /* Logic: '<S4>/Logical Operator6' incorporates:
     *  Constant: '<S4>/Constant'
     *  Logic: '<S4>/Logical Operator1'
     */
    q_2dsfl_open_loop_B.LogicalOperator6 =
      ((q_2dsfl_open_loop_P.LIMIT_SWITCHES_ENABLE != 0.0) &&
       (!rtb_HILReadDigital_o3));

    /* Stop: '<S35>/Stop Simulation' incorporates:
     *  Constant: '<S39>/Constant'
     *  RelationalOperator: '<S39>/Compare'
     */
    if (q_2dsfl_open_loop_B.LogicalOperator6 !=
        q_2dsfl_open_loop_P.Constant_Value_f) {
      rtmSetStopRequested(q_2dsfl_open_loop_M, 1);
    }

    /* End of Stop: '<S35>/Stop Simulation' */

    /* Logic: '<S4>/Logical Operator7' incorporates:
     *  Constant: '<S4>/Constant'
     *  Logic: '<S4>/Logical Operator'
     */
    q_2dsfl_open_loop_B.LogicalOperator7 =
      ((q_2dsfl_open_loop_P.LIMIT_SWITCHES_ENABLE != 0.0) &&
       (!rtb_HILReadDigital_o4));

    /* Stop: '<S36>/Stop Simulation' incorporates:
     *  Constant: '<S40>/Constant'
     *  RelationalOperator: '<S40>/Compare'
     */
    if (q_2dsfl_open_loop_B.LogicalOperator7 !=
        q_2dsfl_open_loop_P.Constant_Value_kl) {
      rtmSetStopRequested(q_2dsfl_open_loop_M, 1);
    }

    /* End of Stop: '<S36>/Stop Simulation' */
  }
}

/* Model update function */
void q_2dsfl_open_loop_update(void)
{
  if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
    /* Update for Atomic SubSystem: '<S1>/Bias Removal' */
    q_2dsfl_open_BiasRemoval_Update(&q_2dsfl_open_loop_B.BiasRemoval,
      &q_2dsfl_open_loop_DW.BiasRemoval);

    /* End of Update for SubSystem: '<S1>/Bias Removal' */

    /* Update for Atomic SubSystem: '<S2>/Bias Removal' */
    q_2dsfl_open_BiasRemoval_Update(&q_2dsfl_open_loop_B.BiasRemoval_e,
      &q_2dsfl_open_loop_DW.BiasRemoval_e);

    /* End of Update for SubSystem: '<S2>/Bias Removal' */
  }

  if (rtmIsMajorTimeStep(q_2dsfl_open_loop_M)) {
    rt_ertODEUpdateContinuousStates(&q_2dsfl_open_loop_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++q_2dsfl_open_loop_M->Timing.clockTick0)) {
    ++q_2dsfl_open_loop_M->Timing.clockTickH0;
  }

  q_2dsfl_open_loop_M->Timing.t[0] = rtsiGetSolverStopTime
    (&q_2dsfl_open_loop_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++q_2dsfl_open_loop_M->Timing.clockTick1)) {
      ++q_2dsfl_open_loop_M->Timing.clockTickH1;
    }

    q_2dsfl_open_loop_M->Timing.t[1] = q_2dsfl_open_loop_M->Timing.clockTick1 *
      q_2dsfl_open_loop_M->Timing.stepSize1 +
      q_2dsfl_open_loop_M->Timing.clockTickH1 *
      q_2dsfl_open_loop_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void q_2dsfl_open_loop_derivatives(void)
{
  XDot_q_2dsfl_open_loop_T *_rtXdot;
  int32_T ustStage2DOFSFJRobotStateSpaceM;
  int_T ci;
  _rtXdot = ((XDot_q_2dsfl_open_loop_T *) q_2dsfl_open_loop_M->derivs);

  /* Derivatives for StateSpace: '<Root>/1st Stage: 2-DOF SFJ Robot: State-Space Model' */
  _rtXdot->ustStage2DOFSFJRobotStateSpaceM[0] = 0.0;
  _rtXdot->ustStage2DOFSFJRobotStateSpaceM[1] = 0.0;
  _rtXdot->ustStage2DOFSFJRobotStateSpaceM[2] = 0.0;
  _rtXdot->ustStage2DOFSFJRobotStateSpaceM[3] = 0.0;

  /* Derivatives for TransferFcn: '<S1>/Filter3' */
  _rtXdot->Filter3_CSTATE[0] = 0.0;
  _rtXdot->Filter3_CSTATE[0] += q_2dsfl_open_loop_P.Filter3_A[0] *
    q_2dsfl_open_loop_X.Filter3_CSTATE[0];
  _rtXdot->Filter3_CSTATE[1] = 0.0;
  _rtXdot->Filter3_CSTATE[0] += q_2dsfl_open_loop_P.Filter3_A[1] *
    q_2dsfl_open_loop_X.Filter3_CSTATE[1];
  _rtXdot->Filter3_CSTATE[1] += q_2dsfl_open_loop_X.Filter3_CSTATE[0];
  _rtXdot->Filter3_CSTATE[0] += q_2dsfl_open_loop_B.StraintoDeflection;

  /* Derivatives for TransferFcn: '<S1>/Derivative Filter1' */
  _rtXdot->DerivativeFilter1_CSTATE[0] = 0.0;
  _rtXdot->DerivativeFilter1_CSTATE[0] +=
    q_2dsfl_open_loop_P.DerivativeFilter1_A[0] *
    q_2dsfl_open_loop_X.DerivativeFilter1_CSTATE[0];
  _rtXdot->DerivativeFilter1_CSTATE[1] = 0.0;
  _rtXdot->DerivativeFilter1_CSTATE[0] +=
    q_2dsfl_open_loop_P.DerivativeFilter1_A[1] *
    q_2dsfl_open_loop_X.DerivativeFilter1_CSTATE[1];
  _rtXdot->DerivativeFilter1_CSTATE[1] +=
    q_2dsfl_open_loop_X.DerivativeFilter1_CSTATE[0];
  _rtXdot->DerivativeFilter1_CSTATE[0] += q_2dsfl_open_loop_B.Motor1EncoderCalib;

  /* Derivatives for TransferFcn: '<S1>/Derivative Filter2' */
  _rtXdot->DerivativeFilter2_CSTATE[0] = 0.0;
  _rtXdot->DerivativeFilter2_CSTATE[0] +=
    q_2dsfl_open_loop_P.DerivativeFilter2_A[0] *
    q_2dsfl_open_loop_X.DerivativeFilter2_CSTATE[0];
  _rtXdot->DerivativeFilter2_CSTATE[1] = 0.0;
  _rtXdot->DerivativeFilter2_CSTATE[0] +=
    q_2dsfl_open_loop_P.DerivativeFilter2_A[1] *
    q_2dsfl_open_loop_X.DerivativeFilter2_CSTATE[1];
  _rtXdot->DerivativeFilter2_CSTATE[1] +=
    q_2dsfl_open_loop_X.DerivativeFilter2_CSTATE[0];
  _rtXdot->DerivativeFilter2_CSTATE[0] += q_2dsfl_open_loop_B.StraintoDeflection;

  /* Derivatives for StateSpace: '<Root>/2nd Stage: 2-DOF SFJ Robot: State-Space Model' */
  _rtXdot->undStage2DOFSFJRobotStateSpaceM[0] = 0.0;
  _rtXdot->undStage2DOFSFJRobotStateSpaceM[1] = 0.0;
  _rtXdot->undStage2DOFSFJRobotStateSpaceM[2] = 0.0;
  _rtXdot->undStage2DOFSFJRobotStateSpaceM[3] = 0.0;
  for (ci = 0; ci < 4; ci++) {
    /* Derivatives for StateSpace: '<Root>/1st Stage: 2-DOF SFJ Robot: State-Space Model' incorporates:
     *  StateSpace: '<Root>/2nd Stage: 2-DOF SFJ Robot: State-Space Model'
     */
    ustStage2DOFSFJRobotStateSpaceM = ci << 2;
    _rtXdot->ustStage2DOFSFJRobotStateSpaceM[0] +=
      q_2dsfl_open_loop_P.A1[ustStage2DOFSFJRobotStateSpaceM] *
      q_2dsfl_open_loop_X.ustStage2DOFSFJRobotStateSpaceM[ci];
    _rtXdot->ustStage2DOFSFJRobotStateSpaceM[1] +=
      q_2dsfl_open_loop_P.A1[ustStage2DOFSFJRobotStateSpaceM + 1] *
      q_2dsfl_open_loop_X.ustStage2DOFSFJRobotStateSpaceM[ci];
    _rtXdot->ustStage2DOFSFJRobotStateSpaceM[2] +=
      q_2dsfl_open_loop_P.A1[ustStage2DOFSFJRobotStateSpaceM + 2] *
      q_2dsfl_open_loop_X.ustStage2DOFSFJRobotStateSpaceM[ci];
    _rtXdot->ustStage2DOFSFJRobotStateSpaceM[3] +=
      q_2dsfl_open_loop_P.A1[ustStage2DOFSFJRobotStateSpaceM + 3] *
      q_2dsfl_open_loop_X.ustStage2DOFSFJRobotStateSpaceM[ci];

    /* Derivatives for StateSpace: '<Root>/2nd Stage: 2-DOF SFJ Robot: State-Space Model' incorporates:
     *  StateSpace: '<Root>/1st Stage: 2-DOF SFJ Robot: State-Space Model'
     */
    _rtXdot->undStage2DOFSFJRobotStateSpaceM[0] +=
      q_2dsfl_open_loop_P.A2[ustStage2DOFSFJRobotStateSpaceM] *
      q_2dsfl_open_loop_X.undStage2DOFSFJRobotStateSpaceM[ci];
    _rtXdot->undStage2DOFSFJRobotStateSpaceM[1] +=
      q_2dsfl_open_loop_P.A2[ustStage2DOFSFJRobotStateSpaceM + 1] *
      q_2dsfl_open_loop_X.undStage2DOFSFJRobotStateSpaceM[ci];
    _rtXdot->undStage2DOFSFJRobotStateSpaceM[2] +=
      q_2dsfl_open_loop_P.A2[ustStage2DOFSFJRobotStateSpaceM + 2] *
      q_2dsfl_open_loop_X.undStage2DOFSFJRobotStateSpaceM[ci];
    _rtXdot->undStage2DOFSFJRobotStateSpaceM[3] +=
      q_2dsfl_open_loop_P.A2[ustStage2DOFSFJRobotStateSpaceM + 3] *
      q_2dsfl_open_loop_X.undStage2DOFSFJRobotStateSpaceM[ci];
  }

  /* Derivatives for StateSpace: '<Root>/1st Stage: 2-DOF SFJ Robot: State-Space Model' */
  _rtXdot->ustStage2DOFSFJRobotStateSpaceM[0] += q_2dsfl_open_loop_P.B1[0] *
    q_2dsfl_open_loop_B.Im_r1Saturation;
  _rtXdot->ustStage2DOFSFJRobotStateSpaceM[1] += q_2dsfl_open_loop_P.B1[1] *
    q_2dsfl_open_loop_B.Im_r1Saturation;
  _rtXdot->ustStage2DOFSFJRobotStateSpaceM[2] += q_2dsfl_open_loop_P.B1[2] *
    q_2dsfl_open_loop_B.Im_r1Saturation;
  _rtXdot->ustStage2DOFSFJRobotStateSpaceM[3] += q_2dsfl_open_loop_P.B1[3] *
    q_2dsfl_open_loop_B.Im_r1Saturation;

  /* Derivatives for StateSpace: '<Root>/2nd Stage: 2-DOF SFJ Robot: State-Space Model' */
  _rtXdot->undStage2DOFSFJRobotStateSpaceM[0] += q_2dsfl_open_loop_P.B2[0] *
    q_2dsfl_open_loop_B.Im_r2Saturation;
  _rtXdot->undStage2DOFSFJRobotStateSpaceM[1] += q_2dsfl_open_loop_P.B2[1] *
    q_2dsfl_open_loop_B.Im_r2Saturation;
  _rtXdot->undStage2DOFSFJRobotStateSpaceM[2] += q_2dsfl_open_loop_P.B2[2] *
    q_2dsfl_open_loop_B.Im_r2Saturation;
  _rtXdot->undStage2DOFSFJRobotStateSpaceM[3] += q_2dsfl_open_loop_P.B2[3] *
    q_2dsfl_open_loop_B.Im_r2Saturation;

  /* Derivatives for TransferFcn: '<S2>/Derivative Filter3' */
  _rtXdot->DerivativeFilter3_CSTATE[0] = 0.0;
  _rtXdot->DerivativeFilter3_CSTATE[0] +=
    q_2dsfl_open_loop_P.DerivativeFilter3_A[0] *
    q_2dsfl_open_loop_X.DerivativeFilter3_CSTATE[0];
  _rtXdot->DerivativeFilter3_CSTATE[1] = 0.0;
  _rtXdot->DerivativeFilter3_CSTATE[0] +=
    q_2dsfl_open_loop_P.DerivativeFilter3_A[1] *
    q_2dsfl_open_loop_X.DerivativeFilter3_CSTATE[1];
  _rtXdot->DerivativeFilter3_CSTATE[1] +=
    q_2dsfl_open_loop_X.DerivativeFilter3_CSTATE[0];
  _rtXdot->DerivativeFilter3_CSTATE[0] +=
    q_2dsfl_open_loop_B.StraintoDeflection_g;

  /* Derivatives for TransferFcn: '<S2>/Derivative Filter1' */
  _rtXdot->DerivativeFilter1_CSTATE_a[0] = 0.0;
  _rtXdot->DerivativeFilter1_CSTATE_a[0] +=
    q_2dsfl_open_loop_P.DerivativeFilter1_A_l[0] *
    q_2dsfl_open_loop_X.DerivativeFilter1_CSTATE_a[0];
  _rtXdot->DerivativeFilter1_CSTATE_a[1] = 0.0;
  _rtXdot->DerivativeFilter1_CSTATE_a[0] +=
    q_2dsfl_open_loop_P.DerivativeFilter1_A_l[1] *
    q_2dsfl_open_loop_X.DerivativeFilter1_CSTATE_a[1];
  _rtXdot->DerivativeFilter1_CSTATE_a[1] +=
    q_2dsfl_open_loop_X.DerivativeFilter1_CSTATE_a[0];
  _rtXdot->DerivativeFilter1_CSTATE_a[0] +=
    q_2dsfl_open_loop_B.Motor2EncoderCalib;

  /* Derivatives for TransferFcn: '<S2>/Derivative Filter2' */
  _rtXdot->DerivativeFilter2_CSTATE_l[0] = 0.0;
  _rtXdot->DerivativeFilter2_CSTATE_l[0] +=
    q_2dsfl_open_loop_P.DerivativeFilter2_A_g[0] *
    q_2dsfl_open_loop_X.DerivativeFilter2_CSTATE_l[0];
  _rtXdot->DerivativeFilter2_CSTATE_l[1] = 0.0;
  _rtXdot->DerivativeFilter2_CSTATE_l[0] +=
    q_2dsfl_open_loop_P.DerivativeFilter2_A_g[1] *
    q_2dsfl_open_loop_X.DerivativeFilter2_CSTATE_l[1];
  _rtXdot->DerivativeFilter2_CSTATE_l[1] +=
    q_2dsfl_open_loop_X.DerivativeFilter2_CSTATE_l[0];
  _rtXdot->DerivativeFilter2_CSTATE_l[0] +=
    q_2dsfl_open_loop_B.StraintoDeflection_g;
}

/* Model initialize function */
void q_2dsfl_open_loop_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: q_2dsfl_open_loop/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &q_2dsfl_open_loop_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (q_2dsfl_open_loop_DW.HILInitialize_Card,
       "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(q_2dsfl_open_loop_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
      return;
    }

    if ((q_2dsfl_open_loop_P.HILInitialize_AIPStart && !is_switching) ||
        (q_2dsfl_open_loop_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &q_2dsfl_open_loop_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (q_2dsfl_open_loop_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &q_2dsfl_open_loop_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = q_2dsfl_open_loop_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges
        (q_2dsfl_open_loop_DW.HILInitialize_Card,
         q_2dsfl_open_loop_P.HILInitialize_AIChannels, 8U,
         &q_2dsfl_open_loop_DW.HILInitialize_AIMinimums[0],
         &q_2dsfl_open_loop_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
        return;
      }
    }

    if ((q_2dsfl_open_loop_P.HILInitialize_AOPStart && !is_switching) ||
        (q_2dsfl_open_loop_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &q_2dsfl_open_loop_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (q_2dsfl_open_loop_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &q_2dsfl_open_loop_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = q_2dsfl_open_loop_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (q_2dsfl_open_loop_DW.HILInitialize_Card,
         q_2dsfl_open_loop_P.HILInitialize_AOChannels, 8U,
         &q_2dsfl_open_loop_DW.HILInitialize_AOMinimums[0],
         &q_2dsfl_open_loop_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
        return;
      }
    }

    if ((q_2dsfl_open_loop_P.HILInitialize_AOStart && !is_switching) ||
        (q_2dsfl_open_loop_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &q_2dsfl_open_loop_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = q_2dsfl_open_loop_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(q_2dsfl_open_loop_DW.HILInitialize_Card,
        q_2dsfl_open_loop_P.HILInitialize_AOChannels, 8U,
        &q_2dsfl_open_loop_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
        return;
      }
    }

    if (q_2dsfl_open_loop_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &q_2dsfl_open_loop_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = q_2dsfl_open_loop_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (q_2dsfl_open_loop_DW.HILInitialize_Card,
         q_2dsfl_open_loop_P.HILInitialize_AOChannels, 8U,
         &q_2dsfl_open_loop_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
        return;
      }
    }

    if ((q_2dsfl_open_loop_P.HILInitialize_EIPStart && !is_switching) ||
        (q_2dsfl_open_loop_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &q_2dsfl_open_loop_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] =
            q_2dsfl_open_loop_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (q_2dsfl_open_loop_DW.HILInitialize_Card,
         q_2dsfl_open_loop_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &q_2dsfl_open_loop_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
        return;
      }
    }

    if ((q_2dsfl_open_loop_P.HILInitialize_EIStart && !is_switching) ||
        (q_2dsfl_open_loop_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &q_2dsfl_open_loop_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = q_2dsfl_open_loop_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(q_2dsfl_open_loop_DW.HILInitialize_Card,
        q_2dsfl_open_loop_P.HILInitialize_EIChannels, 8U,
        &q_2dsfl_open_loop_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
        return;
      }
    }

    if ((q_2dsfl_open_loop_P.HILInitialize_POPStart && !is_switching) ||
        (q_2dsfl_open_loop_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &q_2dsfl_open_loop_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = q_2dsfl_open_loop_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(q_2dsfl_open_loop_DW.HILInitialize_Card,
        q_2dsfl_open_loop_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &q_2dsfl_open_loop_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          q_2dsfl_open_loop_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &q_2dsfl_open_loop_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            q_2dsfl_open_loop_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = (p_HILInitialize_POChannels[i1]);
            q_2dsfl_open_loop_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = q_2dsfl_open_loop_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            q_2dsfl_open_loop_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            q_2dsfl_open_loop_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              q_2dsfl_open_loop_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(q_2dsfl_open_loop_DW.HILInitialize_Card,
          &q_2dsfl_open_loop_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes,
          &q_2dsfl_open_loop_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(q_2dsfl_open_loop_DW.HILInitialize_Card,
          &q_2dsfl_open_loop_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &q_2dsfl_open_loop_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &q_2dsfl_open_loop_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            q_2dsfl_open_loop_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &q_2dsfl_open_loop_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = q_2dsfl_open_loop_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &q_2dsfl_open_loop_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = q_2dsfl_open_loop_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(q_2dsfl_open_loop_DW.HILInitialize_Card,
        q_2dsfl_open_loop_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *)
        &q_2dsfl_open_loop_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &q_2dsfl_open_loop_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &q_2dsfl_open_loop_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &q_2dsfl_open_loop_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = q_2dsfl_open_loop_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &q_2dsfl_open_loop_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = q_2dsfl_open_loop_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(q_2dsfl_open_loop_DW.HILInitialize_Card,
        q_2dsfl_open_loop_P.HILInitialize_POChannels, 8U,
        &q_2dsfl_open_loop_DW.HILInitialize_POSortedFreqs[0],
        &q_2dsfl_open_loop_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
        return;
      }
    }

    if ((q_2dsfl_open_loop_P.HILInitialize_POStart && !is_switching) ||
        (q_2dsfl_open_loop_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &q_2dsfl_open_loop_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = q_2dsfl_open_loop_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(q_2dsfl_open_loop_DW.HILInitialize_Card,
        q_2dsfl_open_loop_P.HILInitialize_POChannels, 8U,
        &q_2dsfl_open_loop_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
        return;
      }
    }

    if (q_2dsfl_open_loop_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &q_2dsfl_open_loop_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = q_2dsfl_open_loop_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (q_2dsfl_open_loop_DW.HILInitialize_Card,
         q_2dsfl_open_loop_P.HILInitialize_POChannels, 8U,
         &q_2dsfl_open_loop_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S1>/HIL Read Encoder Timebase' */

  /* S-Function Block: q_2dsfl_open_loop/1st Stage: 2-DOF SFL Robot + Q8: Actual Plant/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (q_2dsfl_open_loop_DW.HILInitialize_Card,
       q_2dsfl_open_loop_P.HILReadEncoderTimebase_SamplesI,
       &q_2dsfl_open_loop_P.HILReadEncoderTimebase_Channels, 1,
       &q_2dsfl_open_loop_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (q_2dsfl_open_loop_DW.HILReadEncoderTimebase_Task,
         (t_buffer_overflow_mode)
         (q_2dsfl_open_loop_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
    }
  }

  /* Start for Atomic SubSystem: '<S1>/Bias Removal' */
  q_2dsfl_open__BiasRemoval_Start(&q_2dsfl_open_loop_DW.BiasRemoval);

  /* End of Start for SubSystem: '<S1>/Bias Removal' */

  /* Start for Enabled SubSystem: '<S1>/Position Watchdog' */
  q_2dsfl_open_loop_DW.PositionWatchdog_MODE_k = false;

  /* End of Start for SubSystem: '<S1>/Position Watchdog' */

  /* Start for Atomic SubSystem: '<S2>/Bias Removal' */
  q_2dsfl_open__BiasRemoval_Start(&q_2dsfl_open_loop_DW.BiasRemoval_e);

  /* End of Start for SubSystem: '<S2>/Bias Removal' */

  /* Start for Enabled SubSystem: '<S2>/Position Watchdog' */
  q_2dsfl_open_loop_DW.PositionWatchdog_MODE = false;

  /* End of Start for SubSystem: '<S2>/Position Watchdog' */

  /* InitializeConditions for StateSpace: '<Root>/1st Stage: 2-DOF SFJ Robot: State-Space Model' */
  q_2dsfl_open_loop_X.ustStage2DOFSFJRobotStateSpaceM[0] =
    q_2dsfl_open_loop_P.ustStage2DOFSFJRobotStateSpaceM;
  q_2dsfl_open_loop_X.ustStage2DOFSFJRobotStateSpaceM[1] =
    q_2dsfl_open_loop_P.ustStage2DOFSFJRobotStateSpaceM;
  q_2dsfl_open_loop_X.ustStage2DOFSFJRobotStateSpaceM[2] =
    q_2dsfl_open_loop_P.ustStage2DOFSFJRobotStateSpaceM;
  q_2dsfl_open_loop_X.ustStage2DOFSFJRobotStateSpaceM[3] =
    q_2dsfl_open_loop_P.ustStage2DOFSFJRobotStateSpaceM;

  /* InitializeConditions for TransferFcn: '<S1>/Filter3' */
  q_2dsfl_open_loop_X.Filter3_CSTATE[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Derivative Filter1' */
  q_2dsfl_open_loop_X.DerivativeFilter1_CSTATE[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Derivative Filter2' */
  q_2dsfl_open_loop_X.DerivativeFilter2_CSTATE[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Filter3' */
  q_2dsfl_open_loop_X.Filter3_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Derivative Filter1' */
  q_2dsfl_open_loop_X.DerivativeFilter1_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S1>/Derivative Filter2' */
  q_2dsfl_open_loop_X.DerivativeFilter2_CSTATE[1] = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/2nd Stage: 2-DOF SFJ Robot: State-Space Model' */
  q_2dsfl_open_loop_X.undStage2DOFSFJRobotStateSpaceM[0] =
    q_2dsfl_open_loop_P.undStage2DOFSFJRobotStateSpaceM;
  q_2dsfl_open_loop_X.undStage2DOFSFJRobotStateSpaceM[1] =
    q_2dsfl_open_loop_P.undStage2DOFSFJRobotStateSpaceM;
  q_2dsfl_open_loop_X.undStage2DOFSFJRobotStateSpaceM[2] =
    q_2dsfl_open_loop_P.undStage2DOFSFJRobotStateSpaceM;
  q_2dsfl_open_loop_X.undStage2DOFSFJRobotStateSpaceM[3] =
    q_2dsfl_open_loop_P.undStage2DOFSFJRobotStateSpaceM;

  /* InitializeConditions for TransferFcn: '<S2>/Derivative Filter3' */
  q_2dsfl_open_loop_X.DerivativeFilter3_CSTATE[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Derivative Filter1' */
  q_2dsfl_open_loop_X.DerivativeFilter1_CSTATE_a[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Derivative Filter2' */
  q_2dsfl_open_loop_X.DerivativeFilter2_CSTATE_l[0] = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Derivative Filter3' */
  q_2dsfl_open_loop_X.DerivativeFilter3_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Derivative Filter1' */
  q_2dsfl_open_loop_X.DerivativeFilter1_CSTATE_a[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Derivative Filter2' */
  q_2dsfl_open_loop_X.DerivativeFilter2_CSTATE_l[1] = 0.0;

  /* SystemInitialize for Atomic SubSystem: '<S1>/Bias Removal' */
  q_2dsfl_open_l_BiasRemoval_Init(&q_2dsfl_open_loop_B.BiasRemoval,
    &q_2dsfl_open_loop_DW.BiasRemoval, &q_2dsfl_open_loop_P.BiasRemoval);

  /* End of SystemInitialize for SubSystem: '<S1>/Bias Removal' */

  /* SystemInitialize for Atomic SubSystem: '<S2>/Bias Removal' */
  q_2dsfl_open_l_BiasRemoval_Init(&q_2dsfl_open_loop_B.BiasRemoval_e,
    &q_2dsfl_open_loop_DW.BiasRemoval_e, &q_2dsfl_open_loop_P.BiasRemoval_e);

  /* End of SystemInitialize for SubSystem: '<S2>/Bias Removal' */
}

/* Model terminate function */
void q_2dsfl_open_loop_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: q_2dsfl_open_loop/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(q_2dsfl_open_loop_DW.HILInitialize_Card);
    hil_monitor_stop_all(q_2dsfl_open_loop_DW.HILInitialize_Card);
    is_switching = false;
    if ((q_2dsfl_open_loop_P.HILInitialize_AOTerminate && !is_switching) ||
        (q_2dsfl_open_loop_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &q_2dsfl_open_loop_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = q_2dsfl_open_loop_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((q_2dsfl_open_loop_P.HILInitialize_POTerminate && !is_switching) ||
        (q_2dsfl_open_loop_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &q_2dsfl_open_loop_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = q_2dsfl_open_loop_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    } else {
      num_final_pwm_outputs = 0;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(q_2dsfl_open_loop_DW.HILInitialize_Card
                         , q_2dsfl_open_loop_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , q_2dsfl_open_loop_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &q_2dsfl_open_loop_DW.HILInitialize_AOVoltages[0]
                         , &q_2dsfl_open_loop_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (q_2dsfl_open_loop_DW.HILInitialize_Card,
             q_2dsfl_open_loop_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &q_2dsfl_open_loop_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(q_2dsfl_open_loop_DW.HILInitialize_Card,
            q_2dsfl_open_loop_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &q_2dsfl_open_loop_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(q_2dsfl_open_loop_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(q_2dsfl_open_loop_DW.HILInitialize_Card);
    hil_monitor_delete_all(q_2dsfl_open_loop_DW.HILInitialize_Card);
    hil_close(q_2dsfl_open_loop_DW.HILInitialize_Card);
    q_2dsfl_open_loop_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  q_2dsfl_open_loop_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  q_2dsfl_open_loop_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  q_2dsfl_open_loop_initialize();
}

void MdlTerminate(void)
{
  q_2dsfl_open_loop_terminate();
}

/* Registration function */
RT_MODEL_q_2dsfl_open_loop_T *q_2dsfl_open_loop(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)q_2dsfl_open_loop_M, 0,
                sizeof(RT_MODEL_q_2dsfl_open_loop_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&q_2dsfl_open_loop_M->solverInfo,
                          &q_2dsfl_open_loop_M->Timing.simTimeStep);
    rtsiSetTPtr(&q_2dsfl_open_loop_M->solverInfo, &rtmGetTPtr
                (q_2dsfl_open_loop_M));
    rtsiSetStepSizePtr(&q_2dsfl_open_loop_M->solverInfo,
                       &q_2dsfl_open_loop_M->Timing.stepSize0);
    rtsiSetdXPtr(&q_2dsfl_open_loop_M->solverInfo, &q_2dsfl_open_loop_M->derivs);
    rtsiSetContStatesPtr(&q_2dsfl_open_loop_M->solverInfo, (real_T **)
                         &q_2dsfl_open_loop_M->contStates);
    rtsiSetNumContStatesPtr(&q_2dsfl_open_loop_M->solverInfo,
      &q_2dsfl_open_loop_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&q_2dsfl_open_loop_M->solverInfo,
      &q_2dsfl_open_loop_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&q_2dsfl_open_loop_M->solverInfo,
      &q_2dsfl_open_loop_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&q_2dsfl_open_loop_M->solverInfo,
      &q_2dsfl_open_loop_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&q_2dsfl_open_loop_M->solverInfo, (&rtmGetErrorStatus
      (q_2dsfl_open_loop_M)));
    rtsiSetRTModelPtr(&q_2dsfl_open_loop_M->solverInfo, q_2dsfl_open_loop_M);
  }

  rtsiSetSimTimeStep(&q_2dsfl_open_loop_M->solverInfo, MAJOR_TIME_STEP);
  q_2dsfl_open_loop_M->intgData.f[0] = q_2dsfl_open_loop_M->odeF[0];
  q_2dsfl_open_loop_M->contStates = ((real_T *) &q_2dsfl_open_loop_X);
  rtsiSetSolverData(&q_2dsfl_open_loop_M->solverInfo, (void *)
                    &q_2dsfl_open_loop_M->intgData);
  rtsiSetSolverName(&q_2dsfl_open_loop_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = q_2dsfl_open_loop_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    q_2dsfl_open_loop_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    q_2dsfl_open_loop_M->Timing.sampleTimes =
      (&q_2dsfl_open_loop_M->Timing.sampleTimesArray[0]);
    q_2dsfl_open_loop_M->Timing.offsetTimes =
      (&q_2dsfl_open_loop_M->Timing.offsetTimesArray[0]);

    /* task periods */
    q_2dsfl_open_loop_M->Timing.sampleTimes[0] = (0.0);
    q_2dsfl_open_loop_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    q_2dsfl_open_loop_M->Timing.offsetTimes[0] = (0.0);
    q_2dsfl_open_loop_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(q_2dsfl_open_loop_M, &q_2dsfl_open_loop_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = q_2dsfl_open_loop_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    q_2dsfl_open_loop_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(q_2dsfl_open_loop_M, -1);
  q_2dsfl_open_loop_M->Timing.stepSize0 = 0.002;
  q_2dsfl_open_loop_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  q_2dsfl_open_loop_M->Sizes.checksums[0] = (678128688U);
  q_2dsfl_open_loop_M->Sizes.checksums[1] = (1395511955U);
  q_2dsfl_open_loop_M->Sizes.checksums[2] = (4258944247U);
  q_2dsfl_open_loop_M->Sizes.checksums[3] = (461382240U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[16];
    q_2dsfl_open_loop_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &q_2dsfl_open_loop_DW.BiasRemoval.EnabledMovingAverage_SubsysRanB;
    systemRan[2] = (sysRanDType *)
      &q_2dsfl_open_loop_DW.BiasRemoval.SwitchCaseActionSubsystem_Subsy;
    systemRan[3] = (sysRanDType *)
      &q_2dsfl_open_loop_DW.BiasRemoval.SwitchCaseActionSubsystem1_Subs;
    systemRan[4] = (sysRanDType *)
      &q_2dsfl_open_loop_DW.BiasRemoval.SwitchCaseActionSubsystem2_Subs;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = (sysRanDType *)
      &q_2dsfl_open_loop_DW.PositionWatchdog_SubsysRanBC_b;
    systemRan[7] = (sysRanDType *)
      &q_2dsfl_open_loop_DW.BiasRemoval_e.EnabledMovingAverage_SubsysRanB;
    systemRan[8] = (sysRanDType *)
      &q_2dsfl_open_loop_DW.BiasRemoval_e.SwitchCaseActionSubsystem_Subsy;
    systemRan[9] = (sysRanDType *)
      &q_2dsfl_open_loop_DW.BiasRemoval_e.SwitchCaseActionSubsystem1_Subs;
    systemRan[10] = (sysRanDType *)
      &q_2dsfl_open_loop_DW.BiasRemoval_e.SwitchCaseActionSubsystem2_Subs;
    systemRan[11] = &rtAlwaysEnabled;
    systemRan[12] = (sysRanDType *)
      &q_2dsfl_open_loop_DW.PositionWatchdog_SubsysRanBC;
    systemRan[13] = &rtAlwaysEnabled;
    systemRan[14] = &rtAlwaysEnabled;
    systemRan[15] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(q_2dsfl_open_loop_M->extModeInfo,
      &q_2dsfl_open_loop_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(q_2dsfl_open_loop_M->extModeInfo,
                        q_2dsfl_open_loop_M->Sizes.checksums);
    rteiSetTPtr(q_2dsfl_open_loop_M->extModeInfo, rtmGetTPtr(q_2dsfl_open_loop_M));
  }

  q_2dsfl_open_loop_M->solverInfoPtr = (&q_2dsfl_open_loop_M->solverInfo);
  q_2dsfl_open_loop_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&q_2dsfl_open_loop_M->solverInfo, 0.002);
  rtsiSetSolverMode(&q_2dsfl_open_loop_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  q_2dsfl_open_loop_M->blockIO = ((void *) &q_2dsfl_open_loop_B);
  (void) memset(((void *) &q_2dsfl_open_loop_B), 0,
                sizeof(B_q_2dsfl_open_loop_T));

  {
    q_2dsfl_open_loop_B.Im_r1 = 0.0;
    q_2dsfl_open_loop_B.Motor1EncoderCalib = 0.0;
    q_2dsfl_open_loop_B.Gain[0] = 0.0;
    q_2dsfl_open_loop_B.Gain[1] = 0.0;
    q_2dsfl_open_loop_B.Gain_a[0] = 0.0;
    q_2dsfl_open_loop_B.Gain_a[1] = 0.0;
    q_2dsfl_open_loop_B.positiveCCW = 0.0;
    q_2dsfl_open_loop_B.VoltstoBaseStrain = 0.0;
    q_2dsfl_open_loop_B.Im_r1Saturation = 0.0;
    q_2dsfl_open_loop_B.VoltstoAmps = 0.0;
    q_2dsfl_open_loop_B.AmpstoVolts = 0.0;
    q_2dsfl_open_loop_B.StraintoDeflection = 0.0;
    q_2dsfl_open_loop_B.Motor2EncoderCalib = 0.0;
    q_2dsfl_open_loop_B.Gain_p[0] = 0.0;
    q_2dsfl_open_loop_B.Gain_p[1] = 0.0;
    q_2dsfl_open_loop_B.Gain_m[0] = 0.0;
    q_2dsfl_open_loop_B.Gain_m[1] = 0.0;
    q_2dsfl_open_loop_B.positiveCCW_l = 0.0;
    q_2dsfl_open_loop_B.VoltstoStrain = 0.0;
    q_2dsfl_open_loop_B.Im_r2Saturation = 0.0;
    q_2dsfl_open_loop_B.VoltstoAmps_h = 0.0;
    q_2dsfl_open_loop_B.AmpstoVolts_d = 0.0;
    q_2dsfl_open_loop_B.StraintoDeflection_g = 0.0;
    q_2dsfl_open_loop_B.BiasRemoval_e.Switch = 0.0;
    q_2dsfl_open_loop_B.BiasRemoval_e.VVavg = 0.0;
    q_2dsfl_open_loop_B.BiasRemoval_e.Vin = 0.0;
    q_2dsfl_open_loop_B.BiasRemoval_e.Constant = 0.0;
    q_2dsfl_open_loop_B.BiasRemoval_e.Count = 0.0;
    q_2dsfl_open_loop_B.BiasRemoval_e.Sum = 0.0;
    q_2dsfl_open_loop_B.BiasRemoval_e.div = 0.0;
    q_2dsfl_open_loop_B.BiasRemoval.Switch = 0.0;
    q_2dsfl_open_loop_B.BiasRemoval.VVavg = 0.0;
    q_2dsfl_open_loop_B.BiasRemoval.Vin = 0.0;
    q_2dsfl_open_loop_B.BiasRemoval.Constant = 0.0;
    q_2dsfl_open_loop_B.BiasRemoval.Count = 0.0;
    q_2dsfl_open_loop_B.BiasRemoval.Sum = 0.0;
    q_2dsfl_open_loop_B.BiasRemoval.div = 0.0;
  }

  /* parameters */
  q_2dsfl_open_loop_M->defaultParam = ((real_T *)&q_2dsfl_open_loop_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &q_2dsfl_open_loop_X;
    q_2dsfl_open_loop_M->contStates = (x);
    (void) memset((void *)&q_2dsfl_open_loop_X, 0,
                  sizeof(X_q_2dsfl_open_loop_T));
  }

  /* states (dwork) */
  q_2dsfl_open_loop_M->dwork = ((void *) &q_2dsfl_open_loop_DW);
  (void) memset((void *)&q_2dsfl_open_loop_DW, 0,
                sizeof(DW_q_2dsfl_open_loop_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_2dsfl_open_loop_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_2dsfl_open_loop_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_2dsfl_open_loop_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_2dsfl_open_loop_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_2dsfl_open_loop_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_2dsfl_open_loop_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_2dsfl_open_loop_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_2dsfl_open_loop_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  q_2dsfl_open_loop_DW.HILReadAnalog_Buffer[0] = 0.0;
  q_2dsfl_open_loop_DW.HILReadAnalog_Buffer[1] = 0.0;
  q_2dsfl_open_loop_DW.HILReadAnalog_Buffer_d[0] = 0.0;
  q_2dsfl_open_loop_DW.HILReadAnalog_Buffer_d[1] = 0.0;
  q_2dsfl_open_loop_DW.BiasRemoval_e.UnitDelay_DSTATE = 0.0;
  q_2dsfl_open_loop_DW.BiasRemoval_e.Sumk1n1xk_DSTATE = 0.0;
  q_2dsfl_open_loop_DW.BiasRemoval.UnitDelay_DSTATE = 0.0;
  q_2dsfl_open_loop_DW.BiasRemoval.Sumk1n1xk_DSTATE = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    q_2dsfl_open_loop_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 17;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  q_2dsfl_open_loop_M->Sizes.numContStates = (20);/* Number of continuous states */
  q_2dsfl_open_loop_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  q_2dsfl_open_loop_M->Sizes.numY = (0);/* Number of model outputs */
  q_2dsfl_open_loop_M->Sizes.numU = (0);/* Number of model inputs */
  q_2dsfl_open_loop_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  q_2dsfl_open_loop_M->Sizes.numSampTimes = (2);/* Number of sample times */
  q_2dsfl_open_loop_M->Sizes.numBlocks = (147);/* Number of blocks */
  q_2dsfl_open_loop_M->Sizes.numBlockIO = (47);/* Number of block outputs */
  q_2dsfl_open_loop_M->Sizes.numBlockPrms = (312);/* Sum of parameter "widths" */
  return q_2dsfl_open_loop_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
