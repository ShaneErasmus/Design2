/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MicroMouseTemplate.c
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
#include "rtwtypes.h"
#include "MicroMouseTemplate_types.h"
#include "MicroMouseTemplate_private.h"
#include <string.h>
#include <math.h>
#include "rt_nonfinite.h"
#include "stm_adc_ll.h"

/* Named constants for Chart: '<Root>/Chart' */
#define MicroMouseTe_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define MicroMouseTem_IN_ShowDetections ((uint8_T)2U)
#define MicroMouseTemplate_IN_Cal1     ((uint8_T)1U)
#define MicroMouseTemplate_IN_Cal2     ((uint8_T)2U)
#define MicroMouseTemplate_IN_Cal3     ((uint8_T)3U)
#define MicroMouseTemplate_IN_Cal4     ((uint8_T)4U)
#define MicroMouseTemplate_IN_Calibrate ((uint8_T)1U)

/* user code (top of source file) */
/* System '<Root>' */
TIM_HandleTypeDef htim3;

/* System '<Root>' */
I2C_HandleTypeDef hi2c2;

/* Exported block states */
real32_T IMU_Accel[3];                 /* '<S5>/Data Store Memory' */
real32_T IMU_Gyro[3];                  /* '<S5>/Data Store Memory1' */
uint32_T IR_LED_TIMER;                 /* '<S4>/Data Store Memory1' */
uint16_T ADC2s[9];                     /* '<S1>/Data Store Memory3' */
uint16_T ADC1s[9];                     /* '<S1>/Data Store Memory' */
uint16_T ADC_H[9];                     /* '<S1>/Data Store Memory1' */
uint16_T ADC_L[9];                     /* '<S1>/Data Store Memory2' */
uint16_T MOT_R[2];                     /* '<S11>/Data Store Memory' */
uint16_T MOT_L[2];                     /* '<S11>/Data Store Memory1' */
boolean_T IR_LEDs[8];                  /* '<S4>/Data Store Memory' */

/* Block signals (default storage) */
B_MicroMouseTemplate_T MicroMouseTemplate_B;

/* Block states (default storage) */
DW_MicroMouseTemplate_T MicroMouseTemplate_DW;

/* Real-time model */
static RT_MODEL_MicroMouseTemplate_T MicroMouseTemplate_M_;
RT_MODEL_MicroMouseTemplate_T *const MicroMouseTemplate_M =
  &MicroMouseTemplate_M_;

/* Forward declaration for local functions */
static void MicroMouseTemp_SystemCore_setup(stm32cube_blocks_AnalogInput__T *obj);
static void rate_scheduler(void);

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (MicroMouseTemplate_M->Timing.TaskCounters.TID[1])++;
  if ((MicroMouseTemplate_M->Timing.TaskCounters.TID[1]) > 2) {
                                /* Sample time: [0.037500000000000006s, 0.0s] */
    MicroMouseTemplate_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* System initialize for atomic system: */
void MicroMouseTe_MovingMaximum_Init(DW_MovingMaximum_MicroMouseTe_T *localDW)
{
  g_dsp_internal_SlidingWindowM_T *obj;
  int32_T i;

  /* Start for MATLABSystem: '<S16>/Moving Maximum' */
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  localDW->obj.isInitialized = 1;
  localDW->obj.NumChannels = 1;
  localDW->obj._pobj0.isInitialized = 0;
  localDW->obj.pStat = &localDW->obj._pobj0;
  obj = localDW->obj.pStat;
  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  obj->isSetupComplete = true;
  localDW->obj.isSetupComplete = true;

  /* InitializeConditions for MATLABSystem: '<S16>/Moving Maximum' */
  obj = localDW->obj.pStat;
  if (obj->isInitialized == 1) {
    for (i = 0; i < 20; i++) {
      obj->pBuffer[i] = 0.0;
    }

    for (i = 0; i < 20; i++) {
      obj->pBufferIdx[i] = 0;
    }

    obj->pNumElements = 0;
    obj->pCount = 1;
    obj->pTop = 1;
  }

  /* End of InitializeConditions for MATLABSystem: '<S16>/Moving Maximum' */
}

/* Output and update for atomic system: */
void MicroMouseTemplat_MovingMaximum(real_T rtu_0,
  B_MovingMaximum_MicroMouseTem_T *localB, DW_MovingMaximum_MicroMouseTe_T
  *localDW)
{
  g_dsp_internal_SlidingWindowM_T *obj;
  int32_T N;
  int32_T b_ind;
  int32_T cnt;
  int32_T i;
  int32_T indVal;
  int32_T placement;
  int32_T qY;
  int32_T qY_0;
  int32_T top;
  boolean_T exitg1;

  /* MATLABSystem: '<S16>/Moving Maximum' */
  obj = localDW->obj.pStat;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    obj->isSetupComplete = true;
    for (i = 0; i < 20; i++) {
      obj->pBuffer[i] = 0.0;
    }

    for (i = 0; i < 20; i++) {
      obj->pBufferIdx[i] = 0;
    }

    obj->pNumElements = 0;
    obj->pCount = 1;
    obj->pTop = 1;
  }

  for (i = 0; i < 20; i++) {
    localB->buf[i] = obj->pBuffer[i];
  }

  for (i = 0; i < 20; i++) {
    localB->bufIdx[i] = obj->pBufferIdx[i];
  }

  i = obj->pNumElements;
  cnt = obj->pCount;
  top = obj->pTop;
  if (i > 0) {
    N = localB->bufIdx[top - 1];
    if ((cnt >= 0) && (N < cnt - MAX_int32_T)) {
      b_ind = MAX_int32_T;
    } else if ((cnt < 0) && (N > cnt - MIN_int32_T)) {
      b_ind = MIN_int32_T;
    } else {
      b_ind = cnt - N;
    }

    if (b_ind == 20) {
      if (top > 2147483646) {
        top = MAX_int32_T;
      } else {
        top++;
      }

      if (top > 20) {
        top = 1;
      }

      i--;
    }
  }

  if ((i < 0) && (top < MIN_int32_T - i)) {
    qY = MIN_int32_T;
  } else if ((i > 0) && (top > MAX_int32_T - i)) {
    qY = MAX_int32_T;
  } else {
    qY = i + top;
  }

  if (qY < -2147483647) {
    placement = MIN_int32_T;
  } else {
    placement = qY - 1;
  }

  if (placement >= 20) {
    placement -= 20;
  }

  memset(&localB->ind_vect[0], 0, 20U * sizeof(int32_T));
  N = i;
  if (i > 0) {
    qY = i - 1;
    if (top < -2147483647) {
      qY_0 = MIN_int32_T;
    } else {
      qY_0 = top - 1;
    }

    for (b_ind = qY; b_ind >= 0; b_ind--) {
      if ((qY_0 < 0) && (b_ind < MIN_int32_T - qY_0)) {
        indVal = MIN_int32_T;
      } else if ((qY_0 > 0) && (b_ind > MAX_int32_T - qY_0)) {
        indVal = MAX_int32_T;
      } else {
        indVal = qY_0 + b_ind;
      }

      if (indVal >= 20) {
        indVal -= 20;
      }

      localB->ind_vect[(i - b_ind) - 1] = indVal + 1;
    }

    qY = 1;
    exitg1 = false;
    while ((!exitg1) && (qY - 1 <= i - 1)) {
      b_ind = localB->ind_vect[qY - 1] - 1;
      if (rtu_0 < localB->buf[b_ind]) {
        exitg1 = true;
      } else {
        placement = b_ind;
        if (N < -2147483647) {
          N = MIN_int32_T;
        } else {
          N--;
        }

        qY++;
      }
    }
  }

  localB->buf[placement] = rtu_0;
  localB->bufIdx[placement] = cnt;
  if (cnt > 2147483646) {
    cnt = MAX_int32_T;
  } else {
    cnt++;
  }

  if (cnt > 1000000) {
    cnt -= 1000000;
    for (b_ind = 0; b_ind < 20; b_ind++) {
      i = localB->bufIdx[b_ind];
      if (i < -2146483648) {
        localB->bufIdx[b_ind] = MIN_int32_T;
      } else {
        localB->bufIdx[b_ind] = i - 1000000;
      }
    }
  }

  for (i = 0; i < 20; i++) {
    obj->pBuffer[i] = localB->buf[i];
  }

  for (i = 0; i < 20; i++) {
    obj->pBufferIdx[i] = localB->bufIdx[i];
  }

  if (N > 2147483646) {
    obj->pNumElements = MAX_int32_T;
  } else {
    obj->pNumElements = N + 1;
  }

  obj->pCount = cnt;
  obj->pTop = top;

  /* MATLABSystem: '<S16>/Moving Maximum' */
  localB->MovingMaximum = localB->buf[top - 1];
}

/* Termination for atomic system: */
void MicroMouseTe_MovingMaximum_Term(DW_MovingMaximum_MicroMouseTe_T *localDW)
{
  g_dsp_internal_SlidingWindowM_T *obj;

  /* Terminate for MATLABSystem: '<S16>/Moving Maximum' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      localDW->obj.NumChannels = -1;
      obj = localDW->obj.pStat;
      if (obj->isInitialized == 1) {
        obj->isInitialized = 2;
      }
    }
  }

  /* End of Terminate for MATLABSystem: '<S16>/Moving Maximum' */
}

/* System initialize for atomic system: */
void MicroMouseTe_MovingMinimum_Init(DW_MovingMinimum_MicroMouseTe_T *localDW)
{
  g_dsp_internal_SlidingWindo_g_T *obj;
  int32_T i;

  /* Start for MATLABSystem: '<S16>/Moving Minimum' */
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  localDW->obj.isInitialized = 1;
  localDW->obj.NumChannels = 1;
  localDW->obj._pobj0.isInitialized = 0;
  localDW->obj.pStat = &localDW->obj._pobj0;
  obj = localDW->obj.pStat;
  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  obj->isSetupComplete = true;
  localDW->obj.isSetupComplete = true;

  /* InitializeConditions for MATLABSystem: '<S16>/Moving Minimum' */
  obj = localDW->obj.pStat;
  if (obj->isInitialized == 1) {
    for (i = 0; i < 20; i++) {
      obj->pBuffer[i] = 0.0;
    }

    for (i = 0; i < 20; i++) {
      obj->pBufferIdx[i] = 0;
    }

    obj->pNumElements = 0;
    obj->pCount = 1;
    obj->pTop = 1;
  }

  /* End of InitializeConditions for MATLABSystem: '<S16>/Moving Minimum' */
}

/* Output and update for atomic system: */
void MicroMouseTemplat_MovingMinimum(real_T rtu_0,
  B_MovingMinimum_MicroMouseTem_T *localB, DW_MovingMinimum_MicroMouseTe_T
  *localDW)
{
  g_dsp_internal_SlidingWindo_g_T *obj;
  int32_T N;
  int32_T b_ind;
  int32_T cnt;
  int32_T i;
  int32_T indVal;
  int32_T placement;
  int32_T qY;
  int32_T qY_0;
  int32_T top;
  boolean_T exitg1;

  /* MATLABSystem: '<S16>/Moving Minimum' */
  obj = localDW->obj.pStat;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    obj->isSetupComplete = true;
    for (i = 0; i < 20; i++) {
      obj->pBuffer[i] = 0.0;
    }

    for (i = 0; i < 20; i++) {
      obj->pBufferIdx[i] = 0;
    }

    obj->pNumElements = 0;
    obj->pCount = 1;
    obj->pTop = 1;
  }

  for (i = 0; i < 20; i++) {
    localB->buf[i] = obj->pBuffer[i];
  }

  for (i = 0; i < 20; i++) {
    localB->bufIdx[i] = obj->pBufferIdx[i];
  }

  i = obj->pNumElements;
  cnt = obj->pCount;
  top = obj->pTop;
  if (i > 0) {
    N = localB->bufIdx[top - 1];
    if ((cnt >= 0) && (N < cnt - MAX_int32_T)) {
      b_ind = MAX_int32_T;
    } else if ((cnt < 0) && (N > cnt - MIN_int32_T)) {
      b_ind = MIN_int32_T;
    } else {
      b_ind = cnt - N;
    }

    if (b_ind == 20) {
      if (top > 2147483646) {
        top = MAX_int32_T;
      } else {
        top++;
      }

      if (top > 20) {
        top = 1;
      }

      i--;
    }
  }

  if ((i < 0) && (top < MIN_int32_T - i)) {
    qY = MIN_int32_T;
  } else if ((i > 0) && (top > MAX_int32_T - i)) {
    qY = MAX_int32_T;
  } else {
    qY = i + top;
  }

  if (qY < -2147483647) {
    placement = MIN_int32_T;
  } else {
    placement = qY - 1;
  }

  if (placement >= 20) {
    placement -= 20;
  }

  memset(&localB->ind_vect[0], 0, 20U * sizeof(int32_T));
  N = i;
  if (i > 0) {
    qY = i - 1;
    if (top < -2147483647) {
      qY_0 = MIN_int32_T;
    } else {
      qY_0 = top - 1;
    }

    for (b_ind = qY; b_ind >= 0; b_ind--) {
      if ((qY_0 < 0) && (b_ind < MIN_int32_T - qY_0)) {
        indVal = MIN_int32_T;
      } else if ((qY_0 > 0) && (b_ind > MAX_int32_T - qY_0)) {
        indVal = MAX_int32_T;
      } else {
        indVal = qY_0 + b_ind;
      }

      if (indVal >= 20) {
        indVal -= 20;
      }

      localB->ind_vect[(i - b_ind) - 1] = indVal + 1;
    }

    qY = 1;
    exitg1 = false;
    while ((!exitg1) && (qY - 1 <= i - 1)) {
      b_ind = localB->ind_vect[qY - 1] - 1;
      if (rtu_0 > localB->buf[b_ind]) {
        exitg1 = true;
      } else {
        placement = b_ind;
        if (N < -2147483647) {
          N = MIN_int32_T;
        } else {
          N--;
        }

        qY++;
      }
    }
  }

  localB->buf[placement] = rtu_0;
  localB->bufIdx[placement] = cnt;
  if (cnt > 2147483646) {
    cnt = MAX_int32_T;
  } else {
    cnt++;
  }

  if (cnt > 1000000) {
    cnt -= 1000000;
    for (b_ind = 0; b_ind < 20; b_ind++) {
      i = localB->bufIdx[b_ind];
      if (i < -2146483648) {
        localB->bufIdx[b_ind] = MIN_int32_T;
      } else {
        localB->bufIdx[b_ind] = i - 1000000;
      }
    }
  }

  for (i = 0; i < 20; i++) {
    obj->pBuffer[i] = localB->buf[i];
  }

  for (i = 0; i < 20; i++) {
    obj->pBufferIdx[i] = localB->bufIdx[i];
  }

  if (N > 2147483646) {
    obj->pNumElements = MAX_int32_T;
  } else {
    obj->pNumElements = N + 1;
  }

  obj->pCount = cnt;
  obj->pTop = top;

  /* MATLABSystem: '<S16>/Moving Minimum' */
  localB->MovingMinimum = localB->buf[top - 1];
}

