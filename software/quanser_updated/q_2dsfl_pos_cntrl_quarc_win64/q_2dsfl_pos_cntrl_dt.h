/*
 * q_2dsfl_pos_cntrl_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "q_2dsfl_pos_cntrl".
 *
 * Model version              : 28.2
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Thu May 14 17:16:51 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(void*),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(t_task),
  sizeof(t_boolean),
  sizeof(t_card)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "t_task",
  "t_boolean",
  "t_card"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&q_2dsfl_pos_cntrl_B.ContinuousSigmoid_o1), 0, 0, 53 },

  { (char_T *)(&q_2dsfl_pos_cntrl_B.FixPtSwitch), 3, 0, 1 },

  { (char_T *)(&q_2dsfl_pos_cntrl_B.LogicalOperator4), 8, 0, 12 },

  { (char_T *)(&q_2dsfl_pos_cntrl_B.BiasRemoval_m.Switch), 0, 0, 7 },

  { (char_T *)(&q_2dsfl_pos_cntrl_B.BiasRemoval.Switch), 0, 0, 7 }
  ,

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.HILInitialize_AIMinimums[0]), 0, 0, 90 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.HILReadEncoderTimebase_Task), 14, 0, 1 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.HILInitialize_Card), 16, 0, 1 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.ContinuousSigmoid_RWORK.Time), 0, 0, 3 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.Scope_PWORK.LoggedData), 11, 0, 22 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.HILInitialize_ClockModes[0]), 6, 0, 45 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.HILInitialize_POSortedChans[0]), 7, 0, 8 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.TransportDelay_IWORK.Tail), 10, 0, 1 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.Output_DSTATE), 3, 0, 1 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.PositionWatchdog_SubsysRanBC), 2, 0, 2 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.ContinuousSigmoid_Flag), 3, 0, 2 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.HILWriteDigital_Buffer[0]), 15, 0, 7 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.PositionWatchdog_MODE), 8, 0, 2 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.BiasRemoval_m.UnitDelay_DSTATE), 0, 0, 2 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.BiasRemoval_m.SwitchCase_ActiveSubsystem),
    2, 0, 5 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.BiasRemoval_m.EnabledMovingAverage_MODE), 8,
    0, 1 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.BiasRemoval.UnitDelay_DSTATE), 0, 0, 2 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.BiasRemoval.SwitchCase_ActiveSubsystem), 2,
    0, 5 },

  { (char_T *)(&q_2dsfl_pos_cntrl_DW.BiasRemoval.EnabledMovingAverage_MODE), 8,
    0, 1 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  24U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&q_2dsfl_pos_cntrl_P.DTH1_LIM_ENABLE), 0, 0, 35 },

  { (char_T *)(&q_2dsfl_pos_cntrl_P.HILReadAnalog_channels[0]), 7, 0, 14 },

  { (char_T *)(&q_2dsfl_pos_cntrl_P.StopwithMessage_message_icon), 2, 0, 8 },

  { (char_T *)(&q_2dsfl_pos_cntrl_P.LimitedCounter_uplimit), 3, 0, 1 },

  { (char_T *)(&q_2dsfl_pos_cntrl_P.Constant2_Value[0]), 0, 0, 100 },

  { (char_T *)(&q_2dsfl_pos_cntrl_P.HILInitialize_CKChannels[0]), 6, 0, 10 },

  { (char_T *)(&q_2dsfl_pos_cntrl_P.HILInitialize_AIChannels[0]), 7, 0, 35 },

  { (char_T *)(&q_2dsfl_pos_cntrl_P.Constant_Value), 8, 0, 51 },

  { (char_T *)(&q_2dsfl_pos_cntrl_P.Constant_Value_d), 3, 0, 6 },

  { (char_T *)(&q_2dsfl_pos_cntrl_P.BiasRemoval_m.unity_Value), 0, 0, 11 },

  { (char_T *)(&q_2dsfl_pos_cntrl_P.BiasRemoval.unity_Value), 0, 0, 11 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  11U,
  rtPTransitions
};

/* [EOF] q_2dsfl_pos_cntrl_dt.h */
