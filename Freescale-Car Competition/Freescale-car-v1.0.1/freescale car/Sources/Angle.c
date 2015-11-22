#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Common.h"
#include "ATD.h"
#include "Angle.h"
#include "PLL.h"
#include "SCI.h"
#include "PWM.h"

unsigned int AD_Gyro[20];    //陀螺仪20次采集值
unsigned int AD_Z[20];       //加速度计20次采集值

unsigned int Acce_z;        //加速度计Z轴AD采集值
unsigned int Gyro_hori;     //陀螺仪水平轴AD采集值

float GravityAngle;         //加速度计得出的倾角
float GyroAngleSpeed;       //陀螺仪得出的角速度
float GyroIntegarl;         //对角速度的积分值
float LeftMotorOut;
float RightMotorOut;

float CarAngle;             //综合得出的倾角

float AngleControlOut;

//速度控制函数变量和常量
float fCarSpeed = 0;		        // Car Speed = (nLeftMotorSpeedCount + nRightMotorSpeedCount) / 2;
int   nLeftMotorPulseSigma = 0, nRightMotorPulseSigma = 0;//累加值，为速度控制
float fSpeedControlOutOld = 0, fSpeedControlOutNew = 0,fSpeedControlOut=0;
float fSpeedControlIntegral = 0;			// Keep the Speed Control Integral value
int   nSpeedControlFlag = 0;
int   nSpeedControlPeriod = 0;

//速度控制函数
float  fSpeedControlOut;
/*************************************************************/
/*                       模块AD采样值获取                    */
/*************************************************************/
void CarVoltage_get(void) 
{
  int i;
  for(i=0;i<20;i++)
  {
    AD_Z[i]=AD_once(Acce_z_channel);
    //SCI0_send(AD_Z[i]);
  }
  for(i=0;i<20;i++) 
  {
    AD_Gyro[i]=AD_once(Gyro_hori_channel);
  }
  Acce_z = AD_ave(AD_Z);
  //SCI0_send(Acce_z);
  Gyro_hori = AD_ave(AD_Gyro);
  //SCI0_send(Gyro_hori);
}

/*************************************************************/
/*                         小车倾角计算                      */
/*************************************************************/
void AngleCalculate(void) {
  
  int GravityAngle_Voltage;   
  int GyroAngleSpeed_Voltage; 

  GravityAngle_Voltage = (Acce_z - Acce_Z_OFFSET); 
  GyroAngleSpeed_Voltage = (Gyro_hori - Gyro_Hori_OFFSET);  

  GravityAngle = -(GravityAngle_Voltage * Gravity_Angle_RATIO / 1000);
  //计算出加速计得出的角度
  
  GyroAngleSpeed = GyroAngleSpeed_Voltage * Gyro_Angle_RATIO / 100;
  GyroIntegarl += GyroAngleSpeed * dt;
  //对陀螺仪的角速度积分
  
  Kalman_Filter(GravityAngle,GyroAngleSpeed);
  
 

}

  
/*************************************************************/
/*                       卡尔曼滤波函数                      */
/*************************************************************/
void Kalman_Filter(float angle_m,float gyro_m)
{
  //angle_m 为重力加速度计得出的角度，单位是度
  //gyro_m  为陀螺仪得到的角速度，单位是度每秒
  
  static const float Q_angle = 0.001;
  static const float Q_gyro  = 0.003;
  static const float R_angle = 0.05; //原来是300
  //static const float      dt = 0.005; //在common.h中定义
  //注意：dt的取值为kalman滤波器采样时间
  //山东大学：R_angle = 0.001;Q_angle = 0.001;Q_gyro = 0.0015;
  
  static float P[2][2] = { { 1,0 }, { 0,1 } };
  static float Pdot[4] = { 0,0,0,0 };
  static const char C_0 = 1;
  static float q_bias,angle_err,PCt_0,PCt_1,E,K_0,K_1,t_0,t_1;
  
  CarAngle += (gyro_m - q_bias) * dt;     //先验估计
  
  Pdot[0] = Q_angle - P[0][1] - P[1][0];  //Pk-'先验估计误差协方差的微分
  Pdot[1] = -P[1][1];
  Pdot[2] = -P[1][1];
  Pdot[3] = Q_gyro;                       
  
  P[0][0] += Pdot[0] * dt;  //Pk- 先验估计误差协方差微分的积分 = 先验估计误差协方差
  P[0][1] += Pdot[1] * dt;
  P[1][0] += Pdot[2] * dt;
  P[1][1] += Pdot[3] * dt;
  
  angle_err = angle_m - CarAngle; //zk- 先验估计
  
  PCt_0 = C_0 * P[0][0];
  PCt_1 = C_0 * P[1][0];
  
  E = (R_angle + C_0 * PCt_0);
  
  K_0 = PCt_0 / E;
  K_1 = PCt_1 / E;
  
  t_0 = PCt_0;
  t_1 = C_0 * P[0][1];
  
  P[0][0] -= K_0 * t_0;    //后验估计误差协方差
  P[0][1] -= K_0 * t_1;
  P[1][0] -= K_1 * t_0;
  P[1][1] -= K_1 * t_1;
  
  CarAngle += K_0 * angle_err;  //后验估计
  q_bias   += K_1 * angle_err;  //后验估计
  GyroAngleSpeed = gyro_m - q_bias;  //输出值(后验估计)的微分 = 角速度
  
  
}

