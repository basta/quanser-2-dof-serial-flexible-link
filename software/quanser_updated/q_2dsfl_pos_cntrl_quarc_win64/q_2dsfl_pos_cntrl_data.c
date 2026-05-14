/*
 * q_2dsfl_pos_cntrl_data.c
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

#include "q_2dsfl_pos_cntrl.h"
#include "q_2dsfl_pos_cntrl_private.h"

/* Block parameters (default storage) */
P_q_2dsfl_pos_cntrl_T q_2dsfl_pos_cntrl_P = {
  /* Variable: DTH1_LIM_ENABLE
   * Referenced by: '<S1>/Constant'
   */
  1.0,

  /* Variable: DTH2_LIM_ENABLE
   * Referenced by: '<S2>/Constant'
   */
  1.0,

  /* Variable: DTH2_MAX
   * Referenced by:
   *   '<S10>/X MAX'
   *   '<S22>/X MAX'
   */
  7.5,

  /* Variable: DTH2_MIN
   * Referenced by:
   *   '<S10>/X IN'
   *   '<S22>/X IN'
   */
  -7.5,

  /* Variable: K1
   * Referenced by: '<Root>/LQR Gain 1'
   */
  { 15.811388300841923, -42.931266034576765, 2.1825283220124763,
    -0.70654135223787584 },

  /* Variable: K1_defl_b
   * Referenced by: '<S1>/Strain to Deflection'
   */
  106.03674540682414,

  /* Variable: K1_strain_b
   * Referenced by: '<S1>/Volts to Base Strain'
   */
  0.0001286,

  /* Variable: K2
   * Referenced by: '<Root>/LQR Gain 2'
   */
  { 15.811388300841914, -40.334902221974758, 0.42388465683411214,
    -0.71090260284671969 },

  /* Variable: K2_defl_b
   * Referenced by: '<S2>/Strain to Deflection'
   */
  151.36857892763405,

  /* Variable: K2_strain_b
   * Referenced by: '<S2>/Volts to Strain'
   */
  0.0001235,

  /* Variable: KE_D1
   * Referenced by: '<S1>/Motor #1 Encoder Calib'
   */
  1.5339807878856413E-5,

  /* Variable: KE_D2
   * Referenced by: '<S2>/Motor #2 Encoder Calib'
   */
  3.0679615757712826E-5,

  /* Variable: LIMIT_SWITCHES_ENABLE
   * Referenced by: '<S4>/Constant'
   */
  1.0,

  /* Mask Parameter: RepeatingSequenceStair_OutValue
   * Referenced by: '<S46>/Vector'
   */
  { 0.0, 5.0, -5.0, 10.0, -10.0, 20.0, -20.0, 30.0, -30.0, 0.0 },

  /* Mask Parameter: BiasRemoval_end_time
   * Referenced by: '<S1>/Bias Removal'
   */
  1.0,

  /* Mask Parameter: BiasRemoval_end_time_g
   * Referenced by: '<S2>/Bias Removal'
   */
  0.2,

  /* Mask Parameter: BiasRemoval_start_time
   * Referenced by: '<S1>/Bias Removal'
   */
  0.0,

  /* Mask Parameter: BiasRemoval_start_time_l
   * Referenced by: '<S2>/Bias Removal'
   */
  0.0,

  /* Mask Parameter: BiasRemoval_switch_id
   * Referenced by: '<S1>/Bias Removal'
   */
  1.0,

  /* Mask Parameter: BiasRemoval_switch_id_n
   * Referenced by: '<S2>/Bias Removal'
   */
  1.0,

  /* Mask Parameter: HILReadAnalog_channels
   * Referenced by: '<S1>/HIL Read Analog'
   */
  { 0U, 2U },

  /* Mask Parameter: HILWriteAnalog_channels
   * Referenced by: '<S1>/HIL Write Analog'
   */
  0U,

  /* Mask Parameter: HILReadEncoder_channels
   * Referenced by: '<S2>/HIL Read Encoder'
   */
  1U,

  /* Mask Parameter: HILReadAnalog_channels_a
   * Referenced by: '<S2>/HIL Read Analog'
   */
  { 1U, 3U },

  /* Mask Parameter: HILWriteAnalog_channels_e
   * Referenced by: '<S2>/HIL Write Analog'
   */
  1U,

  /* Mask Parameter: HILWriteDigital_channels
   * Referenced by: '<S3>/HIL Write Digital'
   */
  { 0U, 1U, 4U },

  /* Mask Parameter: HILReadDigital_channels
   * Referenced by: '<S4>/HIL Read Digital'
   */
  { 0U, 1U, 2U, 3U },

  /* Mask Parameter: StopwithMessage_message_icon
   * Referenced by: '<S17>/Show Message on Host'
   */
  1,

  /* Mask Parameter: StopwithMessage1_message_icon
   * Referenced by: '<S18>/Show Message on Host'
   */
  1,

  /* Mask Parameter: StopwithMessage_message_icon_a
   * Referenced by: '<S29>/Show Message on Host'
   */
  1,

  /* Mask Parameter: StopwithMessage1_message_icon_g
   * Referenced by: '<S30>/Show Message on Host'
   */
  1,

  /* Mask Parameter: StopwithMessage_message_icon_c
   * Referenced by: '<S33>/Show Message on Host'
   */
  1,

  /* Mask Parameter: StopwithMessage1_message_icon_m
   * Referenced by: '<S34>/Show Message on Host'
   */
  1,

  /* Mask Parameter: StopwithMessage2_message_icon
   * Referenced by: '<S35>/Show Message on Host'
   */
  1,

  /* Mask Parameter: StopwithMessage3_message_icon
   * Referenced by: '<S36>/Show Message on Host'
   */
  1,

  /* Mask Parameter: LimitedCounter_uplimit
   * Referenced by: '<S49>/FixPt Switch'
   */
  9U,

  /* Expression: [1; 1; 1; 1 ]
   * Referenced by: '<Root>/Constant2'
   */
  { 1.0, 1.0, 1.0, 1.0 },

  /* Expression: [ 1; 0; 1; 0 ]
   * Referenced by: '<Root>/Cnstant1'
   */
  { 1.0, 0.0, 1.0, 0.0 },

  /* Expression: [1; 1; 1; 1 ]
   * Referenced by: '<Root>/Constant1'
   */
  { 1.0, 1.0, 1.0, 1.0 },

  /* Expression: [ 1; 0; 1; 0 ]
   * Referenced by: '<Root>/Cnstant2'
   */
  { 1.0, 0.0, 1.0, 0.0 },

  /* Expression: set_other_outputs_at_terminate
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: set_other_outputs_at_switch_out
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: set_other_outputs_at_start
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: set_other_outputs_at_switch_in
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: final_analog_outputs
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: final_pwm_outputs
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: analog_input_maximums
   * Referenced by: '<Root>/HIL Initialize'
   */
  10.0,

  /* Expression: analog_input_minimums
   * Referenced by: '<Root>/HIL Initialize'
   */
  -10.0,

  /* Expression: analog_output_maximums
   * Referenced by: '<Root>/HIL Initialize'
   */
  10.0,

  /* Expression: analog_output_minimums
   * Referenced by: '<Root>/HIL Initialize'
   */
  -10.0,

  /* Expression: initial_analog_outputs
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: watchdog_analog_outputs
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: pwm_frequency
   * Referenced by: '<Root>/HIL Initialize'
   */
  24305.934065934067,

  /* Expression: pwm_leading_deadband
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: pwm_trailing_deadband
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: initial_pwm_outputs
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: watchdog_pwm_outputs
   * Referenced by: '<Root>/HIL Initialize'
   */
  0.0,

  /* Expression: initial_position
   * Referenced by: '<S7>/Continuous Sigmoid'
   */
  0.0,

  /* Expression: initial_velocity
   * Referenced by: '<S7>/Continuous Sigmoid'
   */
  0.0,

  /* Expression: hold_off
   * Referenced by: '<S7>/Continuous Sigmoid'
   */
  0.5,

  /* Expression: i_max_velocity
   * Referenced by: '<S7>/Continuous Sigmoid'
   */
  2.35,

  /* Expression: i_max_acceleration
   * Referenced by: '<S7>/Continuous Sigmoid'
   */
  4.45,

  /* Expression:  [1; 0; 0; 0]
   * Referenced by: '<S7>/[ 1; 1; 0; 0 ]'
   */
  { 1.0, 0.0, 0.0, 0.0 },

  /* Computed Parameter: Filter3_A
   * Referenced by: '<S1>/Filter3'
   */
  { -22.61946710584651, -157.91367041742973 },

  /* Computed Parameter: Filter3_C
   * Referenced by: '<S1>/Filter3'
   */
  { 0.0, 157.91367041742973 },

  /* Computed Parameter: DerivativeFilter1_A
   * Referenced by: '<S1>/Derivative Filter1'
   */
  { -452.38934211693021, -63165.468166971892 },

  /* Computed Parameter: DerivativeFilter1_C
   * Referenced by: '<S1>/Derivative Filter1'
   */
  { 63165.468166971892, 0.0 },

  /* Computed Parameter: DerivativeFilter2_A
   * Referenced by: '<S1>/Derivative Filter2'
   */
  { -22.61946710584651, -157.91367041742973 },

  /* Computed Parameter: DerivativeFilter2_C
   * Referenced by: '<S1>/Derivative Filter2'
   */
  { 157.91367041742973, 0.0 },

  /* Expression: 180/pi
   * Referenced by: '<S41>/Gain'
   */
  57.295779513082323,

  /* Expression: 180/pi
   * Referenced by: '<S42>/Gain'
   */
  57.295779513082323,

  /* Expression: 0.94
   * Referenced by: '<Root>/Im_r1: Saturation'
   */
  0.94,

  /* Expression: -0.94
   * Referenced by: '<Root>/Im_r1: Saturation'
   */
  -0.94,

  /* Expression: -2.0
   * Referenced by: '<S1>/Volts to Amps'
   */
  -2.0,

  /* Expression: 1/0.5
   * Referenced by: '<S1>/Amps to Volts'
   */
  2.0,

  /* Expression: 180/pi
   * Referenced by: '<S11>/Gain'
   */
  57.295779513082323,

  /* Expression: 2.5
   * Referenced by: '<S8>/Transport Delay'
   */
  2.5,

  /* Expression: 0
   * Referenced by: '<S8>/Transport Delay'
   */
  0.0,

  /* Expression:  [1; 0; 0; 0]
   * Referenced by: '<S8>/[ 1; 1; 0; 0 ]1'
   */
  { 1.0, 0.0, 0.0, 0.0 },

  /* Computed Parameter: DerivativeFilter3_A
   * Referenced by: '<S2>/Derivative Filter3'
   */
  { -22.61946710584651, -157.91367041742973 },

  /* Computed Parameter: DerivativeFilter3_C
   * Referenced by: '<S2>/Derivative Filter3'
   */
  { 0.0, 157.91367041742973 },

  /* Computed Parameter: DerivativeFilter1_A_c
   * Referenced by: '<S2>/Derivative Filter1'
   */
  { -452.38934211693021, -63165.468166971892 },

  /* Computed Parameter: DerivativeFilter1_C_l
   * Referenced by: '<S2>/Derivative Filter1'
   */
  { 63165.468166971892, 0.0 },

  /* Computed Parameter: DerivativeFilter2_A_m
   * Referenced by: '<S2>/Derivative Filter2'
   */
  { -22.61946710584651, -157.91367041742973 },

  /* Computed Parameter: DerivativeFilter2_C_g
   * Referenced by: '<S2>/Derivative Filter2'
   */
  { 157.91367041742973, 0.0 },

  /* Expression: 180/pi
   * Referenced by: '<S43>/Gain'
   */
  57.295779513082323,

  /* Expression: 180/pi
   * Referenced by: '<S44>/Gain'
   */
  57.295779513082323,

  /* Expression: 1.2
   * Referenced by: '<Root>/Im_r2: Saturation'
   */
  1.2,

  /* Expression: -1.2
   * Referenced by: '<Root>/Im_r2: Saturation'
   */
  -1.2,

  /* Expression: -2.0
   * Referenced by: '<S2>/Volts to Amps'
   */
  -2.0,

  /* Expression: 1/0.5
   * Referenced by: '<S2>/Amps to Volts'
   */
  2.0,

  /* Expression: 180/pi
   * Referenced by: '<S23>/Gain'
   */
  57.295779513082323,

  /* Expression: 1
   * Referenced by: '<S8>/Square Wave1'
   */
  1.0,

  /* Expression: 0.1
   * Referenced by: '<S8>/Square Wave1'
   */
  0.1,

  /* Expression: 0
   * Referenced by: '<S8>/Amplitude (deg)1'
   */
  0.0,

  /* Expression: initial_position
   * Referenced by: '<S8>/Continuous Sigmoid1'
   */
  0.0,

  /* Expression: initial_velocity
   * Referenced by: '<S8>/Continuous Sigmoid1'
   */
  0.0,

  /* Expression: hold_off
   * Referenced by: '<S8>/Continuous Sigmoid1'
   */
  0.5,

  /* Expression: i_max_velocity
   * Referenced by: '<S8>/Continuous Sigmoid1'
   */
  2.0,

  /* Expression: i_max_acceleration
   * Referenced by: '<S8>/Continuous Sigmoid1'
   */
  5.0,

  /* Expression: pi/180
   * Referenced by: '<S50>/Gain1'
   */
  0.017453292519943295,

  /* Expression: [ 0 0 ]
   * Referenced by: '<S3>/Enable: Active Low'
   */
  { 0.0, 0.0 },

  /* Expression: 1
   * Referenced by: '<S3>/Master Enable: Active High'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S7>/Amplitude (deg)'
   */
  1.0,

  /* Expression: pi/180
   * Referenced by: '<S45>/Gain1'
   */
  0.017453292519943295,

  /* Computed Parameter: HILInitialize_CKChannels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0, 1, 2 },

  /* Computed Parameter: HILInitialize_DOWatchdog
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILInitialize_EIInitial
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POModes
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POConfiguration
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POAlignment
   * Referenced by: '<Root>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POPolarity
   * Referenced by: '<Root>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILReadEncoderTimebase_Clock
   * Referenced by: '<S1>/HIL Read Encoder Timebase'
   */
  0,

  /* Computed Parameter: HILInitialize_AIChannels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /* Computed Parameter: HILInitialize_AOChannels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /* Computed Parameter: HILInitialize_EIChannels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /* Computed Parameter: HILInitialize_EIQuadrature
   * Referenced by: '<Root>/HIL Initialize'
   */
  4U,

  /* Computed Parameter: HILInitialize_POChannels
   * Referenced by: '<Root>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /* Computed Parameter: HILReadEncoderTimebase_Channels
   * Referenced by: '<S1>/HIL Read Encoder Timebase'
   */
  0U,

  /* Computed Parameter: HILReadEncoderTimebase_SamplesI
   * Referenced by: '<S1>/HIL Read Encoder Timebase'
   */
  500U,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S19>/Constant'
   */
  false,

  /* Computed Parameter: Constant_Value_a
   * Referenced by: '<S20>/Constant'
   */
  false,

  /* Computed Parameter: Constant_Value_p
   * Referenced by: '<S31>/Constant'
   */
  false,

  /* Computed Parameter: Constant_Value_f
   * Referenced by: '<S32>/Constant'
   */
  false,

  /* Computed Parameter: Constant_Value_g
   * Referenced by: '<S37>/Constant'
   */
  false,

  /* Computed Parameter: Constant_Value_fj
   * Referenced by: '<S38>/Constant'
   */
  false,

  /* Computed Parameter: Constant_Value_k
   * Referenced by: '<S39>/Constant'
   */
  false,

  /* Computed Parameter: Constant_Value_ks
   * Referenced by: '<S40>/Constant'
   */
  false,

  /* Computed Parameter: HILInitialize_Active
   * Referenced by: '<Root>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_AOTerminate
   * Referenced by: '<Root>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_AOExit
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOTerminate
   * Referenced by: '<Root>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_DOExit
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_POTerminate
   * Referenced by: '<Root>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_POExit
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_CKPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_CKPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_CKStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_CKEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_AIPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_AIPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_AOPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_AOPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_AOStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_AOEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_AOReset
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_DOEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOReset
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_EIPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_EIPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_EIStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_EIEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_POPStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_POPEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_POStart
   * Referenced by: '<Root>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_POEnter
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_POReset
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_OOReset
   * Referenced by: '<Root>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOFinal
   * Referenced by: '<Root>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_DOInitial
   * Referenced by: '<Root>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILReadEncoderTimebase_Active
   * Referenced by: '<S1>/HIL Read Encoder Timebase'
   */
  true,

  /* Computed Parameter: HILReadAnalog_Active
   * Referenced by: '<S1>/HIL Read Analog'
   */
  true,

  /* Computed Parameter: HILWriteAnalog_Active
   * Referenced by: '<S1>/HIL Write Analog'
   */
  false,

  /* Computed Parameter: HILReadEncoder_Active
   * Referenced by: '<S2>/HIL Read Encoder'
   */
  true,

  /* Computed Parameter: HILReadAnalog_Active_i
   * Referenced by: '<S2>/HIL Read Analog'
   */
  true,

  /* Computed Parameter: HILWriteAnalog_Active_f
   * Referenced by: '<S2>/HIL Write Analog'
   */
  false,

  /* Computed Parameter: HILWriteDigital_Active
   * Referenced by: '<S3>/HIL Write Digital'
   */
  false,

  /* Computed Parameter: HILReadDigital_Active
   * Referenced by: '<S4>/HIL Read Digital'
   */
  true,

  /* Computed Parameter: Constant_Value_d
   * Referenced by: '<S49>/Constant'
   */
  0U,

  /* Computed Parameter: HILReadEncoderTimebase_Overflow
   * Referenced by: '<S1>/HIL Read Encoder Timebase'
   */
  1U,

  /* Computed Parameter: ManualSwitch1_CurrentSetting
   * Referenced by: '<Root>/Manual Switch1'
   */
  1U,

  /* Computed Parameter: ManualSwitch2_CurrentSetting
   * Referenced by: '<Root>/Manual Switch2'
   */
  1U,

  /* Computed Parameter: Output_InitialCondition
   * Referenced by: '<S47>/Output'
   */
  0U,

  /* Computed Parameter: FixPtConstant_Value
   * Referenced by: '<S48>/FixPt Constant'
   */
  1U,

  /* Start of '<S2>/Bias Removal' */
  {
    /* Expression: 1
     * Referenced by: '<S28>/unity'
     */
    1.0,

    /* Expression: 0
     * Referenced by: '<S28>/Unit Delay'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S24>/Sum( k=1,n-1, x(k) )'
     */
    0.0,

    /* Expression: [0]
     * Referenced by: '<S25>/zero'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S25>/Constant'
     */
    0.0,

    /* Expression: [0]
     * Referenced by: '<S26>/Vbiased'
     */
    0.0,

    /* Expression: [0]
     * Referenced by: '<S27>/Vunbiased'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S21>/Step: start_time'
     */
    0.0,

    /* Expression: 1
     * Referenced by: '<S21>/Step: start_time'
     */
    1.0,

    /* Expression: 0
     * Referenced by: '<S21>/Step: end_time'
     */
    0.0,

    /* Expression: 1
     * Referenced by: '<S21>/Step: end_time'
     */
    1.0
  }
  ,

  /* End of '<S2>/Bias Removal' */

  /* Start of '<S1>/Bias Removal' */
  {
    /* Expression: 1
     * Referenced by: '<S16>/unity'
     */
    1.0,

    /* Expression: 0
     * Referenced by: '<S16>/Unit Delay'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S12>/Sum( k=1,n-1, x(k) )'
     */
    0.0,

    /* Expression: [0]
     * Referenced by: '<S13>/zero'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S13>/Constant'
     */
    0.0,

    /* Expression: [0]
     * Referenced by: '<S14>/Vbiased'
     */
    0.0,

    /* Expression: [0]
     * Referenced by: '<S15>/Vunbiased'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S9>/Step: start_time'
     */
    0.0,

    /* Expression: 1
     * Referenced by: '<S9>/Step: start_time'
     */
    1.0,

    /* Expression: 0
     * Referenced by: '<S9>/Step: end_time'
     */
    0.0,

    /* Expression: 1
     * Referenced by: '<S9>/Step: end_time'
     */
    1.0
  }
  /* End of '<S1>/Bias Removal' */
};
