#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Common.h"
#include "PLL.h"
#include "PWM.h"

/*************************************************************/
/*                        初始化PWM                          */
/*************************************************************/
void INIT_PWM(void) 
 {
  PWME=0x00;
  PWMCTL= 0xf0;  //联结通道01;23;45;67为16位的PWM
  PWMPOL=0xff;       //通道1,3,5,7的极性为低电平有效
  PWMCAE=0x00;       //左对齐
  PWMCLK= 0x00;     //通道01,45用A时钟作为时钟源，通道23,67用B时钟作为时钟源
  PWMPRCLK = 0x22;   //A时钟和B时钟的分频系数为4,频率为20MHz
  PWMSCLA  =  5;     //SA时钟频率为2MHz
  PWMSCLB  =  5;     //SB时钟频率为2MHz
  PWMPER01 = 2000;   //通道01的周期为10KHz
  PWMPER23 = 2000;   //通道23的周期为10KHz
  PWMPER45 = 2000;   //通道45的周期为10KHz
  PWMPER67 = 2000;   //通道67的周期为10KHz 
  PWMDTY01 = 0;      //通道01的占空比为0%   左面的轮子反转 
  PWMDTY23 = 0;      //通道23的占空比为0%  
  PWMDTY45 = 0;      //通道45的占空比为0%  
  PWMDTY67 = 0;      //通道67的占空比为0%   右面的轮子反转。。驱动能力差，加300 
  PWME = 0xff;    //使能通道                

 }