/* Termination for atomic system: */
void MicroMouseTe_MovingMinimum_Term(DW_MovingMinimum_MicroMouseTe_T *localDW)
{
  g_dsp_internal_SlidingWindo_g_T *obj;

  /* Terminate for MATLABSystem: '<S16>/Moving Minimum' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      localDW->obj.NumChannels = -1;
      obj = localDW->obj.pStat;
      if (obj->isInitialized == 1) {
        obj->isInitialized = 2;
      }
    }
  }

  /* End of Terminate for MATLABSystem: '<S16>/Moving Minimum' */
}

/* System initialize for atomic system: */
void MicroMouseT_MovingMaximum1_Init(DW_MovingMaximum1_MicroMouseT_T *localDW)
{
  g_dsp_internal_SlidingWindo_k_T *obj;
  int32_T i;

  /* Start for MATLABSystem: '<S17>/Moving Maximum1' */
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  localDW->obj.isInitialized = 1;
  localDW->obj.NumChannels = 1;
  localDW->obj._pobj0.isInitialized = 0;
  localDW->obj.pStat = &localDW->obj._pobj0;
  obj = localDW->obj.pStat;
  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  obj->isSetupComplete = true;
  localDW->obj.isSetupComplete = true;

  /* InitializeConditions for MATLABSystem: '<S17>/Moving Maximum1' */
  obj = localDW->obj.pStat;
  if (obj->isInitialized == 1) {
    for (i = 0; i < 5; i++) {
      obj->pBuffer[i] = 0.0;
    }

    for (i = 0; i < 5; i++) {
      obj->pBufferIdx[i] = 0;
    }

    obj->pNumElements = 0;
    obj->pCount = 1;
    obj->pTop = 1;
  }

  /* End of InitializeConditions for MATLABSystem: '<S17>/Moving Maximum1' */
}

/* Output and update for atomic system: */
void MicroMouseTempla_MovingMaximum1(real_T rtu_0,
  B_MovingMaximum1_MicroMouseTe_T *localB, DW_MovingMaximum1_MicroMouseT_T
  *localDW)
{
  g_dsp_internal_SlidingWindo_k_T *obj;
  int32_T ind_vect[5];
  int32_T N;
  int32_T b_ind;
  int32_T cnt;
  int32_T i;
  int32_T indVal;
  int32_T placement;
  int32_T qY;
  int32_T qY_0;
  int32_T top;
  boolean_T exitg1;

  /* MATLABSystem: '<S17>/Moving Maximum1' */
  obj = localDW->obj.pStat;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    obj->isSetupComplete = true;
    for (i = 0; i < 5; i++) {
      obj->pBuffer[i] = 0.0;
    }

    for (i = 0; i < 5; i++) {
      obj->pBufferIdx[i] = 0;
    }

    obj->pNumElements = 0;
    obj->pCount = 1;
    obj->pTop = 1;
  }

  for (i = 0; i < 5; i++) {
    localB->buf[i] = obj->pBuffer[i];
  }

  for (i = 0; i < 5; i++) {
    localB->bufIdx[i] = obj->pBufferIdx[i];
  }

  i = obj->pNumElements;
  cnt = obj->pCount;
  top = obj->pTop;
  if (i > 0) {
    N = localB->bufIdx[top - 1];
    if ((cnt >= 0) && (N < cnt - MAX_int32_T)) {
      b_ind = MAX_int32_T;
    } else if ((cnt < 0) && (N > cnt - MIN_int32_T)) {
      b_ind = MIN_int32_T;
    } else {
      b_ind = cnt - N;
    }

    if (b_ind == 5) {
      if (top > 2147483646) {
        top = MAX_int32_T;
      } else {
        top++;
      }

      if (top > 5) {
        top = 1;
      }

      i--;
    }
  }

  if ((i < 0) && (top < MIN_int32_T - i)) {
    qY = MIN_int32_T;
  } else if ((i > 0) && (top > MAX_int32_T - i)) {
    qY = MAX_int32_T;
  } else {
    qY = i + top;
  }

  if (qY < -2147483647) {
    placement = MIN_int32_T;
  } else {
    placement = qY - 1;
  }

  if (placement >= 5) {
    placement -= 5;
  }

  for (b_ind = 0; b_ind < 5; b_ind++) {
    ind_vect[b_ind] = 0;
  }

  N = i;
  if (i > 0) {
    qY = i - 1;
    if (top < -2147483647) {
      qY_0 = MIN_int32_T;
    } else {
      qY_0 = top - 1;
    }

    for (b_ind = qY; b_ind >= 0; b_ind--) {
      if ((qY_0 < 0) && (b_ind < MIN_int32_T - qY_0)) {
        indVal = MIN_int32_T;
      } else if ((qY_0 > 0) && (b_ind > MAX_int32_T - qY_0)) {
        indVal = MAX_int32_T;
      } else {
        indVal = qY_0 + b_ind;
      }

      if (indVal >= 5) {
        indVal -= 5;
      }

      ind_vect[(i - b_ind) - 1] = indVal + 1;
    }

    qY = 1;
    exitg1 = false;
    while ((!exitg1) && (qY - 1 <= i - 1)) {
      b_ind = ind_vect[qY - 1] - 1;
      if (rtu_0 < localB->buf[b_ind]) {
        exitg1 = true;
      } else {
        placement = b_ind;
        if (N < -2147483647) {
          N = MIN_int32_T;
        } else {
          N--;
        }

        qY++;
      }
    }
  }

  localB->buf[placement] = rtu_0;
  localB->bufIdx[placement] = cnt;
  if (cnt > 2147483646) {
    cnt = MAX_int32_T;
  } else {
    cnt++;
  }

  if (cnt > 1000000) {
    cnt -= 1000000;
    for (b_ind = 0; b_ind < 5; b_ind++) {
      i = localB->bufIdx[b_ind];
      if (i < -2146483648) {
        localB->bufIdx[b_ind] = MIN_int32_T;
      } else {
        localB->bufIdx[b_ind] = i - 1000000;
      }
    }
  }

  for (i = 0; i < 5; i++) {
    obj->pBuffer[i] = localB->buf[i];
  }

  for (i = 0; i < 5; i++) {
    obj->pBufferIdx[i] = localB->bufIdx[i];
  }

  if (N > 2147483646) {
    obj->pNumElements = MAX_int32_T;
  } else {
    obj->pNumElements = N + 1;
  }

  obj->pCount = cnt;
  obj->pTop = top;

  /* MATLABSystem: '<S17>/Moving Maximum1' */
  localB->MovingMaximum1 = localB->buf[top - 1];
}

/* Termination for atomic system: */
void MicroMouseT_MovingMaximum1_Term(DW_MovingMaximum1_MicroMouseT_T *localDW)
{
  g_dsp_internal_SlidingWindo_k_T *obj;

  /* Terminate for MATLABSystem: '<S17>/Moving Maximum1' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      localDW->obj.NumChannels = -1;
      obj = localDW->obj.pStat;
      if (obj->isInitialized == 1) {
        obj->isInitialized = 2;
      }
    }
  }

  /* End of Terminate for MATLABSystem: '<S17>/Moving Maximum1' */
}

/* System initialize for atomic system: */
void MicroMouseT_MovingMinimum2_Init(DW_MovingMinimum2_MicroMouseT_T *localDW)
{
  g_dsp_internal_SlidingWind_gt_T *obj;
  int32_T i;

  /* Start for MATLABSystem: '<S17>/Moving Minimum2' */
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  localDW->obj.isInitialized = 1;
  localDW->obj.NumChannels = 1;
  localDW->obj._pobj0.isInitialized = 0;
  localDW->obj.pStat = &localDW->obj._pobj0;
  obj = localDW->obj.pStat;
  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  obj->isSetupComplete = true;
  localDW->obj.isSetupComplete = true;

  /* InitializeConditions for MATLABSystem: '<S17>/Moving Minimum2' */
  obj = localDW->obj.pStat;
  if (obj->isInitialized == 1) {
    for (i = 0; i < 15; i++) {
      obj->pBuffer[i] = 0.0;
    }

    for (i = 0; i < 15; i++) {
      obj->pBufferIdx[i] = 0;
    }

    obj->pNumElements = 0;
    obj->pCount = 1;
    obj->pTop = 1;
  }

  /* End of InitializeConditions for MATLABSystem: '<S17>/Moving Minimum2' */
}

/* Output and update for atomic system: */
void MicroMouseTempla_MovingMinimum2(real_T rtu_0,
  B_MovingMinimum2_MicroMouseTe_T *localB, DW_MovingMinimum2_MicroMouseT_T
  *localDW)
{
  g_dsp_internal_SlidingWind_gt_T *obj;
  int32_T N;
  int32_T b_ind;
  int32_T cnt;
  int32_T i;
  int32_T indVal;
  int32_T placement;
  int32_T qY;
  int32_T qY_0;
  int32_T top;
  boolean_T exitg1;

  /* MATLABSystem: '<S17>/Moving Minimum2' */
  obj = localDW->obj.pStat;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    obj->isSetupComplete = true;
    for (i = 0; i < 15; i++) {
      obj->pBuffer[i] = 0.0;
    }

    for (i = 0; i < 15; i++) {
      obj->pBufferIdx[i] = 0;
    }

    obj->pNumElements = 0;
    obj->pCount = 1;
    obj->pTop = 1;
  }

  for (i = 0; i < 15; i++) {
    localB->buf[i] = obj->pBuffer[i];
  }

  for (i = 0; i < 15; i++) {
    localB->bufIdx[i] = obj->pBufferIdx[i];
  }

  i = obj->pNumElements;
  cnt = obj->pCount;
  top = obj->pTop;
  if (i > 0) {
    N = localB->bufIdx[top - 1];
    if ((cnt >= 0) && (N < cnt - MAX_int32_T)) {
      b_ind = MAX_int32_T;
    } else if ((cnt < 0) && (N > cnt - MIN_int32_T)) {
      b_ind = MIN_int32_T;
    } else {
      b_ind = cnt - N;
    }

    if (b_ind == 15) {
      if (top > 2147483646) {
        top = MAX_int32_T;
      } else {
        top++;
      }

      if (top > 15) {
        top = 1;
      }

      i--;
    }
  }

  if ((i < 0) && (top < MIN_int32_T - i)) {
    qY = MIN_int32_T;
  } else if ((i > 0) && (top > MAX_int32_T - i)) {
    qY = MAX_int32_T;
  } else {
    qY = i + top;
  }

  if (qY < -2147483647) {
    placement = MIN_int32_T;
  } else {
    placement = qY - 1;
  }

  if (placement >= 15) {
    placement -= 15;
  }

  for (b_ind = 0; b_ind < 15; b_ind++) {
    localB->ind_vect[b_ind] = 0;
  }

  N = i;
  if (i > 0) {
    qY = i - 1;
    if (top < -2147483647) {
      qY_0 = MIN_int32_T;
    } else {
      qY_0 = top - 1;
    }

    for (b_ind = qY; b_ind >= 0; b_ind--) {
      if ((qY_0 < 0) && (b_ind < MIN_int32_T - qY_0)) {
        indVal = MIN_int32_T;
      } else if ((qY_0 > 0) && (b_ind > MAX_int32_T - qY_0)) {
        indVal = MAX_int32_T;
      } else {
        indVal = qY_0 + b_ind;
      }

      if (indVal >= 15) {
        indVal -= 15;
      }

      localB->ind_vect[(i - b_ind) - 1] = indVal + 1;
    }

    qY = 1;
    exitg1 = false;
    while ((!exitg1) && (qY - 1 <= i - 1)) {
      b_ind = localB->ind_vect[qY - 1] - 1;
      if (rtu_0 > localB->buf[b_ind]) {
        exitg1 = true;
      } else {
        placement = b_ind;
        if (N < -2147483647) {
          N = MIN_int32_T;
        } else {
          N--;
        }

        qY++;
      }
    }
  }

  localB->buf[placement] = rtu_0;
  localB->bufIdx[placement] = cnt;
  if (cnt > 2147483646) {
    cnt = MAX_int32_T;
  } else {
    cnt++;
  }

  if (cnt > 1000000) {
    cnt -= 1000000;
    for (b_ind = 0; b_ind < 15; b_ind++) {
      i = localB->bufIdx[b_ind];
      if (i < -2146483648) {
        localB->bufIdx[b_ind] = MIN_int32_T;
      } else {
        localB->bufIdx[b_ind] = i - 1000000;
      }
    }
  }

  for (i = 0; i < 15; i++) {
    obj->pBuffer[i] = localB->buf[i];
  }

  for (i = 0; i < 15; i++) {
    obj->pBufferIdx[i] = localB->bufIdx[i];
  }

  if (N > 2147483646) {
    obj->pNumElements = MAX_int32_T;
  } else {
    obj->pNumElements = N + 1;
  }

  obj->pCount = cnt;
  obj->pTop = top;

  /* MATLABSystem: '<S17>/Moving Minimum2' */
  localB->MovingMinimum2 = localB->buf[top - 1];
}

