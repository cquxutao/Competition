#ifndef __LCD12864_H
#define __LCD12864_H

//头文件包含
#include "stdio.h"	 
#include <string.h>

//函数声明
void delay_ms(uint16_t time);
void delay_us(uint16_t time);
void lcd12864_IOInitOut(void);
void lcd12864_IOInitIn(void);
void lcd12864_WaitBusy(void);
void lcd12864_WriteCmd(uint8_t cmd);
void lcd12864_WriteData(uint8_t data);


unsigned char lcd12864_readbyte(void);
void lcd12864_clear(void);



void lcd12864_InitDis(void);
void lcd12864_DisStr(uint8_t *s) ;
void lcd12864_locate16(uint8_t row, uint8_t col);


void lcd12864_DrawPoint_f(unsigned char x,unsigned char y,unsigned char Color );
void lcd12864_LCD_set_dot(unsigned char px,unsigned char py);
void lcd12864_draw_horizontal_line(unsigned char px,unsigned char py,unsigned char n,unsigned char xu);
//void lcd12864_draw_Rline(unsigned char px,unsigned char py,unsigned char n,unsigned char xu);
void lcd12864_draw_frame();

#endif
