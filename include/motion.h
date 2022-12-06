#ifndef MOTION_H
#define MOTION_H

// Define library 
#include <Arduino.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include "scara.h"

#define X_AXIS 0
#define Y_AXIS 1

// define pin for CNC SHIELD V3 
//*********************************************************************************************
// define pin to enable for driver active 
#define stepEN 8

// define driver pin for stepper motor X
#define step_x 2
#define dir_x 5
#define microStep_x 1

// define driver pin for stepper motor Y
#define step_y 3
#define dir_y 6
#define mircoStep_y 1

// define driver pin for stepper motor Z 
#define step_z 4
#define dir_z 7
#define mircoStep_z 1

// define driver pin for stepper motor A (No check)
#define step_a 12
#define dir_a 13
#define mircoStep_a 1

// define limit pin X+/X- 
#define limit_X 9

// define limit pin Y+/Y-
#define limit_Y 10

// define limit pin Z+/Z-
#define limit_Z 1

//**********************************************************************************************

void stepper_init(void);
long stepper_getPos(int motor);
void stepper_moveRelative(long *steps);
void stepper_deltaStepCalc(float *target, float *current, float *delta_step);
bool stepper_isRunning(void);
void runX(long pwm);
#endif