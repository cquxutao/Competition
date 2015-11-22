#pragma LINK_INFO DERIVATIVE "MC9S12XS128"

#ifndef _5110t
#define _5110t
#include "derivative.h"	//derivative-specific definitions

#define uchar unsigned char
#define uint unsigned int
//LCD Pins连接方式和定义
#define SCE PORTB_PB0
#define RST PORTB_PB1
#define DC PORTB_PB2
#define DIN PORTB_PB3
#define CLK PORTB_PB4
//LCD initize
#define LCD_EXT 0x21	//初始化LCD,功能设定使用扩充指令
#define LCD_DC  0xD0	//设定液晶偏置电压,如果是可调亮度的改值试
#define LCD_BASE 0x20	//使用基本指令
#define LCD_MODE 0x0C	//设定显示模式，正常显示
#define LCD_Y 0x40	  //设定LCD显示高
#define LCD_X 0x80	  //设定LCD显示宽
//LCD On/Off
#define LCD_DIN_OFF 0	//LCD输入开关
#define LCD_DIN_ON 1
#define LCD_CLK_OFF 0	//LCD时钟开关
#define LCD_CLK_ON 1
#define LCD_SCE_OFF 0	//LCD片选
#define LCD_SCE_ON 1
#define LCD_RST_OFF 0	//LCD复位
#define LCD_RST_ON 1
#define LCD_DC_OFF 0	//LCD数据链接
#define LCD_DC_ON 1

//ECT定义
#define TSCR2_Db 0x06;//禁止溢出中断，分频系数为64
#define TCTL4_Db 0x01;//捕捉上升沿
#define TSCR1_Db 0x80;//使能定时器

//void SetBusClock(void);
void LCD_init(void);
void LCD_clear(void);
void LCD_DISP(void);
void LCD_write_byte(unsigned char dat,unsigned char command);
void LCD_set_XY(unsigned char X, unsigned char Y);
void LCD_Write_char(unsigned char row,unsigned char page,unsigned char c);
void LCD_write_hanzi(unsigned char row,unsigned char page,unsigned char c);
void xianshi(unsigned int a);
void xianshi1(unsigned int a);



#endif