/* Termination for atomic system: */
void MicroMouseT_MovingMinimum2_Term(DW_MovingMinimum2_MicroMouseT_T *localDW)
{
  g_dsp_internal_SlidingWind_gt_T *obj;

  /* Terminate for MATLABSystem: '<S17>/Moving Minimum2' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      localDW->obj.NumChannels = -1;
      obj = localDW->obj.pStat;
      if (obj->isInitialized == 1) {
        obj->isInitialized = 2;
      }
    }
  }

  /* End of Terminate for MATLABSystem: '<S17>/Moving Minimum2' */
}

/* System initialize for atomic system: */
void MicroMouse_MovingMaximum_i_Init(DW_MovingMaximum_MicroMouse_p_T *localDW)
{
  g_dsp_internal_SlidingWindo_n_T *obj;
  int32_T i;

  /* Start for MATLABSystem: '<S29>/Moving Maximum' */
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  localDW->obj.isInitialized = 1;
  localDW->obj.NumChannels = 1;
  localDW->obj._pobj0.isInitialized = 0;
  localDW->obj.pStat = &localDW->obj._pobj0;
  obj = localDW->obj.pStat;
  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  obj->isSetupComplete = true;
  localDW->obj.isSetupComplete = true;

  /* InitializeConditions for MATLABSystem: '<S29>/Moving Maximum' */
  obj = localDW->obj.pStat;
  if (obj->isInitialized == 1) {
    for (i = 0; i < 15; i++) {
      obj->pBuffer[i] = 0.0;
    }

    for (i = 0; i < 15; i++) {
      obj->pBufferIdx[i] = 0;
    }

    obj->pNumElements = 0;
    obj->pCount = 1;
    obj->pTop = 1;
  }

  /* End of InitializeConditions for MATLABSystem: '<S29>/Moving Maximum' */
}

/* Output and update for atomic system: */
void MicroMouseTempl_MovingMaximum_j(real_T rtu_0,
  B_MovingMaximum_MicroMouseT_o_T *localB, DW_MovingMaximum_MicroMouse_p_T
  *localDW)
{
  g_dsp_internal_SlidingWindo_n_T *obj;
  int32_T N;
  int32_T b_ind;
  int32_T cnt;
  int32_T i;
  int32_T indVal;
  int32_T placement;
  int32_T qY;
  int32_T qY_0;
  int32_T top;
  boolean_T exitg1;

  /* MATLABSystem: '<S29>/Moving Maximum' */
  obj = localDW->obj.pStat;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    obj->isSetupComplete = true;
    for (i = 0; i < 15; i++) {
      obj->pBuffer[i] = 0.0;
    }

    for (i = 0; i < 15; i++) {
      obj->pBufferIdx[i] = 0;
    }

    obj->pNumElements = 0;
    obj->pCount = 1;
    obj->pTop = 1;
  }

  for (i = 0; i < 15; i++) {
    localB->buf[i] = obj->pBuffer[i];
  }

  for (i = 0; i < 15; i++) {
    localB->bufIdx[i] = obj->pBufferIdx[i];
  }

  i = obj->pNumElements;
  cnt = obj->pCount;
  top = obj->pTop;
  if (i > 0) {
    N = localB->bufIdx[top - 1];
    if ((cnt >= 0) && (N < cnt - MAX_int32_T)) {
      b_ind = MAX_int32_T;
    } else if ((cnt < 0) && (N > cnt - MIN_int32_T)) {
      b_ind = MIN_int32_T;
    } else {
      b_ind = cnt - N;
    }

    if (b_ind == 15) {
      if (top > 2147483646) {
        top = MAX_int32_T;
      } else {
        top++;
      }

      if (top > 15) {
        top = 1;
      }

      i--;
    }
  }

  if ((i < 0) && (top < MIN_int32_T - i)) {
    qY = MIN_int32_T;
  } else if ((i > 0) && (top > MAX_int32_T - i)) {
    qY = MAX_int32_T;
  } else {
    qY = i + top;
  }

  if (qY < -2147483647) {
    placement = MIN_int32_T;
  } else {
    placement = qY - 1;
  }

  if (placement >= 15) {
    placement -= 15;
  }

  for (b_ind = 0; b_ind < 15; b_ind++) {
    localB->ind_vect[b_ind] = 0;
  }

  N = i;
  if (i > 0) {
    qY = i - 1;
    if (top < -2147483647) {
      qY_0 = MIN_int32_T;
    } else {
      qY_0 = top - 1;
    }

    for (b_ind = qY; b_ind >= 0; b_ind--) {
      if ((qY_0 < 0) && (b_ind < MIN_int32_T - qY_0)) {
        indVal = MIN_int32_T;
      } else if ((qY_0 > 0) && (b_ind > MAX_int32_T - qY_0)) {
        indVal = MAX_int32_T;
      } else {
        indVal = qY_0 + b_ind;
      }

      if (indVal >= 15) {
        indVal -= 15;
      }

      localB->ind_vect[(i - b_ind) - 1] = indVal + 1;
    }

    qY = 1;
    exitg1 = false;
    while ((!exitg1) && (qY - 1 <= i - 1)) {
      b_ind = localB->ind_vect[qY - 1] - 1;
      if (rtu_0 < localB->buf[b_ind]) {
        exitg1 = true;
      } else {
        placement = b_ind;
        if (N < -2147483647) {
          N = MIN_int32_T;
        } else {
          N--;
        }

        qY++;
      }
    }
  }

  localB->buf[placement] = rtu_0;
  localB->bufIdx[placement] = cnt;
  if (cnt > 2147483646) {
    cnt = MAX_int32_T;
  } else {
    cnt++;
  }

  if (cnt > 1000000) {
    cnt -= 1000000;
    for (b_ind = 0; b_ind < 15; b_ind++) {
      i = localB->bufIdx[b_ind];
      if (i < -2146483648) {
        localB->bufIdx[b_ind] = MIN_int32_T;
      } else {
        localB->bufIdx[b_ind] = i - 1000000;
      }
    }
  }

  for (i = 0; i < 15; i++) {
    obj->pBuffer[i] = localB->buf[i];
  }

  for (i = 0; i < 15; i++) {
    obj->pBufferIdx[i] = localB->bufIdx[i];
  }

  if (N > 2147483646) {
    obj->pNumElements = MAX_int32_T;
  } else {
    obj->pNumElements = N + 1;
  }

  obj->pCount = cnt;
  obj->pTop = top;

  /* MATLABSystem: '<S29>/Moving Maximum' */
  localB->MovingMaximum = localB->buf[top - 1];
}

/* Termination for atomic system: */
void MicroMouse_MovingMaximum_o_Term(DW_MovingMaximum_MicroMouse_p_T *localDW)
{
  g_dsp_internal_SlidingWindo_n_T *obj;

  /* Terminate for MATLABSystem: '<S29>/Moving Maximum' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      localDW->obj.NumChannels = -1;
      obj = localDW->obj.pStat;
      if (obj->isInitialized == 1) {
        obj->isInitialized = 2;
      }
    }
  }

  /* End of Terminate for MATLABSystem: '<S29>/Moving Maximum' */
}

/* System initialize for atomic system: */
void MicroMouse_MovingMinimum_f_Init(DW_MovingMinimum_MicroMouse_p_T *localDW)
{
  g_dsp_internal_SlidingWind_gt_T *obj;
  int32_T i;

  /* Start for MATLABSystem: '<S29>/Moving Minimum' */
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  localDW->obj.isInitialized = 1;
  localDW->obj.NumChannels = 1;
  localDW->obj._pobj0.isInitialized = 0;
  localDW->obj.pStat = &localDW->obj._pobj0;
  obj = localDW->obj.pStat;
  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  obj->isSetupComplete = true;
  localDW->obj.isSetupComplete = true;

  /* InitializeConditions for MATLABSystem: '<S29>/Moving Minimum' */
  obj = localDW->obj.pStat;
  if (obj->isInitialized == 1) {
    for (i = 0; i < 15; i++) {
      obj->pBuffer[i] = 0.0;
    }

    for (i = 0; i < 15; i++) {
      obj->pBufferIdx[i] = 0;
    }

    obj->pNumElements = 0;
    obj->pCount = 1;
    obj->pTop = 1;
  }

  /* End of InitializeConditions for MATLABSystem: '<S29>/Moving Minimum' */
}

/* Output and update for atomic system: */
void MicroMouseTempl_MovingMinimum_j(real_T rtu_0,
  B_MovingMinimum_MicroMouseT_o_T *localB, DW_MovingMinimum_MicroMouse_p_T
  *localDW)
{
  g_dsp_internal_SlidingWind_gt_T *obj;
  int32_T N;
  int32_T b_ind;
  int32_T cnt;
  int32_T i;
  int32_T indVal;
  int32_T placement;
  int32_T qY;
  int32_T qY_0;
  int32_T top;
  boolean_T exitg1;

  /* MATLABSystem: '<S29>/Moving Minimum' */
  obj = localDW->obj.pStat;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    obj->isSetupComplete = true;
    for (i = 0; i < 15; i++) {
      obj->pBuffer[i] = 0.0;
    }

    for (i = 0; i < 15; i++) {
      obj->pBufferIdx[i] = 0;
    }

    obj->pNumElements = 0;
    obj->pCount = 1;
    obj->pTop = 1;
  }

  for (i = 0; i < 15; i++) {
    localB->buf[i] = obj->pBuffer[i];
  }

  for (i = 0; i < 15; i++) {
    localB->bufIdx[i] = obj->pBufferIdx[i];
  }

  i = obj->pNumElements;
  cnt = obj->pCount;
  top = obj->pTop;
  if (i > 0) {
    N = localB->bufIdx[top - 1];
    if ((cnt >= 0) && (N < cnt - MAX_int32_T)) {
      b_ind = MAX_int32_T;
    } else if ((cnt < 0) && (N > cnt - MIN_int32_T)) {
      b_ind = MIN_int32_T;
    } else {
      b_ind = cnt - N;
    }

    if (b_ind == 15) {
      if (top > 2147483646) {
        top = MAX_int32_T;
      } else {
        top++;
      }

      if (top > 15) {
        top = 1;
      }

      i--;
    }
  }

  if ((i < 0) && (top < MIN_int32_T - i)) {
    qY = MIN_int32_T;
  } else if ((i > 0) && (top > MAX_int32_T - i)) {
    qY = MAX_int32_T;
  } else {
    qY = i + top;
  }

  if (qY < -2147483647) {
    placement = MIN_int32_T;
  } else {
    placement = qY - 1;
  }

  if (placement >= 15) {
    placement -= 15;
  }

  for (b_ind = 0; b_ind < 15; b_ind++) {
    localB->ind_vect[b_ind] = 0;
  }

  N = i;
  if (i > 0) {
    qY = i - 1;
    if (top < -2147483647) {
      qY_0 = MIN_int32_T;
    } else {
      qY_0 = top - 1;
    }

    for (b_ind = qY; b_ind >= 0; b_ind--) {
      if ((qY_0 < 0) && (b_ind < MIN_int32_T - qY_0)) {
        indVal = MIN_int32_T;
      } else if ((qY_0 > 0) && (b_ind > MAX_int32_T - qY_0)) {
        indVal = MAX_int32_T;
      } else {
        indVal = qY_0 + b_ind;
      }

      if (indVal >= 15) {
        indVal -= 15;
      }

      localB->ind_vect[(i - b_ind) - 1] = indVal + 1;
    }

    qY = 1;
    exitg1 = false;
    while ((!exitg1) && (qY - 1 <= i - 1)) {
      b_ind = localB->ind_vect[qY - 1] - 1;
      if (rtu_0 > localB->buf[b_ind]) {
        exitg1 = true;
      } else {
        placement = b_ind;
        if (N < -2147483647) {
          N = MIN_int32_T;
        } else {
          N--;
        }

        qY++;
      }
    }
  }

  localB->buf[placement] = rtu_0;
  localB->bufIdx[placement] = cnt;
  if (cnt > 2147483646) {
    cnt = MAX_int32_T;
  } else {
    cnt++;
  }

  if (cnt > 1000000) {
    cnt -= 1000000;
    for (b_ind = 0; b_ind < 15; b_ind++) {
      i = localB->bufIdx[b_ind];
      if (i < -2146483648) {
        localB->bufIdx[b_ind] = MIN_int32_T;
      } else {
        localB->bufIdx[b_ind] = i - 1000000;
      }
    }
  }

  for (i = 0; i < 15; i++) {
    obj->pBuffer[i] = localB->buf[i];
  }

  for (i = 0; i < 15; i++) {
    obj->pBufferIdx[i] = localB->bufIdx[i];
  }

  if (N > 2147483646) {
    obj->pNumElements = MAX_int32_T;
  } else {
    obj->pNumElements = N + 1;
  }

  obj->pCount = cnt;
  obj->pTop = top;

  /* MATLABSystem: '<S29>/Moving Minimum' */
  localB->MovingMinimum = localB->buf[top - 1];
}

