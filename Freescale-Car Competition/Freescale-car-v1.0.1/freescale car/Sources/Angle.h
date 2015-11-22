#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

void CarVoltage_get(void);
void AngleCalculate(void);
void Kalman_Filter(float angle_m,float gyro_m);
void Calculate(void);
void Angle_Control(void);
void GetMotorPulse(void);
void SpeedControl(void) ;
void SpeedControlOutput(void) ;
void MotorOutput(void);
//void MotorSpeedOut(void);
void SetMotorVoltage(float LeftVoltage,float RightVal);
