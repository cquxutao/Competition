#define  BUS_CLOCK		80000000	   //����Ƶ��
#define  OSC_CLOCK		16000000	   //����Ƶ��
#define  BAUD         9600         //���ڲ�����

#define  Acce_z_channel    2
#define  Gyro_hori_channel 0
#define  Gyro_vert_channel 1

#define  Acce_Z_OFFSET     1143  //*1875

#define  Gyro_Hori_OFFSET  1377 //*1172
#define  Gyro_Vert_OFFSET  1164

#define Gravity_Angle_RATIO  99.67   //94.7
//Gravity_Angle_RATIO = 90��/(Acce_Z_POS_45 - Acce_Z_NAG_45) = 0.09879 �Ŵ�1000��
#define Gyro_Angle_RATIO     35  //����ΪС�����ȷŴ�100��
#define Acce_Z_NAG_45        753    //* 753
//���ٶȼ���ǰ��45�Ƚ�                   
#define Acce_Z_POS_45       1180    //* 1700
//���ٶȼ������45�Ƚ�

#define dt 0.005         //ע�⣺ dt ��ȡֵΪkalman�˲�������ʱ�� �˲�������ʱ�� ;
#define Ta 12

#define Car_Angle_Set       -3.5   //17
#define Car_Angle_Speed_Set 0

#define Angle_Control_P      330  //150
#define Angle_Control_D      1.1



#define OPTICAL_ENCODE_CONSTANT   200
#define SPEED_CONTROL_COUNT				20  	// 20 ms * 5 ms  100ms����һ���ٶȵ���
#define CONTROL_PERIOD            5
#define CAR_SPEED_CONSTANT				1000.0 / (SPEED_CONTROL_COUNT * CONTROL_PERIOD) / (float)OPTICAL_ENCODE_CONSTANT
#define SPEED_CONTROL_PERIOD		  100 //	(SPEED_CONTROL_COUNT * CONTROL_PERIOD) //unit: ms

#define CAR_SPEED_SET				   0     
//#define CAR_SPEED_SET_RATIO	  12	
#define SPEED_CONTROL_P			  30    
#define SPEED_CONTROL_I		   	0.1                 
  
#define MOTOR_LEFT_SPEED_POSITIVE		(LeftMotorOut  > 0)
#define MOTOR_RIGHT_SPEED_POSITIVE		(RightMotorOut > 0)






#define Angle_Control_OUT_MAX 2000
#define Angle_Control_OUT_MIN -2000

#define MOTOR_OUT_DEAD_VAL  0
#define MOTOR_OUT_MAX       1860 
#define MOTOR_OUT_MIN       1360



#define Left_F  PWMDTY01     //���÷�Χ��0-2000
#define Left_B  PWMDTY23     //
#define Right_F PWMDTY45     //
#define Right_B PWMDTY67     //
#define Death_Value 150 
//���ֳ����� = 24 ���ٳ����� = 28 С���� = 10 ���ְ뾶 = 26mm ������������ = 25

