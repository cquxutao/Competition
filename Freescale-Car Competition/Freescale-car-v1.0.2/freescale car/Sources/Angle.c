#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Common.h"
#include "ATD.h"
#include "Angle.h"
#include "PLL.h"
#include "SCI.h"
#include "PWM.h"

unsigned int AD_Gyro[20];    //������20�βɼ�ֵ
unsigned int AD_Z[20];       //���ٶȼ�20�βɼ�ֵ

unsigned int Acce_z;        //���ٶȼ�Z��AD�ɼ�ֵ
unsigned int Gyro_hori;     //������ˮƽ��AD�ɼ�ֵ

float GravityAngle;         //���ٶȼƵó������
float GyroAngleSpeed;       //�����ǵó��Ľ��ٶ�
float GyroIntegarl;         //�Խ��ٶȵĻ���ֵ
float LeftMotorOut;
float RightMotorOut;

float CarAngle;             //�ۺϵó������

float AngleControlOut;

//�ٶȿ��ƺ��������ͳ���
float fCarSpeed = 0;		        // Car Speed = (nLeftMotorSpeedCount + nRightMotorSpeedCount) / 2;
int   nLeftMotorPulseSigma = 0, nRightMotorPulseSigma = 0;//�ۼ�ֵ��Ϊ�ٶȿ���
float fSpeedControlOutOld = 0, fSpeedControlOutNew = 0,fSpeedControlOut=0;
float fSpeedControlIntegral = 0;			// Keep the Speed Control Integral value
int   nSpeedControlFlag = 0;
int   nSpeedControlPeriod = 0;

//�ٶȿ��ƺ���
float  fSpeedControlOut;
/*************************************************************/
/*                       ģ��AD����ֵ��ȡ                    */
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
/*                         С����Ǽ���                      */
/*************************************************************/
void AngleCalculate(void) {
  
  int GravityAngle_Voltage;   
  int GyroAngleSpeed_Voltage; 

  GravityAngle_Voltage = (Acce_z - Acce_Z_OFFSET); 
  GyroAngleSpeed_Voltage = (Gyro_hori - Gyro_Hori_OFFSET);  

  GravityAngle = -(GravityAngle_Voltage * Gravity_Angle_RATIO / 1000);
  //��������ټƵó��ĽǶ�
  
  GyroAngleSpeed = GyroAngleSpeed_Voltage * Gyro_Angle_RATIO / 100;
  GyroIntegarl += GyroAngleSpeed * dt;
  //�������ǵĽ��ٶȻ���
  
  Kalman_Filter(GravityAngle,GyroAngleSpeed);
  
 

}

  
/*************************************************************/
/*                       �������˲�����                      */
/*************************************************************/
void Kalman_Filter(float angle_m,float gyro_m)
{
  //angle_m Ϊ�������ٶȼƵó��ĽǶȣ���λ�Ƕ�
  //gyro_m  Ϊ�����ǵõ��Ľ��ٶȣ���λ�Ƕ�ÿ��
  
  static const float Q_angle = 0.001;
  static const float Q_gyro  = 0.003;
  static const float R_angle = 0.05; //ԭ����300
  //static const float      dt = 0.005; //��common.h�ж���
  //ע�⣺dt��ȡֵΪkalman�˲�������ʱ��
  //ɽ����ѧ��R_angle = 0.001;Q_angle = 0.001;Q_gyro = 0.0015;
  
  static float P[2][2] = { { 1,0 }, { 0,1 } };
  static float Pdot[4] = { 0,0,0,0 };
  static const char C_0 = 1;
  static float q_bias,angle_err,PCt_0,PCt_1,E,K_0,K_1,t_0,t_1;
  
  CarAngle += (gyro_m - q_bias) * dt;     //�������
  
  Pdot[0] = Q_angle - P[0][1] - P[1][0];  //Pk-'����������Э�����΢��
  Pdot[1] = -P[1][1];
  Pdot[2] = -P[1][1];
  Pdot[3] = Q_gyro;                       
  
  P[0][0] += Pdot[0] * dt;  //Pk- ����������Э����΢�ֵĻ��� = ����������Э����
  P[0][1] += Pdot[1] * dt;
  P[1][0] += Pdot[2] * dt;
  P[1][1] += Pdot[3] * dt;
  
  angle_err = angle_m - CarAngle; //zk- �������
  
  PCt_0 = C_0 * P[0][0];
  PCt_1 = C_0 * P[1][0];
  
  E = (R_angle + C_0 * PCt_0);
  
  K_0 = PCt_0 / E;
  K_1 = PCt_1 / E;
  
  t_0 = PCt_0;
  t_1 = C_0 * P[0][1];
  
  P[0][0] -= K_0 * t_0;    //����������Э����
  P[0][1] -= K_0 * t_1;
  P[1][0] -= K_1 * t_0;
  P[1][1] -= K_1 * t_1;
  
  CarAngle += K_0 * angle_err;  //�������
  q_bias   += K_1 * angle_err;  //�������
  GyroAngleSpeed = gyro_m - q_bias;  //���ֵ(�������)��΢�� = ���ٶ�
  
  
}

