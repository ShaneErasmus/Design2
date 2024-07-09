/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MicroMouseTemplate_private.h
 *
 * Code generated for Simulink model 'MicroMouseTemplate'.
 *
 * Model version                  : 1.159
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Tue Jul  9 06:02:44 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_MicroMouseTemplate_private_h_
#define RTW_HEADER_MicroMouseTemplate_private_h_
#include "rtwtypes.h"
#include "MicroMouseTemplate.h"
#include "MicroMouseTemplate_types.h"
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

/* Skipping ulong_long/long_long check: insufficient preprocessor integer range. */
extern void MicroMouseTe_MovingMaximum_Init(DW_MovingMaximum_MicroMouseTe_T
  *localDW);
extern void MicroMouseTemplat_MovingMaximum(real_T rtu_0,
  B_MovingMaximum_MicroMouseTem_T *localB, DW_MovingMaximum_MicroMouseTe_T
  *localDW);
extern void MicroMouseTe_MovingMinimum_Init(DW_MovingMinimum_MicroMouseTe_T
  *localDW);
extern void MicroMouseTemplat_MovingMinimum(real_T rtu_0,
  B_MovingMinimum_MicroMouseTem_T *localB, DW_MovingMinimum_MicroMouseTe_T
  *localDW);
extern void MicroMouseT_MovingMaximum1_Init(DW_MovingMaximum1_MicroMouseT_T
  *localDW);
extern void MicroMouseTempla_MovingMaximum1(real_T rtu_0,
  B_MovingMaximum1_MicroMouseTe_T *localB, DW_MovingMaximum1_MicroMouseT_T
  *localDW);
extern void MicroMouseT_MovingMinimum2_Init(DW_MovingMinimum2_MicroMouseT_T
  *localDW);
extern void MicroMouseTempla_MovingMinimum2(real_T rtu_0,
  B_MovingMinimum2_MicroMouseTe_T *localB, DW_MovingMinimum2_MicroMouseT_T
  *localDW);
extern void MicroMouse_MovingMaximum_i_Init(DW_MovingMaximum_MicroMouse_p_T
  *localDW);
extern void MicroMouseTempl_MovingMaximum_j(real_T rtu_0,
  B_MovingMaximum_MicroMouseT_o_T *localB, DW_MovingMaximum_MicroMouse_p_T
  *localDW);
extern void MicroMouse_MovingMinimum_f_Init(DW_MovingMinimum_MicroMouse_p_T
  *localDW);
extern void MicroMouseTempl_MovingMinimum_j(real_T rtu_0,
  B_MovingMinimum_MicroMouseT_o_T *localB, DW_MovingMinimum_MicroMouse_p_T
  *localDW);
extern void MicroMouse_MovingMaximum_h_Init(DW_MovingMaximum_MicroMous_pl_T
  *localDW);
extern void MicroMouseTemp_MovingMaximum_jn(real_T rtu_0,
  B_MovingMaximum_MicroMouse_oj_T *localB, DW_MovingMaximum_MicroMous_pl_T
  *localDW);
extern void MicroMouseTe_MovingMaximum_Term(DW_MovingMaximum_MicroMouseTe_T
  *localDW);
extern void MicroMouseTe_MovingMinimum_Term(DW_MovingMinimum_MicroMouseTe_T
  *localDW);
extern void MicroMouseT_MovingMaximum1_Term(DW_MovingMaximum1_MicroMouseT_T
  *localDW);
extern void MicroMouseT_MovingMinimum2_Term(DW_MovingMinimum2_MicroMouseT_T
  *localDW);
extern void MicroMouse_MovingMaximum_o_Term(DW_MovingMaximum_MicroMouse_p_T
  *localDW);
extern void MicroMouse_MovingMinimum_a_Term(DW_MovingMinimum_MicroMouse_p_T
  *localDW);
extern void MicroMouse_MovingMaximum_g_Term(DW_MovingMaximum_MicroMous_pl_T
  *localDW);

#endif                            /* RTW_HEADER_MicroMouseTemplate_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
