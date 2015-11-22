#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Common.h"
#include "ECT.h"

/************************************************************/
/*                    初始化ECT模块                         */
/************************************************************/
void INIT_ECT(void){
  TSCR1_TFFCA = 1;  // 定时器标志位快速清除
  TSCR1_TEN = 1;    // 定时器使能位. 1=允许定时器正常工作; 0=使主定时器不起作用(包括计数器)
  TIOS  = 0x00;     //IOC7必须设置为输入，否则无法捕捉
  TCTL1 = 0x00;	    // 后四个通道设置为定时器与输出引脚断开
  TCTL2 = 0x00;     // 前四个通道设置为定时器与输出引脚断开
  TIE   = 0x00;     // 禁止所有通道定时中断
  TSCR2 = 0x07;	    // 预分频系数pr2-pr0:111,,时钟周期为4us,
  TFLG1 = 0xff;	    // 清除各IC/OC中断标志位
  TFLG2 = 0xff;     // 清除自由定时器中断标志位
}

/*************************************************************/
/*                      初始化累加器                         */
/*************************************************************/
void INIT_PAI(void) 
{
  PACTL = 0x50;      //始能脉冲累加器，累加上升沿
}
  