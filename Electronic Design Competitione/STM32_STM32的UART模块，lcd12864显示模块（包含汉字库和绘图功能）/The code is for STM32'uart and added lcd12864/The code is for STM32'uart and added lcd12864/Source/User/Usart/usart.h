#ifndef __USART_H
#define __USART_H

//ͷ�ļ�����
#include "stdio.h"	 
#include <string.h>

//��������
void USART1_Send_Byte(u16 dat);
uint8_t USART1_Receive_Byte(void);
void Init_Usart(void);
void Usart_Configuration(uint32_t BaudRate); 

#endif
