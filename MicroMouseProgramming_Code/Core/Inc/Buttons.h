//********************************************************************
//*                          Micro Mouse                             *
//*                          Button Library                          *
//*==================================================================*
//* @author:    Jesse Jabez Arendse                                  *
//* @date:      09-06-2025                                           *
//*==================================================================*
//*                                                                  *
//* Description:                                                     *
//* This header file provides an interface for managing buttons on   *
//* the Micro Mouse robot. It includes initialization, state         *
//* refreshing, and handling button presses for user interaction.    *
//*                                                                  *
//********************************************************************

#ifndef BUTTONS_H
#define BUTTONS_H

#include "stm32l4xx.h"
#include "main.h"

//====================================================================
// GLOBAL CONSTANTS
//====================================================================
#define BUTTON_DEBOUNCE_DELAY_MS 50 // Debounce delay in milliseconds
#define BUTTON_PRESSED_STATE     1  // State indicating button is pressed
#define BUTTON_RELEASED_STATE    0  // State indicating button is released
//====================================================================

//====================================================================
// FUNCTION DECLARATIONS
//====================================================================
void initSW();               // Initialize the buttons
void refreshSWValues();      // Refresh button states
//====================================================================

#endif

//********************************************************************
// END OF PROGRAM
//********************************************************************