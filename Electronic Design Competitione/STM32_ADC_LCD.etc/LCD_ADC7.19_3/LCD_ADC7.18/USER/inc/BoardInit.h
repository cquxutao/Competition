#ifndef __BOARDINIT_H
#define __BOARDINIT_H

void Target_Init(void);
void RCC_Configuration();
void GPIO_config();
void USART1_Configuration(void);
void USART2_Configuration(void);
void USART3_Configuration(void);
void I2C1_Configuration(void);
void ADC_Configuration(void);
void NVIC_Configuration(void);
void TIM_Init(void);
void TIM2_Configuration(vu16 v_div);
void TIM3_Configuration(void);
void TIM4_Configuration(void);
void TIM5_Configuration(void);
void TIM6_Configuration(void);
void TIM7_Configuration(void);
void EXTI4_Configuration(void);
void EXTI5_Configuration(void);
void EXTI6_Configuration(void);
void DMA_Configuration(void);
void KEY_Configuration(void);
void DMAReConfig(void);
#endif