/*************************************************************/
/*                       清华方案倾角计算                    */
/*************************************************************/
void Calculate(void) {
  
  float deltavalue;
  int GravityAngle_Voltage;   
  int GyroAngleSpeed_Voltage; 

  GravityAngle_Voltage = (Acce_z - Acce_Z_OFFSET); 
  GyroAngleSpeed_Voltage = (Gyro_hori - Gyro_Hori_OFFSET);  

  GravityAngle = -(GravityAngle_Voltage * Gravity_Angle_RATIO / 1000);
  //计算出加速计得出的角度

  GyroAngleSpeed = GyroAngleSpeed_Voltage * Gyro_Angle_RATIO / 100;

  CarAngle = GyroIntegarl;

  deltavalue = (GravityAngle - CarAngle)/Ta;

  GyroIntegarl += (GyroAngleSpeed + deltavalue) * dt;

}

/*************************************************************/
/*                 小车角度控制使保持直立状态                */
/*************************************************************/
void Angle_Control(void) {
   
  float value;
  
  value = (Car_Angle_Set - CarAngle) * Angle_Control_P 
        + (Car_Angle_Speed_Set - GyroAngleSpeed) * Angle_Control_D;

  if(value > Angle_Control_OUT_MAX)
     value = Angle_Control_OUT_MAX;
  else if(value < Angle_Control_OUT_MIN)
     value = Angle_Control_OUT_MIN;

  AngleControlOut = value;

}

/**************************************************************
函 数 名 :  GetMotorPulse
功能描述 :  读取编码器脉冲值处理函数
输入参数 :  无
输出参数 :  无
返 回 值 :  无
**************************************************************/
void GetMotorPulse(void) 
{
    //将读取的数据赋值给全局变量，单位电机每秒转动的圈数 round/second	
	int LeftMotorPulse = 0, RightMotorPulse = 0,jishu = PORTA;
	if(PITTF_PTF0 == 1)
    PITTF_PTF0 = 1; 
	LeftMotorPulse  = jishu;
	RightMotorPulse = PACNT;
	PACNT = 0;
  PTT_PTT1=1;
    asm("NOP");
    asm("NOP");
    PTT_PTT1=1;
    PTT_PTT1=0;
    
	//根据输出的电压正负将读取的编码器的数值转换为相应的速度
	if(!MOTOR_LEFT_SPEED_POSITIVE)
	{
	    LeftMotorPulse = -LeftMotorPulse;
	}
	if(!MOTOR_RIGHT_SPEED_POSITIVE)
	{
	    RightMotorPulse = -RightMotorPulse;
	}	
	//编码器读数累加，在速度调整函数中将其值读出处理并清零	
	nLeftMotorPulseSigma += LeftMotorPulse;
	nRightMotorPulseSigma += RightMotorPulse;
}
/**************************************************************
函 数 名 :  SpeedControl
功能描述 :  速度控制函数
输入参数 :  无
输出参数 :  无
返 回 值 :  无
**************************************************************/
void SpeedControl(void) 
{
	float fP = 0, fDelta = 0;
	float fI = 0;
	//--------------------------------------------------------------------------
	fCarSpeed = (nLeftMotorPulseSigma + nRightMotorPulseSigma) / 2;
	nLeftMotorPulseSigma = nRightMotorPulseSigma = 0;
	fCarSpeed *= CAR_SPEED_CONSTANT;
	
	
	//--------------------------------------------------------------------------	
/*	if(nSpeedControlFlag == 0) 
	{
		fSpeedControlOutOld = fSpeedControlOutNew = fSpeedControlOut = 0;
		fSpeedControlIntegral = 0;
		return;
	}*/
		
	//PID调节
	fDelta = CAR_SPEED_SET;
	fDelta -= fCarSpeed;
	
	fP = fDelta * SPEED_CONTROL_P;
	fI = fDelta * SPEED_CONTROL_I;
	fSpeedControlIntegral += fI;
		
	//限幅输出
	/*if(g_fSpeedControlIntegral > SPEED_CONTROL_OUT_MAX)
	{	
		g_fSpeedControlIntegral = SPEED_CONTROL_OUT_MAX;
	}
	if(g_fSpeedControlIntegral < SPEED_CONTROL_OUT_MIN) 
	{ 	
		g_fSpeedControlIntegral = SPEED_CONTROL_OUT_MIN;
	}*/
	fSpeedControlOutOld = fSpeedControlOutNew;

	fSpeedControlOutNew = fP + fSpeedControlIntegral;
	
}


