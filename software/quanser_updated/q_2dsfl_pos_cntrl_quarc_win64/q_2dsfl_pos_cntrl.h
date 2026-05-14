/*
 * q_2dsfl_pos_cntrl.h
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

#ifndef RTW_HEADER_q_2dsfl_pos_cntrl_h_
#define RTW_HEADER_q_2dsfl_pos_cntrl_h_
#include <float.h>
#include <math.h>
#include <string.h>
#ifndef q_2dsfl_pos_cntrl_COMMON_INCLUDES_
#define q_2dsfl_pos_cntrl_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "dt_info.h"
#include "ext_work.h"
#include "hil.h"
#include "quanser_messages.h"
#include "quanser_sigmoid.h"
#include "quanser_extern.h"
#endif                                 /* q_2dsfl_pos_cntrl_COMMON_INCLUDES_ */

#include "q_2dsfl_pos_cntrl_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlockIO
#define rtmGetBlockIO(rtm)             ((rtm)->blockIO)
#endif

#ifndef rtmSetBlockIO
#define rtmSetBlockIO(rtm, val)        ((rtm)->blockIO = (val))
#endif

#ifndef rtmGetChecksums
#define rtmGetChecksums(rtm)           ((rtm)->Sizes.checksums)
#endif

#ifndef rtmSetChecksums
#define rtmSetChecksums(rtm, val)      ((rtm)->Sizes.checksums = (val))
#endif

#ifndef rtmGetConstBlockIO
#define rtmGetConstBlockIO(rtm)        ((rtm)->constBlockIO)
#endif

#ifndef rtmSetConstBlockIO
#define rtmSetConstBlockIO(rtm, val)   ((rtm)->constBlockIO = (val))
#endif

#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetCtrlRateMdlRefTiming
#define rtmGetCtrlRateMdlRefTiming(rtm) ()
#endif

#ifndef rtmSetCtrlRateMdlRefTiming
#define rtmSetCtrlRateMdlRefTiming(rtm, val) ()
#endif

#ifndef rtmGetCtrlRateMdlRefTimingPtr
#define rtmGetCtrlRateMdlRefTimingPtr(rtm) ()
#endif

#ifndef rtmSetCtrlRateMdlRefTimingPtr
#define rtmSetCtrlRateMdlRefTimingPtr(rtm, val) ()
#endif

#ifndef rtmGetCtrlRateNumTicksToNextHit
#define rtmGetCtrlRateNumTicksToNextHit(rtm) ()
#endif

#ifndef rtmSetCtrlRateNumTicksToNextHit
#define rtmSetCtrlRateNumTicksToNextHit(rtm, val) ()
#endif

#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm)         ()
#endif

#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val)    ()
#endif

#ifndef rtmGetDefaultParam
#define rtmGetDefaultParam(rtm)        ((rtm)->defaultParam)
#endif

#ifndef rtmSetDefaultParam
#define rtmSetDefaultParam(rtm, val)   ((rtm)->defaultParam = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetDirectFeedThrough
#define rtmGetDirectFeedThrough(rtm)   ((rtm)->Sizes.sysDirFeedThru)
#endif

#ifndef rtmSetDirectFeedThrough
#define rtmSetDirectFeedThrough(rtm, val) ((rtm)->Sizes.sysDirFeedThru = (val))
#endif

#ifndef rtmGetErrorStatusFlag
#define rtmGetErrorStatusFlag(rtm)     ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatusFlag
#define rtmSetErrorStatusFlag(rtm, val) ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetFinalTime
#define rtmSetFinalTime(rtm, val)      ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetFirstInitCondFlag
#define rtmGetFirstInitCondFlag(rtm)   ()
#endif

#ifndef rtmSetFirstInitCondFlag
#define rtmSetFirstInitCondFlag(rtm, val) ()
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetMdlRefGlobalRuntimeEventIndices
#define rtmGetMdlRefGlobalRuntimeEventIndices(rtm) ()
#endif

#ifndef rtmSetMdlRefGlobalRuntimeEventIndices
#define rtmSetMdlRefGlobalRuntimeEventIndices(rtm, val) ()
#endif

#ifndef rtmGetMdlRefGlobalTID
#define rtmGetMdlRefGlobalTID(rtm)     ()
#endif

#ifndef rtmSetMdlRefGlobalTID
#define rtmSetMdlRefGlobalTID(rtm, val) ()
#endif

#ifndef rtmGetMdlRefTriggerTID
#define rtmGetMdlRefTriggerTID(rtm)    ()
#endif

#ifndef rtmSetMdlRefTriggerTID
#define rtmSetMdlRefTriggerTID(rtm, val) ()
#endif

#ifndef rtmGetModelMappingInfo
#define rtmGetModelMappingInfo(rtm)    ((rtm)->SpecialInfo.mappingInfo)
#endif

#ifndef rtmSetModelMappingInfo
#define rtmSetModelMappingInfo(rtm, val) ((rtm)->SpecialInfo.mappingInfo = (val))
#endif

#ifndef rtmGetModelName
#define rtmGetModelName(rtm)           ((rtm)->modelName)
#endif

#ifndef rtmSetModelName
#define rtmSetModelName(rtm, val)      ((rtm)->modelName = (val))
#endif

#ifndef rtmGetNonInlinedSFcns
#define rtmGetNonInlinedSFcns(rtm)     ()
#endif

#ifndef rtmSetNonInlinedSFcns
#define rtmSetNonInlinedSFcns(rtm, val) ()
#endif

#ifndef rtmGetNumBlockIO
#define rtmGetNumBlockIO(rtm)          ((rtm)->Sizes.numBlockIO)
#endif

#ifndef rtmSetNumBlockIO
#define rtmSetNumBlockIO(rtm, val)     ((rtm)->Sizes.numBlockIO = (val))
#endif

#ifndef rtmGetNumBlockParams
#define rtmGetNumBlockParams(rtm)      ((rtm)->Sizes.numBlockPrms)
#endif

#ifndef rtmSetNumBlockParams
#define rtmSetNumBlockParams(rtm, val) ((rtm)->Sizes.numBlockPrms = (val))
#endif

#ifndef rtmGetNumBlocks
#define rtmGetNumBlocks(rtm)           ((rtm)->Sizes.numBlocks)
#endif

#ifndef rtmSetNumBlocks
#define rtmSetNumBlocks(rtm, val)      ((rtm)->Sizes.numBlocks = (val))
#endif

#ifndef rtmGetNumContStates
#define rtmGetNumContStates(rtm)       ((rtm)->Sizes.numContStates)
#endif

#ifndef rtmSetNumContStates
#define rtmSetNumContStates(rtm, val)  ((rtm)->Sizes.numContStates = (val))
#endif

#ifndef rtmGetNumDWork
#define rtmGetNumDWork(rtm)            ((rtm)->Sizes.numDwork)
#endif

#ifndef rtmSetNumDWork
#define rtmSetNumDWork(rtm, val)       ((rtm)->Sizes.numDwork = (val))
#endif

#ifndef rtmGetNumInputPorts
#define rtmGetNumInputPorts(rtm)       ((rtm)->Sizes.numIports)
#endif

#ifndef rtmSetNumInputPorts
#define rtmSetNumInputPorts(rtm, val)  ((rtm)->Sizes.numIports = (val))
#endif

#ifndef rtmGetNumNonSampledZCs
#define rtmGetNumNonSampledZCs(rtm)    ((rtm)->Sizes.numNonSampZCs)
#endif

#ifndef rtmSetNumNonSampledZCs
#define rtmSetNumNonSampledZCs(rtm, val) ((rtm)->Sizes.numNonSampZCs = (val))
#endif

#ifndef rtmGetNumOutputPorts
#define rtmGetNumOutputPorts(rtm)      ((rtm)->Sizes.numOports)
#endif

#ifndef rtmSetNumOutputPorts
#define rtmSetNumOutputPorts(rtm, val) ((rtm)->Sizes.numOports = (val))
#endif

#ifndef rtmGetNumPeriodicContStates
#define rtmGetNumPeriodicContStates(rtm) ((rtm)->Sizes.numPeriodicContStates)
#endif

#ifndef rtmSetNumPeriodicContStates
#define rtmSetNumPeriodicContStates(rtm, val) ((rtm)->Sizes.numPeriodicContStates = (val))
#endif

#ifndef rtmGetNumSFcnParams
#define rtmGetNumSFcnParams(rtm)       ((rtm)->Sizes.numSFcnPrms)
#endif

#ifndef rtmSetNumSFcnParams
#define rtmSetNumSFcnParams(rtm, val)  ((rtm)->Sizes.numSFcnPrms = (val))
#endif

#ifndef rtmGetNumSFunctions
#define rtmGetNumSFunctions(rtm)       ((rtm)->Sizes.numSFcns)
#endif

#ifndef rtmSetNumSFunctions
#define rtmSetNumSFunctions(rtm, val)  ((rtm)->Sizes.numSFcns = (val))
#endif

#ifndef rtmGetNumSampleTimes
#define rtmGetNumSampleTimes(rtm)      ((rtm)->Sizes.numSampTimes)
#endif

#ifndef rtmSetNumSampleTimes
#define rtmSetNumSampleTimes(rtm, val) ((rtm)->Sizes.numSampTimes = (val))
#endif

#ifndef rtmGetNumU
#define rtmGetNumU(rtm)                ((rtm)->Sizes.numU)
#endif

#ifndef rtmSetNumU
#define rtmSetNumU(rtm, val)           ((rtm)->Sizes.numU = (val))
#endif

#ifndef rtmGetNumY
#define rtmGetNumY(rtm)                ((rtm)->Sizes.numY)
#endif

#ifndef rtmSetNumY
#define rtmSetNumY(rtm, val)           ((rtm)->Sizes.numY = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ()
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ()
#endif

#ifndef rtmGetOffsetTimeArray
#define rtmGetOffsetTimeArray(rtm)     ((rtm)->Timing.offsetTimesArray)
#endif

#ifndef rtmSetOffsetTimeArray
#define rtmSetOffsetTimeArray(rtm, val) ((rtm)->Timing.offsetTimesArray = (val))
#endif

#ifndef rtmGetOffsetTimePtr
#define rtmGetOffsetTimePtr(rtm)       ((rtm)->Timing.offsetTimes)
#endif

