#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Common.h"
#include "SCI.h"


/*************************************************************/
/*                        初始化SCI1                         */
/*************************************************************/
void INIT_SCI0(void) 
{
  SCI0BD = BUS_CLOCK/16/BAUD;   //设置SCI1波特率为9600
  SCI0CR1 = 0x00;               //设置SCI1为正常模式，八位数据位，无奇偶校验
  //SCI0CR2 = 0x08;               //允许发送数据
  SCI0CR2 = 0x2c;                 //发送允许   接受中断允许  
}

/*************************************************************/
/*                       串口1发送函数                       */
/*************************************************************/
void SCI0_send(unsigned char data) 
{
  while(!SCI0SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空
  SCI0DRH=0;
  SCI0DRL = data;
}

/*************************************************************/
/*                       串口1接收函数                       */
/*************************************************************/
unsigned char SCI0_receive(void)
{
   unsigned char temp;
   while(!SCI0SR1_RDRF)   //表明数据从位移寄存器传输到SCI数据寄存器
   asm("nop");
   SCI0SR1_RDRF = 1;
   temp = SCI0DRL;
   asm("nop");
   return temp;           //返回数据寄存器的数据     
}
/*************************************************************/
/*                        串口显示                           */
/*************************************************************/
/*#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt 20 void SCI_SHOW(void) 
{
  unsigned char date_receive;
  DisableInterrupts;
  date_receive = SCI0_receive();
  if(date_receive == 'a') 
    {
      SCI0_send(tmp);
     } 
  else
    {
      for(i=0;i<20;i++) 
      SCI_send(AD_Z[i]);
    }
    EnableInterrupts; 
}  
#pragma CODE_SEG DEFAULT */ 

/*************************************************************/
/*函数名称：CRC校验码                                        */
/*函数返回: 无                                               */
/*参数说明: array[8]发送的4个1word数据，RCVBUF[2]16位校验码  */
/*          len发送的位长                                    */
/*功能概要: 用于发送给visual scope                           */
/*************************************************************/
void CRC16(unsigned char *ARRAY,unsigned char *RCVBUF,unsigned int Len)
{
  unsigned int IX,IY,CRC;
  CRC=0XFFFF;
  
  if(Len<=0)
    CRC = 0;
  else
  {
    Len--;
    for(IX=0;IX<=Len;IX++)
    {
      CRC=CRC^(unsigned int)(ARRAY[IX]);
      for(IY=0;IY<=7;IY++)
      {
        if((CRC&1)!=0)
        CRC = (CRC>>1)^0XA001;
        else 
        CRC=CRC>>1;
      }
    }
  }
  RCVBUF[0]= (CRC&0X00FF);     //低位置
  RCVBUF[1]= (CRC&0XFF00)>>8;  //高位置
}
                    


