/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: PerformanceTester_SVD.h
 *
 * Code generated for Simulink model 'PerformanceTester_SVD'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Sat Nov 14 09:06:04 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: STMicroelectronics->STM32 32-bit Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_PerformanceTester_SVD_h_
#define RTW_HEADER_PerformanceTester_SVD_h_
#include <stddef.h>
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#ifndef PerformanceTester_SVD_COMMON_INCLUDES_
# define PerformanceTester_SVD_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                              /* PerformanceTester_SVD_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

#ifndef typedef_dsp_simulink_SVD
#define typedef_dsp_simulink_SVD

typedef struct {
  int32_T isInitialized;
} dsp_simulink_SVD;

#endif                                 /*typedef_dsp_simulink_SVD*/

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  dsp_simulink_SVD obj;              /* '<Root>/Singular Value Decomposition' */
  real_T s[2500];
  real_T A[5000];
  real_T Vf[2500];
  real_T A_m[5000];
  real_T Vf_c[2500];
  boolean_T bv[5000];
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Inport[5000];                 /* '<Root>/Inport' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Outport[5000];                /* '<Root>/Outport' */
  real_T Outport1[50];                 /* '<Root>/Outport1' */
  real_T Outport2[2500];               /* '<Root>/Outport2' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void PerformanceTester_SVD_initialize(void);
extern void PerformanceTester_SVD_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

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
 * '<Root>' : 'PerformanceTester_SVD'
 */
#endif                                 /* RTW_HEADER_PerformanceTester_SVD_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