#ifndef rtmSetOffsetTimePtr
#define rtmSetOffsetTimePtr(rtm, val)  ((rtm)->Timing.offsetTimes = (val))
#endif

#ifndef rtmGetOptions
#define rtmGetOptions(rtm)             ((rtm)->Sizes.options)
#endif

#ifndef rtmSetOptions
#define rtmSetOptions(rtm, val)        ((rtm)->Sizes.options = (val))
#endif

#ifndef rtmGetParamIsMalloced
#define rtmGetParamIsMalloced(rtm)     ()
#endif

#ifndef rtmSetParamIsMalloced
#define rtmSetParamIsMalloced(rtm, val) ()
#endif

#ifndef rtmGetPath
#define rtmGetPath(rtm)                ((rtm)->path)
#endif

#ifndef rtmSetPath
#define rtmSetPath(rtm, val)           ((rtm)->path = (val))
#endif

#ifndef rtmGetPerTaskSampleHits
#define rtmGetPerTaskSampleHits(rtm)   ()
#endif

#ifndef rtmSetPerTaskSampleHits
#define rtmSetPerTaskSampleHits(rtm, val) ()
#endif

#ifndef rtmGetPerTaskSampleHitsArray
#define rtmGetPerTaskSampleHitsArray(rtm) ((rtm)->Timing.perTaskSampleHitsArray)
#endif

#ifndef rtmSetPerTaskSampleHitsArray
#define rtmSetPerTaskSampleHitsArray(rtm, val) ((rtm)->Timing.perTaskSampleHitsArray = (val))
#endif

#ifndef rtmGetPerTaskSampleHitsPtr
#define rtmGetPerTaskSampleHitsPtr(rtm) ((rtm)->Timing.perTaskSampleHits)
#endif

#ifndef rtmSetPerTaskSampleHitsPtr
#define rtmSetPerTaskSampleHitsPtr(rtm, val) ((rtm)->Timing.perTaskSampleHits = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetPrevZCSigState
#define rtmGetPrevZCSigState(rtm)      ((rtm)->prevZCSigState)
#endif

#ifndef rtmSetPrevZCSigState
#define rtmSetPrevZCSigState(rtm, val) ((rtm)->prevZCSigState = (val))
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmSetRTWExtModeInfo
#define rtmSetRTWExtModeInfo(rtm, val) ((rtm)->extModeInfo = (val))
#endif

#ifndef rtmGetRTWGeneratedSFcn
#define rtmGetRTWGeneratedSFcn(rtm)    ((rtm)->Sizes.rtwGenSfcn)
#endif

#ifndef rtmSetRTWGeneratedSFcn
#define rtmSetRTWGeneratedSFcn(rtm, val) ((rtm)->Sizes.rtwGenSfcn = (val))
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ()
#endif

#ifndef rtmSetRTWLogInfo
#define rtmSetRTWLogInfo(rtm, val)     ()
#endif

#ifndef rtmGetRTWRTModelMethodsInfo
#define rtmGetRTWRTModelMethodsInfo(rtm) ()
#endif

#ifndef rtmSetRTWRTModelMethodsInfo
#define rtmSetRTWRTModelMethodsInfo(rtm, val) ()
#endif

#ifndef rtmGetRTWSfcnInfo
#define rtmGetRTWSfcnInfo(rtm)         ((rtm)->sfcnInfo)
#endif

#ifndef rtmSetRTWSfcnInfo
#define rtmSetRTWSfcnInfo(rtm, val)    ((rtm)->sfcnInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfo
#define rtmGetRTWSolverInfo(rtm)       ((rtm)->solverInfo)
#endif

#ifndef rtmSetRTWSolverInfo
#define rtmSetRTWSolverInfo(rtm, val)  ((rtm)->solverInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfoPtr
#define rtmGetRTWSolverInfoPtr(rtm)    ((rtm)->solverInfoPtr)
#endif

#ifndef rtmSetRTWSolverInfoPtr
#define rtmSetRTWSolverInfoPtr(rtm, val) ((rtm)->solverInfoPtr = (val))
#endif

#ifndef rtmGetReservedForXPC
#define rtmGetReservedForXPC(rtm)      ((rtm)->SpecialInfo.xpcData)
#endif

#ifndef rtmSetReservedForXPC
#define rtmSetReservedForXPC(rtm, val) ((rtm)->SpecialInfo.xpcData = (val))
#endif

#ifndef rtmGetRootDWork
#define rtmGetRootDWork(rtm)           ((rtm)->dwork)
#endif

#ifndef rtmSetRootDWork
#define rtmSetRootDWork(rtm, val)      ((rtm)->dwork = (val))
#endif

#ifndef rtmGetSFunctions
#define rtmGetSFunctions(rtm)          ((rtm)->childSfunctions)
#endif

#ifndef rtmSetSFunctions
#define rtmSetSFunctions(rtm, val)     ((rtm)->childSfunctions = (val))
#endif

#ifndef rtmGetSampleHitArray
#define rtmGetSampleHitArray(rtm)      ((rtm)->Timing.sampleHitArray)
#endif

#ifndef rtmSetSampleHitArray
#define rtmSetSampleHitArray(rtm, val) ((rtm)->Timing.sampleHitArray = (val))
#endif

#ifndef rtmGetSampleHitPtr
#define rtmGetSampleHitPtr(rtm)        ((rtm)->Timing.sampleHits)
#endif

#ifndef rtmSetSampleHitPtr
#define rtmSetSampleHitPtr(rtm, val)   ((rtm)->Timing.sampleHits = (val))
#endif

#ifndef rtmGetSampleTimeArray
#define rtmGetSampleTimeArray(rtm)     ((rtm)->Timing.sampleTimesArray)
#endif

#ifndef rtmSetSampleTimeArray
#define rtmSetSampleTimeArray(rtm, val) ((rtm)->Timing.sampleTimesArray = (val))
#endif

#ifndef rtmGetSampleTimePtr
#define rtmGetSampleTimePtr(rtm)       ((rtm)->Timing.sampleTimes)
#endif

#ifndef rtmSetSampleTimePtr
#define rtmSetSampleTimePtr(rtm, val)  ((rtm)->Timing.sampleTimes = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDArray
#define rtmGetSampleTimeTaskIDArray(rtm) ((rtm)->Timing.sampleTimeTaskIDArray)
#endif

#ifndef rtmSetSampleTimeTaskIDArray
#define rtmSetSampleTimeTaskIDArray(rtm, val) ((rtm)->Timing.sampleTimeTaskIDArray = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDPtr
#define rtmGetSampleTimeTaskIDPtr(rtm) ((rtm)->Timing.sampleTimeTaskIDPtr)
#endif

#ifndef rtmSetSampleTimeTaskIDPtr
#define rtmSetSampleTimeTaskIDPtr(rtm, val) ((rtm)->Timing.sampleTimeTaskIDPtr = (val))
#endif

#ifndef rtmGetSelf
#define rtmGetSelf(rtm)                ()
#endif

#ifndef rtmSetSelf
#define rtmSetSelf(rtm, val)           ()
#endif

#ifndef rtmGetSimMode
#define rtmGetSimMode(rtm)             ((rtm)->simMode)
#endif

#ifndef rtmSetSimMode
#define rtmSetSimMode(rtm, val)        ((rtm)->simMode = (val))
#endif

#ifndef rtmGetSimTimeStep
#define rtmGetSimTimeStep(rtm)         ((rtm)->Timing.simTimeStep)
#endif

#ifndef rtmSetSimTimeStep
#define rtmSetSimTimeStep(rtm, val)    ((rtm)->Timing.simTimeStep = (val))
#endif

#ifndef rtmGetStartTime
#define rtmGetStartTime(rtm)           ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetStartTime
#define rtmSetStartTime(rtm, val)      ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmGetStepSize
#define rtmGetStepSize(rtm)            ((rtm)->Timing.stepSize)
#endif

#ifndef rtmSetStepSize
#define rtmSetStepSize(rtm, val)       ((rtm)->Timing.stepSize = (val))
#endif

#ifndef rtmGetStopRequestedFlag
#define rtmGetStopRequestedFlag(rtm)   ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequestedFlag
#define rtmSetStopRequestedFlag(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetTaskCounters
#define rtmGetTaskCounters(rtm)        ((rtm)->Timing.TaskCounters)
#endif

#ifndef rtmSetTaskCounters
#define rtmSetTaskCounters(rtm, val)   ((rtm)->Timing.TaskCounters = (val))
#endif

#ifndef rtmGetTaskTimeArray
#define rtmGetTaskTimeArray(rtm)       ((rtm)->Timing.tArray)
#endif

#ifndef rtmSetTaskTimeArray
#define rtmSetTaskTimeArray(rtm, val)  ((rtm)->Timing.tArray = (val))
#endif

#ifndef rtmGetTimePtr
#define rtmGetTimePtr(rtm)             ((rtm)->Timing.t)
#endif

#ifndef rtmSetTimePtr
#define rtmSetTimePtr(rtm, val)        ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTimingData
#define rtmGetTimingData(rtm)          ((rtm)->Timing.timingData)
#endif

#ifndef rtmSetTimingData
#define rtmSetTimingData(rtm, val)     ((rtm)->Timing.timingData = (val))
#endif

#ifndef rtmGetU
#define rtmGetU(rtm)                   ((rtm)->inputs)
#endif

#ifndef rtmSetU
#define rtmSetU(rtm, val)              ((rtm)->inputs = (val))
#endif

#ifndef rtmGetVarNextHitTimesListPtr
#define rtmGetVarNextHitTimesListPtr(rtm) ((rtm)->Timing.varNextHitTimesList)
#endif

#ifndef rtmSetVarNextHitTimesListPtr
#define rtmSetVarNextHitTimesListPtr(rtm, val) ((rtm)->Timing.varNextHitTimesList = (val))
#endif

#ifndef rtmGetY
#define rtmGetY(rtm)                   ((rtm)->outputs)
#endif

#ifndef rtmSetY
#define rtmSetY(rtm, val)              ((rtm)->outputs = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetZCSignalValues
#define rtmGetZCSignalValues(rtm)      ((rtm)->zcSignalValues)
#endif

#ifndef rtmSetZCSignalValues
#define rtmSetZCSignalValues(rtm, val) ((rtm)->zcSignalValues = (val))
#endif

