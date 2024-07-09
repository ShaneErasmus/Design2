/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MicroMouseTemplate.h
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

#ifndef RTW_HEADER_MicroMouseTemplate_h_
#define RTW_HEADER_MicroMouseTemplate_h_
#ifndef MicroMouseTemplate_COMMON_INCLUDES_
#define MicroMouseTemplate_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "main.h"
#endif                                 /* MicroMouseTemplate_COMMON_INCLUDES_ */

#include "MicroMouseTemplate_types.h"
#include "rt_nonfinite.h"
#include <stddef.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* user code (top of header file) */
#include "MicroMouseProgramming\Core\Inc\IMU.h"
#include "MicroMouseProgramming\Core\Inc\CustomWhile.h"
#include "MicroMouseProgramming\Core\Inc\Motors.h"

/* Block signals for system '<S16>/Moving Maximum' */
typedef struct {
  real_T buf[20];
  int32_T bufIdx[20];
  int32_T ind_vect[20];
  real_T MovingMaximum;                /* '<S16>/Moving Maximum' */
} B_MovingMaximum_MicroMouseTem_T;

/* Block states (default storage) for system '<S16>/Moving Maximum' */
typedef struct {
  dsp_simulink_MovingMaximum_Mi_T obj; /* '<S16>/Moving Maximum' */
  boolean_T objisempty;                /* '<S16>/Moving Maximum' */
} DW_MovingMaximum_MicroMouseTe_T;

/* Block signals for system '<S16>/Moving Minimum' */
typedef struct {
  real_T buf[20];
  int32_T bufIdx[20];
  int32_T ind_vect[20];
  real_T MovingMinimum;                /* '<S16>/Moving Minimum' */
} B_MovingMinimum_MicroMouseTem_T;

/* Block states (default storage) for system '<S16>/Moving Minimum' */
typedef struct {
  dsp_simulink_MovingMinimum_Mi_T obj; /* '<S16>/Moving Minimum' */
  boolean_T objisempty;                /* '<S16>/Moving Minimum' */
} DW_MovingMinimum_MicroMouseTe_T;

/* Block signals for system '<S17>/Moving Maximum1' */
typedef struct {
  real_T buf[5];
  int32_T bufIdx[5];
  real_T MovingMaximum1;               /* '<S17>/Moving Maximum1' */
} B_MovingMaximum1_MicroMouseTe_T;

/* Block states (default storage) for system '<S17>/Moving Maximum1' */
typedef struct {
  dsp_simulink_MovingMaximum_m_T obj;  /* '<S17>/Moving Maximum1' */
  boolean_T objisempty;                /* '<S17>/Moving Maximum1' */
} DW_MovingMaximum1_MicroMouseT_T;

/* Block signals for system '<S17>/Moving Minimum2' */
typedef struct {
  real_T buf[15];
  int32_T bufIdx[15];
  int32_T ind_vect[15];
  real_T MovingMinimum2;               /* '<S17>/Moving Minimum2' */
} B_MovingMinimum2_MicroMouseTe_T;

/* Block states (default storage) for system '<S17>/Moving Minimum2' */
typedef struct {
  dsp_simulink_MovingMinimum_p_T obj;  /* '<S17>/Moving Minimum2' */
  boolean_T objisempty;                /* '<S17>/Moving Minimum2' */
} DW_MovingMinimum2_MicroMouseT_T;

/* Block signals for system '<S29>/Moving Maximum' */
typedef struct {
  real_T buf[15];
  int32_T bufIdx[15];
  int32_T ind_vect[15];
  real_T MovingMaximum;                /* '<S29>/Moving Maximum' */
} B_MovingMaximum_MicroMouseT_o_T;

/* Block states (default storage) for system '<S29>/Moving Maximum' */
typedef struct {
  dsp_simulink_MovingMaximum_j_T obj;  /* '<S29>/Moving Maximum' */
  boolean_T objisempty;                /* '<S29>/Moving Maximum' */
} DW_MovingMaximum_MicroMouse_p_T;

/* Block signals for system '<S29>/Moving Minimum' */
typedef struct {
  real_T buf[15];
  int32_T bufIdx[15];
  int32_T ind_vect[15];
  real_T MovingMinimum;                /* '<S29>/Moving Minimum' */
} B_MovingMinimum_MicroMouseT_o_T;