/* Termination for atomic system: */
void MicroMouse_MovingMinimum_a_Term(DW_MovingMinimum_MicroMouse_p_T *localDW)
{
  g_dsp_internal_SlidingWind_gt_T *obj;

  /* Terminate for MATLABSystem: '<S29>/Moving Minimum' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      localDW->obj.NumChannels = -1;
      obj = localDW->obj.pStat;
      if (obj->isInitialized == 1) {
        obj->isInitialized = 2;
      }
    }
  }

  /* End of Terminate for MATLABSystem: '<S29>/Moving Minimum' */
}

/* System initialize for atomic system: */
void MicroMouse_MovingMaximum_h_Init(DW_MovingMaximum_MicroMous_pl_T *localDW)
{
  g_dsp_internal_SlidingWindo_k_T *obj;
  int32_T i;

  /* Start for MATLABSystem: '<S31>/Moving Maximum' */
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  localDW->obj.isInitialized = 1;
  localDW->obj.NumChannels = 1;
  localDW->obj._pobj0.isInitialized = 0;
  localDW->obj.pStat = &localDW->obj._pobj0;
  obj = localDW->obj.pStat;
  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  obj->isSetupComplete = true;
  localDW->obj.isSetupComplete = true;

  /* InitializeConditions for MATLABSystem: '<S31>/Moving Maximum' */
  obj = localDW->obj.pStat;
  if (obj->isInitialized == 1) {
    for (i = 0; i < 5; i++) {
      obj->pBuffer[i] = 0.0;
    }

    for (i = 0; i < 5; i++) {
      obj->pBufferIdx[i] = 0;
    }

    obj->pNumElements = 0;
    obj->pCount = 1;
    obj->pTop = 1;
  }

  /* End of InitializeConditions for MATLABSystem: '<S31>/Moving Maximum' */
}

/* Output and update for atomic system: */
void MicroMouseTemp_MovingMaximum_jn(real_T rtu_0,
  B_MovingMaximum_MicroMouse_oj_T *localB, DW_MovingMaximum_MicroMous_pl_T
  *localDW)
{
  g_dsp_internal_SlidingWindo_k_T *obj;
  int32_T ind_vect[5];
  int32_T N;
  int32_T b_ind;
  int32_T cnt;
  int32_T i;
  int32_T indVal;
  int32_T placement;
  int32_T qY;
  int32_T qY_0;
  int32_T top;
  boolean_T exitg1;

  /* MATLABSystem: '<S31>/Moving Maximum' */
  obj = localDW->obj.pStat;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    obj->isSetupComplete = true;
    for (i = 0; i < 5; i++) {
      obj->pBuffer[i] = 0.0;
    }

    for (i = 0; i < 5; i++) {
      obj->pBufferIdx[i] = 0;
    }

    obj->pNumElements = 0;
    obj->pCount = 1;
    obj->pTop = 1;
  }

  for (i = 0; i < 5; i++) {
    localB->buf[i] = obj->pBuffer[i];
  }

  for (i = 0; i < 5; i++) {
    localB->bufIdx[i] = obj->pBufferIdx[i];
  }

  i = obj->pNumElements;
  cnt = obj->pCount;
  top = obj->pTop;
  if (i > 0) {
    N = localB->bufIdx[top - 1];
    if ((cnt >= 0) && (N < cnt - MAX_int32_T)) {
      b_ind = MAX_int32_T;
    } else if ((cnt < 0) && (N > cnt - MIN_int32_T)) {
      b_ind = MIN_int32_T;
    } else {
      b_ind = cnt - N;
    }

    if (b_ind == 5) {
      if (top > 2147483646) {
        top = MAX_int32_T;
      } else {
        top++;
      }

      if (top > 5) {
        top = 1;
      }

      i--;
    }
  }

  if ((i < 0) && (top < MIN_int32_T - i)) {
    qY = MIN_int32_T;
  } else if ((i > 0) && (top > MAX_int32_T - i)) {
    qY = MAX_int32_T;
  } else {
    qY = i + top;
  }

  if (qY < -2147483647) {
    placement = MIN_int32_T;
  } else {
    placement = qY - 1;
  }

  if (placement >= 5) {
    placement -= 5;
  }

  for (b_ind = 0; b_ind < 5; b_ind++) {
    ind_vect[b_ind] = 0;
  }

  N = i;
  if (i > 0) {
    qY = i - 1;
    if (top < -2147483647) {
      qY_0 = MIN_int32_T;
    } else {
      qY_0 = top - 1;
    }

    for (b_ind = qY; b_ind >= 0; b_ind--) {
      if ((qY_0 < 0) && (b_ind < MIN_int32_T - qY_0)) {
        indVal = MIN_int32_T;
      } else if ((qY_0 > 0) && (b_ind > MAX_int32_T - qY_0)) {
        indVal = MAX_int32_T;
      } else {
        indVal = qY_0 + b_ind;
      }

      if (indVal >= 5) {
        indVal -= 5;
      }

      ind_vect[(i - b_ind) - 1] = indVal + 1;
    }

    qY = 1;
    exitg1 = false;
    while ((!exitg1) && (qY - 1 <= i - 1)) {
      b_ind = ind_vect[qY - 1] - 1;
      if (rtu_0 < localB->buf[b_ind]) {
        exitg1 = true;
      } else {
        placement = b_ind;
        if (N < -2147483647) {
          N = MIN_int32_T;
        } else {
          N--;
        }

        qY++;
      }
    }
  }

  localB->buf[placement] = rtu_0;
  localB->bufIdx[placement] = cnt;
  if (cnt > 2147483646) {
    cnt = MAX_int32_T;
  } else {
    cnt++;
  }

  if (cnt > 1000000) {
    cnt -= 1000000;
    for (b_ind = 0; b_ind < 5; b_ind++) {
      i = localB->bufIdx[b_ind];
      if (i < -2146483648) {
        localB->bufIdx[b_ind] = MIN_int32_T;
      } else {
        localB->bufIdx[b_ind] = i - 1000000;
      }
    }
  }

  for (i = 0; i < 5; i++) {
    obj->pBuffer[i] = localB->buf[i];
  }

  for (i = 0; i < 5; i++) {
    obj->pBufferIdx[i] = localB->bufIdx[i];
  }

  if (N > 2147483646) {
    obj->pNumElements = MAX_int32_T;
  } else {
    obj->pNumElements = N + 1;
  }

  obj->pCount = cnt;
  obj->pTop = top;

  /* MATLABSystem: '<S31>/Moving Maximum' */
  localB->MovingMaximum = localB->buf[top - 1];
}

/* Termination for atomic system: */
void MicroMouse_MovingMaximum_g_Term(DW_MovingMaximum_MicroMous_pl_T *localDW)
{
  g_dsp_internal_SlidingWindo_k_T *obj;

  /* Terminate for MATLABSystem: '<S31>/Moving Maximum' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      localDW->obj.NumChannels = -1;
      obj = localDW->obj.pStat;
      if (obj->isInitialized == 1) {
        obj->isInitialized = 2;
      }
    }
  }

  /* End of Terminate for MATLABSystem: '<S31>/Moving Maximum' */
}

static void MicroMouseTemp_SystemCore_setup(stm32cube_blocks_AnalogInput__T *obj)
{
  uint16_T module;
  uint16_T triggerType;
  uint32_T noConv;
  ADC_Type_T adcStructLoc;
  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  adcStructLoc.dmastream = LL_DMA_CHANNEL_2;
  adcStructLoc.dmaPeripheralPtr = DMA1;
  adcStructLoc.InternalBufferPtr = (void*)(&obj->ADCInternalBuffer[0]);
  adcStructLoc.peripheralPtr = ADC2;
  adcStructLoc.InjectedNoOfConversion = 0U;
  adcStructLoc.InternalBufferSize = 9U;
  module = ADC_DMA_INTERRUPT_MODE;
  triggerType = ADC_TRIGGER_AND_READ;
  noConv = LL_ADC_REG_SEQ_SCAN_ENABLE_9RANKS;
  adcStructLoc.RegularNoOfConversion = 9U;
  obj->ADCHandle = ADC_Handle_Init(&adcStructLoc, module, 1, triggerType, noConv);
  enableADCAutomaticCalibrationOffset(obj->ADCHandle, 2);
  enableADC(obj->ADCHandle);
  startADCConversionForExternalTrigger(obj->ADCHandle, 1);
  obj->isSetupComplete = true;
}