#ifndef rtmGet_TimeOfLastOutput
#define rtmGet_TimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmSet_TimeOfLastOutput
#define rtmSet_TimeOfLastOutput(rtm, val) ((rtm)->Timing.timeOfLastOutput = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGettimingBridge
#define rtmGettimingBridge(rtm)        ()
#endif

#ifndef rtmSettimingBridge
#define rtmSettimingBridge(rtm, val)   ()
#endif

#ifndef rtmGetChecksumVal
#define rtmGetChecksumVal(rtm, idx)    ((rtm)->Sizes.checksums[idx])
#endif

#ifndef rtmSetChecksumVal
#define rtmSetChecksumVal(rtm, idx, val) ((rtm)->Sizes.checksums[idx] = (val))
#endif

#ifndef rtmGetDWork
#define rtmGetDWork(rtm, idx)          ((rtm)->dwork[idx])
#endif

#ifndef rtmSetDWork
#define rtmSetDWork(rtm, idx, val)     ((rtm)->dwork[idx] = (val))
#endif

#ifndef rtmGetOffsetTime
#define rtmGetOffsetTime(rtm, idx)     ((rtm)->Timing.offsetTimes[idx])
#endif

#ifndef rtmSetOffsetTime
#define rtmSetOffsetTime(rtm, idx, val) ((rtm)->Timing.offsetTimes[idx] = (val))
#endif

#ifndef rtmGetSFunction
#define rtmGetSFunction(rtm, idx)      ((rtm)->childSfunctions[idx])
#endif

#ifndef rtmSetSFunction
#define rtmSetSFunction(rtm, idx, val) ((rtm)->childSfunctions[idx] = (val))
#endif

#ifndef rtmGetSampleTime
#define rtmGetSampleTime(rtm, idx)     ((rtm)->Timing.sampleTimes[idx])
#endif

#ifndef rtmSetSampleTime
#define rtmSetSampleTime(rtm, idx, val) ((rtm)->Timing.sampleTimes[idx] = (val))
#endif

#ifndef rtmGetSampleTimeTaskID
#define rtmGetSampleTimeTaskID(rtm, idx) ((rtm)->Timing.sampleTimeTaskIDPtr[idx])
#endif

#ifndef rtmSetSampleTimeTaskID
#define rtmSetSampleTimeTaskID(rtm, idx, val) ((rtm)->Timing.sampleTimeTaskIDPtr[idx] = (val))
#endif

#ifndef rtmGetVarNextHitTimeList
#define rtmGetVarNextHitTimeList(rtm, idx) ((rtm)->Timing.varNextHitTimesList[idx])
#endif

#ifndef rtmSetVarNextHitTimeList
#define rtmSetVarNextHitTimeList(rtm, idx, val) ((rtm)->Timing.varNextHitTimesList[idx] = (val))
#endif

#ifndef rtmIsContinuousTask
#define rtmIsContinuousTask(rtm, tid)  ((tid) <= 1)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmIsSampleHit
#define rtmIsSampleHit(rtm, sti, tid)  (((rtm)->Timing.sampleTimeTaskIDPtr[sti] == (tid)))
#endif

#ifndef rtmStepTask
#define rtmStepTask(rtm, idx)          ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmSetT
#define rtmSetT(rtm, val)                                        /* Do Nothing */
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetTStart
#define rtmSetTStart(rtm, val)         ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmTaskCounter
#define rtmTaskCounter(rtm, idx)       ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

#ifndef rtmGetTaskTime
#define rtmGetTaskTime(rtm, sti)       (rtmGetTPtr((rtm))[(rtm)->Timing.sampleTimeTaskIDPtr[sti]])
#endif

#ifndef rtmSetTaskTime
#define rtmSetTaskTime(rtm, sti, val)  (rtmGetTPtr((rtm))[sti] = (val))
#endif

#ifndef rtmGetTimeOfLastOutput
#define rtmGetTimeOfLastOutput(rtm)    ((rtm)->Timing.timeOfLastOutput)
#endif

#ifdef rtmGetRTWSolverInfo
#undef rtmGetRTWSolverInfo
#endif

#define rtmGetRTWSolverInfo(rtm)       &((rtm)->solverInfo)

/* Definition for use in the target main file */
#define q_2dsfl_pos_cntrl_rtModel      RT_MODEL_q_2dsfl_pos_cntrl_T

/* Block signals for system '<S1>/Bias Removal' */
typedef struct {
  real_T Switch;                       /* '<S9>/Switch' */
  real_T VVavg;                        /* '<S15>/V-Vavg' */
  real_T Vin;                          /* '<S14>/Vin' */
  real_T Constant;                     /* '<S13>/Constant' */
  real_T Count;                        /* '<S16>/Count' */
  real_T Sum;                          /* '<S12>/Sum' */
  real_T div;                          /* '<S12>/div' */
} B_BiasRemoval_q_2dsfl_pos_cnt_T;

/* Block states (default storage) for system '<S1>/Bias Removal' */
typedef struct {
  real_T UnitDelay_DSTATE;             /* '<S16>/Unit Delay' */
  real_T Sumk1n1xk_DSTATE;             /* '<S12>/Sum( k=1,n-1, x(k) )' */
  int8_T SwitchCase_ActiveSubsystem;   /* '<S9>/Switch Case' */
  int8_T SwitchCaseActionSubsystem2_Subs;
                                      /* '<S9>/Switch Case Action Subsystem2' */
  int8_T SwitchCaseActionSubsystem1_Subs;
                                      /* '<S9>/Switch Case Action Subsystem1' */
  int8_T SwitchCaseActionSubsystem_Subsy;/* '<S9>/Switch Case Action Subsystem' */
  int8_T EnabledMovingAverage_SubsysRanB;/* '<S9>/Enabled Moving Average' */
  boolean_T EnabledMovingAverage_MODE; /* '<S9>/Enabled Moving Average' */
} DW_BiasRemoval_q_2dsfl_pos_cn_T;

