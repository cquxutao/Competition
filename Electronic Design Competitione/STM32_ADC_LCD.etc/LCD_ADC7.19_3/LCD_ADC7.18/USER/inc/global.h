#ifndef __GLOBAL_H
#define __GLOBAL_H

OS_STK                  TaskKeyStk[KEY_STK_SIZE];
OS_STK                  TaskLedStk[LED_STK_SIZE];

USART_DATA  usart_data;
CSW         csw;


#endif