#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Common.h"
#include "PLL.h"
#include "PWM.h"

/*************************************************************/
/*                        ��ʼ��PWM                          */
/*************************************************************/
void INIT_PWM(void) 
 {
  PWME=0x00;
  PWMCTL= 0xf0;  //����ͨ��01;23;45;67Ϊ16λ��PWM
  PWMPOL=0xff;       //ͨ��1,3,5,7�ļ���Ϊ�͵�ƽ��Ч
  PWMCAE=0x00;       //�����
  PWMCLK= 0x00;     //ͨ��01,45��Aʱ����Ϊʱ��Դ��ͨ��23,67��Bʱ����Ϊʱ��Դ
  PWMPRCLK = 0x22;   //Aʱ�Ӻ�Bʱ�ӵķ�Ƶϵ��Ϊ4,Ƶ��Ϊ20MHz
  PWMSCLA  =  5;     //SAʱ��Ƶ��Ϊ2MHz
  PWMSCLB  =  5;     //SBʱ��Ƶ��Ϊ2MHz
  PWMPER01 = 2000;   //ͨ��01������Ϊ10KHz
  PWMPER23 = 2000;   //ͨ��23������Ϊ10KHz
  PWMPER45 = 2000;   //ͨ��45������Ϊ10KHz
  PWMPER67 = 2000;   //ͨ��67������Ϊ10KHz 
  PWMDTY01 = 0;      //ͨ��01��ռ�ձ�Ϊ0%   ��������ӷ�ת 
  PWMDTY23 = 0;      //ͨ��23��ռ�ձ�Ϊ0%  
  PWMDTY45 = 0;      //ͨ��45��ռ�ձ�Ϊ0%  
  PWMDTY67 = 0;      //ͨ��67��ռ�ձ�Ϊ0%   ��������ӷ�ת���������������300 
  PWME = 0xff;    //ʹ��ͨ��                

 }