
//*********************************************************************************************************
//* 文 件 名 : BoardInit.c
//* 文件描述 : STM32系统目标板初始化模块
//* 作    者 : 
//* 版    本 : 
//* 编 译 器 : IAR EWARM 5.20
//*********************************************************************************************************

#include "includes.h"


/*******************************************************************************
* Function Name  : Target_Init
* Description    : STM32各个模块初始化
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Target_Init(void)
{  
    RCC_Configuration();
    GPIO_config();
    LCD12864_Config(); 
    NVIC_Configuration();
    ADC_Configuration();
    DMA_Configuration();
   
    TIM_Init();
    USART1_Configuration();
    KEY_Configuration();
  //  USART2_Configuration();
   // USART3_Configuration();
   // I2C1_Configuration();
}

void TIM_Init(void)
{
    TIM2_Configuration(0);
    //TIM3_Configuration();
    //TIM4_Configuration();
//    TIM5_Configuration();
//    TIM6_Configuration();
//    TIM7_Configuration();
}
/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : 中断向量设置
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
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);    
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
   
    /* Configure the NVIC Preemption Priority Bits */  
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    

    
    /* 开USART1中断 */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_Init(&NVIC_InitStructure);
    
     /* Enable the ADC Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
     /* Enable DMA channel6 IRQ Channel */
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}



/********************************************************************************************************
* 函 数 名 : RCC_Configuration()
* 描    述 : 系统、外围设备时钟初始化
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
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
        
        /* PLLCLK = 8MHz * 7 = 56 MHz */
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_7);
        
        /* ADCCLK = PCLK2/4 */
       //RCC_ADCCLKConfig(RCC_PCLK2_Div4);

        
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
    
    /* Enable AFIO clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    /* TIM2 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);    
    /* TIM3 clock enable 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);*/
    /* TIM4 clock enable
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); */
    /* TIM5 clock enable 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);*/
    /* TIM6 clock enable
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); */
    /* TIM7 clock enable 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);*/
    
    /* USART1 clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);  
    /* USART2 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
    /* USART3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
    
    /* Enable I2C1 clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    
    /* Enable ADC2 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}

/********************************************************************************************************
* 函 数 名 : GPIO_config()
* 描    述 : GPIO管脚初始化
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void GPIO_config()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin = LED2  ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_2_GRP, &GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin =  LED5 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_5_GRP, &GPIO_InitStructure);

    /*GPIO_InitStructure.GPIO_Pin = KEY3 ; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
    GPIO_Init(KEY_3_GRP, &GPIO_InitStructure);*/
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = KEY1|KEY2|KEY4|KEY5|KEY6|KEY7|KEY8; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
    GPIO_Init(KEY_1_8_GRP, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = SW1 | SW2 | SW3;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
    GPIO_Init(SW_GRP, &GPIO_InitStructure);
    
    
     /*USART1 GPIO Config*/
    GPIO_InitStructure.GPIO_Pin = UART1_TX ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(UART1_GRP, &GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin = UART1_RX ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(UART1_GRP, &GPIO_InitStructure);
    
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;                 // Configure ADC channel10/11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
}
/*******************************************************************************
* Function Name  : void TIM2_Configuration(void)
* Description    : TIM2配置为PWM输出格式
* Input          : None
* Output         : None   100ms中断一次
* Return         : None
* (1+TIM_Prescaler)/36M)*(1+TIM_Period)=100ms
*******************************************************************************/
//vu16 v_div;
void TIM2_Configuration(vu16 v_div)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    
    TIM_TimeBaseStructure.TIM_Period =55; //5599;//55;//111999;
    TIM_TimeBaseStructure.TIM_Prescaler = v_div;//0;//1999;//99
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_Cmd(TIM2, ENABLE);
    
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//下面详细说明 
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//TIM_OutputState_Disable;  
    TIM_OCInitStructure.TIM_Channel = TIM_Channel_2;//CC2
    TIM_OCInitStructure.TIM_Pulse = 1; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//如果是PWM1要为LowPWM2则为High 
    TIM_OC2Init(TIM2, & TIM_OCInitStructure); 
    TIM_Cmd(TIM2, ENABLE); 
    TIM_InternalClockConfig(TIM2); 
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable); 
    TIM_UpdateDisableConfig(TIM2, DISABLE); 
}

