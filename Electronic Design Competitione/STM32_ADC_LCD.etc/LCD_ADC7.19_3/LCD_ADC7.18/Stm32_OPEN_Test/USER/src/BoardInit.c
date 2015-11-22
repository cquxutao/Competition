
//*********************************************************************************************************
//* �� �� �� : BoardInit.c
//* �ļ����� : STM32ϵͳĿ����ʼ��ģ��
//* ��    �� : 
//* ��    �� : 
//* �� �� �� : IAR EWARM 5.20
//*********************************************************************************************************

#include "includes.h"


/*******************************************************************************
* Function Name  : Target_Init
* Description    : STM32����ģ���ʼ��
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Target_Init(void)
{  
    RCC_Configuration();
    GPIO_config();
    NVIC_Configuration();
    TIM_Init();
    Init_PWM(3600);
    //USART1_Configuration();
    //USART2_Configuration();
    //USART3_Configuration();
    //I2C1_Configuration();
}

void TIM_Init(void)
{
    //TIM2_Configuration();
    //TIM3_Configuration();
    TIM4_Configuration();
//    TIM5_Configuration();
//    TIM6_Configuration();
//    TIM7_Configuration();
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: PWM_Init
** ��������: ����PWMͨ����ռ�ձ�
** ����������Dutyfactor ����ռ�ձȴ�С
** ��  ����: Dream
** �ա�  ��: 2011��6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_PWM(u16 Dutyfactor)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;					//����һ��ͨ������ṹ


	TIM_OCStructInit(&TIM_OCInitStructure);					//����ȱʡֵ

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	   	//PWM ģʽ 1 ��� 	
	TIM_OCInitStructure.TIM_Pulse = Dutyfactor; 			//����ռ�ձȣ�ռ�ձ�=(CCRx/ARR)*100%��(TIM_Pulse/TIM_Period)*100%
															//PWM�����Ƶ��ΪFpwm=72M/7200=1Mhz��  
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
															//TIM ����Ƚϼ��Ը�   	    
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;    
															//ʹ�����״̬  ��ҪPWM�������Ҫ���д���
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);				//���ݲ�����ʼ��PWM�Ĵ���    

	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);	   	//ʹ�� TIMx�� CCR2 �ϵ�Ԥװ�ؼĴ���

    TIM_CtrlPWMOutputs(TIM4,ENABLE);  						//����TIM4 ��PWM ���Ϊʹ��  
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : �ж���������
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
#ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x20000000 */
    NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x08000000 */
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
   
    /* Configure the NVIC Preemption Priority Bits */  
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
//    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQChannel;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//    
//    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQChannel;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//    
//    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQChannel;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//    
//    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQChannel;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /* ��USART1�ж� */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /* ��USART2�ж� */  
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /*��USART3�ж�*/  
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
     /* Enable the ADC Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 
}



/********************************************************************************************************
* �� �� �� : RCC_Configuration()
* ��    �� : ϵͳ����Χ�豸ʱ�ӳ�ʼ��
* ������� : None.
* ������� : None.
* ��   ��  : None.
********************************************************************************************************/
void RCC_Configuration(void)
{   /* RCC system reset(for debug purpose) */
    ErrorStatus HSEStartUpStatus;
    
    RCC_DeInit();
    
    /* Enable HSE */
    RCC_HSEConfig(RCC_HSE_ON);
    RCC_LSEConfig(RCC_LSE_OFF); 

    /* Wait till HSE is ready */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    
    if(HSEStartUpStatus == SUCCESS)
    {
        /* Enable Prefetch Buffer */
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        /* Flash 2 wait state */
        FLASH_SetLatency(FLASH_Latency_2);
        
        /* HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        
        /* PCLK2 = HCLK */
        RCC_PCLK2Config(RCC_HCLK_Div1);
        
        /* PCLK1 = HCLK/4 */
        RCC_PCLK1Config(RCC_HCLK_Div2);
        
        /* PLLCLK = 8MHz * 9 = 72 MHz */
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
        
        /* ADCCLK = PCLK2/4 */
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);

        
        /* Enable PLL */
        RCC_PLLCmd(ENABLE);
        
        /* Wait till PLL is ready */
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
        }
        
        /* Select PLL as system clock source */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        
        /* Wait till PLL is used as system clock source */
        while(RCC_GetSYSCLKSource() != 0x08)
        {
        }
    }
    /* GPIO clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB| RCC_APB2Periph_GPIOC 
                           | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE |RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); 
    /* Enable AFIO clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    /* TIM2 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);    
    /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    /* TIM4 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    /* TIM5 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    /* TIM6 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    /* TIM7 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    
    /* USART1 clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);  
    /* USART2 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
    /* USART3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
    
    /* Enable I2C1 clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    
    /* Enable ADC2 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
}

/********************************************************************************************************
* �� �� �� : GPIO_config()
* ��    �� : GPIO�ܽų�ʼ��
* ������� : None.
* ������� : None.
* ��   ��  : None.
********************************************************************************************************/
void GPIO_config()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_AFIODeInit();
    GPIO_InitStructure.GPIO_Pin = LED1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_1_GRP, &GPIO_InitStructure); 
    
    GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = LED2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_2_GRP, &GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin = LED3 | LED4 | LED5 | LED6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_3_6_GRP, &GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin = LED7 | LED8 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_7_8_GRP, &GPIO_InitStructure); 

    GPIO_InitStructure.GPIO_Pin = KEY1 | KEY2 | KEY3 | KEY4 | KEY5; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = KEY6 | KEY7 | KEY8 | SW1 | SW2 | SW3 | SW4;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource5);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource6);
    
    GPIO_InitStructure.GPIO_Pin = HEX_D0 | HEX_D1 | HEX_D2 | HEX_D3 | HEX_SCC;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin = HEX_SCA | HEX_SCB ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin = HEX_D4 | HEX_D5 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = HEX_D6 | HEX_D7 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
    
     /*USART1 GPIO Config*/
    GPIO_InitStructure.GPIO_Pin = UART1_TX ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(UART1_GRP, &GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin = UART1_RX ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(UART1_GRP, &GPIO_InitStructure);
    
    /*USART2 GPIO Config**********/
    GPIO_InitStructure.GPIO_Pin = UART2_TX ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(UART2_GRP, &GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin = UART2_RX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(UART2_GRP, &GPIO_InitStructure);  
    
    /***************USART3 GPIO Config********************/
    GPIO_InitStructure.GPIO_Pin = UART3_485_TX ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(UART3_GRP, &GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin = UART3_485_RX ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(UART3_GRP, &GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin = UART3_485_DIR ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(UART3_GRP, &GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin = I2C1_SCL | I2C1_SDA;    //Configure I2C1 SCL and SDA(PB6 as alternate function push-pull 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
    GPIO_Init(I2C1_GRP, &GPIO_InitStructure);
    
    /*����Lcd��������Ϊ�������*/
    /*16λ����*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7| GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    /*���ƽ�*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
    /*�������*/
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;                 // Configure ADC channel10/11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    /***************�ⲿ�ж�********************/
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource5);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource6);
}
/*******************************************************************************
* Function Name  : void TIM2_Configuration(void)
* Description    : TIM2����ΪPWM�����ʽ
* Input          : None
* Output         : None   100ms�ж�һ��
* Return         : None
* (1+TIM_Prescaler)/36M)*(1+TIM_Period)=100ms
*******************************************************************************/
void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    
    TIM_TimeBaseStructure.TIM_Period = 7200;
    TIM_TimeBaseStructure.TIM_Prescaler = 5000;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
}

/*******************************************************************************
* Function Name  : void TIM3_Configuration(void)
* Description    : TIM3����ΪPWM�����ʽ
* Input          : None
* Output         : None   100ms�ж�һ��
* Return         : None
* (1+TIM_Prescaler)/36M)*(1+TIM_Period)=100ms
*******************************************************************************/
void TIM3_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    
    TIM_TimeBaseStructure.TIM_Period =7200;
    TIM_TimeBaseStructure.TIM_Prescaler = 20;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
}

