//********************************************************************
//*                          Micro Mouse                             *
//*                          LED Library                             *
//*==================================================================*
//* @author:    Jesse Jabez Arendse                                  *
//* @date:      24-10-2023                                           *
//*==================================================================*
//*                                                                  *
//* Description:                                                     *
//* This header file provides an interface for controlling LEDs      *
//* connected to GPIO pins PC13, PC14, and PC15 on the Micro Mouse   *
//* robot. It includes functions for initializing the LEDs and       *
//* refreshing their states based on an array.                       *
//*                                                                  *
//********************************************************************

#ifndef LEDS_H
#define LEDS_H

#include "stm32l4xx.h"
#include "main.h"

// LED array corresponding to PC13, PC14, PC15
extern uint8_t LED[3];

// Function declarations
void initLEDs();
void refreshLEDs();

#endif