/* Block states (default storage) for system '<S29>/Moving Minimum' */
typedef struct {
  dsp_simulink_MovingMinimum_p_T obj;  /* '<S29>/Moving Minimum' */
  boolean_T objisempty;                /* '<S29>/Moving Minimum' */
} DW_MovingMinimum_MicroMouse_p_T;

/* Block signals for system '<S31>/Moving Maximum' */
typedef struct {
  real_T buf[5];
  int32_T bufIdx[5];
  real_T MovingMaximum;                /* '<S31>/Moving Maximum' */
} B_MovingMaximum_MicroMouse_oj_T;

/* Block states (default storage) for system '<S31>/Moving Maximum' */
typedef struct {
  dsp_simulink_MovingMaximum_m_T obj;  /* '<S31>/Moving Maximum' */
  boolean_T objisempty;                /* '<S31>/Moving Maximum' */
} DW_MovingMaximum_MicroMous_pl_T;

/* Block signals (default storage) */
typedef struct {
  real_T ADCs[8];                      /* '<Root>/Chart' */
  real_T CastToDouble1[8];             /* '<Root>/Cast To Double1' */
  real_T CastToDouble2[8];             /* '<Root>/Cast To Double2' */
  real_T CastToDouble_f[8];            /* '<S1>/Cast To Double' */
  uint16_T triggerType;
  GPIO_TypeDef * portNameLoc;
  real_T MOT_RS;                       /* '<Root>/pulse 1' */
  real_T Switch2;                      /* '<S11>/Switch2' */
  real_T d;
  real_T Saturation;                   /* '<S36>/Saturation' */
  int32_T i;
  uint32_T pinReadLoc;
  uint32_T pinReadLoc_m;
  boolean_T LED0;                      /* '<Root>/Chart' */
  boolean_T LED1;                      /* '<Root>/Chart' */
  boolean_T LED2;                      /* '<Root>/Chart' */
  boolean_T IR_LED_out[8];             /* '<Root>/Chart' */
  boolean_T b;
  boolean_T b1;
  B_MovingMinimum_MicroMouseT_o_T MovingMinimum_jncvpnvp;/* '<S29>/Moving Minimum' */
  B_MovingMaximum_MicroMouseT_o_T MovingMaximum_jncvpnvp;/* '<S29>/Moving Maximum' */
  B_MovingMinimum_MicroMouseT_o_T MovingMinimum_jncvpnv;/* '<S29>/Moving Minimum' */
  B_MovingMaximum_MicroMouseT_o_T MovingMaximum_jncvpnv;/* '<S29>/Moving Maximum' */
  B_MovingMinimum_MicroMouseT_o_T MovingMinimum_jncvpn;/* '<S29>/Moving Minimum' */
  B_MovingMaximum_MicroMouseT_o_T MovingMaximum_jncvpn;/* '<S29>/Moving Maximum' */
  B_MovingMinimum_MicroMouseT_o_T MovingMinimum_jncvp;/* '<S29>/Moving Minimum' */
  B_MovingMaximum_MicroMouseT_o_T MovingMaximum_jncvp;/* '<S29>/Moving Maximum' */
  B_MovingMinimum_MicroMouseT_o_T MovingMinimum1_j;/* '<S29>/Moving Minimum' */
  B_MovingMinimum_MicroMouseT_o_T MovingMinimum_jncv;/* '<S29>/Moving Minimum' */
  B_MovingMaximum_MicroMouse_oj_T MovingMaximum_jncv;/* '<S31>/Moving Maximum' */
  B_MovingMinimum_MicroMouseT_o_T MovingMinimum1;/* '<S29>/Moving Minimum' */
  B_MovingMinimum_MicroMouseT_o_T MovingMinimum_jnc;/* '<S29>/Moving Minimum' */
  B_MovingMaximum_MicroMouse_oj_T MovingMaximum_jnc;/* '<S31>/Moving Maximum' */
  B_MovingMinimum_MicroMouseT_o_T MovingMinimum_jn;/* '<S29>/Moving Minimum' */
  B_MovingMaximum_MicroMouseT_o_T MovingMaximum_jn;/* '<S29>/Moving Maximum' */
  B_MovingMinimum_MicroMouseT_o_T MovingMinimum_j;/* '<S29>/Moving Minimum' */
  B_MovingMaximum_MicroMouseT_o_T MovingMaximum_j;/* '<S29>/Moving Maximum' */
  B_MovingMinimum_MicroMouseTem_T MovingMinimum_pnaevvf;/* '<S16>/Moving Minimum' */
  B_MovingMaximum_MicroMouseTem_T MovingMaximum_pnaev;/* '<S16>/Moving Maximum' */
  B_MovingMinimum2_MicroMouseTe_T MovingMinimum2_p;/* '<S17>/Moving Minimum2' */
  B_MovingMinimum_MicroMouseTem_T MovingMinimum_pnaevv;/* '<S16>/Moving Minimum' */
  B_MovingMaximum1_MicroMouseTe_T MovingMaximum1_p;/* '<S17>/Moving Maximum1' */
  B_MovingMinimum_MicroMouseTem_T MovingMinimum_pnaev;/* '<S16>/Moving Minimum' */
  B_MovingMaximum_MicroMouseTem_T MovingMaximum_pnae;/* '<S16>/Moving Maximum' */
  B_MovingMinimum_MicroMouseTem_T MovingMinimum_pnae;/* '<S16>/Moving Minimum' */
  B_MovingMaximum_MicroMouseTem_T MovingMaximum_pna;/* '<S16>/Moving Maximum' */
  B_MovingMinimum_MicroMouseTem_T MovingMinimum_pna;/* '<S16>/Moving Minimum' */
  B_MovingMaximum_MicroMouseTem_T MovingMaximum_pn;/* '<S16>/Moving Maximum' */
  B_MovingMinimum_MicroMouseTem_T MovingMinimum_pn;/* '<S16>/Moving Minimum' */
  B_MovingMaximum_MicroMouseTem_T MovingMaximum_p;/* '<S16>/Moving Maximum' */
  B_MovingMinimum2_MicroMouseTe_T MovingMinimum2;/* '<S17>/Moving Minimum2' */
  B_MovingMinimum_MicroMouseTem_T MovingMinimum_p;/* '<S16>/Moving Minimum' */
  B_MovingMaximum1_MicroMouseTe_T MovingMaximum1;/* '<S17>/Moving Maximum1' */
  B_MovingMinimum_MicroMouseTem_T MovingMinimum;/* '<S16>/Moving Minimum' */
  B_MovingMaximum_MicroMouseTem_T MovingMaximum;/* '<S16>/Moving Maximum' */
} B_MicroMouseTemplate_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  stm32cube_blocks_AnalogInput__T obj; /* '<S15>/Analog to Digital Converter' */
  real_T vThreshLower[8];              /* '<Root>/Chart' */
  real_T Thresholds[8];                /* '<Root>/Chart' */
  int32_T clockTickCounter;            /* '<Root>/pulse 1' */
  int32_T clockTickCounter_g;          /* '<Root>/pulse 2' */
  uint8_T is_active_c3_MicroMouseTemplate;/* '<Root>/Chart' */
  uint8_T is_MainChart;                /* '<Root>/Chart' */
  uint8_T is_Calibrate;                /* '<Root>/Chart' */
  uint8_T temporalCounter_i1;          /* '<Root>/Chart' */
  DW_MovingMinimum_MicroMouse_p_T MovingMinimum_jncvpnvp;/* '<S29>/Moving Minimum' */
  DW_MovingMaximum_MicroMouse_p_T MovingMaximum_jncvpnvp;/* '<S29>/Moving Maximum' */
  DW_MovingMinimum_MicroMouse_p_T MovingMinimum_jncvpnv;/* '<S29>/Moving Minimum' */
  DW_MovingMaximum_MicroMouse_p_T MovingMaximum_jncvpnv;/* '<S29>/Moving Maximum' */
  DW_MovingMinimum_MicroMouse_p_T MovingMinimum_jncvpn;/* '<S29>/Moving Minimum' */
  DW_MovingMaximum_MicroMouse_p_T MovingMaximum_jncvpn;/* '<S29>/Moving Maximum' */
  DW_MovingMinimum_MicroMouse_p_T MovingMinimum_jncvp;/* '<S29>/Moving Minimum' */
  DW_MovingMaximum_MicroMouse_p_T MovingMaximum_jncvp;/* '<S29>/Moving Maximum' */
  DW_MovingMinimum_MicroMouse_p_T MovingMinimum1_j;/* '<S29>/Moving Minimum' */
  DW_MovingMinimum_MicroMouse_p_T MovingMinimum_jncv;/* '<S29>/Moving Minimum' */
  DW_MovingMaximum_MicroMous_pl_T MovingMaximum_jncv;/* '<S31>/Moving Maximum' */
  DW_MovingMinimum_MicroMouse_p_T MovingMinimum1;/* '<S29>/Moving Minimum' */
  DW_MovingMinimum_MicroMouse_p_T MovingMinimum_jnc;/* '<S29>/Moving Minimum' */
  DW_MovingMaximum_MicroMous_pl_T MovingMaximum_jnc;/* '<S31>/Moving Maximum' */
  DW_MovingMinimum_MicroMouse_p_T MovingMinimum_jn;/* '<S29>/Moving Minimum' */
  DW_MovingMaximum_MicroMouse_p_T MovingMaximum_jn;/* '<S29>/Moving Maximum' */
  DW_MovingMinimum_MicroMouse_p_T MovingMinimum_j;/* '<S29>/Moving Minimum' */
  DW_MovingMaximum_MicroMouse_p_T MovingMaximum_j;/* '<S29>/Moving Maximum' */
  DW_MovingMinimum_MicroMouseTe_T MovingMinimum_pnaevvf;/* '<S16>/Moving Minimum' */
  DW_MovingMaximum_MicroMouseTe_T MovingMaximum_pnaev;/* '<S16>/Moving Maximum' */
  DW_MovingMinimum2_MicroMouseT_T MovingMinimum2_p;/* '<S17>/Moving Minimum2' */
  DW_MovingMinimum_MicroMouseTe_T MovingMinimum_pnaevv;/* '<S16>/Moving Minimum' */
  DW_MovingMaximum1_MicroMouseT_T MovingMaximum1_p;/* '<S17>/Moving Maximum1' */
  DW_MovingMinimum_MicroMouseTe_T MovingMinimum_pnaev;/* '<S16>/Moving Minimum' */
  DW_MovingMaximum_MicroMouseTe_T MovingMaximum_pnae;/* '<S16>/Moving Maximum' */
  DW_MovingMinimum_MicroMouseTe_T MovingMinimum_pnae;/* '<S16>/Moving Minimum' */
  DW_MovingMaximum_MicroMouseTe_T MovingMaximum_pna;/* '<S16>/Moving Maximum' */
  DW_MovingMinimum_MicroMouseTe_T MovingMinimum_pna;/* '<S16>/Moving Minimum' */
  DW_MovingMaximum_MicroMouseTe_T MovingMaximum_pn;/* '<S16>/Moving Maximum' */
  DW_MovingMinimum_MicroMouseTe_T MovingMinimum_pn;/* '<S16>/Moving Minimum' */
  DW_MovingMaximum_MicroMouseTe_T MovingMaximum_p;/* '<S16>/Moving Maximum' */
  DW_MovingMinimum2_MicroMouseT_T MovingMinimum2;/* '<S17>/Moving Minimum2' */
  DW_MovingMinimum_MicroMouseTe_T MovingMinimum_p;/* '<S16>/Moving Minimum' */
  DW_MovingMaximum1_MicroMouseT_T MovingMaximum1;/* '<S17>/Moving Maximum1' */
  DW_MovingMinimum_MicroMouseTe_T MovingMinimum;/* '<S16>/Moving Minimum' */
  DW_MovingMaximum_MicroMouseTe_T MovingMaximum;/* '<S16>/Moving Maximum' */
} DW_MicroMouseTemplate_T;

