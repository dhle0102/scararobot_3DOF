#include "cnc_shield_v3.h"
#include<Arduino.h>


// contructor function 
cnc_shield_v3::cnc_shield_v3(){
    // declare pinout EN
    pinMode(stepEN,OUTPUT);
    // declare pinout step
    pinMode(step_x,OUTPUT);
    pinMode(step_y,OUTPUT);
    pinMode(step_z,OUTPUT);
    pinMode(step_a,OUTPUT);
    // declare pinout dir
    pinMode(dir_x,OUTPUT);
    pinMode(dir_y,OUTPUT);
    pinMode(dir_z,OUTPUT);
    pinMode(dir_a,OUTPUT);
    // declare pinout input pullup 
    pinMode(limit_X,INPUT_PULLUP);
    pinMode(limit_Z,INPUT_PULLUP);
    pinMode(limit_Y,INPUT_PULLUP);
    //
};

// set step motor 
void cnc_shield_v3::set(uint8_t microStepX,uint8_t microStepY,uint8_t mircoStepZ){
    // declare stepper 
    extern AccelStepper stepperX;


    // multi stepper

}