/* Block signals (default storage) */
typedef struct {
  real_T ContinuousSigmoid_o1;         /* '<S7>/Continuous Sigmoid' */
  real_T ContinuousSigmoid_o2;         /* '<S7>/Continuous Sigmoid' */
  real_T ContinuousSigmoid_o3;         /* '<S7>/Continuous Sigmoid' */
  real_T ContinuousSigmoid_o4;         /* '<S7>/Continuous Sigmoid' */
  real_T u100[4];                      /* '<S7>/[ 1; 1; 0; 0 ]' */
  real_T Motor1EncoderCalib;           /* '<S1>/Motor #1 Encoder Calib' */
  real_T Filter3;                      /* '<S1>/Filter3' */
  real_T DerivativeFilter1;            /* '<S1>/Derivative Filter1' */
  real_T DerivativeFilter2;            /* '<S1>/Derivative Filter2' */
  real_T Gain[2];                      /* '<S41>/Gain' */
  real_T Gain_n[2];                    /* '<S42>/Gain' */
  real_T ManualSwitch1[4];             /* '<Root>/Manual Switch1' */
  real_T Im_r1Saturation;              /* '<Root>/Im_r1: Saturation' */
  real_T VoltstoAmps;                  /* '<S1>/Volts to Amps' */
  real_T AmpstoVolts;                  /* '<S1>/Amps to Volts' */
  real_T positiveCCW;                  /* '<S1>/positive  CCW' */
  real_T StraintoDeflection;           /* '<S1>/Strain to Deflection' */
  real_T u1001[4];                     /* '<S8>/[ 1; 1; 0; 0 ]1' */
  real_T Motor2EncoderCalib;           /* '<S2>/Motor #2 Encoder Calib' */
  real_T DerivativeFilter3;            /* '<S2>/Derivative Filter3' */
  real_T DerivativeFilter1_l;          /* '<S2>/Derivative Filter1' */
  real_T DerivativeFilter2_e;          /* '<S2>/Derivative Filter2' */
  real_T Gain_m[2];                    /* '<S43>/Gain' */
  real_T Gain_b[2];                    /* '<S44>/Gain' */
  real_T positiveCCW_h;                /* '<S2>/positive  CCW' */
  real_T VoltstoStrain;                /* '<S2>/Volts to Strain' */
  real_T ManualSwitch2[4];             /* '<Root>/Manual Switch2' */
  real_T Im_r2Saturation;              /* '<Root>/Im_r2: Saturation' */
  real_T VoltstoAmps_i;                /* '<S2>/Volts to Amps' */
  real_T AmpstoVolts_g;                /* '<S2>/Amps to Volts' */
  real_T StraintoDeflection_i;         /* '<S2>/Strain to Deflection' */
  real_T ContinuousSigmoid1_o1;        /* '<S8>/Continuous Sigmoid1' */
  real_T ContinuousSigmoid1_o2;        /* '<S8>/Continuous Sigmoid1' */
  real_T ContinuousSigmoid1_o3;        /* '<S8>/Continuous Sigmoid1' */
  real_T ContinuousSigmoid1_o4;        /* '<S8>/Continuous Sigmoid1' */
  real_T Gain1;                        /* '<S50>/Gain1' */
  real_T Gain1_e;                      /* '<S45>/Gain1' */
  uint8_T FixPtSwitch;                 /* '<S49>/FixPt Switch' */
  boolean_T LogicalOperator4;          /* '<S4>/Logical Operator4' */
  boolean_T LogicalOperator5;          /* '<S4>/Logical Operator5' */
  boolean_T LogicalOperator6;          /* '<S4>/Logical Operator6' */
  boolean_T LogicalOperator7;          /* '<S4>/Logical Operator7' */
  boolean_T CheckMaximumAllowedPosition;
                                    /* '<S22>/Check Maximum Allowed Position' */
  boolean_T Compare;                   /* '<S31>/Compare' */
  boolean_T CheckMinimumAllowedPosition;
                                    /* '<S22>/Check Minimum Allowed Position' */
  boolean_T Compare_j;                 /* '<S32>/Compare' */
  boolean_T CheckMaximumAllowedPosition_c;
                                    /* '<S10>/Check Maximum Allowed Position' */
  boolean_T Compare_c;                 /* '<S19>/Compare' */
  boolean_T CheckMinimumAllowedPosition_a;
                                    /* '<S10>/Check Minimum Allowed Position' */
  boolean_T Compare_e;                 /* '<S20>/Compare' */
  B_BiasRemoval_q_2dsfl_pos_cnt_T BiasRemoval_m;/* '<S2>/Bias Removal' */
  B_BiasRemoval_q_2dsfl_pos_cnt_T BiasRemoval;/* '<S1>/Bias Removal' */
} B_q_2dsfl_pos_cntrl_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T HILInitialize_AIMinimums[8];  /* '<Root>/HIL Initialize' */
  real_T HILInitialize_AIMaximums[8];  /* '<Root>/HIL Initialize' */
  real_T HILInitialize_AOMinimums[8];  /* '<Root>/HIL Initialize' */
  real_T HILInitialize_AOMaximums[8];  /* '<Root>/HIL Initialize' */
  real_T HILInitialize_AOVoltages[8];  /* '<Root>/HIL Initialize' */
  real_T HILInitialize_FilterFrequency[8];/* '<Root>/HIL Initialize' */
  real_T HILInitialize_POSortedFreqs[8];/* '<Root>/HIL Initialize' */
  real_T HILInitialize_POValues[8];    /* '<Root>/HIL Initialize' */
  real_T ContinuousSigmoid_Sigmoid[11];/* '<S7>/Continuous Sigmoid' */
  real_T HILReadAnalog_Buffer[2];      /* '<S1>/HIL Read Analog' */
  real_T HILReadAnalog_Buffer_p[2];    /* '<S2>/HIL Read Analog' */
  real_T ContinuousSigmoid1_Sigmoid[11];/* '<S8>/Continuous Sigmoid1' */
  t_task HILReadEncoderTimebase_Task;  /* '<S1>/HIL Read Encoder Timebase' */
  t_card HILInitialize_Card;           /* '<Root>/HIL Initialize' */
  struct {
    real_T Time;
    real_T Target;
    real_T PPos;
    real_T PVel;
    real_T MVel;
    real_T MAcc;
  } ContinuousSigmoid_RWORK;           /* '<S7>/Continuous Sigmoid' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[10000];
  } TransportDelay_RWORK;              /* '<S8>/Transport Delay' */

  struct {
    real_T Time;
    real_T Target;
    real_T PPos;
    real_T PVel;
    real_T MVel;
    real_T MAcc;
  } ContinuousSigmoid1_RWORK;          /* '<S8>/Continuous Sigmoid1' */

  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<Root>/Scope' */

  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<Root>/Scope1' */

  struct {
    void *LoggedData;
  } theta11deg_PWORK;                  /* '<S5>/theta11 (deg)' */

  struct {
    void *LoggedData;
  } theta12deg_PWORK;                  /* '<S5>/theta12 (deg)' */

  void *HILReadAnalog_PWORK;           /* '<S1>/HIL Read Analog' */
  struct {
    void *LoggedData;
  } CurrentResponse1A_PWORK;           /* '<S1>/Current Response #1 (A)' */

  void *HILWriteAnalog_PWORK;          /* '<S1>/HIL Write Analog' */
  struct {
    void *LoggedData;
  } StrainGauge0V_PWORK;               /* '<S1>/Strain Gauge 0 (V)' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK;              /* '<S8>/Transport Delay' */

  struct {
    void *LoggedData;
  } Scope2_PWORK;                      /* '<Root>/Scope2' */

  void *HILReadEncoder_PWORK;          /* '<S2>/HIL Read Encoder' */
  struct {
    void *LoggedData;
  } Scope3_PWORK;                      /* '<Root>/Scope3' */

  struct {
    void *LoggedData;
  } theta21deg_PWORK;                  /* '<S6>/theta21 (deg)' */

  struct {
    void *LoggedData;
  } theta22deg_PWORK;                  /* '<S6>/theta22 (deg)' */

  void *HILReadAnalog_PWORK_f;         /* '<S2>/HIL Read Analog' */
  struct {
    void *LoggedData;
  } BaseStrainmmmm_PWORK;              /* '<S2>/Base Strain (mm//mm)' */

  struct {
    void *LoggedData;
  } CurrentResponse2A_PWORK;           /* '<S2>/Current Response #2 (A)' */

  void *HILWriteAnalog_PWORK_l;        /* '<S2>/HIL Write Analog' */
  struct {
    void *LoggedData;
  } StrainGauge1V_PWORK;               /* '<S2>/Strain Gauge 1 (V)' */

  void *HILWriteDigital_PWORK;         /* '<S3>/HIL Write Digital' */
  void *HILReadDigital_PWORK;          /* '<S4>/HIL Read Digital' */
  int32_T HILInitialize_ClockModes[3]; /* '<Root>/HIL Initialize' */
  int32_T HILInitialize_QuadratureModes[8];/* '<Root>/HIL Initialize' */
  int32_T HILInitialize_InitialEICounts[8];/* '<Root>/HIL Initialize' */
  int32_T HILInitialize_POModeValues[8];/* '<Root>/HIL Initialize' */
  int32_T HILInitialize_POAlignValues[8];/* '<Root>/HIL Initialize' */
  int32_T HILInitialize_POPolarityVals[8];/* '<Root>/HIL Initialize' */
  int32_T HILReadEncoderTimebase_Buffer;/* '<S1>/HIL Read Encoder Timebase' */
  int32_T HILReadEncoder_Buffer;       /* '<S2>/HIL Read Encoder' */
  uint32_T HILInitialize_POSortedChans[8];/* '<Root>/HIL Initialize' */
  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK;              /* '<S8>/Transport Delay' */

  uint8_T Output_DSTATE;               /* '<S47>/Output' */
  int8_T PositionWatchdog_SubsysRanBC; /* '<S2>/Position Watchdog' */
  int8_T PositionWatchdog_SubsysRanBC_c;/* '<S1>/Position Watchdog' */
  uint8_T ContinuousSigmoid_Flag;      /* '<S7>/Continuous Sigmoid' */
  uint8_T ContinuousSigmoid1_Flag;     /* '<S8>/Continuous Sigmoid1' */
  t_boolean HILWriteDigital_Buffer[3]; /* '<S3>/HIL Write Digital' */
  t_boolean HILReadDigital_Buffer[4];  /* '<S4>/HIL Read Digital' */
  boolean_T PositionWatchdog_MODE;     /* '<S2>/Position Watchdog' */
  boolean_T PositionWatchdog_MODE_l;   /* '<S1>/Position Watchdog' */
  DW_BiasRemoval_q_2dsfl_pos_cn_T BiasRemoval_m;/* '<S2>/Bias Removal' */
  DW_BiasRemoval_q_2dsfl_pos_cn_T BiasRemoval;/* '<S1>/Bias Removal' */
} DW_q_2dsfl_pos_cntrl_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Filter3_CSTATE[2];            /* '<S1>/Filter3' */
  real_T DerivativeFilter1_CSTATE[2];  /* '<S1>/Derivative Filter1' */
  real_T DerivativeFilter2_CSTATE[2];  /* '<S1>/Derivative Filter2' */
  real_T DerivativeFilter3_CSTATE[2];  /* '<S2>/Derivative Filter3' */
  real_T DerivativeFilter1_CSTATE_n[2];/* '<S2>/Derivative Filter1' */
  real_T DerivativeFilter2_CSTATE_p[2];/* '<S2>/Derivative Filter2' */
} X_q_2dsfl_pos_cntrl_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Filter3_CSTATE[2];            /* '<S1>/Filter3' */
  real_T DerivativeFilter1_CSTATE[2];  /* '<S1>/Derivative Filter1' */
  real_T DerivativeFilter2_CSTATE[2];  /* '<S1>/Derivative Filter2' */
  real_T DerivativeFilter3_CSTATE[2];  /* '<S2>/Derivative Filter3' */
  real_T DerivativeFilter1_CSTATE_n[2];/* '<S2>/Derivative Filter1' */
  real_T DerivativeFilter2_CSTATE_p[2];/* '<S2>/Derivative Filter2' */
} XDot_q_2dsfl_pos_cntrl_T;

/* State disabled  */
typedef struct {
  boolean_T Filter3_CSTATE[2];         /* '<S1>/Filter3' */
  boolean_T DerivativeFilter1_CSTATE[2];/* '<S1>/Derivative Filter1' */
  boolean_T DerivativeFilter2_CSTATE[2];/* '<S1>/Derivative Filter2' */
  boolean_T DerivativeFilter3_CSTATE[2];/* '<S2>/Derivative Filter3' */
  boolean_T DerivativeFilter1_CSTATE_n[2];/* '<S2>/Derivative Filter1' */
  boolean_T DerivativeFilter2_CSTATE_p[2];/* '<S2>/Derivative Filter2' */
} XDis_q_2dsfl_pos_cntrl_T;

#ifndef ODE1_INTG
#define ODE1_INTG

/* ODE1 Integration Data */
typedef struct {
  real_T *f[1];                        /* derivatives */
} ODE1_IntgData;

#endif

/* Backward compatible GRT Identifiers */
#define rtB                            q_2dsfl_pos_cntrl_B
#define BlockIO                        B_q_2dsfl_pos_cntrl_T
#define rtX                            q_2dsfl_pos_cntrl_X
#define ContinuousStates               X_q_2dsfl_pos_cntrl_T
#define rtXdot                         q_2dsfl_pos_cntrl_XDot
#define StateDerivatives               XDot_q_2dsfl_pos_cntrl_T
#define tXdis                          q_2dsfl_pos_cntrl_XDis
#define StateDisabled                  XDis_q_2dsfl_pos_cntrl_T
#define rtP                            q_2dsfl_pos_cntrl_P
#define Parameters                     P_q_2dsfl_pos_cntrl_T
#define rtDWork                        q_2dsfl_pos_cntrl_DW
#define D_Work                         DW_q_2dsfl_pos_cntrl_T