/*******************************************************************************
* Function Name  : EXTI4_Configuration
* Description    : EXTI4 配置（用于485通信，可根据需要修改波特率）
* Input          : PE4

*******************************************************************************/
void KEY_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
        
	/* Configure the EXTI4 */
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);		//使能IO复用功能，使用中断功能重要！！！
        
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, GPIO_PinSource0);
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, GPIO_PinSource1);
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, GPIO_PinSource2);
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, GPIO_PinSource3);
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, GPIO_PinSource4);
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, GPIO_PinSource5);
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, GPIO_PinSource10);//配置端口C的13引脚为中断源	  重要！！ 板上标号INT2
  	
        EXTI_InitStructure.EXTI_Line = EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
        
	EXTI_InitStructure.EXTI_Line = EXTI_Line0|EXTI_Line1|EXTI_Line3|EXTI_Line4|EXTI_Line5|EXTI_Line10;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
       
}


/*******************************************************************************
* Function Name  : UART1_Configuration
* Description    : UART1 配置
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART1_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;  
    USART_ClockInitTypeDef USART_ClockInitStructure;
    
    USART_InitStructure.USART_BaudRate = 115200;
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
* Description    : UART2 配置
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART2_Configuration(void)
{
  
    USART_InitTypeDef USART_InitStructure;  
    USART_ClockInitTypeDef USART_ClockInitStructure;
    
    USART_InitStructure.USART_BaudRate = 115200;
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
* Description    : UART3 配置（用于485通信，可根据需要修改波特率）
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
* Description    : I2C1 配置
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
* Description    : ADC2 配置
* Input          : PC5

*******************************************************************************/
#define ADC1_DR_Address    ((u32)0x4001244C)
#define ADC1_temp    ADCConvertedValue
vu16 ADCConvertedValue[104];
void ADC_Configuration(void)
{
  ADC_InitTypeDef ADC_InitStructure;
  
  /* Configure the ADC1 */
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_CC2;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);
  
 
  //ADC_TempSensorVrefintCmd(ENABLE);
  
  /* ADC2 regular channel5 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_1Cycles5);
   //ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 2, ADC_SampleTime_239Cycles5);
  
  /* Enable ADC2 */
  
  ADC_Cmd(ADC1, ENABLE);
  
  /* Enable ADC2 reset calibaration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC2 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));
  /* Start ADC2 calibaration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC2 calibration */
  while(ADC_GetCalibrationStatus(ADC1));  
  /* Start ADC2 Software Conversion */ 
  //ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  ADC_DMACmd(ADC1,ENABLE);
  ADC_ExternalTrigConvCmd(ADC1, ENABLE);
  //ADC_ITConfig(ADC2, ADC_IT_EOC, ENABLE); 
  //ADC_ClearITPendingBit(ADC2,ADC_IT_EOC);
}
static DMA_InitTypeDef DMA_InitStructure;
void DMA_Configuration(void)
{
   //DMA_InitTypeDef DMA_InitStructure;     
        DMA_DeInit(DMA1_Channel1);
  	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADCConvertedValue;
  	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  	DMA_InitStructure.DMA_BufferSize =104;
  	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  	DMA_Init(DMA1_Channel1, &DMA_InitStructure);	 
        DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE); 
  	/* Enable DMA1 channel1 */
  	DMA_Cmd(DMA1_Channel1, ENABLE);	
}

void DMAReConfig(void)//重启DMA
{
   DMA_DeInit(DMA1_Channel1);
   DMA_Init(DMA1_Channel1, &DMA_InitStructure);
   DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
   DMA_Cmd(DMA1_Channel1, ENABLE);
}
//*********************************************************************************************************
//**                            End Of File
//*********************************************************************************************************