/* Model step function */
void MicroMouseTemplate_step(void)
{
  /* MATLABSystem: '<S15>/Analog to Digital Converter' */
  MicroMouseTemplate_B.triggerType = ADC_TRIGGER_AND_READ;
  regularReadADCDMA(MicroMouseTemplate_DW.obj.ADCHandle,
                    MicroMouseTemplate_B.triggerType, &ADC1s[0]);

  /* MATLABSystem: '<S68>/Digital Port Read' */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  MicroMouseTemplate_B.pinReadLoc = LL_GPIO_ReadInputPort
    (MicroMouseTemplate_B.portNameLoc);

  /* MATLABSystem: '<S70>/Digital Port Read' */
  MicroMouseTemplate_B.portNameLoc = GPIOB;
  MicroMouseTemplate_B.pinReadLoc_m = LL_GPIO_ReadInputPort
    (MicroMouseTemplate_B.portNameLoc);
  for (MicroMouseTemplate_B.i = 0; MicroMouseTemplate_B.i < 8;
       MicroMouseTemplate_B.i++) {
    /* DataTypeConversion: '<Root>/Cast To Double1' incorporates:
     *  DataStoreRead: '<S1>/Data Store Read'
     *  Gain: '<S1>/Gain1'
     */
    MicroMouseTemplate_B.CastToDouble1[MicroMouseTemplate_B.i] = (real_T)
      ((uint32_T)MicroMouseTemplate_P.Gain1_Gain * ADC_H[MicroMouseTemplate_B.i])
      * 1.4901161193847656E-8;

    /* DataTypeConversion: '<Root>/Cast To Double2' incorporates:
     *  DataStoreRead: '<S1>/Data Store Read1'
     *  Gain: '<S1>/Gain2'
     */
    MicroMouseTemplate_B.CastToDouble2[MicroMouseTemplate_B.i] = (real_T)
      ((uint32_T)MicroMouseTemplate_P.Gain2_Gain * ADC_L[MicroMouseTemplate_B.i])
      * 1.4901161193847656E-8;
  }

  if (MicroMouseTemplate_M->Timing.TaskCounters.TID[1] == 0) {
    /* DiscretePulseGenerator: '<Root>/pulse 1' */
    MicroMouseTemplate_B.MOT_RS = (MicroMouseTemplate_DW.clockTickCounter <
      MicroMouseTemplate_P.pulse1_Duty) &&
      (MicroMouseTemplate_DW.clockTickCounter >= 0) ?
      MicroMouseTemplate_P.pulse1_Amp : 0.0;

    /* DiscretePulseGenerator: '<Root>/pulse 1' */
    if (MicroMouseTemplate_DW.clockTickCounter >=
        MicroMouseTemplate_P.pulse1_Period - 1.0) {
      MicroMouseTemplate_DW.clockTickCounter = 0;
    } else {
      MicroMouseTemplate_DW.clockTickCounter++;
    }
  }

  /* DiscretePulseGenerator: '<Root>/pulse 2' */
  MicroMouseTemplate_B.Switch2 = (MicroMouseTemplate_DW.clockTickCounter_g <
    MicroMouseTemplate_P.pulse2_Duty) &&
    (MicroMouseTemplate_DW.clockTickCounter_g >= 0) ?
    MicroMouseTemplate_P.pulse2_Amp : 0.0;
  if (MicroMouseTemplate_DW.clockTickCounter_g >=
      MicroMouseTemplate_P.pulse2_Period - 1.0) {
    MicroMouseTemplate_DW.clockTickCounter_g = 0;
  } else {
    MicroMouseTemplate_DW.clockTickCounter_g++;
  }

  /* End of DiscretePulseGenerator: '<Root>/pulse 2' */

  /* Chart: '<Root>/Chart' incorporates:
   *  Constant: '<Root>/Constant8'
   *  DataTypeConversion: '<Root>/Cast To Boolean'
   *  DataTypeConversion: '<Root>/Cast To Double'
   *  Gain: '<S1>/Gain'
   *  Logic: '<Root>/NOT'
   *  Logic: '<Root>/NOT1'
   *  Logic: '<S26>/AND'
   *  MATLABSystem: '<S15>/Analog to Digital Converter'
   *  MATLABSystem: '<S68>/Digital Port Read'
   *  MATLABSystem: '<S70>/Digital Port Read'
   *  SignalConversion generated from: '<Root>/Transpose'
   *  Switch: '<S31>/Switch'
   *  Switch: '<S32>/Switch'
   */
  if (MicroMouseTemplate_DW.temporalCounter_i1 < 127U) {
    MicroMouseTemplate_DW.temporalCounter_i1++;
  }

  if (MicroMouseTemplate_DW.is_active_c3_MicroMouseTemplate == 0U) {
    MicroMouseTemplate_DW.is_active_c3_MicroMouseTemplate = 1U;
    MicroMouseTemplate_DW.is_MainChart = MicroMouseTemplate_IN_Calibrate;
    MicroMouseTemplate_DW.is_Calibrate = MicroMouseTemplate_IN_Cal1;
    for (MicroMouseTemplate_B.i = 0; MicroMouseTemplate_B.i < 8;
         MicroMouseTemplate_B.i++) {
      MicroMouseTemplate_B.IR_LED_out[MicroMouseTemplate_B.i] = false;
    }
  } else if (MicroMouseTemplate_DW.is_MainChart ==
             MicroMouseTemplate_IN_Calibrate) {
    switch (MicroMouseTemplate_DW.is_Calibrate) {
     case MicroMouseTemplate_IN_Cal1:
      if ((MicroMouseTemplate_B.pinReadLoc & 64U) == 0U) {
        MicroMouseTemplate_B.LED0 = false;
        MicroMouseTemplate_B.LED1 = false;
        MicroMouseTemplate_B.LED2 = false;
        MicroMouseTemplate_DW.is_Calibrate = MicroMouseTemplate_IN_Cal2;
        for (MicroMouseTemplate_B.i = 0; MicroMouseTemplate_B.i < 8;
             MicroMouseTemplate_B.i++) {
          MicroMouseTemplate_DW.vThreshLower[MicroMouseTemplate_B.i] =
            MicroMouseTemplate_B.CastToDouble1[MicroMouseTemplate_B.i] -
            MicroMouseTemplate_B.CastToDouble2[MicroMouseTemplate_B.i];
        }
      } else {
        MicroMouseTemplate_B.LED0 = !MicroMouseTemplate_B.LED0;
        MicroMouseTemplate_B.LED1 = !MicroMouseTemplate_B.LED1;
        MicroMouseTemplate_B.LED2 = !MicroMouseTemplate_B.LED2;
      }
      break;

     case MicroMouseTemplate_IN_Cal2:
      if ((MicroMouseTemplate_B.pinReadLoc_m & 4U) == 0U) {
        MicroMouseTemplate_DW.is_Calibrate = MicroMouseTemplate_IN_Cal3;
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        MicroMouseTemplate_B.IR_LED_out[0] = (MicroMouseTemplate_B.MOT_RS != 0.0);
        MicroMouseTemplate_B.IR_LED_out[1] = (MicroMouseTemplate_B.Switch2 !=
          0.0);
        MicroMouseTemplate_B.IR_LED_out[2] = (MicroMouseTemplate_B.MOT_RS != 0.0);
        MicroMouseTemplate_B.IR_LED_out[3] =
          (MicroMouseTemplate_P.Constant8_Value != 0.0);
        MicroMouseTemplate_B.IR_LED_out[4] =
          (MicroMouseTemplate_P.Constant8_Value != 0.0);
        MicroMouseTemplate_B.IR_LED_out[5] = (MicroMouseTemplate_B.MOT_RS != 0.0);
        MicroMouseTemplate_B.IR_LED_out[6] = (MicroMouseTemplate_B.Switch2 !=
          0.0);
        MicroMouseTemplate_B.IR_LED_out[7] = (MicroMouseTemplate_B.MOT_RS != 0.0);
      }
      break;

     case MicroMouseTemplate_IN_Cal3:
      if (MicroMouseTemplate_DW.temporalCounter_i1 >= 80U) {
        MicroMouseTemplate_DW.is_Calibrate = MicroMouseTemplate_IN_Cal4;
        MicroMouseTemplate_DW.temporalCounter_i1 = 0U;
        for (MicroMouseTemplate_B.i = 0; MicroMouseTemplate_B.i < 8;
             MicroMouseTemplate_B.i++) {
          MicroMouseTemplate_DW.Thresholds[MicroMouseTemplate_B.i] =
            ((MicroMouseTemplate_B.CastToDouble1[MicroMouseTemplate_B.i] -
              MicroMouseTemplate_B.CastToDouble2[MicroMouseTemplate_B.i]) +
             MicroMouseTemplate_DW.vThreshLower[MicroMouseTemplate_B.i]) / 2.0;
        }
      }
      break;

     default:
      /* case IN_Cal4: */
      if (MicroMouseTemplate_DW.temporalCounter_i1 >= 80U) {
        MicroMouseTemplate_B.LED0 = true;
        MicroMouseTemplate_B.LED1 = true;
        MicroMouseTemplate_B.LED2 = true;
        MicroMouseTemplate_DW.is_Calibrate = MicroMouseTe_IN_NO_ACTIVE_CHILD;
        MicroMouseTemplate_DW.is_MainChart = MicroMouseTem_IN_ShowDetections;
      }
      break;
    }
  } else {
    /* case IN_ShowDetections: */
    for (MicroMouseTemplate_B.i = 0; MicroMouseTemplate_B.i < 8;
         MicroMouseTemplate_B.i++) {
      MicroMouseTemplate_B.ADCs[MicroMouseTemplate_B.i] = (real_T)((uint32_T)
        MicroMouseTemplate_P.Gain_Gain * ADC1s[MicroMouseTemplate_B.i]) *
        1.4901161193847656E-8;
    }

    /* Outputs for Function Call SubSystem: '<S3>/MainChart.ShowDetections.showDetections' */
    MicroMouseTempl_MovingMaximum_j(MicroMouseTemplate_B.ADCs[0],
      &MicroMouseTemplate_B.MovingMaximum_jncvpnv,
      &MicroMouseTemplate_DW.MovingMaximum_jncvpnv);
    MicroMouseTempl_MovingMinimum_j(MicroMouseTemplate_B.ADCs[0],
      &MicroMouseTemplate_B.MovingMinimum_jncvpnv,
      &MicroMouseTemplate_DW.MovingMinimum_jncvpnv);

    /* Switch: '<S35>/Switch' incorporates:
     *  DataTypeConversion: '<Root>/Cast To Double'
     *  Gain: '<S1>/Gain'
     *  MATLABSystem: '<S15>/Analog to Digital Converter'
     *  ParameterWriter: '<S35>/Parameter Writer'
     */
    MicroMouseTemplate_P.Switch_Threshold_j = (real32_T)
      MicroMouseTemplate_DW.Thresholds[0];
    MicroMouseTemp_MovingMaximum_jn(MicroMouseTemplate_B.ADCs[1],
      &MicroMouseTemplate_B.MovingMaximum_jncv,
      &MicroMouseTemplate_DW.MovingMaximum_jncv);
    MicroMouseTempl_MovingMinimum_j
      (MicroMouseTemplate_B.MovingMaximum_jncv.MovingMaximum,
       &MicroMouseTemplate_B.MovingMinimum1_j,
       &MicroMouseTemplate_DW.MovingMinimum1_j);
    MicroMouseTempl_MovingMinimum_j(MicroMouseTemplate_B.ADCs[1],
      &MicroMouseTemplate_B.MovingMinimum_jncv,
      &MicroMouseTemplate_DW.MovingMinimum_jncv);

    /* Switch: '<S32>/Switch' incorporates:
     *  ParameterWriter: '<S32>/Parameter Writer'
     */
    MicroMouseTemplate_P.Switch_Threshold_m = (real32_T)
      MicroMouseTemplate_DW.Thresholds[1];
    MicroMouseTempl_MovingMaximum_j(MicroMouseTemplate_B.ADCs[2],
      &MicroMouseTemplate_B.MovingMaximum_jn,
      &MicroMouseTemplate_DW.MovingMaximum_jn);
    MicroMouseTempl_MovingMinimum_j(MicroMouseTemplate_B.ADCs[2],
      &MicroMouseTemplate_B.MovingMinimum_jn,
      &MicroMouseTemplate_DW.MovingMinimum_jn);

    /* Switch: '<S30>/Switch' incorporates:
     *  ParameterWriter: '<S30>/Parameter Writer'
     */
    MicroMouseTemplate_P.Switch_Threshold_h = (real32_T)
      MicroMouseTemplate_DW.Thresholds[2];

    /* Saturate: '<S36>/Saturation' */
    if (MicroMouseTemplate_B.ADCs[3] > MicroMouseTemplate_P.Saturation_UpperSat)
    {
      /* Saturate: '<S36>/Saturation' */
      MicroMouseTemplate_B.Saturation = MicroMouseTemplate_P.Saturation_UpperSat;
    } else if (MicroMouseTemplate_B.ADCs[3] <
               MicroMouseTemplate_P.Saturation_LowerSat) {
      /* Saturate: '<S36>/Saturation' */
      MicroMouseTemplate_B.Saturation = MicroMouseTemplate_P.Saturation_LowerSat;
    } else {
      /* Saturate: '<S36>/Saturation' */
      MicroMouseTemplate_B.Saturation = MicroMouseTemplate_B.ADCs[3];
    }

    /* End of Saturate: '<S36>/Saturation' */
    MicroMouseTempl_MovingMaximum_j(MicroMouseTemplate_B.Saturation,
      &MicroMouseTemplate_B.MovingMaximum_jncvpnvp,
      &MicroMouseTemplate_DW.MovingMaximum_jncvpnvp);
    MicroMouseTempl_MovingMinimum_j(MicroMouseTemplate_B.Saturation,
      &MicroMouseTemplate_B.MovingMinimum_jncvpnvp,
      &MicroMouseTemplate_DW.MovingMinimum_jncvpnvp);

    /* Switch: '<S36>/Switch' incorporates:
     *  ParameterWriter: '<S36>/Parameter Writer'
     */
    MicroMouseTemplate_P.Switch_Threshold_f = (real32_T)
      MicroMouseTemplate_DW.Thresholds[3];
    MicroMouseTempl_MovingMaximum_j(MicroMouseTemplate_B.ADCs[4],
      &MicroMouseTemplate_B.MovingMaximum_jncvp,
      &MicroMouseTemplate_DW.MovingMaximum_jncvp);
    MicroMouseTempl_MovingMinimum_j(MicroMouseTemplate_B.ADCs[4],
      &MicroMouseTemplate_B.MovingMinimum_jncvp,
      &MicroMouseTemplate_DW.MovingMinimum_jncvp);

    /* Switch: '<S33>/Switch' incorporates:
     *  ParameterWriter: '<S33>/Parameter Writer'
     */
    MicroMouseTemplate_P.Switch_Threshold_a = (real32_T)
      MicroMouseTemplate_DW.Thresholds[4];
    MicroMouseTempl_MovingMaximum_j(MicroMouseTemplate_B.ADCs[5],
      &MicroMouseTemplate_B.MovingMaximum_j,
      &MicroMouseTemplate_DW.MovingMaximum_j);
    MicroMouseTempl_MovingMinimum_j(MicroMouseTemplate_B.ADCs[5],
      &MicroMouseTemplate_B.MovingMinimum_j,
      &MicroMouseTemplate_DW.MovingMinimum_j);

    /* Switch: '<S29>/Switch' incorporates:
     *  ParameterWriter: '<S29>/Parameter Writer'
     */
    MicroMouseTemplate_P.Switch_Threshold_k = (real32_T)
      MicroMouseTemplate_DW.Thresholds[5];
    MicroMouseTemp_MovingMaximum_jn(MicroMouseTemplate_B.ADCs[6],
      &MicroMouseTemplate_B.MovingMaximum_jnc,
      &MicroMouseTemplate_DW.MovingMaximum_jnc);
    MicroMouseTempl_MovingMinimum_j
      (MicroMouseTemplate_B.MovingMaximum_jnc.MovingMaximum,
       &MicroMouseTemplate_B.MovingMinimum1,
       &MicroMouseTemplate_DW.MovingMinimum1);
    MicroMouseTempl_MovingMinimum_j(MicroMouseTemplate_B.ADCs[6],
      &MicroMouseTemplate_B.MovingMinimum_jnc,
      &MicroMouseTemplate_DW.MovingMinimum_jnc);

    /* Switch: '<S31>/Switch' incorporates:
     *  ParameterWriter: '<S31>/Parameter Writer'
     */
    MicroMouseTemplate_P.Switch_Threshold_i = (real32_T)
      MicroMouseTemplate_DW.Thresholds[6];
    MicroMouseTempl_MovingMaximum_j(MicroMouseTemplate_B.ADCs[7],
      &MicroMouseTemplate_B.MovingMaximum_jncvpn,
      &MicroMouseTemplate_DW.MovingMaximum_jncvpn);
    MicroMouseTempl_MovingMinimum_j(MicroMouseTemplate_B.ADCs[7],
      &MicroMouseTemplate_B.MovingMinimum_jncvpn,
      &MicroMouseTemplate_DW.MovingMinimum_jncvpn);

    /* Switch: '<S34>/Switch' incorporates:
     *  ParameterWriter: '<S34>/Parameter Writer'
     */
    MicroMouseTemplate_P.Switch_Threshold_d = (real32_T)
      MicroMouseTemplate_DW.Thresholds[7];

    /* Switch: '<S33>/Switch' incorporates:
     *  Abs: '<S33>/Abs'
     *  Constant: '<S33>/Constant2'
     *  Constant: '<S33>/Constant3'
     *  DataTypeConversion: '<S28>/Cast To Boolean'
     *  Sum: '<S33>/Minus'
     */
    if ((real32_T)fabs((real32_T)
                       MicroMouseTemplate_B.MovingMaximum_jncvp.MovingMaximum -
                       (real32_T)
                       MicroMouseTemplate_B.MovingMinimum_jncvp.MovingMinimum) >
        MicroMouseTemplate_P.Switch_Threshold_a) {
      MicroMouseTemplate_B.LED0 = (MicroMouseTemplate_P.Constant2_Value_i != 0.0);
    } else {
      MicroMouseTemplate_B.LED0 = (MicroMouseTemplate_P.Constant3_Value_f != 0.0);
    }

    /* End of Switch: '<S33>/Switch' */

    /* Switch: '<S32>/Switch' incorporates:
     *  Abs: '<S32>/Abs'
     *  Constant: '<S32>/Constant2'
     *  Constant: '<S32>/Constant3'
     *  DataTypeConversion: '<S28>/Cast To Boolean'
     *  Sum: '<S32>/Minus'
     */
    if ((real32_T)fabs((real32_T)
                       MicroMouseTemplate_B.MovingMinimum1_j.MovingMinimum -
                       (real32_T)
                       MicroMouseTemplate_B.MovingMinimum_jncv.MovingMinimum) >
        MicroMouseTemplate_P.Switch_Threshold_m) {
      MicroMouseTemplate_B.b = (MicroMouseTemplate_P.Constant2_Value_j != 0.0);
    } else {
      MicroMouseTemplate_B.b = (MicroMouseTemplate_P.Constant3_Value_b != 0.0);
    }

    /* Switch: '<S31>/Switch' incorporates:
     *  Abs: '<S31>/Abs'
     *  Constant: '<S31>/Constant2'
     *  Constant: '<S31>/Constant3'
     *  DataTypeConversion: '<S28>/Cast To Boolean'
     *  Sum: '<S31>/Minus'
     */
    if ((real32_T)fabs((real32_T)
                       MicroMouseTemplate_B.MovingMinimum1.MovingMinimum -
                       (real32_T)
                       MicroMouseTemplate_B.MovingMinimum_jnc.MovingMinimum) >
        MicroMouseTemplate_P.Switch_Threshold_i) {
      MicroMouseTemplate_B.b1 = (MicroMouseTemplate_P.Constant2_Value_e != 0.0);
    } else {
      MicroMouseTemplate_B.b1 = (MicroMouseTemplate_P.Constant3_Value_d != 0.0);
    }

    MicroMouseTemplate_B.LED1 = (MicroMouseTemplate_B.b &&
      MicroMouseTemplate_B.b1);

    /* Switch: '<S36>/Switch' incorporates:
     *  Abs: '<S36>/Abs'
     *  Constant: '<S36>/Constant2'
     *  Constant: '<S36>/Constant3'
     *  DataTypeConversion: '<S28>/Cast To Boolean'
     *  Logic: '<S26>/AND'
     *  Sum: '<S36>/Minus'
     *  Switch: '<S31>/Switch'
     *  Switch: '<S32>/Switch'
     */
    if ((real32_T)fabs((real32_T)
                       MicroMouseTemplate_B.MovingMaximum_jncvpnvp.MovingMaximum
                       - (real32_T)
                       MicroMouseTemplate_B.MovingMinimum_jncvpnvp.MovingMinimum)
        > MicroMouseTemplate_P.Switch_Threshold_f) {
      MicroMouseTemplate_B.LED2 = (MicroMouseTemplate_P.Constant2_Value_b != 0.0);
    } else {
      MicroMouseTemplate_B.LED2 = (MicroMouseTemplate_P.Constant3_Value_dx !=
        0.0);
    }

    /* End of Switch: '<S36>/Switch' */
    /* End of Outputs for SubSystem: '<S3>/MainChart.ShowDetections.showDetections' */
  }

  /* End of Chart: '<Root>/Chart' */

  /* DataStoreWrite: '<S4>/Data Store Write' */
  for (MicroMouseTemplate_B.i = 0; MicroMouseTemplate_B.i < 8;
       MicroMouseTemplate_B.i++) {
    IR_LEDs[MicroMouseTemplate_B.i] =
      MicroMouseTemplate_B.IR_LED_out[MicroMouseTemplate_B.i];
  }

  /* End of DataStoreWrite: '<S4>/Data Store Write' */

  /* MATLABSystem: '<S46>/Digital Port Write' */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.IR_LED_out[3]) {
    MicroMouseTemplate_B.i = 512;
  } else {
    MicroMouseTemplate_B.i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)
                       MicroMouseTemplate_B.i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)
    MicroMouseTemplate_B.i & 512U);

  /* End of MATLABSystem: '<S46>/Digital Port Write' */

  /* MATLABSystem: '<S48>/Digital Port Write' */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.IR_LED_out[4]) {
    MicroMouseTemplate_B.i = 16384;
  } else {
    MicroMouseTemplate_B.i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)
                       MicroMouseTemplate_B.i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)
    MicroMouseTemplate_B.i & 16384U);

  /* End of MATLABSystem: '<S48>/Digital Port Write' */

  /* MATLABSystem: '<S50>/Digital Port Write' */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.IR_LED_out[1]) {
    MicroMouseTemplate_B.i = 256;
  } else {
    MicroMouseTemplate_B.i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)
                       MicroMouseTemplate_B.i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)
    MicroMouseTemplate_B.i & 256U);

  /* End of MATLABSystem: '<S50>/Digital Port Write' */

  /* MATLABSystem: '<S52>/Digital Port Write' */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.IR_LED_out[6]) {
    MicroMouseTemplate_B.i = 32768;
  } else {
    MicroMouseTemplate_B.i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)
                       MicroMouseTemplate_B.i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)
    MicroMouseTemplate_B.i & 32768U);

  /* End of MATLABSystem: '<S52>/Digital Port Write' */

  /* MATLABSystem: '<S54>/Digital Port Write' */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.IR_LED_out[2]) {
    MicroMouseTemplate_B.i = 4096;
  } else {
    MicroMouseTemplate_B.i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)
                       MicroMouseTemplate_B.i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)
    MicroMouseTemplate_B.i & 4096U);

  /* End of MATLABSystem: '<S54>/Digital Port Write' */

  /* MATLABSystem: '<S56>/Digital Port Write' */
  MicroMouseTemplate_B.portNameLoc = GPIOB;
  if (MicroMouseTemplate_B.IR_LED_out[0]) {
    MicroMouseTemplate_B.i = 4096;
  } else {
    MicroMouseTemplate_B.i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)
                       MicroMouseTemplate_B.i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)
    MicroMouseTemplate_B.i & 4096U);

  /* End of MATLABSystem: '<S56>/Digital Port Write' */

  /* MATLABSystem: '<S58>/Digital Port Write' */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.IR_LED_out[7]) {
    MicroMouseTemplate_B.i = 8192;
  } else {
    MicroMouseTemplate_B.i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)
                       MicroMouseTemplate_B.i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)
    MicroMouseTemplate_B.i & 8192U);

  /* End of MATLABSystem: '<S58>/Digital Port Write' */

  /* MATLABSystem: '<S60>/Digital Port Write' */
  MicroMouseTemplate_B.portNameLoc = GPIOE;
  if (MicroMouseTemplate_B.IR_LED_out[5]) {
    MicroMouseTemplate_B.i = 2048;
  } else {
    MicroMouseTemplate_B.i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)
                       MicroMouseTemplate_B.i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)
    MicroMouseTemplate_B.i & 2048U);

  /* End of MATLABSystem: '<S60>/Digital Port Write' */
  for (MicroMouseTemplate_B.i = 0; MicroMouseTemplate_B.i < 8;
       MicroMouseTemplate_B.i++) {
    /* DataTypeConversion: '<S1>/Cast To Double' incorporates:
     *  MATLABSystem: '<S15>/Analog to Digital Converter'
     */
    MicroMouseTemplate_B.CastToDouble_f[MicroMouseTemplate_B.i] =
      ADC1s[MicroMouseTemplate_B.i];
  }

  MicroMouseTemplat_MovingMaximum(MicroMouseTemplate_B.CastToDouble_f[0],
    &MicroMouseTemplate_B.MovingMaximum, &MicroMouseTemplate_DW.MovingMaximum);
  MicroMouseTempla_MovingMaximum1(MicroMouseTemplate_B.CastToDouble_f[1],
    &MicroMouseTemplate_B.MovingMaximum1, &MicroMouseTemplate_DW.MovingMaximum1);
  MicroMouseTempla_MovingMinimum2
    (MicroMouseTemplate_B.MovingMaximum1.MovingMaximum1,
     &MicroMouseTemplate_B.MovingMinimum2, &MicroMouseTemplate_DW.MovingMinimum2);
  MicroMouseTemplat_MovingMaximum(MicroMouseTemplate_B.CastToDouble_f[2],
    &MicroMouseTemplate_B.MovingMaximum_p,
    &MicroMouseTemplate_DW.MovingMaximum_p);
  MicroMouseTemplat_MovingMaximum(MicroMouseTemplate_B.CastToDouble_f[3],
    &MicroMouseTemplate_B.MovingMaximum_pn,
    &MicroMouseTemplate_DW.MovingMaximum_pn);
  MicroMouseTemplat_MovingMaximum(MicroMouseTemplate_B.CastToDouble_f[4],
    &MicroMouseTemplate_B.MovingMaximum_pna,
    &MicroMouseTemplate_DW.MovingMaximum_pna);
  MicroMouseTemplat_MovingMaximum(MicroMouseTemplate_B.CastToDouble_f[5],
    &MicroMouseTemplate_B.MovingMaximum_pnae,
    &MicroMouseTemplate_DW.MovingMaximum_pnae);
  MicroMouseTempla_MovingMaximum1(MicroMouseTemplate_B.CastToDouble_f[6],
    &MicroMouseTemplate_B.MovingMaximum1_p,
    &MicroMouseTemplate_DW.MovingMaximum1_p);
  MicroMouseTempla_MovingMinimum2
    (MicroMouseTemplate_B.MovingMaximum1_p.MovingMaximum1,
     &MicroMouseTemplate_B.MovingMinimum2_p,
     &MicroMouseTemplate_DW.MovingMinimum2_p);
  MicroMouseTemplat_MovingMaximum(MicroMouseTemplate_B.CastToDouble_f[7],
    &MicroMouseTemplate_B.MovingMaximum_pnaev,
    &MicroMouseTemplate_DW.MovingMaximum_pnaev);

  /* DataTypeConversion: '<S13>/Cast2' incorporates:
   *  Constant: '<S13>/Constant'
   *  DataStoreWrite: '<S13>/Data Store Write1'
   */
  MicroMouseTemplate_B.Switch2 = floor
    (MicroMouseTemplate_B.MovingMaximum.MovingMaximum);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_H[0] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);
  MicroMouseTemplate_B.Switch2 = floor
    (MicroMouseTemplate_B.MovingMinimum2.MovingMinimum2);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_H[1] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);
  MicroMouseTemplate_B.Switch2 = floor
    (MicroMouseTemplate_B.MovingMaximum_p.MovingMaximum);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_H[2] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);
  MicroMouseTemplate_B.Switch2 = floor
    (MicroMouseTemplate_B.MovingMaximum_pn.MovingMaximum);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_H[3] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);
  MicroMouseTemplate_B.Switch2 = floor
    (MicroMouseTemplate_B.MovingMaximum_pna.MovingMaximum);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_H[4] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);
  MicroMouseTemplate_B.Switch2 = floor
    (MicroMouseTemplate_B.MovingMaximum_pnae.MovingMaximum);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_H[5] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);
  MicroMouseTemplate_B.Switch2 = floor
    (MicroMouseTemplate_B.MovingMinimum2_p.MovingMinimum2);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_H[6] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);
  MicroMouseTemplate_B.Switch2 = floor
    (MicroMouseTemplate_B.MovingMaximum_pnaev.MovingMaximum);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_H[7] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);
  MicroMouseTemplate_B.Switch2 = floor(MicroMouseTemplate_P.Constant_Value);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_H[8] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);

  /* End of DataTypeConversion: '<S13>/Cast2' */
  MicroMouseTemplat_MovingMinimum(MicroMouseTemplate_B.CastToDouble_f[0],
    &MicroMouseTemplate_B.MovingMinimum, &MicroMouseTemplate_DW.MovingMinimum);
  MicroMouseTemplat_MovingMinimum(MicroMouseTemplate_B.CastToDouble_f[1],
    &MicroMouseTemplate_B.MovingMinimum_p,
    &MicroMouseTemplate_DW.MovingMinimum_p);
  MicroMouseTemplat_MovingMinimum(MicroMouseTemplate_B.CastToDouble_f[2],
    &MicroMouseTemplate_B.MovingMinimum_pn,
    &MicroMouseTemplate_DW.MovingMinimum_pn);
  MicroMouseTemplat_MovingMinimum(MicroMouseTemplate_B.CastToDouble_f[3],
    &MicroMouseTemplate_B.MovingMinimum_pna,
    &MicroMouseTemplate_DW.MovingMinimum_pna);
  MicroMouseTemplat_MovingMinimum(MicroMouseTemplate_B.CastToDouble_f[4],
    &MicroMouseTemplate_B.MovingMinimum_pnae,
    &MicroMouseTemplate_DW.MovingMinimum_pnae);
  MicroMouseTemplat_MovingMinimum(MicroMouseTemplate_B.CastToDouble_f[5],
    &MicroMouseTemplate_B.MovingMinimum_pnaev,
    &MicroMouseTemplate_DW.MovingMinimum_pnaev);
  MicroMouseTemplat_MovingMinimum(MicroMouseTemplate_B.CastToDouble_f[6],
    &MicroMouseTemplate_B.MovingMinimum_pnaevv,
    &MicroMouseTemplate_DW.MovingMinimum_pnaevv);
  MicroMouseTemplat_MovingMinimum(MicroMouseTemplate_B.CastToDouble_f[7],
    &MicroMouseTemplate_B.MovingMinimum_pnaevvf,
    &MicroMouseTemplate_DW.MovingMinimum_pnaevvf);

  /* DataTypeConversion: '<S13>/Cast1' incorporates:
   *  Constant: '<S13>/Constant1'
   *  DataStoreWrite: '<S13>/Data Store Write2'
   */
  MicroMouseTemplate_B.Switch2 = floor
    (MicroMouseTemplate_B.MovingMinimum.MovingMinimum);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_L[0] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);
  MicroMouseTemplate_B.Switch2 = floor
    (MicroMouseTemplate_B.MovingMinimum_p.MovingMinimum);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_L[1] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);
  MicroMouseTemplate_B.Switch2 = floor
    (MicroMouseTemplate_B.MovingMinimum_pn.MovingMinimum);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_L[2] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);
  MicroMouseTemplate_B.Switch2 = floor
    (MicroMouseTemplate_B.MovingMinimum_pna.MovingMinimum);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_L[3] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);
  MicroMouseTemplate_B.Switch2 = floor
    (MicroMouseTemplate_B.MovingMinimum_pnae.MovingMinimum);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_L[4] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);
  MicroMouseTemplate_B.Switch2 = floor
    (MicroMouseTemplate_B.MovingMinimum_pnaev.MovingMinimum);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_L[5] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);
  MicroMouseTemplate_B.Switch2 = floor
    (MicroMouseTemplate_B.MovingMinimum_pnaevv.MovingMinimum);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_L[6] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);
  MicroMouseTemplate_B.Switch2 = floor
    (MicroMouseTemplate_B.MovingMinimum_pnaevvf.MovingMinimum);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_L[7] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);
  MicroMouseTemplate_B.Switch2 = floor(MicroMouseTemplate_P.Constant1_Value);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  ADC_L[8] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);

  /* End of DataTypeConversion: '<S13>/Cast1' */

  /* Gain: '<S11>/Gain' incorporates:
   *  Gain: '<S11>/Gain1'
   */
  MicroMouseTemplate_B.Switch2 = MicroMouseTemplate_P.TIM3_ARR / 100.0;

  /* Switch: '<S11>/Switch1' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<S11>/Off'
   */
  if (MicroMouseTemplate_P.Constant1_Value_a >=
      MicroMouseTemplate_P.Switch1_Threshold) {
    MicroMouseTemplate_B.d = MicroMouseTemplate_P.Constant1_Value_a;
  } else {
    MicroMouseTemplate_B.d = MicroMouseTemplate_P.Off_Value;
  }

  /* Gain: '<S11>/Gain' incorporates:
   *  DataStoreWrite: '<S11>/Data Store Write'
   *  Switch: '<S11>/Switch1'
   */
  MicroMouseTemplate_B.d = floor(MicroMouseTemplate_B.Switch2 *
    MicroMouseTemplate_B.d);
  if (rtIsNaN(MicroMouseTemplate_B.d) || rtIsInf(MicroMouseTemplate_B.d)) {
    MicroMouseTemplate_B.d = 0.0;
  } else {
    MicroMouseTemplate_B.d = fmod(MicroMouseTemplate_B.d, 65536.0);
  }

  MOT_L[0] = (uint16_T)(MicroMouseTemplate_B.d < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.d : (int32_T)
                        (uint16_T)MicroMouseTemplate_B.d);

  /* Switch: '<S11>/Switch' incorporates:
   *  Abs: '<S11>/Abs'
   *  Constant: '<Root>/Constant1'
   *  Constant: '<S11>/Off'
   */
  if (MicroMouseTemplate_P.Constant1_Value_a >=
      MicroMouseTemplate_P.Switch_Threshold) {
    MicroMouseTemplate_B.d = MicroMouseTemplate_P.Off_Value;
  } else {
    MicroMouseTemplate_B.d = fabs(MicroMouseTemplate_P.Constant1_Value_a);
  }

  /* Gain: '<S11>/Gain' incorporates:
   *  DataStoreWrite: '<S11>/Data Store Write'
   *  Switch: '<S11>/Switch'
   */
  MicroMouseTemplate_B.d = floor(MicroMouseTemplate_B.Switch2 *
    MicroMouseTemplate_B.d);
  if (rtIsNaN(MicroMouseTemplate_B.d) || rtIsInf(MicroMouseTemplate_B.d)) {
    MicroMouseTemplate_B.d = 0.0;
  } else {
    MicroMouseTemplate_B.d = fmod(MicroMouseTemplate_B.d, 65536.0);
  }

  MOT_L[1] = (uint16_T)(MicroMouseTemplate_B.d < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.d : (int32_T)
                        (uint16_T)MicroMouseTemplate_B.d);

  /* Switch: '<S11>/Switch3' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<S11>/Off1'
   */
  if (MicroMouseTemplate_P.Constant1_Value_a >=
      MicroMouseTemplate_P.Switch3_Threshold) {
    MicroMouseTemplate_B.d = MicroMouseTemplate_P.Constant1_Value_a;
  } else {
    MicroMouseTemplate_B.d = MicroMouseTemplate_P.Off1_Value;
  }

  /* Gain: '<S11>/Gain1' incorporates:
   *  DataStoreWrite: '<S11>/Data Store Write1'
   *  Switch: '<S11>/Switch3'
   */
  MicroMouseTemplate_B.d = floor(MicroMouseTemplate_B.Switch2 *
    MicroMouseTemplate_B.d);
  if (rtIsNaN(MicroMouseTemplate_B.d) || rtIsInf(MicroMouseTemplate_B.d)) {
    MicroMouseTemplate_B.d = 0.0;
  } else {
    MicroMouseTemplate_B.d = fmod(MicroMouseTemplate_B.d, 65536.0);
  }

  MOT_R[0] = (uint16_T)(MicroMouseTemplate_B.d < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.d : (int32_T)
                        (uint16_T)MicroMouseTemplate_B.d);

  /* Switch: '<S11>/Switch2' incorporates:
   *  Abs: '<S11>/Abs1'
   *  Constant: '<Root>/Constant1'
   *  Constant: '<S11>/Off1'
   */
  if (MicroMouseTemplate_P.Constant1_Value_a >=
      MicroMouseTemplate_P.Switch2_Threshold) {
    MicroMouseTemplate_B.d = MicroMouseTemplate_P.Off1_Value;
  } else {
    MicroMouseTemplate_B.d = fabs(MicroMouseTemplate_P.Constant1_Value_a);
  }

  /* Gain: '<S11>/Gain1' incorporates:
   *  DataStoreWrite: '<S11>/Data Store Write1'
   *  Switch: '<S11>/Switch2'
   */
  MicroMouseTemplate_B.Switch2 = floor(MicroMouseTemplate_B.Switch2 *
    MicroMouseTemplate_B.d);
  if (rtIsNaN(MicroMouseTemplate_B.Switch2) || rtIsInf
      (MicroMouseTemplate_B.Switch2)) {
    MicroMouseTemplate_B.Switch2 = 0.0;
  } else {
    MicroMouseTemplate_B.Switch2 = fmod(MicroMouseTemplate_B.Switch2, 65536.0);
  }

  MOT_R[1] = (uint16_T)(MicroMouseTemplate_B.Switch2 < 0.0 ? (int32_T)(uint16_T)
                        -(int16_T)(uint16_T)-MicroMouseTemplate_B.Switch2 :
                        (int32_T)(uint16_T)MicroMouseTemplate_B.Switch2);

  /* MATLABSystem: '<S73>/Digital Port Write' */
  MicroMouseTemplate_B.portNameLoc = GPIOD;
  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, 0U);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, 128U);

  /* MATLABSystem: '<S62>/Digital Port Write' */
  MicroMouseTemplate_B.portNameLoc = GPIOC;
  if (MicroMouseTemplate_B.LED0) {
    MicroMouseTemplate_B.i = 8192;
  } else {
    MicroMouseTemplate_B.i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)
                       MicroMouseTemplate_B.i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)
    MicroMouseTemplate_B.i & 8192U);

  /* End of MATLABSystem: '<S62>/Digital Port Write' */

  /* MATLABSystem: '<S64>/Digital Port Write' */
  MicroMouseTemplate_B.portNameLoc = GPIOC;
  if (MicroMouseTemplate_B.LED1) {
    MicroMouseTemplate_B.i = 16384;
  } else {
    MicroMouseTemplate_B.i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)
                       MicroMouseTemplate_B.i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)
    MicroMouseTemplate_B.i & 16384U);

  /* End of MATLABSystem: '<S64>/Digital Port Write' */

  /* MATLABSystem: '<S66>/Digital Port Write' */
  MicroMouseTemplate_B.portNameLoc = GPIOC;
  if (MicroMouseTemplate_B.LED2) {
    MicroMouseTemplate_B.i = 32768;
  } else {
    MicroMouseTemplate_B.i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)
                       MicroMouseTemplate_B.i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)
    MicroMouseTemplate_B.i & 32768U);

  /* End of MATLABSystem: '<S66>/Digital Port Write' */

  /* MATLABSystem: '<S25>/Digital Port Write' incorporates:
   *  Constant: '<Root>/Constant'
   */
  MicroMouseTemplate_B.portNameLoc = GPIOB;
  if (MicroMouseTemplate_P.Constant_Value_c != 0.0) {
    MicroMouseTemplate_B.i = 8;
  } else {
    MicroMouseTemplate_B.i = 0;
  }

  LL_GPIO_SetOutputPin(MicroMouseTemplate_B.portNameLoc, (uint32_T)
                       MicroMouseTemplate_B.i);
  LL_GPIO_ResetOutputPin(MicroMouseTemplate_B.portNameLoc, ~(uint32_T)
    MicroMouseTemplate_B.i & 8U);

  /* End of MATLABSystem: '<S25>/Digital Port Write' */

  /* user code (Update function Body) */

  /* System '<Root>' */
  updateSpeeds();

  /* System '<Root>' */
  refreshIMUValues();
  rate_scheduler();
}

