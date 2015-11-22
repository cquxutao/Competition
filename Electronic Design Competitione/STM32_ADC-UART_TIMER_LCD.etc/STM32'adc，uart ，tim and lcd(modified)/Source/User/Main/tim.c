

#include "usually.h"
#include "tim.h"


void timer_init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ;
    
   // NVIC_InitTypeDef NVIC_InitStructure;;
      //打开TIM2外设时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
 //**************************************************************************
   //     定时器2设置： 720分频，500ms中断一次，向上计数
   //**************************************************************************
    TIM_TimeBaseStructure.TIM_Period = 50000;
    TIM_TimeBaseStructure.TIM_Prescaler = 719;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //初始化定时器
    
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //开定时器中断
    
    TIM_Cmd(TIM2, ENABLE); //使能定时器

   //**************************************************************************
   //     定时器3设置： 720分频，250ms中断一次，向上计数
   //**************************************************************************    
    TIM_TimeBaseStructure.TIM_Period = 25000;
    TIM_TimeBaseStructure.TIM_Prescaler = 719;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //初始化定时器
    
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //开定时器中断
    
    TIM_Cmd(TIM3, ENABLE); //使能定时器
    
   //**************************************************************************
   //     定时器4设置： 1440分频，1000ms中断一次，向上计数
   //**************************************************************************
    
    TIM_TimeBaseStructure.TIM_Period = 50000;
    TIM_TimeBaseStructure.TIM_Prescaler = 1439;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //初始化定时器
    
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //开定时器中断
    
    TIM_Cmd(TIM4, ENABLE);    //使能定时器
   
}

