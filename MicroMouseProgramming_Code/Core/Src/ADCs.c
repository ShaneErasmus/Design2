//********************************************************************
//*                          Micro Mouse                             *
//*                          ADC Library                             *
//*==================================================================*
//* @author:    Jesse Jabez Arendse                                  *
//* @date:      24-10-2023                                           *
//*==================================================================*
//*                                                                  *
//* Description:                                                     *
//* This source file implements functions for initializing and       *
//* refreshing ADC values for various sensors on the Micro Mouse     *
//* robot. It includes functions for starting DMA and updating       *
//* sensor values.                                                   *
//*                                                                  *
//********************************************************************

#include "ADCs.h"

extern ADC_HandleTypeDef hadc1; 
extern DMA_HandleTypeDef hdma_adc1;

// ADC variables
uint16_t V_BATT = 0;
uint16_t V_PHOTO_DOWN_LS = 0;
uint16_t V_PHOTO_DOWN_RS = 0;
uint16_t V_PHOTO_MOT_LS = 0;
uint16_t V_PHOTO_MOT_RS = 0;

// ADC array for DMA
uint16_t ADCs[5] = {0, 0, 0, 0, 0};

void initADCs() {
    // Start ADC DMA
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *) ADCs, 5); // start ADC for battery voltage, MOT_RS , DOWN_RS , DOWN_LS , MOT_LS
}

void refreshADCs() {
    // Assign values from ADC array to variables
    V_BATT = ADCs[0];
    V_PHOTO_MOT_RS = ADCs[1];
    V_PHOTO_DOWN_RS = ADCs[2];
    V_PHOTO_DOWN_LS = ADCs[3];
    V_PHOTO_MOT_LS = ADCs[4];
}