/* Parameters for system: '<S1>/Bias Removal' */
struct P_BiasRemoval_q_2dsfl_pos_cnt_T_ {
  real_T unity_Value;                  /* Expression: 1
                                        * Referenced by: '<S16>/unity'
                                        */
  real_T UnitDelay_InitialCondition;   /* Expression: 0
                                        * Referenced by: '<S16>/Unit Delay'
                                        */
  real_T Sumk1n1xk_InitialCondition;   /* Expression: 0
                                        * Referenced by: '<S12>/Sum( k=1,n-1, x(k) )'
                                        */
  real_T zero_Y0;                      /* Expression: [0]
                                        * Referenced by: '<S13>/zero'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S13>/Constant'
                                        */
  real_T Vbiased_Y0;                   /* Expression: [0]
                                        * Referenced by: '<S14>/Vbiased'
                                        */
  real_T Vunbiased_Y0;                 /* Expression: [0]
                                        * Referenced by: '<S15>/Vunbiased'
                                        */
  real_T Stepstart_time_Y0;            /* Expression: 0
                                        * Referenced by: '<S9>/Step: start_time'
                                        */
  real_T Stepstart_time_YFinal;        /* Expression: 1
                                        * Referenced by: '<S9>/Step: start_time'
                                        */
  real_T Stepend_time_Y0;              /* Expression: 0
                                        * Referenced by: '<S9>/Step: end_time'
                                        */
  real_T Stepend_time_YFinal;          /* Expression: 1
                                        * Referenced by: '<S9>/Step: end_time'
                                        */
};

