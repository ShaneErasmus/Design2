/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MicroMouseTemplate_data.c
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

#include "MicroMouseTemplate.h"

/* Block parameters (default storage) */
P_MicroMouseTemplate_T MicroMouseTemplate_P = {
  /* Variable: TIM3_ARR
   * Referenced by:
   *   '<S11>/Gain'
   *   '<S11>/Gain1'
   */
  4000.0,

  /* Expression: 1
   * Referenced by: '<S29>/Constant2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S29>/Constant3'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S30>/Constant2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S30>/Constant3'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S31>/Constant2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S31>/Constant3'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S32>/Constant2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S32>/Constant3'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S33>/Constant2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S33>/Constant3'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S34>/Constant2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S34>/Constant3'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S35>/Constant2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S35>/Constant3'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S36>/Constant2'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S36>/Constant3'
   */
  0.0,

  /* Expression: 3.3
   * Referenced by: '<S36>/Saturation'
   */
  3.3,

  /* Expression: 0
   * Referenced by: '<S36>/Saturation'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<Root>/pulse 1'
   */
  1.0,

  /* Computed Parameter: pulse1_Period
   * Referenced by: '<Root>/pulse 1'
   */
  4.0,

  /* Computed Parameter: pulse1_Duty
   * Referenced by: '<Root>/pulse 1'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<Root>/pulse 1'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<Root>/pulse 2'
   */
  1.0,

  /* Computed Parameter: pulse2_Period
   * Referenced by: '<Root>/pulse 2'
   */
  12.0,

  /* Computed Parameter: pulse2_Duty
   * Referenced by: '<Root>/pulse 2'
   */
  3.0,

  /* Expression: 2*IR_LED_PERIOD
   * Referenced by: '<Root>/pulse 2'
   */
  0.1,

  /* Expression: 0
   * Referenced by: '<Root>/Constant8'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S13>/Constant'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S13>/Constant1'
   */
  0.0,

  /* Expression: 70
   * Referenced by: '<Root>/Constant1'
   */
  70.0,

  /* Expression: 0
   * Referenced by: '<S11>/Off'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S11>/Switch1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S11>/Switch'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S11>/Off1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S11>/Switch3'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S11>/Switch2'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<Root>/Constant'
   */
  1.0,

  /* Computed Parameter: Switch_Threshold_j
   * Referenced by: '<S35>/Switch'
   */
  1.2F,

  /* Computed Parameter: Switch_Threshold_m
   * Referenced by: '<S32>/Switch'
   */
  1.15F,

  /* Computed Parameter: Switch_Threshold_h
   * Referenced by: '<S30>/Switch'
   */
  1.2F,

  /* Computed Parameter: Switch_Threshold_f
   * Referenced by: '<S36>/Switch'
   */
  1.2F,

  /* Computed Parameter: Switch_Threshold_a
   * Referenced by: '<S33>/Switch'
   */
  1.2F,

  /* Computed Parameter: Switch_Threshold_k
   * Referenced by: '<S29>/Switch'
   */
  1.2F,

  /* Computed Parameter: Switch_Threshold_i
   * Referenced by: '<S31>/Switch'
   */
  1.15F,

  /* Computed Parameter: Switch_Threshold_d
   * Referenced by: '<S34>/Switch'
   */
  1.2F,

  /* Computed Parameter: DataStoreMemory_InitialValue
   * Referenced by: '<S5>/Data Store Memory'
   */
  0.0F,

  /* Computed Parameter: DataStoreMemory1_InitialValue
   * Referenced by: '<S5>/Data Store Memory1'
   */
  0.0F,

  /* Computed Parameter: DataStoreMemory1_InitialValue_h
   * Referenced by: '<S4>/Data Store Memory1'
   */
  0U,

  /* Computed Parameter: Gain_Gain
   * Referenced by: '<S1>/Gain'
   */
  54080U,

  /* Computed Parameter: Gain1_Gain
   * Referenced by: '<S1>/Gain1'
   */
  54080U,

  /* Computed Parameter: Gain2_Gain
   * Referenced by: '<S1>/Gain2'
   */
  54080U,

  /* Computed Parameter: DataStoreMemory3_InitialValue
   * Referenced by: '<S1>/Data Store Memory3'
   */
  0U,

  /* Computed Parameter: DataStoreMemory_InitialValue_p
   * Referenced by: '<S1>/Data Store Memory'
   */
  0U,

  /* Computed Parameter: DataStoreMemory1_InitialValue_n
   * Referenced by: '<S1>/Data Store Memory1'
   */
  0U,

  /* Computed Parameter: DataStoreMemory2_InitialValue
   * Referenced by: '<S1>/Data Store Memory2'
   */
  0U,

  /* Computed Parameter: DataStoreMemory_InitialValue_c
   * Referenced by: '<S11>/Data Store Memory'
   */
  0U,

  /* Computed Parameter: DataStoreMemory1_InitialValue_a
   * Referenced by: '<S11>/Data Store Memory1'
   */
  0U,

  /* Computed Parameter: LED0_Y0
   * Referenced by: '<S26>/LED0'
   */
  false,

  /* Computed Parameter: LED1_Y0
   * Referenced by: '<S26>/LED1'
   */
  false,

  /* Computed Parameter: LED2_Y0
   * Referenced by: '<S26>/LED2'
   */
  false,

  /* Computed Parameter: DataStoreMemory_InitialValue_h
   * Referenced by: '<S4>/Data Store Memory'
   */
  false
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