/*******************************************************************************
* Function Name  : void TIM4_Configuration(void)
* Description    : TIM4����ΪPWM�����ʽ
* Input          : None
* Output         : None   100ms�ж�һ��
* Return         : None
* (1+TIM_Prescaler)/36M)*(1+TIM_Period)=100ms
*******************************************************************************/
void TIM4_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    
    TIM_TimeBaseStructure.TIM_Period = 7200;
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
}

/*******************************************************************************
* Function Name  : void TIM5_Configuration(void)
* Description    : TIM5����ΪPWM�����ʽ
* Input          : None
* Output         : None   100ms�ж�һ��
* Return         : None
* (1+TIM_Prescaler)/36M)*(1+TIM_Period)=100ms
*******************************************************************************/
void TIM5_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    
    TIM_TimeBaseStructure.TIM_Period = 7200;
    TIM_TimeBaseStructure.TIM_Prescaler = 5000;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
    

    
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
    TIM_ClearITPendingBit(TIM5, TIM_IT_Update);	
    TIM5->CNT = 0;
    TIM_Cmd(TIM5, ENABLE);

}

/*******************************************************************************
* Function Name  : void TIM6_Configuration(void)
* Description    : TIM6����ΪPWM�����ʽ
* Input          : None
* Output         : None   100ms�ж�һ��
* Return         : None
* (1+TIM_Prescaler)/36M)*(1+TIM_Period)=100ms
*******************************************************************************/
void TIM6_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    
    TIM_TimeBaseStructure.TIM_Period = 7200;
    TIM_TimeBaseStructure.TIM_Prescaler = 5000;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
    

    
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update);	
    TIM6->CNT = 0;
    TIM_Cmd(TIM6, ENABLE);

}

