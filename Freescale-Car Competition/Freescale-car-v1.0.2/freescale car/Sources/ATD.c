#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Common.h"
#include "PLL.h"
#include "ATD.h"

/*************************************************************
�������ƣ�INIT_AD
�������أ���
����������ADת���ľ���
�������ܣ���ʼ��ADת��ģ��                                                 
*************************************************************/
void INIT_AD(void) 
{
  
  ATD0CTL2 = 0xc0;  //����A/Dģ��,��������,��ֹ�ж�
  delay(10);
  ATD0CTL1_SRES=2;
  ATD0CTL3 = 0x88;  //�Ҷ��룬ÿ��ֻת��һ��ͨ��
  ATD0CTL4 = 0x04;  //ADģ��ʱ��Ƶ��Ϊ8MHz
}
                                                            
/*************************************************************
�������ƣ�AD_once
�������أ�ADת��ֵ
������������Ҫ����ADת����ͨ����
�������ܣ�����һ��ADת��                                                 
*************************************************************/
unsigned int AD_once(unsigned char channel) {
  
 unsigned int result;

  ATD0CTL5 = channel;  
  while(!ATD0STAT0_SCF);
  result = ATD0DR0;
 
  return result;
}

/*************************************************************/
/*                        ������                           */
/*************************************************************/ 
unsigned int sort(unsigned int *v) 
 {
   int i,j;
   unsigned int tmp;
   for(i=0;i<5;i++) 
   {
     for(j=1;j<5-i;j++) 
     {
      if(*(v+j)<*(v+j-1))
      {
       tmp=*(v+j),*(v+j)=*(v+j-1),*(v+j-1)=tmp;
      } 
     }
   }
   return *(v+2);
 }
/*************************************************************/
/*                        �˲�����                           */
/*************************************************************/
unsigned int AD_ave(unsigned int *u) 
{
 unsigned int answer;
 unsigned int a1[5],a2[5],a3[5],a4[5];
 int i; 
  for (i=0;i<20;i++) 
  {
    if (i<5 )
        a1[i]=*(u+i);
    else if (i<10)
        a2[i-5]=*(u+i);
    else if (i<15)
        a3[i-10]=*(u+i);
    else
        a4[i-15]=*(u+i);
   }
    answer=(sort(a1)+sort(a2)+sort(a3)+sort(a4))/4;
    return answer;
}