/* Parameters (default storage) */
struct P_q_2dsfl_pos_cntrl_T_ {
  real_T DTH1_LIM_ENABLE;              /* Variable: DTH1_LIM_ENABLE
                                        * Referenced by: '<S1>/Constant'
                                        */
  real_T DTH2_LIM_ENABLE;              /* Variable: DTH2_LIM_ENABLE
                                        * Referenced by: '<S2>/Constant'
                                        */
  real_T DTH2_MAX;                     /* Variable: DTH2_MAX
                                        * Referenced by:
                                        *   '<S10>/X MAX'
                                        *   '<S22>/X MAX'
                                        */
  real_T DTH2_MIN;                     /* Variable: DTH2_MIN
                                        * Referenced by:
                                        *   '<S10>/X IN'
                                        *   '<S22>/X IN'
                                        */
  real_T K1[4];                        /* Variable: K1
                                        * Referenced by: '<Root>/LQR Gain 1'
                                        */
  real_T K1_defl_b;                    /* Variable: K1_defl_b
                                        * Referenced by: '<S1>/Strain to Deflection'
                                        */
  real_T K1_strain_b;                  /* Variable: K1_strain_b
                                        * Referenced by: '<S1>/Volts to Base Strain'
                                        */
  real_T K2[4];                        /* Variable: K2
                                        * Referenced by: '<Root>/LQR Gain 2'
                                        */
  real_T K2_defl_b;                    /* Variable: K2_defl_b
                                        * Referenced by: '<S2>/Strain to Deflection'
                                        */
  real_T K2_strain_b;                  /* Variable: K2_strain_b
                                        * Referenced by: '<S2>/Volts to Strain'
                                        */
  real_T KE_D1;                        /* Variable: KE_D1
                                        * Referenced by: '<S1>/Motor #1 Encoder Calib'
                                        */
  real_T KE_D2;                        /* Variable: KE_D2
                                        * Referenced by: '<S2>/Motor #2 Encoder Calib'
                                        */
  real_T LIMIT_SWITCHES_ENABLE;        /* Variable: LIMIT_SWITCHES_ENABLE
                                        * Referenced by: '<S4>/Constant'
                                        */
  real_T RepeatingSequenceStair_OutValue[10];
                              /* Mask Parameter: RepeatingSequenceStair_OutValue
                               * Referenced by: '<S46>/Vector'
                               */
  real_T BiasRemoval_end_time;         /* Mask Parameter: BiasRemoval_end_time
                                        * Referenced by: '<S1>/Bias Removal'
                                        */
  real_T BiasRemoval_end_time_g;       /* Mask Parameter: BiasRemoval_end_time_g
                                        * Referenced by: '<S2>/Bias Removal'
                                        */
  real_T BiasRemoval_start_time;       /* Mask Parameter: BiasRemoval_start_time
                                        * Referenced by: '<S1>/Bias Removal'
                                        */
  real_T BiasRemoval_start_time_l;   /* Mask Parameter: BiasRemoval_start_time_l
                                      * Referenced by: '<S2>/Bias Removal'
                                      */
  real_T BiasRemoval_switch_id;        /* Mask Parameter: BiasRemoval_switch_id
                                        * Referenced by: '<S1>/Bias Removal'
                                        */
  real_T BiasRemoval_switch_id_n;     /* Mask Parameter: BiasRemoval_switch_id_n
                                       * Referenced by: '<S2>/Bias Removal'
                                       */
  uint32_T HILReadAnalog_channels[2];  /* Mask Parameter: HILReadAnalog_channels
                                        * Referenced by: '<S1>/HIL Read Analog'
                                        */
  uint32_T HILWriteAnalog_channels;   /* Mask Parameter: HILWriteAnalog_channels
                                       * Referenced by: '<S1>/HIL Write Analog'
                                       */
  uint32_T HILReadEncoder_channels;   /* Mask Parameter: HILReadEncoder_channels
                                       * Referenced by: '<S2>/HIL Read Encoder'
                                       */
  uint32_T HILReadAnalog_channels_a[2];
                                     /* Mask Parameter: HILReadAnalog_channels_a
                                      * Referenced by: '<S2>/HIL Read Analog'
                                      */
  uint32_T HILWriteAnalog_channels_e;
                                    /* Mask Parameter: HILWriteAnalog_channels_e
                                     * Referenced by: '<S2>/HIL Write Analog'
                                     */
  uint32_T HILWriteDigital_channels[3];
                                     /* Mask Parameter: HILWriteDigital_channels
                                      * Referenced by: '<S3>/HIL Write Digital'
                                      */
  uint32_T HILReadDigital_channels[4];/* Mask Parameter: HILReadDigital_channels
                                       * Referenced by: '<S4>/HIL Read Digital'
                                       */
  int8_T StopwithMessage_message_icon;
                                 /* Mask Parameter: StopwithMessage_message_icon
                                  * Referenced by: '<S17>/Show Message on Host'
                                  */
  int8_T StopwithMessage1_message_icon;
                                /* Mask Parameter: StopwithMessage1_message_icon
                                 * Referenced by: '<S18>/Show Message on Host'
                                 */
  int8_T StopwithMessage_message_icon_a;
                               /* Mask Parameter: StopwithMessage_message_icon_a
                                * Referenced by: '<S29>/Show Message on Host'
                                */
  int8_T StopwithMessage1_message_icon_g;
                              /* Mask Parameter: StopwithMessage1_message_icon_g
                               * Referenced by: '<S30>/Show Message on Host'
                               */
  int8_T StopwithMessage_message_icon_c;
                               /* Mask Parameter: StopwithMessage_message_icon_c
                                * Referenced by: '<S33>/Show Message on Host'
                                */
  int8_T StopwithMessage1_message_icon_m;
                              /* Mask Parameter: StopwithMessage1_message_icon_m
                               * Referenced by: '<S34>/Show Message on Host'
                               */
  int8_T StopwithMessage2_message_icon;
                                /* Mask Parameter: StopwithMessage2_message_icon
                                 * Referenced by: '<S35>/Show Message on Host'
                                 */
  int8_T StopwithMessage3_message_icon;
                                /* Mask Parameter: StopwithMessage3_message_icon
                                 * Referenced by: '<S36>/Show Message on Host'
                                 */
  uint8_T LimitedCounter_uplimit;      /* Mask Parameter: LimitedCounter_uplimit
                                        * Referenced by: '<S49>/FixPt Switch'
                                        */
  real_T Constant2_Value[4];           /* Expression: [1; 1; 1; 1 ]
                                        * Referenced by: '<Root>/Constant2'
                                        */
  real_T Cnstant1_Value[4];            /* Expression: [ 1; 0; 1; 0 ]
                                        * Referenced by: '<Root>/Cnstant1'
                                        */
  real_T Constant1_Value[4];           /* Expression: [1; 1; 1; 1 ]
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T Cnstant2_Value[4];            /* Expression: [ 1; 0; 1; 0 ]
                                        * Referenced by: '<Root>/Cnstant2'
                                        */
  real_T HILInitialize_OOTerminate;/* Expression: set_other_outputs_at_terminate
                                    * Referenced by: '<Root>/HIL Initialize'
                                    */
  real_T HILInitialize_OOExit;    /* Expression: set_other_outputs_at_switch_out
                                   * Referenced by: '<Root>/HIL Initialize'
                                   */
  real_T HILInitialize_OOStart;        /* Expression: set_other_outputs_at_start
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_OOEnter;    /* Expression: set_other_outputs_at_switch_in
                                    * Referenced by: '<Root>/HIL Initialize'
                                    */
  real_T HILInitialize_AOFinal;        /* Expression: final_analog_outputs
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_POFinal;        /* Expression: final_pwm_outputs
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_AIHigh;         /* Expression: analog_input_maximums
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_AILow;          /* Expression: analog_input_minimums
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_AOHigh;         /* Expression: analog_output_maximums
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_AOLow;          /* Expression: analog_output_minimums
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_AOInitial;      /* Expression: initial_analog_outputs
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_AOWatchdog;     /* Expression: watchdog_analog_outputs
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_POFrequency;    /* Expression: pwm_frequency
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_POLeading;      /* Expression: pwm_leading_deadband
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_POTrailing;     /* Expression: pwm_trailing_deadband
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_POInitial;      /* Expression: initial_pwm_outputs
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T HILInitialize_POWatchdog;     /* Expression: watchdog_pwm_outputs
                                        * Referenced by: '<Root>/HIL Initialize'
                                        */
  real_T ContinuousSigmoid_XI;         /* Expression: initial_position
                                        * Referenced by: '<S7>/Continuous Sigmoid'
                                        */
  real_T ContinuousSigmoid_VI;         /* Expression: initial_velocity
                                        * Referenced by: '<S7>/Continuous Sigmoid'
                                        */
  real_T ContinuousSigmoid_Hold;       /* Expression: hold_off
                                        * Referenced by: '<S7>/Continuous Sigmoid'
                                        */
  real_T ContinuousSigmoid_VMax;       /* Expression: i_max_velocity
                                        * Referenced by: '<S7>/Continuous Sigmoid'
                                        */
  real_T ContinuousSigmoid_AMax;       /* Expression: i_max_acceleration
                                        * Referenced by: '<S7>/Continuous Sigmoid'
                                        */
  real_T u100_Gain[4];                 /* Expression:  [1; 0; 0; 0]
                                        * Referenced by: '<S7>/[ 1; 1; 0; 0 ]'
                                        */
  real_T Filter3_A[2];                 /* Computed Parameter: Filter3_A
                                        * Referenced by: '<S1>/Filter3'
                                        */
  real_T Filter3_C[2];                 /* Computed Parameter: Filter3_C
                                        * Referenced by: '<S1>/Filter3'
                                        */
  real_T DerivativeFilter1_A[2];      /* Computed Parameter: DerivativeFilter1_A
                                       * Referenced by: '<S1>/Derivative Filter1'
                                       */
  real_T DerivativeFilter1_C[2];      /* Computed Parameter: DerivativeFilter1_C
                                       * Referenced by: '<S1>/Derivative Filter1'
                                       */
  real_T DerivativeFilter2_A[2];      /* Computed Parameter: DerivativeFilter2_A
                                       * Referenced by: '<S1>/Derivative Filter2'
                                       */
  real_T DerivativeFilter2_C[2];      /* Computed Parameter: DerivativeFilter2_C
                                       * Referenced by: '<S1>/Derivative Filter2'
                                       */
  real_T Gain_Gain;                    /* Expression: 180/pi
                                        * Referenced by: '<S41>/Gain'
                                        */
  real_T Gain_Gain_o;                  /* Expression: 180/pi
                                        * Referenced by: '<S42>/Gain'
                                        */
  real_T Im_r1Saturation_UpperSat;     /* Expression: 0.94
                                        * Referenced by: '<Root>/Im_r1: Saturation'
                                        */
  real_T Im_r1Saturation_LowerSat;     /* Expression: -0.94
                                        * Referenced by: '<Root>/Im_r1: Saturation'
                                        */
  real_T VoltstoAmps_Gain;             /* Expression: -2.0
                                        * Referenced by: '<S1>/Volts to Amps'
                                        */
  real_T AmpstoVolts_Gain;             /* Expression: 1/0.5
                                        * Referenced by: '<S1>/Amps to Volts'
                                        */
  real_T Gain_Gain_e;                  /* Expression: 180/pi
                                        * Referenced by: '<S11>/Gain'
                                        */
  real_T TransportDelay_Delay;         /* Expression: 2.5
                                        * Referenced by: '<S8>/Transport Delay'
                                        */
  real_T TransportDelay_InitOutput;    /* Expression: 0
                                        * Referenced by: '<S8>/Transport Delay'
                                        */
  real_T u1001_Gain[4];                /* Expression:  [1; 0; 0; 0]
                                        * Referenced by: '<S8>/[ 1; 1; 0; 0 ]1'
                                        */
  real_T DerivativeFilter3_A[2];      /* Computed Parameter: DerivativeFilter3_A
                                       * Referenced by: '<S2>/Derivative Filter3'
                                       */
  real_T DerivativeFilter3_C[2];      /* Computed Parameter: DerivativeFilter3_C
                                       * Referenced by: '<S2>/Derivative Filter3'
                                       */
  real_T DerivativeFilter1_A_c[2];  /* Computed Parameter: DerivativeFilter1_A_c
                                     * Referenced by: '<S2>/Derivative Filter1'
                                     */
  real_T DerivativeFilter1_C_l[2];  /* Computed Parameter: DerivativeFilter1_C_l
                                     * Referenced by: '<S2>/Derivative Filter1'
                                     */
  real_T DerivativeFilter2_A_m[2];  /* Computed Parameter: DerivativeFilter2_A_m
                                     * Referenced by: '<S2>/Derivative Filter2'
                                     */
  real_T DerivativeFilter2_C_g[2];  /* Computed Parameter: DerivativeFilter2_C_g
                                     * Referenced by: '<S2>/Derivative Filter2'
                                     */
  real_T Gain_Gain_g;                  /* Expression: 180/pi
                                        * Referenced by: '<S43>/Gain'
                                        */
  real_T Gain_Gain_k;                  /* Expression: 180/pi
                                        * Referenced by: '<S44>/Gain'
                                        */
  real_T Im_r2Saturation_UpperSat;     /* Expression: 1.2
                                        * Referenced by: '<Root>/Im_r2: Saturation'
                                        */
  real_T Im_r2Saturation_LowerSat;     /* Expression: -1.2
                                        * Referenced by: '<Root>/Im_r2: Saturation'
                                        */
  real_T VoltstoAmps_Gain_p;           /* Expression: -2.0
                                        * Referenced by: '<S2>/Volts to Amps'
                                        */
  real_T AmpstoVolts_Gain_j;           /* Expression: 1/0.5
                                        * Referenced by: '<S2>/Amps to Volts'
                                        */
  real_T Gain_Gain_n;                  /* Expression: 180/pi
                                        * Referenced by: '<S23>/Gain'
                                        */
  real_T SquareWave1_Amplitude;        /* Expression: 1
                                        * Referenced by: '<S8>/Square Wave1'
                                        */
  real_T SquareWave1_Frequency;        /* Expression: 0.1
                                        * Referenced by: '<S8>/Square Wave1'
                                        */
  real_T Amplitudedeg1_Gain;           /* Expression: 0
                                        * Referenced by: '<S8>/Amplitude (deg)1'
                                        */
  real_T ContinuousSigmoid1_XI;        /* Expression: initial_position
                                        * Referenced by: '<S8>/Continuous Sigmoid1'
                                        */
  real_T ContinuousSigmoid1_VI;        /* Expression: initial_velocity
                                        * Referenced by: '<S8>/Continuous Sigmoid1'
                                        */
  real_T ContinuousSigmoid1_Hold;      /* Expression: hold_off
                                        * Referenced by: '<S8>/Continuous Sigmoid1'
                                        */
  real_T ContinuousSigmoid1_VMax;      /* Expression: i_max_velocity
                                        * Referenced by: '<S8>/Continuous Sigmoid1'
                                        */
  real_T ContinuousSigmoid1_AMax;      /* Expression: i_max_acceleration
                                        * Referenced by: '<S8>/Continuous Sigmoid1'
                                        */
  real_T Gain1_Gain;                   /* Expression: pi/180
                                        * Referenced by: '<S50>/Gain1'
                                        */
  real_T EnableActiveLow_Value[2];     /* Expression: [ 0 0 ]
                                        * Referenced by: '<S3>/Enable: Active Low'
                                        */
  real_T MasterEnableActiveHigh_Value; /* Expression: 1
                                        * Referenced by: '<S3>/Master Enable: Active High'
                                        */
  real_T Amplitudedeg_Gain;            /* Expression: 1
                                        * Referenced by: '<S7>/Amplitude (deg)'
                                        */
  real_T Gain1_Gain_j;                 /* Expression: pi/180
                                        * Referenced by: '<S45>/Gain1'
                                        */
  int32_T HILInitialize_CKChannels[3];
                                 /* Computed Parameter: HILInitialize_CKChannels
                                  * Referenced by: '<Root>/HIL Initialize'
                                  */
  int32_T HILInitialize_DOWatchdog;
                                 /* Computed Parameter: HILInitialize_DOWatchdog
                                  * Referenced by: '<Root>/HIL Initialize'
                                  */
  int32_T HILInitialize_EIInitial;/* Computed Parameter: HILInitialize_EIInitial
                                   * Referenced by: '<Root>/HIL Initialize'
                                   */
  int32_T HILInitialize_POModes;    /* Computed Parameter: HILInitialize_POModes
                                     * Referenced by: '<Root>/HIL Initialize'
                                     */
  int32_T HILInitialize_POConfiguration;
                            /* Computed Parameter: HILInitialize_POConfiguration
                             * Referenced by: '<Root>/HIL Initialize'
                             */
  int32_T HILInitialize_POAlignment;
                                /* Computed Parameter: HILInitialize_POAlignment
                                 * Referenced by: '<Root>/HIL Initialize'
                                 */
  int32_T HILInitialize_POPolarity;
                                 /* Computed Parameter: HILInitialize_POPolarity
                                  * Referenced by: '<Root>/HIL Initialize'
                                  */
  int32_T HILReadEncoderTimebase_Clock;
                             /* Computed Parameter: HILReadEncoderTimebase_Clock
                              * Referenced by: '<S1>/HIL Read Encoder Timebase'
                              */
  uint32_T HILInitialize_AIChannels[8];
                                 /* Computed Parameter: HILInitialize_AIChannels
                                  * Referenced by: '<Root>/HIL Initialize'
                                  */
  uint32_T HILInitialize_AOChannels[8];
                                 /* Computed Parameter: HILInitialize_AOChannels
                                  * Referenced by: '<Root>/HIL Initialize'
                                  */
  uint32_T HILInitialize_EIChannels[8];
                                 /* Computed Parameter: HILInitialize_EIChannels
                                  * Referenced by: '<Root>/HIL Initialize'
                                  */
  uint32_T HILInitialize_EIQuadrature;
                               /* Computed Parameter: HILInitialize_EIQuadrature
                                * Referenced by: '<Root>/HIL Initialize'
                                */
  uint32_T HILInitialize_POChannels[8];
                                 /* Computed Parameter: HILInitialize_POChannels
                                  * Referenced by: '<Root>/HIL Initialize'
                                  */
  uint32_T HILReadEncoderTimebase_Channels;
                          /* Computed Parameter: HILReadEncoderTimebase_Channels
                           * Referenced by: '<S1>/HIL Read Encoder Timebase'
                           */
  uint32_T HILReadEncoderTimebase_SamplesI;
                          /* Computed Parameter: HILReadEncoderTimebase_SamplesI
                           * Referenced by: '<S1>/HIL Read Encoder Timebase'
                           */
  boolean_T Constant_Value;            /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S19>/Constant'
                                        */
  boolean_T Constant_Value_a;          /* Computed Parameter: Constant_Value_a
                                        * Referenced by: '<S20>/Constant'
                                        */
  boolean_T Constant_Value_p;          /* Computed Parameter: Constant_Value_p
                                        * Referenced by: '<S31>/Constant'
                                        */
  boolean_T Constant_Value_f;          /* Computed Parameter: Constant_Value_f
                                        * Referenced by: '<S32>/Constant'
                                        */
  boolean_T Constant_Value_g;          /* Computed Parameter: Constant_Value_g
                                        * Referenced by: '<S37>/Constant'
                                        */
  boolean_T Constant_Value_fj;         /* Computed Parameter: Constant_Value_fj
                                        * Referenced by: '<S38>/Constant'
                                        */
  boolean_T Constant_Value_k;          /* Computed Parameter: Constant_Value_k
                                        * Referenced by: '<S39>/Constant'
                                        */
  boolean_T Constant_Value_ks;         /* Computed Parameter: Constant_Value_ks
                                        * Referenced by: '<S40>/Constant'
                                        */
  boolean_T HILInitialize_Active;    /* Computed Parameter: HILInitialize_Active
                                      * Referenced by: '<Root>/HIL Initialize'
                                      */
  boolean_T HILInitialize_AOTerminate;
                                /* Computed Parameter: HILInitialize_AOTerminate
                                 * Referenced by: '<Root>/HIL Initialize'
                                 */
  boolean_T HILInitialize_AOExit;    /* Computed Parameter: HILInitialize_AOExit
                                      * Referenced by: '<Root>/HIL Initialize'
                                      */
  boolean_T HILInitialize_DOTerminate;
                                /* Computed Parameter: HILInitialize_DOTerminate
                                 * Referenced by: '<Root>/HIL Initialize'
                                 */
  boolean_T HILInitialize_DOExit;    /* Computed Parameter: HILInitialize_DOExit
                                      * Referenced by: '<Root>/HIL Initialize'
                                      */
  boolean_T HILInitialize_POTerminate;
                                /* Computed Parameter: HILInitialize_POTerminate
                                 * Referenced by: '<Root>/HIL Initialize'
                                 */
  boolean_T HILInitialize_POExit;    /* Computed Parameter: HILInitialize_POExit
                                      * Referenced by: '<Root>/HIL Initialize'
                                      */
  boolean_T HILInitialize_CKPStart;/* Computed Parameter: HILInitialize_CKPStart
                                    * Referenced by: '<Root>/HIL Initialize'
                                    */
  boolean_T HILInitialize_CKPEnter;/* Computed Parameter: HILInitialize_CKPEnter
                                    * Referenced by: '<Root>/HIL Initialize'
                                    */
  boolean_T HILInitialize_CKStart;  /* Computed Parameter: HILInitialize_CKStart
                                     * Referenced by: '<Root>/HIL Initialize'
                                     */
  boolean_T HILInitialize_CKEnter;  /* Computed Parameter: HILInitialize_CKEnter
                                     * Referenced by: '<Root>/HIL Initialize'
                                     */
  boolean_T HILInitialize_AIPStart;/* Computed Parameter: HILInitialize_AIPStart
                                    * Referenced by: '<Root>/HIL Initialize'
                                    */
  boolean_T HILInitialize_AIPEnter;/* Computed Parameter: HILInitialize_AIPEnter
                                    * Referenced by: '<Root>/HIL Initialize'
                                    */
  boolean_T HILInitialize_AOPStart;/* Computed Parameter: HILInitialize_AOPStart
                                    * Referenced by: '<Root>/HIL Initialize'
                                    */
  boolean_T HILInitialize_AOPEnter;/* Computed Parameter: HILInitialize_AOPEnter
                                    * Referenced by: '<Root>/HIL Initialize'
                                    */
  boolean_T HILInitialize_AOStart;  /* Computed Parameter: HILInitialize_AOStart
                                     * Referenced by: '<Root>/HIL Initialize'
                                     */
  boolean_T HILInitialize_AOEnter;  /* Computed Parameter: HILInitialize_AOEnter
                                     * Referenced by: '<Root>/HIL Initialize'
                                     */
  boolean_T HILInitialize_AOReset;  /* Computed Parameter: HILInitialize_AOReset
                                     * Referenced by: '<Root>/HIL Initialize'
                                     */
  boolean_T HILInitialize_DOPStart;/* Computed Parameter: HILInitialize_DOPStart
                                    * Referenced by: '<Root>/HIL Initialize'
                                    */
  boolean_T HILInitialize_DOPEnter;/* Computed Parameter: HILInitialize_DOPEnter
                                    * Referenced by: '<Root>/HIL Initialize'
                                    */
  boolean_T HILInitialize_DOStart;  /* Computed Parameter: HILInitialize_DOStart
                                     * Referenced by: '<Root>/HIL Initialize'
                                     */
  boolean_T HILInitialize_DOEnter;  /* Computed Parameter: HILInitialize_DOEnter
                                     * Referenced by: '<Root>/HIL Initialize'
                                     */
  boolean_T HILInitialize_DOReset;  /* Computed Parameter: HILInitialize_DOReset
                                     * Referenced by: '<Root>/HIL Initialize'
                                     */
  boolean_T HILInitialize_EIPStart;/* Computed Parameter: HILInitialize_EIPStart
                                    * Referenced by: '<Root>/HIL Initialize'
                                    */
  boolean_T HILInitialize_EIPEnter;/* Computed Parameter: HILInitialize_EIPEnter
                                    * Referenced by: '<Root>/HIL Initialize'
                                    */
  boolean_T HILInitialize_EIStart;  /* Computed Parameter: HILInitialize_EIStart
                                     * Referenced by: '<Root>/HIL Initialize'
                                     */
  boolean_T HILInitialize_EIEnter;  /* Computed Parameter: HILInitialize_EIEnter
                                     * Referenced by: '<Root>/HIL Initialize'
                                     */
  boolean_T HILInitialize_POPStart;/* Computed Parameter: HILInitialize_POPStart
                                    * Referenced by: '<Root>/HIL Initialize'
                                    */
  boolean_T HILInitialize_POPEnter;/* Computed Parameter: HILInitialize_POPEnter
                                    * Referenced by: '<Root>/HIL Initialize'
                                    */
  boolean_T HILInitialize_POStart;  /* Computed Parameter: HILInitialize_POStart
                                     * Referenced by: '<Root>/HIL Initialize'
                                     */
  boolean_T HILInitialize_POEnter;  /* Computed Parameter: HILInitialize_POEnter
                                     * Referenced by: '<Root>/HIL Initialize'
                                     */
  boolean_T HILInitialize_POReset;  /* Computed Parameter: HILInitialize_POReset
                                     * Referenced by: '<Root>/HIL Initialize'
                                     */
  boolean_T HILInitialize_OOReset;  /* Computed Parameter: HILInitialize_OOReset
                                     * Referenced by: '<Root>/HIL Initialize'
                                     */
  boolean_T HILInitialize_DOFinal;  /* Computed Parameter: HILInitialize_DOFinal
                                     * Referenced by: '<Root>/HIL Initialize'
                                     */
  boolean_T HILInitialize_DOInitial;
                                  /* Computed Parameter: HILInitialize_DOInitial
                                   * Referenced by: '<Root>/HIL Initialize'
                                   */
  boolean_T HILReadEncoderTimebase_Active;
                            /* Computed Parameter: HILReadEncoderTimebase_Active
                             * Referenced by: '<S1>/HIL Read Encoder Timebase'
                             */
  boolean_T HILReadAnalog_Active;    /* Computed Parameter: HILReadAnalog_Active
                                      * Referenced by: '<S1>/HIL Read Analog'
                                      */
  boolean_T HILWriteAnalog_Active;  /* Computed Parameter: HILWriteAnalog_Active
                                     * Referenced by: '<S1>/HIL Write Analog'
                                     */
  boolean_T HILReadEncoder_Active;  /* Computed Parameter: HILReadEncoder_Active
                                     * Referenced by: '<S2>/HIL Read Encoder'
                                     */
  boolean_T HILReadAnalog_Active_i;/* Computed Parameter: HILReadAnalog_Active_i
                                    * Referenced by: '<S2>/HIL Read Analog'
                                    */
  boolean_T HILWriteAnalog_Active_f;
                                  /* Computed Parameter: HILWriteAnalog_Active_f
                                   * Referenced by: '<S2>/HIL Write Analog'
                                   */
  boolean_T HILWriteDigital_Active;/* Computed Parameter: HILWriteDigital_Active
                                    * Referenced by: '<S3>/HIL Write Digital'
                                    */
  boolean_T HILReadDigital_Active;  /* Computed Parameter: HILReadDigital_Active
                                     * Referenced by: '<S4>/HIL Read Digital'
                                     */
  uint8_T Constant_Value_d;            /* Computed Parameter: Constant_Value_d
                                        * Referenced by: '<S49>/Constant'
                                        */
  uint8_T HILReadEncoderTimebase_Overflow;
                          /* Computed Parameter: HILReadEncoderTimebase_Overflow
                           * Referenced by: '<S1>/HIL Read Encoder Timebase'
                           */
  uint8_T ManualSwitch1_CurrentSetting;
                             /* Computed Parameter: ManualSwitch1_CurrentSetting
                              * Referenced by: '<Root>/Manual Switch1'
                              */
  uint8_T ManualSwitch2_CurrentSetting;
                             /* Computed Parameter: ManualSwitch2_CurrentSetting
                              * Referenced by: '<Root>/Manual Switch2'
                              */
  uint8_T Output_InitialCondition;/* Computed Parameter: Output_InitialCondition
                                   * Referenced by: '<S47>/Output'
                                   */
  uint8_T FixPtConstant_Value;        /* Computed Parameter: FixPtConstant_Value
                                       * Referenced by: '<S48>/FixPt Constant'
                                       */
  P_BiasRemoval_q_2dsfl_pos_cnt_T BiasRemoval_m;/* '<S2>/Bias Removal' */
  P_BiasRemoval_q_2dsfl_pos_cnt_T BiasRemoval;/* '<S1>/Bias Removal' */
};

