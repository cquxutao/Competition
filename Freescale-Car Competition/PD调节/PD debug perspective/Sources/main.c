#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Common.h"
#include "PLL.h"
#include "ATD.h"
#include "Angle.h"
#include "SCI.h"
#include "PWM.h" 
#include "IO.h"
#include "LCD.h"
#include "PIT.h"     

extern int Acce_z;        //���ٶȼ�Z��AD�ɼ�ֵ
extern int Gyro_hori;     //������ˮƽ��AD�ɼ�ֵ
extern float CarAngle;
extern float GyroAngleSpeed; //�����ǵó��Ľ��ٶ�
extern float GravityAngle;         //���ٶȼƵó������       
extern float GyroIntegarl;         //�Խ��ٶȵĻ���ֵ
unsigned char show[8];
unsigned char CRC_code[2];
unsigned int number;
float test,test1;

int jishu;
int PIT0_1ms_Counter_Num ,PIT0_5ms_Counter_Num;
int g_nSpeedControlCount, g_nSpeedControlPeriod;

void main(void) {
  DisableInterrupts;
  INIT_PLL();
  INIT_SCI0(); 
  INIT_AD();
  INIT_PWM();
  IO_init();
  LCD_init(); //��ʼ��LCDģ��
	LCD_clear();//����Ļ
	LCD_DISP(); //��ʾ��ʼֵ
	//EnableInterrupts;      
	//delay(1000);
 	LCD_clear();//����Ļ
  INIT_PIT();
	EnableInterrupts;


  for(;;) 
  {
  if(PITTF_PTF0 == 1)
   {
   
     PIT0_1ms_Counter_Num ++;
     g_nSpeedControlPeriod++;
     SpeedControlOutput();
     
   if(PIT0_1ms_Counter_Num >= CONTROL_PERIOD)
    {
      GetMotorPulse();
      PIT0_1ms_Counter_Num=0;
      
    }else if(PIT0_1ms_Counter_Num==1)
    {
         CarVoltage_get();
    }else if(PIT0_1ms_Counter_Num==2)
    {                 
         AngleCalculate();
         Angle_Control();
         MotorOutput();
    }else if(PIT0_1ms_Counter_Num==3)
    {
    
      g_nSpeedControlCount++;
      if(g_nSpeedControlCount >= SPEED_CONTROL_COUNT)
      {
       SpeedControl();
       g_nSpeedControlCount = 0;
       g_nSpeedControlPeriod = 0;
      }
    
    }else if(PIT0_1ms_Counter_Num==4)
    { 
      ;
    }

  }
    
  
   /*CarVoltage_get();
   AngleCalculate();
   Angle_Control();
   MotorOutput();
   show[0] = (unsigned char)(((int)(test)) & 0x00FF);  //Z�������ĽǶȿ�1ͨ�� 
   show[1] = (unsigned char)(((int)(test)) >> 8); 
   show[2] = (unsigned char)(((int)(GyroAngleSpeed)) & 0x00FF); //���ٶ�Z��2ͨ��
   show[3] = (unsigned char)(((int)(GyroAngleSpeed)) >>8);
   show[4] = (unsigned char)(((int)(CarAngle)) & 0x00FF);     //�������˲���ĽǶȿ�3ͨ��
   show[5] = (unsigned char)(((int)(CarAngle)) >>8);
   show[6] = (unsigned char)(((int)(test1)) & 0x00FF); //������ֵ��4ͨ��
   show[7] = (unsigned char)(((int)(test1)) >>8); 
      CRC16(show,CRC_code,8);
      SCI0_send(show[0]);
      SCI0_send(show[1]);
      SCI0_send(show[2]);
      SCI0_send(show[3]);
      SCI0_send(show[4]);
      SCI0_send(show[5]);
      SCI0_send(show[6]);
      SCI0_send(show[7]);
      SCI0_send(CRC_code[0]);
      SCI0_send(CRC_code[1]);
      //Left_F = 0;
      //Left_B = 200; 
    */
    
    
        
  } 
  
}


/*************************************************************/
/*                      ��ʱ�жϺ���                         */
/*************************************************************/
#pragma CODE_SEG NON_BANKED
interrupt 66 void PIT_INTER(void)
{ //jishu=PORTA;
  if(PITTF_PTF0 == 1) 
  {
    
    PITTF_PTF0 = 1;    //�����־λ
  }
  
}
#pragma CODE_SEG DEFAULT









  