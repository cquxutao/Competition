#ifndef __LCD12864_H
#define __LCD12864_H

//ͷ�ļ�����
#include "stdio.h"	 
#include <string.h>

//��������
void delay_ms(uint16_t time);
void delay_us(uint16_t time);
void lcd12864_IOInitOut(void);
void lcd12864_IOInitIn(void);
void lcd12864_WaitBusy(void);
void lcd12864_WriteCmd(uint8_t cmd);
void lcd12864_WriteData(uint8_t data);
void lcd12864_InitDis(void);
void lcd12864_DisStr(uint8_t *s) ;

#endif