/* Model initialize function */
void MicroMouseTemplate_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    int32_T i;

    /* Start for DataStoreMemory: '<S4>/Data Store Memory1' */
    IR_LED_TIMER = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_h;

    /* Start for DataStoreMemory: '<S1>/Data Store Memory3' */
    for (i = 0; i < 9; i++) {
      ADC2s[i] = MicroMouseTemplate_P.DataStoreMemory3_InitialValue;
    }

    /* End of Start for DataStoreMemory: '<S1>/Data Store Memory3' */

    /* Start for DiscretePulseGenerator: '<Root>/pulse 2' */
    MicroMouseTemplate_DW.clockTickCounter_g = -7;

    /* Start for DataStoreMemory: '<S4>/Data Store Memory' */
    for (i = 0; i < 8; i++) {
      IR_LEDs[i] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_h;
    }

    /* End of Start for DataStoreMemory: '<S4>/Data Store Memory' */
    for (i = 0; i < 9; i++) {
      /* Start for DataStoreMemory: '<S1>/Data Store Memory' */
      ADC1s[i] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_p;

      /* Start for DataStoreMemory: '<S1>/Data Store Memory1' */
      ADC_H[i] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_n;

      /* Start for DataStoreMemory: '<S1>/Data Store Memory2' */
      ADC_L[i] = MicroMouseTemplate_P.DataStoreMemory2_InitialValue;
    }

    /* Start for DataStoreMemory: '<S11>/Data Store Memory' */
    MOT_R[0] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_c;

    /* Start for DataStoreMemory: '<S11>/Data Store Memory1' */
    MOT_L[0] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_a;

    /* Start for DataStoreMemory: '<S11>/Data Store Memory' */
    MOT_R[1] = MicroMouseTemplate_P.DataStoreMemory_InitialValue_c;

    /* Start for DataStoreMemory: '<S11>/Data Store Memory1' */
    MOT_L[1] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue_a;

    /* Start for DataStoreMemory: '<S5>/Data Store Memory' */
    IMU_Accel[0] = MicroMouseTemplate_P.DataStoreMemory_InitialValue;

    /* Start for DataStoreMemory: '<S5>/Data Store Memory1' */
    IMU_Gyro[0] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue;

    /* Start for DataStoreMemory: '<S5>/Data Store Memory' */
    IMU_Accel[1] = MicroMouseTemplate_P.DataStoreMemory_InitialValue;

    /* Start for DataStoreMemory: '<S5>/Data Store Memory1' */
    IMU_Gyro[1] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue;

    /* Start for DataStoreMemory: '<S5>/Data Store Memory' */
    IMU_Accel[2] = MicroMouseTemplate_P.DataStoreMemory_InitialValue;

    /* Start for DataStoreMemory: '<S5>/Data Store Memory1' */
    IMU_Gyro[2] = MicroMouseTemplate_P.DataStoreMemory1_InitialValue;

    /* user code (Initialize function Body) */

    /* System '<Root>' */
    initMotors();

    /* System '<Root>' */
    initIMU();

    /* SystemInitialize for Chart: '<Root>/Chart' incorporates:
     *  SubSystem: '<S3>/MainChart.ShowDetections.showDetections'
     */
    MicroMouse_MovingMaximum_i_Init(&MicroMouseTemplate_DW.MovingMaximum_jncvpnv);
    MicroMouse_MovingMinimum_f_Init(&MicroMouseTemplate_DW.MovingMinimum_jncvpnv);
    MicroMouse_MovingMaximum_h_Init(&MicroMouseTemplate_DW.MovingMaximum_jncv);
    MicroMouse_MovingMinimum_f_Init(&MicroMouseTemplate_DW.MovingMinimum1_j);
    MicroMouse_MovingMinimum_f_Init(&MicroMouseTemplate_DW.MovingMinimum_jncv);
    MicroMouse_MovingMaximum_i_Init(&MicroMouseTemplate_DW.MovingMaximum_jn);
    MicroMouse_MovingMinimum_f_Init(&MicroMouseTemplate_DW.MovingMinimum_jn);
    MicroMouse_MovingMaximum_i_Init
      (&MicroMouseTemplate_DW.MovingMaximum_jncvpnvp);
    MicroMouse_MovingMinimum_f_Init
      (&MicroMouseTemplate_DW.MovingMinimum_jncvpnvp);
    MicroMouse_MovingMaximum_i_Init(&MicroMouseTemplate_DW.MovingMaximum_jncvp);
    MicroMouse_MovingMinimum_f_Init(&MicroMouseTemplate_DW.MovingMinimum_jncvp);
    MicroMouse_MovingMaximum_i_Init(&MicroMouseTemplate_DW.MovingMaximum_j);
    MicroMouse_MovingMinimum_f_Init(&MicroMouseTemplate_DW.MovingMinimum_j);
    MicroMouse_MovingMaximum_h_Init(&MicroMouseTemplate_DW.MovingMaximum_jnc);
    MicroMouse_MovingMinimum_f_Init(&MicroMouseTemplate_DW.MovingMinimum1);
    MicroMouse_MovingMinimum_f_Init(&MicroMouseTemplate_DW.MovingMinimum_jnc);
    MicroMouse_MovingMaximum_i_Init(&MicroMouseTemplate_DW.MovingMaximum_jncvpn);
    MicroMouse_MovingMinimum_f_Init(&MicroMouseTemplate_DW.MovingMinimum_jncvpn);

    /* Start for MATLABSystem: '<S15>/Analog to Digital Converter' */
    MicroMouseTemplate_DW.obj.isInitialized = 0;
    MicroMouseTemplate_DW.obj.matlabCodegenIsDeleted = false;
    MicroMouseTemp_SystemCore_setup(&MicroMouseTemplate_DW.obj);
    MicroMouseTe_MovingMaximum_Init(&MicroMouseTemplate_DW.MovingMaximum);
    MicroMouseT_MovingMaximum1_Init(&MicroMouseTemplate_DW.MovingMaximum1);
    MicroMouseT_MovingMinimum2_Init(&MicroMouseTemplate_DW.MovingMinimum2);
    MicroMouseTe_MovingMaximum_Init(&MicroMouseTemplate_DW.MovingMaximum_p);
    MicroMouseTe_MovingMaximum_Init(&MicroMouseTemplate_DW.MovingMaximum_pn);
    MicroMouseTe_MovingMaximum_Init(&MicroMouseTemplate_DW.MovingMaximum_pna);
    MicroMouseTe_MovingMaximum_Init(&MicroMouseTemplate_DW.MovingMaximum_pnae);
    MicroMouseT_MovingMaximum1_Init(&MicroMouseTemplate_DW.MovingMaximum1_p);
    MicroMouseT_MovingMinimum2_Init(&MicroMouseTemplate_DW.MovingMinimum2_p);
    MicroMouseTe_MovingMaximum_Init(&MicroMouseTemplate_DW.MovingMaximum_pnaev);
    MicroMouseTe_MovingMinimum_Init(&MicroMouseTemplate_DW.MovingMinimum);
    MicroMouseTe_MovingMinimum_Init(&MicroMouseTemplate_DW.MovingMinimum_p);
    MicroMouseTe_MovingMinimum_Init(&MicroMouseTemplate_DW.MovingMinimum_pn);
    MicroMouseTe_MovingMinimum_Init(&MicroMouseTemplate_DW.MovingMinimum_pna);
    MicroMouseTe_MovingMinimum_Init(&MicroMouseTemplate_DW.MovingMinimum_pnae);
    MicroMouseTe_MovingMinimum_Init(&MicroMouseTemplate_DW.MovingMinimum_pnaev);
    MicroMouseTe_MovingMinimum_Init(&MicroMouseTemplate_DW.MovingMinimum_pnaevv);
    MicroMouseTe_MovingMinimum_Init(&MicroMouseTemplate_DW.MovingMinimum_pnaevvf);
  }
}

