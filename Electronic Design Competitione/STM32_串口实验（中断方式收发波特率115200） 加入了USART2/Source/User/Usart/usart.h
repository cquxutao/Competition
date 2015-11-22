#ifndef __USART_H
#define __USART_H

//头文件包含
#include "stdio.h"	 
#include <string.h>

//函数声明
void USART1_Send_Byte(u16 dat);
void USART2_Send_Byte(u16 dat);
uint8_t USART1_Receive_Byte(void);
uint8_t USART2_Receive_Byte(void);
void Init_Usart1(void);
void Init_Usart2(void);
void Usart1_Configuration(uint32_t BaudRate); 
void Usart2_Configuration(uint32_t BaudRate);

#endif