/* Real-time Model Data Structure */
struct tag_RTM_q_2dsfl_pos_cntrl_T {
  const char_T *path;
  const char_T *modelName;
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;
  RTWSolverInfo *solverInfoPtr;
  void *sfcnInfo;
  void *blockIO;
  const void *constBlockIO;
  void *defaultParam;
  ZCSigState *prevZCSigState;
  real_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  void *zcSignalValues;
  void *inputs;
  void *outputs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeF[1][12];
  ODE1_IntgData intgData;
  void *dwork;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
    uint32_T options;
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numU;
    int_T numY;
    int_T numSampTimes;
    int_T numBlocks;
    int_T numBlockIO;
    int_T numBlockPrms;
    int_T numDwork;
    int_T numSFcnPrms;
    int_T numSFcns;
    int_T numIports;
    int_T numOports;
    int_T numNonSampZCs;
    int_T sysDirFeedThru;
    int_T rtwGenSfcn;
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
    void *xpcData;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T stepSize;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T stepSize1;
    uint32_T clockTick2;
    uint32_T clockTickH2;
    time_T stepSize2;
    struct {
      uint16_T TID[3];
    } TaskCounters;

    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    void *timingData;
    real_T *varNextHitTimesList;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
    time_T sampleTimesArray[3];
    time_T offsetTimesArray[3];
    int_T sampleTimeTaskIDArray[3];
    int_T sampleHitArray[3];
    int_T perTaskSampleHitsArray[9];
    time_T tArray[3];
  } Timing;
};

