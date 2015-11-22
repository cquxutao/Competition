#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Common.h"
#include "LCD.h"
#include "PIT.h"


/*************************************************************/
/*                     PIT模块初始化函数                     */
/*************************************************************/
 void INIT_PIT(void){
 
 PITMTLD0=199;     //为微定时器0计数器赋值
 PITLD0=399;      //为16位定时器0计数器赋值 (199+1)*(1999+1)=2000000个总线周期=1ms  //1ms
 PITMUX_PMUX0=0;   //第0通道使用微计数器0
 PITCE_PCE0=1;     //第0通道计数器工作 
 PITCFLMT=0x80;    //使能周期中断定时器
 PITINTE_PINTE0=1; //0通道定时器定时中断被使能
 }



