#include "motion.h"

AccelStepper stepper_X(AccelStepper::DRIVER, STEP_X, DIR_X);
AccelStepper stepper_Y(AccelStepper::DRIVER, STEP_Y, DIR_Y);
MultiStepper steppers;
void stepper_init(void)
{
  // Configure stepper X
  pinMode(STEP_EN, OUTPUT);
  stepper_X.setMaxSpeed(1000);
  stepper_X.setSpeed(700);
  stepper_X.setAcceleration(700);
  stepper_X.setPinsInverted(true, false, false);
  // Configure stepper Y
  stepper_Y.setMaxSpeed(1500);
  stepper_Y.setSpeed(500);
  stepper_Y.setAcceleration(5000);
  // Then give them to MultiStepper to manage
  steppers.addStepper(stepper_X);
  steppers.addStepper(stepper_Y);
  digitalWrite(STEP_EN, HIGH);
}
long stepper_getPos(int motor)
{
    if (motor)
        return stepper_Y.currentPosition();
    else
        return stepper_X.currentPosition();
}
void stepper_moveRelative(long *steps)
{
    digitalWrite(STEP_EN, LOW);
    steppers.moveTo(steps);
    steppers.runSpeedToPosition();
    digitalWrite(STEP_EN, HIGH);
}
void stepper_deltaStepCalc(float *target, float *current, float *delta_step)
{
    delta_step[0] = lround(target[0] - current[0]);
    delta_step[1] = lround(target[1] - current[1]);
    for (int i = 0; i < 2; i++)
    {
      if (delta_step[i] > 4800)
      {
        delta_step[i] = delta_step[i] - (2 * 4800);
      }
      else if (delta_step[i] < -4800)
      {
        delta_step[i] = delta_step[i] + (2 * 4800);
      }
    }
}
bool stepper_isRunning(void)
{
  if((stepper_X.distanceToGo()!=0)||(stepper_Y.distanceToGo()!=0))
  return true;
  else return false;
}
