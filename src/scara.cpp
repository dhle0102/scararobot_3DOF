#include <Arduino.h>
#include "scara.h"

float L1 = 130.0;
float L2 = 130.0;
void forward_kinematics(float *theta, float *pos)
{
  pos[X_AXIS] = L1 * cosf(RADIANS(theta[X_AXIS])) + L2 * cosf(RADIANS(theta[X_AXIS] + theta[Y_AXIS]));
  pos[Y_AXIS] = L1 * sinf(RADIANS(theta[X_AXIS])) + L2 * sinf(RADIANS(theta[X_AXIS] + theta[Y_AXIS]));
}

void inverse_kinematics(float *pos, float * theta)
{
  if ((pos[X_AXIS] == 0) && (pos[Y_AXIS] == 0))
  {
    theta[X_AXIS] = 0;
    theta[Y_AXIS] = 180;
    return;
}

  double scara_c2 = 0.0f;
  double scara_s2 = 0.0f;
  double scara_k1 = 0.0f;
  double scara_k2 = 0.0f;

  scara_c2 = (sq(pos[X_AXIS]) + sq(pos[Y_AXIS]) - sq(L1) - sq(L2)) / (2 * L1 * L2);
  scara_s2 = sqrtf(1 - sq(scara_c2));
  scara_k1 = L1 + L2 * scara_c2;
  scara_k2 = L2 * scara_s2;
  theta[X_AXIS] = atanf(pos[Y_AXIS] / pos[X_AXIS]) - atanf(scara_k2 / scara_k1);
  theta[Y_AXIS] = atanf(scara_s2 / scara_c2) + PI;
  if (pos[X_AXIS] < 0)
  {
    if (pos[Y_AXIS] > 0)
    {
      theta[X_AXIS] = theta[X_AXIS] + PI;
    }
    else
    {
      theta[X_AXIS] = theta[X_AXIS] - PI;
    }
  }
  for (int i = 0; i < N_AXIS; i++)
  {
    theta[i] = DEGREES(theta[i]);
  }
}

void scara_offset(float *offset_input,float *offset_output)
{
  offset_output[X_AXIS] = offset_input[X_AXIS];
  offset_output[Y_AXIS] = offset_input[Y_AXIS] + offset_input[X_AXIS];
}

void scara_test(float *input, float *output, bool mode)
{
  Serial.print("input[0] :");
  Serial.println(input[0]);
  Serial.print("input[1] :");
  Serial.println(input[1]);

  if (FORWARD)    //mode =0: forward; mode=1: inverse
  {
    Serial.println("FORWARD KINEMATICS transforming...");
    forward_kinematics(input, output);
  }
  else
  {
    Serial.println("INVERSE KINEMATICS transforming...");
    inverse_kinematics(input, output);
    for (int i = 0; i < N_AXIS; i++)
    {
      output[i] = DEGREES(output[i]);
    }
  }
  Serial.print("output [0]:");
  Serial.println(output[0]);
  Serial.print("output[1]:");
  Serial.println(output[1]);
}
void scara_transfer(float *input, int current_coord)
{
  switch (current_coord)
  {
  case DESCARTES_COORD:
    input[0] = input[0] * 26.67;
    input[1] = input[1] * 26.67;
    break;
  case POLAR_COORD:
    Serial.println("POLAR not supported yet");
    break;
  default:
    break;
  }

}
