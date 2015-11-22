#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Common.h"
#include "SCI.h"


/*************************************************************/
/*                        ��ʼ��SCI1                         */
/*************************************************************/
void INIT_SCI0(void) 
{
  SCI0BD = BUS_CLOCK/16/BAUD;   //����SCI1������Ϊ9600
  SCI0CR1 = 0x00;               //����SCI1Ϊ����ģʽ����λ����λ������żУ��
  //SCI0CR2 = 0x08;               //����������
  SCI0CR2 = 0x2c;                 //��������   �����ж�����  
}

/*************************************************************/
/*                       ����1���ͺ���                       */
/*************************************************************/
void SCI0_send(unsigned char data) 
{
  while(!SCI0SR1_TDRE);         //�ȴ��������ݼĴ�������������Ϊ��
  SCI0DRH=0;
  SCI0DRL = data;
}

/*************************************************************/
/*                       ����1���պ���                       */
/*************************************************************/
unsigned char SCI0_receive(void)
{
   unsigned char temp;
   while(!SCI0SR1_RDRF)   //�������ݴ�λ�ƼĴ������䵽SCI���ݼĴ���
   asm("nop");
   SCI0SR1_RDRF = 1;
   temp = SCI0DRL;
   asm("nop");
   return temp;           //�������ݼĴ���������     
}
/*************************************************************/
/*                        ������ʾ                           */
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
/*�������ƣ�CRCУ����                                        */
/*��������: ��                                               */
/*����˵��: array[8]���͵�4��1word���ݣ�RCVBUF[2]16λУ����  */
/*          len���͵�λ��                                    */
/*���ܸ�Ҫ: ���ڷ��͸�visual scope                           */
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
  RCVBUF[0]= (CRC&0X00FF);     //��λ��
  RCVBUF[1]= (CRC&0XFF00)>>8;  //��λ��
}
                    


