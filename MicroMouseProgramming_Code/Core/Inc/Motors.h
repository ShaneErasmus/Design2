//********************************************************************
//*                          Micro Mouse                             *
//*                          Motors Library                          *
//*==================================================================*
//* @author:    Jesse Jabez Arendse                                  *
//* @date:      24-10-2023                                           *
//*==================================================================*
//*                                                                  *
//* Description:                                                     *
//* This header file provides an interface for initializing and      *
//* refreshing motor control values for the Micro Mouse robot.       *
//* It includes functions for starting PWM and updating motor        *
//* speed and direction.                                             *
//*                                                                  *
//********************************************************************

#ifndef MOTORS_H
#define MOTORS_H

#include "stm32l4xx.h"
#include "main.h"

// Motor control variables
extern int8_t MOTOR_LS;
extern int8_t MOTOR_RS;

// Function declarations
void initMotors();
void refreshMotors();

#endif
