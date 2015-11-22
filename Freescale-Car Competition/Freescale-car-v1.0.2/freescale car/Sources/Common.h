#define  BUS_CLOCK		80000000	   //����Ƶ��
#define  OSC_CLOCK		16000000	   //����Ƶ��
#define  BAUD         9600         //���ڲ�����

#define  Acce_z_channel    0
#define  Gyro_hori_channel 1
#define  Gyro_vert_channel 2

#define  Acce_Z_OFFSET     1247      //*1875

#define  Gyro_Hori_OFFSET  1212     //*1172
#define  Gyro_Vert_OFFSET  1164

#define Gravity_Angle_RATIO  94.7  //137.3
//Gravity_Angle_RATIO = 90��/(Acce_Z_POS_45 - Acce_Z_NAG_45) = 0.09879 �Ŵ�1000��
#define Gyro_Angle_RATIO     35  //����ΪС�����ȷŴ�100��
#define Acce_Z_NAG_45        587    //* 753
//���ٶȼ���ǰ��45�Ƚ�                   
#define Acce_Z_POS_45       1928    //* 1700
//���ٶȼ������45�Ƚ�

#define dt 0.005         //ע�⣺ dt ��ȡֵΪkalman�˲�������ʱ�� �˲�������ʱ�� ;
#define Ta 12

#define Car_Angle_Set       0   //17
#define Car_Angle_Speed_Set 0

#define Angle_Control_P      180
#define Angle_Control_D      0.01

#define Angle_Control_OUT_MAX 1600
#define Angle_Control_OUT_MIN -1600

#define MOTOR_OUT_DEAD_VAL  0
#define MOTOR_OUT_MAX       1860 
#define MOTOR_OUT_MIN       1360

#define OPTICAL_ENCODE_CONSTANT   200
#define SPEED_CONTROL_COUNT				20  	// 20 ms * 5 ms  100ms����һ���ٶȵ���
#define CONTROL_PERIOD            5
#define CAR_SPEED_CONSTANT				1000.0 / (SPEED_CONTROL_COUNT * CONTROL_PERIOD) / (float)OPTICAL_ENCODE_CONSTANT

#define DIRECTION_CONTROL_COUNT   20

#define CAR_SPEED_SET				   0     
//#define CAR_SPEED_SET_RATIO	  12	
#define SPEED_CONTROL_P			  0     
#define SPEED_CONTROL_I		   	0 
                
#define SPEED_CONTROL_PERIOD			(SPEED_CONTROL_COUNT * CONTROL_PERIOD) //unit: ms
  
#define MOTOR_LEFT_SPEED_POSITIVE		(LeftMotorOut  > 0)
#define MOTOR_RIGHT_SPEED_POSITIVE		(RightMotorOut > 0)

//#define SPEED_CONTROL_OUT_MAX			MOTOR_OUT_MAX * 10
//#define SPEED_CONTROL_OUT_MIN			MOTOR_OUT_MIN * 10

#define Left_F  PWMDTY01     //���÷�Χ��0-2000
#define Left_B  PWMDTY23     //
#define Right_F PWMDTY45     //
#define Right_B PWMDTY67     //
#define Death_Value 150 
//���ֳ����� = 24 ���ٳ����� = 28 С���� = 10 ���ְ뾶 = 26mm ������������ = 25


//����CCDģ��
#define TSL_SI PORTB_PB5 //�������Դ������Ķ˿� SI
#define TSL_CLK PORTB_PB6 //�������Դ������Ķ˿� CLK


