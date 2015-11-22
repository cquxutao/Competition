#ifndef __MODULE_H
#define __MODULE_H


//管脚宏定义

//LED相关
#define	LED2		        GPIO_Pin_14
#define	LED_2_GRP	        GPIOG

#define	LED5		        GPIO_Pin_13
#define	LED_5_GRP	        GPIOD

//KEY相关
#define	KEY1 		        GPIO_Pin_0
#define	KEY2		        GPIO_Pin_1
//#define	KEY3		        GPIO_Pin_2
#define	KEY4		        GPIO_Pin_3
#define	KEY5		        GPIO_Pin_4
#define	KEY6		        GPIO_Pin_5
#define	KEY7		        GPIO_Pin_6
#define	KEY8		        GPIO_Pin_10
#define	KEY_1_8_GRP		GPIOF  

//#define	KEY3		        GPIO_Pin_13
//#define	KEY_3_GRP		GPIOC

//#define	KEY4		        GPIO_Pin_0
//#define	KEY_4_GRP		GPIOE

//SW相关
#define	SW1		        GPIO_Pin_8
#define	SW2		        GPIO_Pin_9
#define	SW3		        GPIO_Pin_10

#define	SW_GRP		        GPIOE

//UART相关
#define UART1_TX                GPIO_Pin_9
#define UART1_RX                GPIO_Pin_10
#define	UART1_GRP		GPIOA
/*
#define UART2_TX                GPIO_Pin_2
#define UART2_RX                GPIO_Pin_3
#define	UART2_GRP		GPIOA

#define UART3_485_TX            GPIO_Pin_10
#define UART3_485_RX            GPIO_Pin_11
#define UART3_485_DIR           GPIO_Pin_12
#define	UART3_GRP		GPIOB

#define	I2C1_SCL		GPIO_Pin_6
#define	I2C1_SDA		GPIO_Pin_7
#define	I2C1_GRP		GPIOB*/

extern u16 UsartReData;

void delay_nus(u32 us);
void delay_nms(u32 ms);
void LED_open(void);
void LED_close(void);
void function1(void);
void function2(void);
void function3(void);
void function4(void);
void function5(void);
void function6(void);
void function7(void);
void function8(void);
void function1_close(void);
void function2_close(void);
void function3_close(void);
void function4_close(void);
void function5_close(void);
void function6_close(void);
void function7_close(void);
void function8_close(void);
#endif