/*************************************************************/
/*                       �廪������Ǽ���                    */
/*************************************************************/
void Calculate(void) {
  
  float deltavalue;
  int GravityAngle_Voltage;   
  int GyroAngleSpeed_Voltage; 

  GravityAngle_Voltage = (Acce_z - Acce_Z_OFFSET); 
  GyroAngleSpeed_Voltage = (Gyro_hori - Gyro_Hori_OFFSET);  

  GravityAngle = -(GravityAngle_Voltage * Gravity_Angle_RATIO / 1000);
  //��������ټƵó��ĽǶ�

  GyroAngleSpeed = GyroAngleSpeed_Voltage * Gyro_Angle_RATIO / 100;

  CarAngle = GyroIntegarl;

  deltavalue = (GravityAngle - CarAngle)/Ta;

  GyroIntegarl += (GyroAngleSpeed + deltavalue) * dt;

}

/*************************************************************/
/*                 С���Ƕȿ���ʹ����ֱ��״̬                */
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
�� �� �� :  GetMotorPulse
�������� :  ��ȡ����������ֵ������
������� :  ��
������� :  ��
�� �� ֵ :  ��
**************************************************************/
void GetMotorPulse(void) 
{
    //����ȡ�����ݸ�ֵ��ȫ�ֱ�������λ���ÿ��ת����Ȧ�� round/second	
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
    
	//��������ĵ�ѹ��������ȡ�ı���������ֵת��Ϊ��Ӧ���ٶ�
	if(!MOTOR_LEFT_SPEED_POSITIVE)
	{
	    LeftMotorPulse = -LeftMotorPulse;
	}
	if(!MOTOR_RIGHT_SPEED_POSITIVE)
	{
	    RightMotorPulse = -RightMotorPulse;
	}	
	//�����������ۼӣ����ٶȵ��������н���ֵ������������	
	nLeftMotorPulseSigma += LeftMotorPulse;
	nRightMotorPulseSigma += RightMotorPulse;
}
/**************************************************************
�� �� �� :  SpeedControl
�������� :  �ٶȿ��ƺ���
������� :  ��
������� :  ��
�� �� ֵ :  ��
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
		
	//PID����
	fDelta = CAR_SPEED_SET;
	fDelta -= fCarSpeed;
	
	fP = fDelta * SPEED_CONTROL_P;
	fI = fDelta * SPEED_CONTROL_I;
	fSpeedControlIntegral += fI;
		
	//�޷����
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
�� �� �� :  SpeedControlOutput
�������� :  �ٶ����ƽ������
������� :  ��
������� :  ��
�� �� ֵ :  ��
**************************************************************/   
void SpeedControlOutput(void) 
{
	float fValue = 0;
	fValue = fSpeedControlOutNew - fSpeedControlOutOld;
	fSpeedControlOut = fValue * (nSpeedControlPeriod + 1) / SPEED_CONTROL_PERIOD + fSpeedControlOutOld;	
}
/*************************************************************/
/*                 ����������                              */
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
/*                 ������㺯��                              */
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
/*                 ������㺯��                              */
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