/* Parameters (default storage) */
struct P_MicroMouseTemplate_T_ {
  real_T TIM3_ARR;                     /* Variable: TIM3_ARR
                                        * Referenced by:
                                        *   '<S11>/Gain'
                                        *   '<S11>/Gain1'
                                        */
  real_T Constant2_Value;              /* Expression: 1
                                        * Referenced by: '<S29>/Constant2'
                                        */
  real_T Constant3_Value;              /* Expression: 0
                                        * Referenced by: '<S29>/Constant3'
                                        */
  real_T Constant2_Value_o;            /* Expression: 1
                                        * Referenced by: '<S30>/Constant2'
                                        */
  real_T Constant3_Value_p;            /* Expression: 0
                                        * Referenced by: '<S30>/Constant3'
                                        */
  real_T Constant2_Value_e;            /* Expression: 1
                                        * Referenced by: '<S31>/Constant2'
                                        */
  real_T Constant3_Value_d;            /* Expression: 0
                                        * Referenced by: '<S31>/Constant3'
                                        */
  real_T Constant2_Value_j;            /* Expression: 1
                                        * Referenced by: '<S32>/Constant2'
                                        */
  real_T Constant3_Value_b;            /* Expression: 0
                                        * Referenced by: '<S32>/Constant3'
                                        */
  real_T Constant2_Value_i;            /* Expression: 1
                                        * Referenced by: '<S33>/Constant2'
                                        */
  real_T Constant3_Value_f;            /* Expression: 0
                                        * Referenced by: '<S33>/Constant3'
                                        */
  real_T Constant2_Value_m;            /* Expression: 1
                                        * Referenced by: '<S34>/Constant2'
                                        */
  real_T Constant3_Value_j;            /* Expression: 0
                                        * Referenced by: '<S34>/Constant3'
                                        */
  real_T Constant2_Value_h;            /* Expression: 1
                                        * Referenced by: '<S35>/Constant2'
                                        */
  real_T Constant3_Value_i;            /* Expression: 0
                                        * Referenced by: '<S35>/Constant3'
                                        */
  real_T Constant2_Value_b;            /* Expression: 1
                                        * Referenced by: '<S36>/Constant2'
                                        */
  real_T Constant3_Value_dx;           /* Expression: 0
                                        * Referenced by: '<S36>/Constant3'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 3.3
                                        * Referenced by: '<S36>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: 0
                                        * Referenced by: '<S36>/Saturation'
                                        */
  real_T pulse1_Amp;                   /* Expression: 1
                                        * Referenced by: '<Root>/pulse 1'
                                        */
  real_T pulse1_Period;                /* Computed Parameter: pulse1_Period
                                        * Referenced by: '<Root>/pulse 1'
                                        */
  real_T pulse1_Duty;                  /* Computed Parameter: pulse1_Duty
                                        * Referenced by: '<Root>/pulse 1'
                                        */
  real_T pulse1_PhaseDelay;            /* Expression: 0
                                        * Referenced by: '<Root>/pulse 1'
                                        */
  real_T pulse2_Amp;                   /* Expression: 1
                                        * Referenced by: '<Root>/pulse 2'
                                        */
  real_T pulse2_Period;                /* Computed Parameter: pulse2_Period
                                        * Referenced by: '<Root>/pulse 2'
                                        */
  real_T pulse2_Duty;                  /* Computed Parameter: pulse2_Duty
                                        * Referenced by: '<Root>/pulse 2'
                                        */
  real_T pulse2_PhaseDelay;            /* Expression: 2*IR_LED_PERIOD
                                        * Referenced by: '<Root>/pulse 2'
                                        */
  real_T Constant8_Value;              /* Expression: 0
                                        * Referenced by: '<Root>/Constant8'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S13>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<S13>/Constant1'
                                        */
  real_T Constant1_Value_a;            /* Expression: 70
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T Off_Value;                    /* Expression: 0
                                        * Referenced by: '<S11>/Off'
                                        */
  real_T Switch1_Threshold;            /* Expression: 0
                                        * Referenced by: '<S11>/Switch1'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * Referenced by: '<S11>/Switch'
                                        */
  real_T Off1_Value;                   /* Expression: 0
                                        * Referenced by: '<S11>/Off1'
                                        */
  real_T Switch3_Threshold;            /* Expression: 0
                                        * Referenced by: '<S11>/Switch3'
                                        */
  real_T Switch2_Threshold;            /* Expression: 0
                                        * Referenced by: '<S11>/Switch2'
                                        */
  real_T Constant_Value_c;             /* Expression: 1
                                        * Referenced by: '<Root>/Constant'
                                        */
  real32_T Switch_Threshold_j;         /* Computed Parameter: Switch_Threshold_j
                                        * Referenced by: '<S35>/Switch'
                                        */
  real32_T Switch_Threshold_m;         /* Computed Parameter: Switch_Threshold_m
                                        * Referenced by: '<S32>/Switch'
                                        */
  real32_T Switch_Threshold_h;         /* Computed Parameter: Switch_Threshold_h
                                        * Referenced by: '<S30>/Switch'
                                        */
  real32_T Switch_Threshold_f;         /* Computed Parameter: Switch_Threshold_f
                                        * Referenced by: '<S36>/Switch'
                                        */
  real32_T Switch_Threshold_a;         /* Computed Parameter: Switch_Threshold_a
                                        * Referenced by: '<S33>/Switch'
                                        */
  real32_T Switch_Threshold_k;         /* Computed Parameter: Switch_Threshold_k
                                        * Referenced by: '<S29>/Switch'
                                        */
  real32_T Switch_Threshold_i;         /* Computed Parameter: Switch_Threshold_i
                                        * Referenced by: '<S31>/Switch'
                                        */
  real32_T Switch_Threshold_d;         /* Computed Parameter: Switch_Threshold_d
                                        * Referenced by: '<S34>/Switch'
                                        */
  real32_T DataStoreMemory_InitialValue;
                             /* Computed Parameter: DataStoreMemory_InitialValue
                              * Referenced by: '<S5>/Data Store Memory'
                              */
  real32_T DataStoreMemory1_InitialValue;
                            /* Computed Parameter: DataStoreMemory1_InitialValue
                             * Referenced by: '<S5>/Data Store Memory1'
                             */
  uint32_T DataStoreMemory1_InitialValue_h;
                          /* Computed Parameter: DataStoreMemory1_InitialValue_h
                           * Referenced by: '<S4>/Data Store Memory1'
                           */
  uint16_T Gain_Gain;                  /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S1>/Gain'
                                        */
  uint16_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S1>/Gain1'
                                        */
  uint16_T Gain2_Gain;                 /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<S1>/Gain2'
                                        */
  uint16_T DataStoreMemory3_InitialValue;
                            /* Computed Parameter: DataStoreMemory3_InitialValue
                             * Referenced by: '<S1>/Data Store Memory3'
                             */
  uint16_T DataStoreMemory_InitialValue_p;
                           /* Computed Parameter: DataStoreMemory_InitialValue_p
                            * Referenced by: '<S1>/Data Store Memory'
                            */
  uint16_T DataStoreMemory1_InitialValue_n;
                          /* Computed Parameter: DataStoreMemory1_InitialValue_n
                           * Referenced by: '<S1>/Data Store Memory1'
                           */
  uint16_T DataStoreMemory2_InitialValue;
                            /* Computed Parameter: DataStoreMemory2_InitialValue
                             * Referenced by: '<S1>/Data Store Memory2'
                             */
  uint16_T DataStoreMemory_InitialValue_c;
                           /* Computed Parameter: DataStoreMemory_InitialValue_c
                            * Referenced by: '<S11>/Data Store Memory'
                            */
  uint16_T DataStoreMemory1_InitialValue_a;
                          /* Computed Parameter: DataStoreMemory1_InitialValue_a
                           * Referenced by: '<S11>/Data Store Memory1'
                           */
  boolean_T LED0_Y0;                   /* Computed Parameter: LED0_Y0
                                        * Referenced by: '<S26>/LED0'
                                        */
  boolean_T LED1_Y0;                   /* Computed Parameter: LED1_Y0
                                        * Referenced by: '<S26>/LED1'
                                        */
  boolean_T LED2_Y0;                   /* Computed Parameter: LED2_Y0
                                        * Referenced by: '<S26>/LED2'
                                        */
  boolean_T DataStoreMemory_InitialValue_h;
                           /* Computed Parameter: DataStoreMemory_InitialValue_h
                            * Referenced by: '<S4>/Data Store Memory'
                            */
};

