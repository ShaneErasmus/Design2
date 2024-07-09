//********************************************************************
//*                            Micro Mouse                           *
//*                         ADC IR_LED Library                       *
//*==================================================================*
//* @author:    Jesse Jabez Arendse                                  *
//* @date:      04-07-2024                                           *
//*==================================================================*

#include "main.h"
#include "FancySampling.h"
#include "stdbool.h"


extern ADC_HandleTypeDef hadc1;
// extern ADC_HandleTypeDef hadc2;
extern uint16_t ADC1s[9];
extern uint16_t ADC2s[9];
extern uint16_t ADC_H[9];
extern uint16_t ADC_L[9];
extern TIM_HandleTypeDef htim4;

int numberOfConversions = 9;

void initADCs(){
    // HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC1s, 9);
    HAL_TIM_Base_Init(&htim4);
    HAL_TIM_Base_Start(&htim4);
}


bool counter = true;
void TIM4_IRQHandler(){
    HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin); // to test callback rate

    // do your own logic here
    if (counter){
        ADC_H[0] = ADC1s[0];
        ADC_H[7] = ADC1s[1];

        ADC_L[3] = ADC1s[3];
        ADC_L[4] = ADC1s[4];

        counter = false;
    }
    else{
        ADC_L[0] = ADC1s[0];
        ADC_L[7] = ADC1s[1];

        ADC_H[3] = ADC1s[3];
        ADC_H[4] = ADC1s[4];

        counter = true;
    }
    ADC_H[1] = ADC1s[1];
    ADC_H[2] = ADC1s[2];
    ADC_H[5] = ADC1s[5];
    ADC_H[6] = ADC1s[6];
    ADC_H[8] = ADC1s[8];

    ADC_L[1] = ADC1s[1];
    ADC_L[2] = ADC1s[2];
    ADC_L[5] = ADC1s[5];
    ADC_L[6] = ADC1s[6];
    ADC_L[8] = ADC1s[8];
}

