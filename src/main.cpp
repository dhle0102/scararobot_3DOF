#include <Arduino.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

// declare stepper motor x, y, z
#define En 8
#define Step_x 2
#define Dir_x 5
#define Step_y 3
#define Dir_y 6
#define Step_z 4
#define Dir_z 7
#define motorInterfaceType 1
#define speed 800
#define accel 300
#define c_speed 500
#define microStep 10


AccelStepper StepperX =  AccelStepper(1,Step_x,Dir_x); // version with L298N
AccelStepper StepperY = AccelStepper(1,Step_y, Dir_y);
AccelStepper StepperZ = AccelStepper(1,Step_z,Dir_z);

MultiStepper multi;
long position[2] = {0,0};
// declare end x, y, z
#define end_x 9
#define end_y 10
#define end_z 11

// function 
void runCase(uint8_t value);

// array 
long position_X[9] = {-5000,-7300,-10100,-7100,-8650,-10700,-9500,-10200,-11650};
long position_Y[9] = {-450,-290,-420,-1100,-980,-1100,-1900,-1800,-1800};
long position_Z[9] = {-2500,-2500,-2500,-2500,-2500,-2500,-2500,-2500,-2500};
long signX[6] = {-100,200,0,-300,0,0};
long signY[6] = {-100,200,0,200,0,0};

void setup() {
 Serial.begin(9600);

  // declare limit switch x, y, z
  pinMode(end_x, INPUT_PULLUP);
  pinMode(end_y, INPUT_PULLUP);
  pinMode(end_z,INPUT_PULLUP);
  pinMode(En, OUTPUT);
  // set driver x, y, z 
  digitalWrite(En, LOW);

  // define stepper x, y, z
  pinMode(Step_x, OUTPUT);
  pinMode(Dir_x, OUTPUT);
  pinMode(Step_y, OUTPUT);
  pinMode(Dir_y, OUTPUT);
  pinMode(Step_z, OUTPUT);
  pinMode(Dir_z,OUTPUT);
  StepperX.setMaxSpeed(speed);
  StepperX.setAcceleration(accel);
  StepperY.setMaxSpeed(speed);
  StepperY.setAcceleration(accel);
  StepperZ.setMaxSpeed(speed);
  StepperZ.setAcceleration(accel);

  // Multi stepper motor
  multi.addStepper(StepperX);
  multi.addStepper(StepperY);

  // setup home 
  setupHome();
 
  StepperZ.moveTo(position_Z[0]);
  StepperZ.runToPosition();

  StepperX.setCurrentPosition(0);
  StepperY.setCurrentPosition(0);
  StepperZ.setCurrentPosition(0);
  //---------------------------------------

  Serial.println("Nhap vi tri o di den :");
}

void loop() {
  
  if(Serial.available()){
    char valueRead;
    valueRead= Serial.read();
    switch (valueRead)
    {
    case '1':
      runCase(1); 
    break;
    case '2':
     runCase(2);
    break;
    case '3':
      runCase(3);
    break;
    case '4':
      runCase(4);
    break;
    case '5':
      runCase(5);
    break;
    case '6':
      runCase(6);
    break;
    case '7':
      runCase(7);
    break;
    case '8':
      runCase(8);
    break;
    case '9':
      runCase(9);
    break;
    default:
      Serial.println("Xin hay nhap lai");
      Serial.println("Nhap vi tri o di den:");
      break;
    }
  }
}

void draw(uint8_t sign, uint8_t value){
  StepperZ.moveTo(0);
  StepperZ.runToPosition();
  // write sign X
  for(byte i = 0; i < 6; i++){
    position[0] = position_X[value - 1] + signX[i];
    position[1] = position_Y[value - 1] + signY[i];
    multi.moveTo(position);
    multi.runSpeedToPosition();
  };
  StepperZ.moveTo(position_Z[value - 1]);
  StepperZ.runToPosition();
  Serial.print("end draw");


}

void runCase(uint8_t value)
{
  Serial.print("the value before run: ");
  Serial.print(" ");Serial.print(StepperX.currentPosition());
  Serial.print(" ");Serial.print(StepperY.currentPosition());
  Serial.print(" ");Serial.print(StepperZ.currentPosition());
  Serial.println();
  // run v1  
  //StepperX.moveTo(position_X[value - 1]);
  //StepperX.runToPosition();
  //StepperY.moveTo(position_Y[value - 1]);
  //StepperY.runToPosition();
  
  // run v2
  digitalWrite(En, LOW);
  position[0] = long(position_X[value - 1]);
  position[1] = position_Y[value - 1];
  multi.moveTo(position);
  multi.runSpeedToPosition();
  draw(1,value);

  // home
  digitalWrite(En,LOW);
  position[0] = 0;
  position[1] = 0;
  multi.moveTo(position);
  multi.runSpeedToPosition();

  Serial.print("the value after run: ");
  Serial.print(" ");Serial.print(StepperX.currentPosition());
  Serial.print(" ");Serial.print(StepperY.currentPosition());
  Serial.print(" ");Serial.print(StepperZ.currentPosition());
  Serial.println();

  Serial.println("Nhap vi tri o di den :");
}


// set home for scara
void setupHome(){
   // setup Serial 
  Serial.println("Set home for Scara robot 3DOF: ");

   // set up home state X
  Serial.print("start home X");
  while (digitalRead(end_x))
  {
    StepperX.setSpeed(c_speed);
    StepperX.runSpeed();
    delay(microStep);
  };
  Serial.print("=>");
  Serial.println("end home X");
  delay(1000);
  
  // set up home state y 
  Serial.print("start home Y");
  while (digitalRead(end_y))
  {
    StepperY.setSpeed(c_speed);
    StepperY.runSpeed();
    delay(microStep);
  }
  Serial.print("=>");
  Serial.println("end home Y");
  delay(1000);

  // set up home state Z
  Serial.print("start home Z");
  while (digitalRead(end_z))
  {
    StepperZ.setSpeed(c_speed);
    StepperZ.runSpeed();
    delay(microStep);
  }
  Serial.print("=>");
  Serial.println("end home Z");
  delay(1000);

}