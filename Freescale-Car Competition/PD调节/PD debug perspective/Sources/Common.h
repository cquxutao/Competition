#define  BUS_CLOCK		80000000	   //总线频率
#define  OSC_CLOCK		16000000	   //晶振频率
#define  BAUD         9600         //串口波特率

#define  Acce_z_channel    2
#define  Gyro_hori_channel 0
#define  Gyro_vert_channel 1

#define  Acce_Z_OFFSET     1143  //*1875

#define  Gyro_Hori_OFFSET  1377 //*1172
#define  Gyro_Vert_OFFSET  1164

#define Gravity_Angle_RATIO  99.67   //94.7
//Gravity_Angle_RATIO = 90°/(Acce_Z_POS_45 - Acce_Z_NAG_45) = 0.09879 放大1000倍
#define Gyro_Angle_RATIO     35  //由于为小数，先放大100倍
#define Acce_Z_NAG_45        753    //* 753
//加速度计向前倾45度角                   
#define Acce_Z_POS_45       1180    //* 1700
//加速度计向后倾45度角

#define dt 0.005         //注意： dt 的取值为kalman滤波器采样时间 滤波器采样时间 ;
#define Ta 12

#define Car_Angle_Set       -3.5   //17
#define Car_Angle_Speed_Set 0

#define Angle_Control_P      330  //150
#define Angle_Control_D      1.1



#define OPTICAL_ENCODE_CONSTANT   200
#define SPEED_CONTROL_COUNT				20  	// 20 ms * 5 ms  100ms进行一次速度调节
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



#define Left_F  PWMDTY01     //设置范围是0-2000
#define Left_B  PWMDTY23     //
#define Right_F PWMDTY45     //
#define Right_B PWMDTY67     //
#define Death_Value 150 
//车轮齿轮数 = 24 加速齿轮数 = 28 小齿轮 = 10 车轮半径 = 26mm 编码器齿轮数 = 25

