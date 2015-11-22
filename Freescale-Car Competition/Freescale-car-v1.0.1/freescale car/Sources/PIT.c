#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Common.h"
#include "LCD.h"
#include "PIT.h"
#include "Angle.h"
#include "IO.h"


uchar PIT0_1ms_Counter_Num = 0, PIT0_5ms_Counter_Num = 0;
extern int nSpeedControlPeriod;
int nSpeedControlCount=0;
int x=0;

/*************************************************************/
/*                     PITģ���ʼ������                     */
/*************************************************************/
 void INIT_PIT(void){
 
 PITMTLD0=199;     //Ϊ΢��ʱ��0��������ֵ
 PITLD0=399;      //Ϊ16λ��ʱ��0��������ֵ (199+1)*(1999+1)=2000000����������=5ms  //1ms
 PITMUX_PMUX0=0;   //��0ͨ��ʹ��΢������0
 PITCE_PCE0=1;     //��0ͨ������������ 
 PITCFLMT=0x80;    //ʹ�������ж϶�ʱ��
 PITINTE_PINTE0=1; //0ͨ����ʱ����ʱ�жϱ�ʹ��
 }



/*************************************************************/
/*                      ��ʱ�жϺ���                         */
/*************************************************************/
#pragma CODE_SEG NON_BANKED
interrupt 66 void PIT_INTER(void)
{  PIT0_1ms_Counter_Num ++;
   nSpeedControlPeriod ++;
   SpeedControlOutput();
   nDirectionControlPeriod ++;
   DirectionControlOutput();
   if(PIT0_1ms_Counter_Num >= CONTROL_PERIOD){
   PIT0_5ms_Counter_Num++;
   PIT0_1ms_Counter_Num=0;
   GetMotorPulse();
   }else if(PIT0_1ms_Counter_Num==1){
    CarVoltage_get();
   }else if(PIT0_1ms_Counter_Num==2){
   AngleCalculate();
   Angle_Control();
   MotorOutput();
   }else if(PIT0_1ms_Counter_Num==3){
   nSpeedControlCount ++;
   if(nSpeedControlCount >= SPEED_CONTROL_COUNT){
   SpeedControl();
   nSpeedControlCount = 0;
   nSpeedControlPeriod = 0;
   }
   }else if(PIT0_1ms_Counter_Num==4){
   nDirectionControlCount ++;
   DirectionVoltageSigma();
   if(nDirectionControlCount >= DIRECTION_CONTROL_COUNT){
   DirectionControl();
   nDirectionControlCount = 0;
   nDirectionControlPeriod = 0;
   }
}
#pragma CODE_SEG DEFAULT