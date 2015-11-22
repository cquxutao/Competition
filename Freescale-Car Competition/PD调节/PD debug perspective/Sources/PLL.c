#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Common.h"
#include "PLL.h"

/*************************************************************/
/*                      初始化锁相环                         */
/*************************************************************/
void INIT_PLL(void) 
{
    CLKSEL &= 0x7f;        //set OSCCLK as sysclk
    PLLCTL &= 0x8F;        //Disable PLL circuit
    CRGINT &= 0xDF;
    
    #if(BUS_CLOCK == 80000000)
      SYNR = 0xC9;
    #elif(BUS_CLOCK == 64000000) 
      SYNR = 0xC7;
    #elif(BUS_CLOCK == 48000000) 
      SYNR = 0xC5;
    #elif(BUS_CLOCK == 40000000) 
      SYNR = 0x44;
    #elif(BUS_CLOCK == 32000000)
      SYNR = 0x43;     
    #elif(BUS_CLOCK == 24000000)
      SYNR = 0x42;
    #endif 

    REFDV = 0x81;          //PLLCLK=2×OSCCLK×(SYNR+1)/(REFDV+1)＝64MHz ,fbus=32M
    PLLCTL =PLLCTL|0x70;   //Enable PLL circuit
    asm NOP;
    asm NOP;
    while(!(CRGFLG&0x08)); //PLLCLK is Locked already
    CLKSEL |= 0x80;        //set PLLCLK as sysclk
}

/*************************************************************
函数名称：delay
函数返回：无
函数参数：无
函数功能：延时                                                 
*************************************************************/
void delay(int m) 
{
unsigned int i,j;
for(i=0;i<m;i++)  {
  
 for(j=0;j<999;j++)
 {
  asm("nop"); 
 }
}
}
