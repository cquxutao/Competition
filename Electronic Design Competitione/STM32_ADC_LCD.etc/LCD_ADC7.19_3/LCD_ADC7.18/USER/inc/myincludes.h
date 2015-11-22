#include <stdio.h>

#include "stm32f10x_lib.h"			 /* STM32F10x Library Definitions */
#include "module.h"

/*******************************宏定义****************************/

/*************************外设相关************************/

//定义外设端口

#define	LED1 		        GPIO_Pin_5
#define	LED2		        GPIO_Pin_6
#define	LED3		        GPIO_Pin_7
#define	LED4		        GPIO_Pin_8
#define	LED5		        GPIO_Pin_9
#define	LED6		        GPIO_Pin_10

#define	LED_GRP		        GPIOF