/* Model terminate function */
void MicroMouseTemplate_terminate(void)
{
  uint16_T mode;

  /* Terminate for MATLABSystem: '<S15>/Analog to Digital Converter' */
  if (!MicroMouseTemplate_DW.obj.matlabCodegenIsDeleted) {
    MicroMouseTemplate_DW.obj.matlabCodegenIsDeleted = true;
    if ((MicroMouseTemplate_DW.obj.isInitialized == 1) &&
        MicroMouseTemplate_DW.obj.isSetupComplete) {
      mode = ADC_DMA_INTERRUPT_MODE;
      ADC_Handle_Deinit(MicroMouseTemplate_DW.obj.ADCHandle, mode, 1);
    }
  }

  /* End of Terminate for MATLABSystem: '<S15>/Analog to Digital Converter' */

  /* Terminate for Chart: '<Root>/Chart' incorporates:
   *  SubSystem: '<S3>/MainChart.ShowDetections.showDetections'
   */
  MicroMouse_MovingMaximum_o_Term(&MicroMouseTemplate_DW.MovingMaximum_jncvpnv);
  MicroMouse_MovingMinimum_a_Term(&MicroMouseTemplate_DW.MovingMinimum_jncvpnv);
  MicroMouse_MovingMaximum_g_Term(&MicroMouseTemplate_DW.MovingMaximum_jncv);
  MicroMouse_MovingMinimum_a_Term(&MicroMouseTemplate_DW.MovingMinimum1_j);
  MicroMouse_MovingMinimum_a_Term(&MicroMouseTemplate_DW.MovingMinimum_jncv);
  MicroMouse_MovingMaximum_o_Term(&MicroMouseTemplate_DW.MovingMaximum_jn);
  MicroMouse_MovingMinimum_a_Term(&MicroMouseTemplate_DW.MovingMinimum_jn);
  MicroMouse_MovingMaximum_o_Term(&MicroMouseTemplate_DW.MovingMaximum_jncvpnvp);
  MicroMouse_MovingMinimum_a_Term(&MicroMouseTemplate_DW.MovingMinimum_jncvpnvp);
  MicroMouse_MovingMaximum_o_Term(&MicroMouseTemplate_DW.MovingMaximum_jncvp);
  MicroMouse_MovingMinimum_a_Term(&MicroMouseTemplate_DW.MovingMinimum_jncvp);
  MicroMouse_MovingMaximum_o_Term(&MicroMouseTemplate_DW.MovingMaximum_j);
  MicroMouse_MovingMinimum_a_Term(&MicroMouseTemplate_DW.MovingMinimum_j);
  MicroMouse_MovingMaximum_g_Term(&MicroMouseTemplate_DW.MovingMaximum_jnc);
  MicroMouse_MovingMinimum_a_Term(&MicroMouseTemplate_DW.MovingMinimum1);
  MicroMouse_MovingMinimum_a_Term(&MicroMouseTemplate_DW.MovingMinimum_jnc);
  MicroMouse_MovingMaximum_o_Term(&MicroMouseTemplate_DW.MovingMaximum_jncvpn);
  MicroMouse_MovingMinimum_a_Term(&MicroMouseTemplate_DW.MovingMinimum_jncvpn);
  MicroMouseTe_MovingMaximum_Term(&MicroMouseTemplate_DW.MovingMaximum);
  MicroMouseT_MovingMaximum1_Term(&MicroMouseTemplate_DW.MovingMaximum1);
  MicroMouseT_MovingMinimum2_Term(&MicroMouseTemplate_DW.MovingMinimum2);
  MicroMouseTe_MovingMaximum_Term(&MicroMouseTemplate_DW.MovingMaximum_p);
  MicroMouseTe_MovingMaximum_Term(&MicroMouseTemplate_DW.MovingMaximum_pn);
  MicroMouseTe_MovingMaximum_Term(&MicroMouseTemplate_DW.MovingMaximum_pna);
  MicroMouseTe_MovingMaximum_Term(&MicroMouseTemplate_DW.MovingMaximum_pnae);
  MicroMouseT_MovingMaximum1_Term(&MicroMouseTemplate_DW.MovingMaximum1_p);
  MicroMouseT_MovingMinimum2_Term(&MicroMouseTemplate_DW.MovingMinimum2_p);
  MicroMouseTe_MovingMaximum_Term(&MicroMouseTemplate_DW.MovingMaximum_pnaev);
  MicroMouseTe_MovingMinimum_Term(&MicroMouseTemplate_DW.MovingMinimum);
  MicroMouseTe_MovingMinimum_Term(&MicroMouseTemplate_DW.MovingMinimum_p);
  MicroMouseTe_MovingMinimum_Term(&MicroMouseTemplate_DW.MovingMinimum_pn);
  MicroMouseTe_MovingMinimum_Term(&MicroMouseTemplate_DW.MovingMinimum_pna);
  MicroMouseTe_MovingMinimum_Term(&MicroMouseTemplate_DW.MovingMinimum_pnae);
  MicroMouseTe_MovingMinimum_Term(&MicroMouseTemplate_DW.MovingMinimum_pnaev);
  MicroMouseTe_MovingMinimum_Term(&MicroMouseTemplate_DW.MovingMinimum_pnaevv);
  MicroMouseTe_MovingMinimum_Term(&MicroMouseTemplate_DW.MovingMinimum_pnaevvf);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
