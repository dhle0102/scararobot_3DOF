
/**
 * scara.h - SCARA-specific functions
 */
#ifndef SCARA_h
#define SCARA_h

#define CHECK_SCARA_ENABLE 1

#define RADIANS(d) ((d)*(float)M_PI/180.0f)
#define DEGREES(r) ((r)*180.0f/(float)M_PI)
#define DISTANCE(x,y) (sqrt(x*x+y*y))
extern float L1;
extern float L2;
#define X_AXIS 0
#define Y_AXIS 1
#define N_AXIS 2

typedef enum scara_mode
{
  FORWARD,
  INVERSE
} scara_mode_t;
typedef enum  scara_coord
{
  DESCARTES_COORD,
  SCARA_COORD,
  POLAR_COORD
} scara_coord_t;


/**
 * \brief			 Forward_kinematics : (theta1, theta2) -> (x, y)
 *
 * \param[in]        theta[2]  : (theta1, theta2)
 * \param[in]        position  : (x, y)
 *
 * \retval			 void
 *
 */
void forward_kinematics(float *theta, float *pos);

/**
 * \brief			 Inverse_kinematics : (x, y) -> (theta1, theta2)
 *
 * \param[in]        position  : (x, y) -> (float theta1, float theta2)
 * \param[in]        theta[2]  : (theta1, theta2)
 *
 * \retval			 void
 *
 */
void inverse_kinematics(float *theta,float *pos);
void scara_offset(float *offset_input,float *offset_output);
void scara_test(float *input, float *output, bool mode);
void scara_transfer(float *input, int target_coord);
#endif