/* Block parameters (default storage) */
extern P_q_2dsfl_pos_cntrl_T q_2dsfl_pos_cntrl_P;

/* Block signals (default storage) */
extern B_q_2dsfl_pos_cntrl_T q_2dsfl_pos_cntrl_B;

/* Continuous states (default storage) */
extern X_q_2dsfl_pos_cntrl_T q_2dsfl_pos_cntrl_X;

/* Block states (default storage) */
extern DW_q_2dsfl_pos_cntrl_T q_2dsfl_pos_cntrl_DW;

/* External function called from main */
extern time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
  ;

/* Model entry point functions */
extern void q_2dsfl_pos_cntrl_initialize(void);
extern void q_2dsfl_pos_cntrl_output0(void);
extern void q_2dsfl_pos_cntrl_update0(void);
extern void q_2dsfl_pos_cntrl_output2(void);
extern void q_2dsfl_pos_cntrl_update2(void);
extern void q_2dsfl_pos_cntrl_output(int_T tid);
extern void q_2dsfl_pos_cntrl_update(int_T tid);
extern void q_2dsfl_pos_cntrl_terminate(void);

/*====================*
 * External functions *
 *====================*/
extern q_2dsfl_pos_cntrl_rtModel *q_2dsfl_pos_cntrl(void);
extern void MdlInitializeSizes(void);
extern void MdlInitializeSampleTimes(void);
extern void MdlInitialize(void);
extern void MdlStart(void);
extern void MdlOutputs(int_T tid);
extern void MdlUpdate(int_T tid);
extern void MdlTerminate(void);

/* Real-time Model object */
extern RT_MODEL_q_2dsfl_pos_cntrl_T *const q_2dsfl_pos_cntrl_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'q_2dsfl_pos_cntrl'
 * '<S1>'   : 'q_2dsfl_pos_cntrl/1st Stage: 2-DOF SFL Robot: Actual Plant'
 * '<S2>'   : 'q_2dsfl_pos_cntrl/2nd Stage: 2-DOF SFL Robot: Actual Plant'
 * '<S3>'   : 'q_2dsfl_pos_cntrl/Enable AMPAQ'
 * '<S4>'   : 'q_2dsfl_pos_cntrl/Limit Switches'
 * '<S5>'   : 'q_2dsfl_pos_cntrl/Scopes - Stage 1'
 * '<S6>'   : 'q_2dsfl_pos_cntrl/Scopes - Stage 2'
 * '<S7>'   : 'q_2dsfl_pos_cntrl/Stage 1 Setpoint'
 * '<S8>'   : 'q_2dsfl_pos_cntrl/Stage 2 Setpoint'
 * '<S9>'   : 'q_2dsfl_pos_cntrl/1st Stage: 2-DOF SFL Robot: Actual Plant/Bias Removal'
 * '<S10>'  : 'q_2dsfl_pos_cntrl/1st Stage: 2-DOF SFL Robot: Actual Plant/Position Watchdog'
 * '<S11>'  : 'q_2dsfl_pos_cntrl/1st Stage: 2-DOF SFL Robot: Actual Plant/Radians to Degrees'
 * '<S12>'  : 'q_2dsfl_pos_cntrl/1st Stage: 2-DOF SFL Robot: Actual Plant/Bias Removal/Enabled Moving Average'
 * '<S13>'  : 'q_2dsfl_pos_cntrl/1st Stage: 2-DOF SFL Robot: Actual Plant/Bias Removal/Switch Case Action Subsystem'
 * '<S14>'  : 'q_2dsfl_pos_cntrl/1st Stage: 2-DOF SFL Robot: Actual Plant/Bias Removal/Switch Case Action Subsystem1'
 * '<S15>'  : 'q_2dsfl_pos_cntrl/1st Stage: 2-DOF SFL Robot: Actual Plant/Bias Removal/Switch Case Action Subsystem2'
 * '<S16>'  : 'q_2dsfl_pos_cntrl/1st Stage: 2-DOF SFL Robot: Actual Plant/Bias Removal/Enabled Moving Average/Increment'
 * '<S17>'  : 'q_2dsfl_pos_cntrl/1st Stage: 2-DOF SFL Robot: Actual Plant/Position Watchdog/Stop with Message'
 * '<S18>'  : 'q_2dsfl_pos_cntrl/1st Stage: 2-DOF SFL Robot: Actual Plant/Position Watchdog/Stop with Message1'
 * '<S19>'  : 'q_2dsfl_pos_cntrl/1st Stage: 2-DOF SFL Robot: Actual Plant/Position Watchdog/Stop with Message/Compare'
 * '<S20>'  : 'q_2dsfl_pos_cntrl/1st Stage: 2-DOF SFL Robot: Actual Plant/Position Watchdog/Stop with Message1/Compare'
 * '<S21>'  : 'q_2dsfl_pos_cntrl/2nd Stage: 2-DOF SFL Robot: Actual Plant/Bias Removal'
 * '<S22>'  : 'q_2dsfl_pos_cntrl/2nd Stage: 2-DOF SFL Robot: Actual Plant/Position Watchdog'
 * '<S23>'  : 'q_2dsfl_pos_cntrl/2nd Stage: 2-DOF SFL Robot: Actual Plant/Radians to Degrees'
 * '<S24>'  : 'q_2dsfl_pos_cntrl/2nd Stage: 2-DOF SFL Robot: Actual Plant/Bias Removal/Enabled Moving Average'
 * '<S25>'  : 'q_2dsfl_pos_cntrl/2nd Stage: 2-DOF SFL Robot: Actual Plant/Bias Removal/Switch Case Action Subsystem'
 * '<S26>'  : 'q_2dsfl_pos_cntrl/2nd Stage: 2-DOF SFL Robot: Actual Plant/Bias Removal/Switch Case Action Subsystem1'
 * '<S27>'  : 'q_2dsfl_pos_cntrl/2nd Stage: 2-DOF SFL Robot: Actual Plant/Bias Removal/Switch Case Action Subsystem2'
 * '<S28>'  : 'q_2dsfl_pos_cntrl/2nd Stage: 2-DOF SFL Robot: Actual Plant/Bias Removal/Enabled Moving Average/Increment'
 * '<S29>'  : 'q_2dsfl_pos_cntrl/2nd Stage: 2-DOF SFL Robot: Actual Plant/Position Watchdog/Stop with Message'
 * '<S30>'  : 'q_2dsfl_pos_cntrl/2nd Stage: 2-DOF SFL Robot: Actual Plant/Position Watchdog/Stop with Message1'
 * '<S31>'  : 'q_2dsfl_pos_cntrl/2nd Stage: 2-DOF SFL Robot: Actual Plant/Position Watchdog/Stop with Message/Compare'
 * '<S32>'  : 'q_2dsfl_pos_cntrl/2nd Stage: 2-DOF SFL Robot: Actual Plant/Position Watchdog/Stop with Message1/Compare'
 * '<S33>'  : 'q_2dsfl_pos_cntrl/Limit Switches/Stop with Message'
 * '<S34>'  : 'q_2dsfl_pos_cntrl/Limit Switches/Stop with Message1'
 * '<S35>'  : 'q_2dsfl_pos_cntrl/Limit Switches/Stop with Message2'
 * '<S36>'  : 'q_2dsfl_pos_cntrl/Limit Switches/Stop with Message3'
 * '<S37>'  : 'q_2dsfl_pos_cntrl/Limit Switches/Stop with Message/Compare'
 * '<S38>'  : 'q_2dsfl_pos_cntrl/Limit Switches/Stop with Message1/Compare'
 * '<S39>'  : 'q_2dsfl_pos_cntrl/Limit Switches/Stop with Message2/Compare'
 * '<S40>'  : 'q_2dsfl_pos_cntrl/Limit Switches/Stop with Message3/Compare'
 * '<S41>'  : 'q_2dsfl_pos_cntrl/Scopes - Stage 1/rad2deg 1'
 * '<S42>'  : 'q_2dsfl_pos_cntrl/Scopes - Stage 1/rad2deg 2'
 * '<S43>'  : 'q_2dsfl_pos_cntrl/Scopes - Stage 2/rad2deg 1'
 * '<S44>'  : 'q_2dsfl_pos_cntrl/Scopes - Stage 2/rad2deg 2'
 * '<S45>'  : 'q_2dsfl_pos_cntrl/Stage 1 Setpoint/Degrees to Radians'
 * '<S46>'  : 'q_2dsfl_pos_cntrl/Stage 1 Setpoint/Repeating Sequence Stair'
 * '<S47>'  : 'q_2dsfl_pos_cntrl/Stage 1 Setpoint/Repeating Sequence Stair/LimitedCounter'
 * '<S48>'  : 'q_2dsfl_pos_cntrl/Stage 1 Setpoint/Repeating Sequence Stair/LimitedCounter/Increment Real World'
 * '<S49>'  : 'q_2dsfl_pos_cntrl/Stage 1 Setpoint/Repeating Sequence Stair/LimitedCounter/Wrap To Zero'
 * '<S50>'  : 'q_2dsfl_pos_cntrl/Stage 2 Setpoint/Degrees to Radians1'
 */
#endif                                 /* RTW_HEADER_q_2dsfl_pos_cntrl_h_ */
