/*
 * q_2dsfl_orr_hinf_private.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "q_2dsfl_orr_hinf".
 *
 * Model version              : 28.3
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Mon Jun  8 20:19:05 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_q_2dsfl_orr_hinf_private_h_
#define RTW_HEADER_q_2dsfl_orr_hinf_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "zero_crossing_types.h"
#include "q_2dsfl_orr_hinf.h"

/* A global buffer for storing error messages (defined in quanser_common library) */
EXTERN char _rt_error_message[512];
real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                 /* tMinusDelay = currentSimTime - delay */
  real_T tStart,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
  ;
extern void q_2dsfl_orr_hi_BiasRemoval_Init(B_BiasRemoval_q_2dsfl_orr_hin_T
  *localB, DW_BiasRemoval_q_2dsfl_orr_hi_T *localDW,
  P_BiasRemoval_q_2dsfl_orr_hin_T *localP);
extern void q_2dsfl_orr_h_BiasRemoval_Start(DW_BiasRemoval_q_2dsfl_orr_hi_T
  *localDW);
extern void q_2dsfl_orr__BiasRemoval_Update(B_BiasRemoval_q_2dsfl_orr_hin_T
  *localB, DW_BiasRemoval_q_2dsfl_orr_hi_T *localDW);
extern void q_2dsfl_orr_hinf_BiasRemoval(RT_MODEL_q_2dsfl_orr_hinf_T * const
  q_2dsfl_orr_hinf_M, real_T rtu_V, real_T rtp_switch_id, real_T rtp_start_time,
  real_T rtp_end_time, B_BiasRemoval_q_2dsfl_orr_hin_T *localB,
  DW_BiasRemoval_q_2dsfl_orr_hi_T *localDW, P_BiasRemoval_q_2dsfl_orr_hin_T
  *localP);

/* private model entry point functions */
extern void q_2dsfl_orr_hinf_derivatives(void);

#endif                              /* RTW_HEADER_q_2dsfl_orr_hinf_private_h_ */