/* Real-time Model Data Structure */
struct tag_RTM_MicroMouseTemplate_T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block parameters (default storage) */
extern P_MicroMouseTemplate_T MicroMouseTemplate_P;

/* Block signals (default storage) */
extern B_MicroMouseTemplate_T MicroMouseTemplate_B;

/* Block states (default storage) */
extern DW_MicroMouseTemplate_T MicroMouseTemplate_DW;

/*
 * Exported States
 *
 * Note: Exported states are block states with an exported global
 * storage class designation.  Code generation will declare the memory for these
 * states and exports their symbols.
 *
 */
extern real32_T IMU_Accel[3];          /* '<S5>/Data Store Memory' */
extern real32_T IMU_Gyro[3];           /* '<S5>/Data Store Memory1' */
extern uint32_T IR_LED_TIMER;          /* '<S4>/Data Store Memory1' */
extern uint16_T ADC2s[9];              /* '<S1>/Data Store Memory3' */
extern uint16_T ADC1s[9];              /* '<S1>/Data Store Memory' */
extern uint16_T ADC_H[9];              /* '<S1>/Data Store Memory1' */
extern uint16_T ADC_L[9];              /* '<S1>/Data Store Memory2' */
extern uint16_T MOT_R[2];              /* '<S11>/Data Store Memory' */
extern uint16_T MOT_L[2];              /* '<S11>/Data Store Memory1' */
extern boolean_T IR_LEDs[8];           /* '<S4>/Data Store Memory' */

