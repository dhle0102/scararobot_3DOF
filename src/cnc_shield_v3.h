#ifndef CNC_SHIELD_V3_H
#define CNC_SHIELD_V3_H
#include<AccelStepper.h>
#include<MultiStepper.h>

// define number of Stepper used 
#define numberStepper 3

//declare function 
#ifndef UINT8_T_DECLARE
typedef unsigned char uint8_t;
#define UINT8_T_DECLARE
#endif

#ifndef UNIT16_T_DECLARE
typedef unsigned int uint16_t;
#define UINT16_T_DECLARE
#endif



// define pin 
//*********************************************************************************************
#define stepEN 8
// define step x
#define step_x 2
#define dir_x 5
#define microStep_x 1

// define step y 
#define step_y 3
#define dir_y 6
#define mircoStep_y 1

// define step z 
#define step_z 4
#define dir_z 7
#define mircoStep_z 1

// define step A
#define step_a 12
#define dir_a 13
#define mircoStep_a 1

// limit X+/X- 
#define limit_X 9

// limit Y+/Y-
#define limit_Y 10

// limit Z+/Z-
#define limit_Z 1

//*********************************************************************************************

class cnc_shield_v3
{
private:
    /* data */

    // multi stepper

public:
    // contructor function
    cnc_shield_v3();

    // function 
    void set(uint8_t microStepX = microStep_x,uint8_t microStepY = mircoStep_y,uint8_t mircoStepZ = mircoStep_z);
    void runX();
    void runY();
    void runZ(); 
};


#endif