

#include "usually.h"
#include "tim.h"


void timer_init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ;
    
   // NVIC_InitTypeDef NVIC_InitStructure;;
      //��TIM2����ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
 //**************************************************************************
   //     ��ʱ��2���ã� 720��Ƶ��500ms�ж�һ�Σ����ϼ���
   //**************************************************************************
    TIM_TimeBaseStructure.TIM_Period = 50000;
    TIM_TimeBaseStructure.TIM_Prescaler = 719;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //��ʼ����ʱ��
    
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //����ʱ���ж�
    
    TIM_Cmd(TIM2, ENABLE); //ʹ�ܶ�ʱ��

   //**************************************************************************
   //     ��ʱ��3���ã� 720��Ƶ��250ms�ж�һ�Σ����ϼ���
   //**************************************************************************    
    TIM_TimeBaseStructure.TIM_Period = 25000;
    TIM_TimeBaseStructure.TIM_Prescaler = 719;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //��ʼ����ʱ��
    
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //����ʱ���ж�
    
    TIM_Cmd(TIM3, ENABLE); //ʹ�ܶ�ʱ��
    
   //**************************************************************************
   //     ��ʱ��4���ã� 1440��Ƶ��1000ms�ж�һ�Σ����ϼ���
   //**************************************************************************
    
    TIM_TimeBaseStructure.TIM_Period = 50000;
    TIM_TimeBaseStructure.TIM_Prescaler = 1439;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //��ʼ����ʱ��
    
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //����ʱ���ж�
    
    TIM_Cmd(TIM4, ENABLE);    //ʹ�ܶ�ʱ��
   
}

