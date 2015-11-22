#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Common.h"
#include "PLL.h"
#include "ATD.h"

/*************************************************************
函数名称：INIT_AD
函数返回：无
函数参数：AD转换的精度
函数功能：初始化AD转换模块                                                 
*************************************************************/
void INIT_AD(void) 
{
  
  ATD0CTL2 = 0xc0;  //启动A/D模块,快速清零,禁止中断
  delay(10);
  ATD0CTL1_SRES=2;
  ATD0CTL3 = 0x88;  //右对齐，每次只转换一个通道
  ATD0CTL4 = 0x04;  //AD模块时钟频率为8MHz
}
                                                            
/*************************************************************
函数名称：AD_once
函数返回：AD转换值
函数参数：需要进行AD转换的通道号
函数功能：进行一次AD转换                                                 
*************************************************************/
unsigned int AD_once(unsigned char channel) {
  
 unsigned int result;

  ATD0CTL5 = channel;  
  while(!ATD0STAT0_SCF);
  result = ATD0DR0;
 
  return result;
}

/*************************************************************/
/*                        排序函数                           */
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
/*                        滤波函数                           */
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