/* Model entry point functions */
extern void MicroMouseTemplate_initialize(void);
extern void MicroMouseTemplate_step(void);
extern void MicroMouseTemplate_terminate(void);

/* Real-time Model object */
extern RT_MODEL_MicroMouseTemplate_T *const MicroMouseTemplate_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S31>/Display1' : Unused code path elimination
 * Block '<S26>/Cast To Double' : Eliminate redundant data type conversion
 * Block '<S26>/Cast To Double1' : Eliminate redundant data type conversion
 * Block '<S4>/Cast To Boolean' : Eliminate redundant data type conversion
 */

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
 * '<Root>' : 'MicroMouseTemplate'
 * '<S1>'   : 'MicroMouseTemplate/ADCs '
 * '<S2>'   : 'MicroMouseTemplate/CTRL_LEDs'
 * '<S3>'   : 'MicroMouseTemplate/Chart'
 * '<S4>'   : 'MicroMouseTemplate/GPIO for IR LEDs'
 * '<S5>'   : 'MicroMouseTemplate/IMU'
 * '<S6>'   : 'MicroMouseTemplate/LED0'
 * '<S7>'   : 'MicroMouseTemplate/LED1'
 * '<S8>'   : 'MicroMouseTemplate/LED2'
 * '<S9>'   : 'MicroMouseTemplate/SW1'
 * '<S10>'  : 'MicroMouseTemplate/SW2'
 * '<S11>'  : 'MicroMouseTemplate/Subsystem'
 * '<S12>'  : 'MicroMouseTemplate/ADCs /ADC2 IN10  IN1'
 * '<S13>'  : 'MicroMouseTemplate/ADCs /Subsystem1'
 * '<S14>'  : 'MicroMouseTemplate/ADCs /ADC2 IN10  IN1/ECSoC'
 * '<S15>'  : 'MicroMouseTemplate/ADCs /ADC2 IN10  IN1/ECSoC/ECSimCodegen'
 * '<S16>'  : 'MicroMouseTemplate/ADCs /Subsystem1/convert to H and L1'
 * '<S17>'  : 'MicroMouseTemplate/ADCs /Subsystem1/convert to H and L2'
 * '<S18>'  : 'MicroMouseTemplate/ADCs /Subsystem1/convert to H and L3'
 * '<S19>'  : 'MicroMouseTemplate/ADCs /Subsystem1/convert to H and L4'
 * '<S20>'  : 'MicroMouseTemplate/ADCs /Subsystem1/convert to H and L5'
 * '<S21>'  : 'MicroMouseTemplate/ADCs /Subsystem1/convert to H and L6'
 * '<S22>'  : 'MicroMouseTemplate/ADCs /Subsystem1/convert to H and L7'
 * '<S23>'  : 'MicroMouseTemplate/ADCs /Subsystem1/convert to H and L8'
 * '<S24>'  : 'MicroMouseTemplate/CTRL_LEDs/ECSoC'
 * '<S25>'  : 'MicroMouseTemplate/CTRL_LEDs/ECSoC/ECSimCodegen'
 * '<S26>'  : 'MicroMouseTemplate/Chart/MainChart.ShowDetections.showDetections'
 * '<S27>'  : 'MicroMouseTemplate/Chart/MainChart.ShowDetections.showDetections/Subsystem'
 * '<S28>'  : 'MicroMouseTemplate/Chart/MainChart.ShowDetections.showDetections/doCustomDetections'
 * '<S29>'  : 'MicroMouseTemplate/Chart/MainChart.ShowDetections.showDetections/doCustomDetections/detect_DOWN_LS'
 * '<S30>'  : 'MicroMouseTemplate/Chart/MainChart.ShowDetections.showDetections/doCustomDetections/detect_DOWN_RS'
 * '<S31>'  : 'MicroMouseTemplate/Chart/MainChart.ShowDetections.showDetections/doCustomDetections/detect_FWD_LS'
 * '<S32>'  : 'MicroMouseTemplate/Chart/MainChart.ShowDetections.showDetections/doCustomDetections/detect_FWD_RS'
 * '<S33>'  : 'MicroMouseTemplate/Chart/MainChart.ShowDetections.showDetections/doCustomDetections/detect_LS'
 * '<S34>'  : 'MicroMouseTemplate/Chart/MainChart.ShowDetections.showDetections/doCustomDetections/detect_MOT_LS'
 * '<S35>'  : 'MicroMouseTemplate/Chart/MainChart.ShowDetections.showDetections/doCustomDetections/detect_MOT_RS'
 * '<S36>'  : 'MicroMouseTemplate/Chart/MainChart.ShowDetections.showDetections/doCustomDetections/detect_RS'
 * '<S37>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_DOWN_LEFT'
 * '<S38>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_DOWN_RIGHT'
 * '<S39>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_FWD_LEFT'
 * '<S40>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_FWD_RIGHT'
 * '<S41>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_LEFT'
 * '<S42>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_MOT_LEFT'
 * '<S43>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_MOT_RIGHT'
 * '<S44>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_RIGHT'
 * '<S45>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_DOWN_LEFT/ECSoC'
 * '<S46>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_DOWN_LEFT/ECSoC/ECSimCodegen'
 * '<S47>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_DOWN_RIGHT/ECSoC'
 * '<S48>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_DOWN_RIGHT/ECSoC/ECSimCodegen'
 * '<S49>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_FWD_LEFT/ECSoC'
 * '<S50>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_FWD_LEFT/ECSoC/ECSimCodegen'
 * '<S51>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_FWD_RIGHT/ECSoC'
 * '<S52>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_FWD_RIGHT/ECSoC/ECSimCodegen'
 * '<S53>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_LEFT/ECSoC'
 * '<S54>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_LEFT/ECSoC/ECSimCodegen'
 * '<S55>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_MOT_LEFT/ECSoC'
 * '<S56>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_MOT_LEFT/ECSoC/ECSimCodegen'
 * '<S57>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_MOT_RIGHT/ECSoC'
 * '<S58>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_MOT_RIGHT/ECSoC/ECSimCodegen'
 * '<S59>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_RIGHT/ECSoC'
 * '<S60>'  : 'MicroMouseTemplate/GPIO for IR LEDs/LED_RIGHT/ECSoC/ECSimCodegen'
 * '<S61>'  : 'MicroMouseTemplate/LED0/ECSoC'
 * '<S62>'  : 'MicroMouseTemplate/LED0/ECSoC/ECSimCodegen'
 * '<S63>'  : 'MicroMouseTemplate/LED1/ECSoC'
 * '<S64>'  : 'MicroMouseTemplate/LED1/ECSoC/ECSimCodegen'
 * '<S65>'  : 'MicroMouseTemplate/LED2/ECSoC'
 * '<S66>'  : 'MicroMouseTemplate/LED2/ECSoC/ECSimCodegen'
 * '<S67>'  : 'MicroMouseTemplate/SW1/ECSoC'
 * '<S68>'  : 'MicroMouseTemplate/SW1/ECSoC/ECSimCodegen'
 * '<S69>'  : 'MicroMouseTemplate/SW2/ECSoC'
 * '<S70>'  : 'MicroMouseTemplate/SW2/ECSoC/ECSimCodegen'
 * '<S71>'  : 'MicroMouseTemplate/Subsystem/MOTOR_EN'
 * '<S72>'  : 'MicroMouseTemplate/Subsystem/MOTOR_EN/ECSoC'
 * '<S73>'  : 'MicroMouseTemplate/Subsystem/MOTOR_EN/ECSoC/ECSimCodegen'
 */
#endif                                 /* RTW_HEADER_MicroMouseTemplate_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