/**************************************************************
函 数 名 :  SpeedControlOutput
功能描述 :  速度输出平滑函数
输入参数 :  无
输出参数 :  无
返 回 值 :  无
**************************************************************/   
void SpeedControlOutput(void) 
{
	float fValue = 0;
	fValue = fSpeedControlOutNew - fSpeedControlOutOld;
	fSpeedControlOut = fValue * (nSpeedControlPeriod + 1) / SPEED_CONTROL_PERIOD + fSpeedControlOutOld;	
}
/*************************************************************/
/*                 电机输出函数                              */
/*************************************************************/
void MotorOutput(void) 
{
   float Left,Right;
   Left=AngleControlOut-fSpeedControlOut;
   Right=AngleControlOut-fSpeedControlOut;
   LeftMotorOut = Left;
   RightMotorOut = Right;
   SetMotorVoltage(LeftMotorOut,RightMotorOut);
  
} 


/*************************************************************/
/*                 电机计算函数                              */
/*************************************************************/
/*void MotorSpeedOut(void) 
{
  float LeftVal,RightVal;
  
  LeftVal = LeftMotorOut;
  RightVal = RightMotorOut;
  
  if(LeftVal>0)
  LeftVal += MOTOR_OUT_DEAD_VAL;
  else if (LeftVal<0)
  LeftVal -= MOTOR_OUT_DEAD_VAL;
  
  if(RightVal>0)
  RightVal += MOTOR_OUT_DEAD_VAL;
  else if (RightVal<0)
  RightVal -= MOTOR_OUT_DEAD_VAL;
  
  if(LeftVal>MOTOR_OUT_MAX)
  LeftVal=MOTOR_OUT_MAX;
  if(LeftVal<MOTOR_OUT_MIN)
  LeftVal=MOTOR_OUT_MIN;
  if(RightVal>MOTOR_OUT_MAX)
  RightVal=MOTOR_OUT_MAX;
  if(RightVal<MOTOR_OUT_MIN)
  RightVal=MOTOR_OUT_MIN;
  
  SetMotorVoltage(LeftVal,RightVal);
}*/

/*************************************************************/
/*                 电机计算函数                              */
/*************************************************************/
void SetMotorVoltage(float LeftVoltage,float RightVoltage) { 
  if(LeftVoltage > 0) { 
    PWMDTY01= 0;
    
    PWMDTY23=LeftVoltage;
    }
     else { 
     PWMDTY23=0;
  
     LeftVoltage = -LeftVoltage;
      PWMDTY01=LeftVoltage;
       } 
    if(RightVoltage > 0)
    { 
     PWMDTY45=RightVoltage;
     
     PWMDTY67=0; 
          } 
    else { 
     PWMDTY45=0 ;
     
     RightVoltage =-RightVoltage; 
     PWMDTY67=RightVoltage;
      
           }
} 