/*******************************************************************************
* Function Name  : void TIM7_Configuration(void)
* Description    : TIM7����ΪPWM�����ʽ
* Input          : None
* Output         : None   100ms�ж�һ��
* Return         : None
* (1+TIM_Prescaler)/36M)*(1+TIM_Period)=100ms
*******************************************************************************/
void TIM7_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    
    TIM_TimeBaseStructure.TIM_Period = 7200;
    TIM_TimeBaseStructure.TIM_Prescaler = 5000;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
    

    
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
    TIM_ClearITPendingBit(TIM7, TIM_IT_Update);	
    TIM7->CNT = 0;
    TIM_Cmd(TIM7, ENABLE);

}

/*******************************************************************************
* Function Name  : EXTI4_Configuration
* Description    : EXTI4 ���ã�����485ͨ�ţ��ɸ�����Ҫ�޸Ĳ����ʣ�
* Input          : PE4

*******************************************************************************/
void EXTI4_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
        
	/* Configure the EXTI4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
       
}
/*******************************************************************************
* Function Name  : EXTI5_Configuration
* Description    : EXTI5 ���ã�����485ͨ�ţ��ɸ�����Ҫ�޸Ĳ����ʣ�
* Input          : PE5

*******************************************************************************/
void EXTI5_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
        
	/* Configure the EXTI5 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
      
}

/*******************************************************************************
* Function Name  : EXTI6_Configuration
* Description    : EXTI6 ���ã�����485ͨ�ţ��ɸ�����Ҫ�޸Ĳ����ʣ�
* Input          : PE6

*******************************************************************************/
void EXTI6_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
        
	/* Configure the EXTI6 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

/*******************************************************************************
* Function Name  : UART1_Configuration
* Description    : UART1 ����
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART1_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;  
    USART_ClockInitTypeDef USART_ClockInitStructure;
    
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  
    /* Configure the USART1 */
    USART_Init(USART1, &USART_InitStructure);
    
    USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
    USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
    USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
    USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
    USART_ClockStructInit(&USART_ClockInitStructure);
}
/*******************************************************************************
* Function Name  : UART2_Configuration
* Description    : UART2 ����
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART2_Configuration(void)
{
  
    USART_InitTypeDef USART_InitStructure;  
    USART_ClockInitTypeDef USART_ClockInitStructure;
    
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  
    /* Configure the USART2 */
    USART_Init(USART2, &USART_InitStructure);
    
    USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
    USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
    USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
    USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
    USART_ClockStructInit(&USART_ClockInitStructure);
}

/*******************************************************************************
* Function Name  : UART3_Configuration
* Description    : UART3 ���ã�����485ͨ�ţ��ɸ�����Ҫ�޸Ĳ����ʣ�
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART3_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;  
    USART_ClockInitTypeDef USART_ClockInitStructure;
    
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  
    /* Configure the USART3 */
    USART_Init(USART3, &USART_InitStructure);
    
    USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
    USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
    USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
    USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
    USART_ClockStructInit(&USART_ClockInitStructure);
}
/*******************************************************************************
* Function Name  : I2C1_Configuration
* Description    : I2C1 ����
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_Configuration(void)
{
  I2C_InitTypeDef I2C_InitStructure;
  
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = 0xa2;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = 100000;
  
  /* Configure the I2C1 */
  I2C_Init(I2C1, &I2C_InitStructure);
}
/*******************************************************************************
* Function Name  : ADC_Configuration
* Description    : ADC2 ����
* Input          : PC5

*******************************************************************************/
void ADC_Configuration(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  
  /* Configure the ADC2 */
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC2, &ADC_InitStructure);
  
  /* ADC2 regular channel5 configuration */ 
  ADC_RegularChannelConfig(ADC2, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5);
  
  /* Enable ADC2 */
  ADC_Cmd(ADC2, ENABLE);
  /* Enable ADC2 reset calibaration register */   
  ADC_ResetCalibration(ADC2);
  /* Check the end of ADC2 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC2));
  /* Start ADC2 calibaration */
  ADC_StartCalibration(ADC2);
  /* Check the end of ADC2 calibration */
  while(ADC_GetCalibrationStatus(ADC2));  
  /* Start ADC2 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC2, ENABLE);
  
  ADC_ITConfig(ADC2, ADC_IT_EOC, ENABLE); 
  ADC_ClearITPendingBit(ADC2,ADC_IT_EOC);
}
//*********************************************************************************************************
//**                            End Of File
//*********************************************************************************************************

