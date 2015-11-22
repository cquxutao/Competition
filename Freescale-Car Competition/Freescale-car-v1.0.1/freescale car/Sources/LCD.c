#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>/* derivative information */
#include "LCD.h"    /* 5110t derivative information */
#include "PLL.h"
#include "IO.h"

unsigned int js,jt,b[3],c[3];

//宽x高=5x7 8X8 ASCII点阵码
const unsigned char num[][6]={
{0x00,0x3E,0x51,0x49,0x45,0x3E},//0
{0x00,0x00,0x42,0x7F,0x40,0x00},//1
{0x00,0x42,0x61,0x51,0x49,0x46},//2
{0x00,0x21,0x41,0x45,0x4B,0x31},//3
{0x00,0x18,0x14,0x12,0x7F,0x10},//4
{0x00,0x27,0x45,0x45,0x45,0x39},//5-5
{0x00,0x3C,0x4A,0x49,0x49,0x30},//6
{0x00,0x01,0x71,0x09,0x05,0x03},//7
{0x00,0x36,0x49,0x49,0x49,0x36},//8
{0x00,0x06,0x49,0x49,0x29,0x1E},//9
{0x00,0x20,0x54,0x54,0x54,0x78},//a-10
{0x00,0x7F,0x48,0x44,0x44,0x38},//b
{0x00,0x38,0x44,0x44,0x44,0x20},//c
{0x00,0x38,0x44,0x44,0x48,0x7F},//d
{0x00,0x38,0x54,0x54,0x54,0x18},//e
{0x00,0x08,0x7E,0x09,0x01,0x02},//f-15
{0x00,0x18,0xA4,0xA4,0xA4,0x7C},//g
{0x00,0x7F,0x08,0x04,0x04,0x78},//h
{0x00,0x00,0x44,0x7D,0x40,0x00},//i
{0x00,0x40,0x80,0x84,0x7D,0x00},//j
{0x00,0x7F,0x10,0x28,0x44,0x00},//k-20
{0x00,0x00,0x41,0x7F,0x40,0x00},//l
{0x00,0x7C,0x04,0x18,0x04,0x78},//m
{0x00,0x7C,0x08,0x04,0x04,0x78},//n
{0x00,0x38,0x44,0x44,0x44,0x38},//o
{0x00,0xFC,0x24,0x24,0x24,0x18},//p-25
{0x00,0x18,0x24,0x24,0x18,0xFC},//q
{0x00,0x7C,0x08,0x04,0x04,0x08},//r
{0x00,0x48,0x54,0x54,0x54,0x20},//s
{0x00,0x04,0x3F,0x44,0x40,0x20},//t
{0x00,0x3C,0x40,0x40,0x20,0x7C},//u-30
{0x00,0x1C,0x20,0x40,0x20,0x1C},//v
{0x00,0x3C,0x40,0x30,0x40,0x3C},//w
{0x00,0x44,0x28,0x10,0x28,0x44},//x
{0x00,0x1C,0xA0,0xA0,0xA0,0x7C},//y
{0x00,0x44,0x64,0x54,0x4C,0x44},//z-35
{0x00,0x00,0x60,0x60,0x00,0x00},//.
{0x00,0x14,0x14,0x14,0x14,0x14},//=
{0x00,0x08,0x08,0x3E,0x08,0x08},//+
{0x00,0x08,0x08,0x08,0x08,0x08},//-
{0x00,0x00,0x00,0x2f,0x00,0x00},//!-40
{0x00,0x32,0x49,0x59,0x51,0x3E},//@
{0x00,0x14,0x7f,0x14,0x7f,0x14},//#
{0x00,0x24,0x2a,0x7f,0x2a,0x12},//$
{0x00,0x62,0x64,0x08,0x13,0x23},//%
{0x00,0x36,0x49,0x55,0x22,0x50},//&-45
{0x00,0x14,0x08,0x3E,0x08,0x14},//*
{0x00,0x00,0x1c,0x22,0x41,0x00},//(
{0x00,0x00,0x41,0x22,0x1c,0x00},//)
{0x00,0x00,0x00,0x00,0x00,0x00},//sp
{0x00,0x00,0x01,0x02,0x04,0x00},//,-50
{0x00,0x20,0x10,0x08,0x04,0x02},///
{0x00,0x00,0x08,0x36,0x61,0x00},//{
{0x00,0x00,0xFF,0x00,0x00,0x00},//|
{0x00,0x00,0x61,0x36,0x08,0x00},//}
{0x00,0x02,0x04,0x02,0x01,0x02},//~-55
{0x00,0x00,0x36,0x36,0x00,0x00},//:
{0x00,0x00,0x56,0x36,0x00,0x00},//;
{0x00,0x08,0x14,0x22,0x41,0x00},//<
{0x00,0x00,0x05,0x03,0x00,0x00},//'
{0x00,0x00,0x41,0x22,0x14,0x08},//>-60
{0x00,0x02,0x01,0x51,0x09,0x06},//?
{0x00,0x00,0x07,0x00,0x07,0x00},//"
{0x00,0x00,0x7F,0x41,0x41,0x00},//[
{0x00,0x80,0x60,0x18,0x06,0x01},//\
{0x00,0x00,0x41,0x41,0x7F,0x00},//]-65
{0x00,0x04,0x02,0x01,0x02,0x04},//^
{0x00,0x40,0x40,0x40,0x40,0x40},//_
{0x00,0x55,0x2A,0x55,0x2A,0x55},//
{0x00,0x7C,0x12,0x11,0x12,0x7C},//A
{0x00,0x7F,0x49,0x49,0x49,0x36},//B-70
{0x00,0x3E,0x41,0x41,0x41,0x22},//C
{0x00,0x7F,0x41,0x41,0x22,0x1C},//D
{0x00,0x7F,0x49,0x49,0x49,0x41},//E
{0x00,0x7F,0x09,0x09,0x09,0x01},//F
{0x00,0x3E,0x41,0x49,0x49,0x7A},//G-75
{0x00,0x7F,0x08,0x08,0x08,0x7F},//H
{0x00,0x00,0x41,0x7F,0x41,0x00},//I
{0x00,0x20,0x40,0x41,0x3F,0x01},//J
{0x00,0x7F,0x08,0x14,0x22,0x41},//K
{0x00,0x7F,0x40,0x40,0x40,0x40},//L-80
{0x00,0x7F,0x02,0x0C,0x02,0x7F},//M
{0x00,0x7F,0x04,0x08,0x10,0x7F},//N
{0x00,0x3E,0x41,0x41,0x41,0x3E},//O
{0x00,0x7F,0x09,0x09,0x09,0x06},//P
{0x00,0x3E,0x41,0x51,0x21,0x5E},//Q-85
{0x00,0x7F,0x09,0x19,0x29,0x46},//R
{0x00,0x46,0x49,0x49,0x49,0x31},//S
{0x00,0x01,0x01,0x7F,0x01,0x01},//T
{0x00,0x3F,0x40,0x40,0x40,0x3F},//U
{0x00,0x1F,0x20,0x40,0x20,0x1F},//V-90
{0x00,0x3F,0x40,0x38,0x40,0x3F},//W
{0x00,0x63,0x14,0x08,0x14,0x63},//X
{0x00,0x07,0x08,0x70,0x08,0x07},//Y
{0x00,0x61,0x51,0x49,0x45,0x43},//Z
{0x00,0x18,0x30,0x1F,0x10,0x18},//个-95
{0x14,0x14,0x14,0x14,0x14,0x14}//horiz lines
};
//--16X16 汉字点阵码 联大管理学院
const unsigned char hanzi[]={
0x02,0xFE,0x92,0x92,0x92,0xFE,0x12,0x11,0x12,0x1C,0xF0,0x18,0x17,0x12,0x10,0x00,//联99-102
0x08,0x1F,0x08,0x08,0x04,0xFF,0x05,0x81,0x41,0x31,0x0F,0x11,0x21,0xC1,0x41,0x00,
0x20,0x20,0x20,0x20,0x20,0x20,0xA0,0x7F,0xA0,0x20,0x20,0x20,0x20,0x20,0x20,0x00,//大103-106
0x00,0x80,0x40,0x20,0x10,0x0C,0x03,0x00,0x01,0x06,0x08,0x30,0x60,0xC0,0x40,0x00,
0x08,0x64,0x23,0xA6,0xAA,0xA2,0xAA,0xB4,0xA3,0xA2,0xA6,0x2A,0x22,0x62,0x20,0x00,//管107-110
0x00,0x00,0x00,0xFF,0x4A,0x4A,0x4A,0x4A,0x4A,0x4A,0x4B,0xF8,0x00,0x00,0x00,0x00,
0x44,0x44,0xFC,0x44,0x44,0x00,0xFE,0x92,0x92,0xFE,0x92,0x92,0x92,0xFE,0x00,0x00,//理111-114
0x10,0x10,0x0F,0x08,0x48,0x40,0x45,0x44,0x44,0x7F,0x44,0x44,0x44,0x45,0x40,0x00,
0x40,0x30,0x10,0x12,0x5C,0x54,0x50,0x51,0x5E,0xD4,0x50,0x18,0x57,0x32,0x10,0x00,//学115-118
0x00,0x02,0x02,0x02,0x02,0x02,0x42,0x82,0x7F,0x02,0x02,0x02,0x02,0x02,0x02,0x00,
0xFE,0x02,0x32,0x4A,0x86,0x0C,0x24,0x24,0x25,0x26,0x24,0x24,0x24,0x0C,0x04,0x00,//院119-122
0xFF,0x00,0x02,0x04,0x83,0x41,0x31,0x0F,0x01,0x01,0x7F,0x81,0x81,0x81,0xF1,0x00,
//--16X16 汉字点阵码 极速奔驰
0x08,0x08,0xC8,0xFF,0x48,0x88,0x0A,0x02,0xFE,0x82,0x62,0x52,0x4E,0xC2,0x00,0x00,//极123-126
0x04,0x03,0x00,0xFF,0x40,0x21,0x58,0x47,0x20,0x21,0x12,0x0C,0x33,0x60,0x20,0x00,
0x40,0x42,0xCC,0x00,0x04,0xE4,0x24,0x24,0xFF,0x24,0x24,0x24,0xE4,0x04,0x00,0x00,//速127-130
0x40,0x20,0x1F,0x20,0x48,0x49,0x45,0x43,0x7F,0x41,0x43,0x45,0x4D,0x40,0x40,0x00,
0x80,0x84,0x44,0x24,0x54,0x4C,0x47,0xF4,0x44,0x4C,0x54,0x24,0x24,0xC4,0x44,0x00,//奔131-134
0x04,0x84,0x44,0x34,0x0F,0x04,0x04,0x05,0x04,0x04,0xFF,0x04,0x04,0x04,0x04,0x00,
0x00,0x02,0xFA,0x82,0xFE,0x80,0x40,0xFC,0x20,0x20,0xFF,0x10,0x10,0xF8,0x00,0x00,//驰135-138
0x08,0x08,0x04,0x24,0x40,0x3F,0x00,0x3F,0x40,0x40,0x4F,0x40,0x44,0x47,0x70,0x00,
//--16X16 汉字点阵 飞扬梦想队
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0xFE,0x60,0x90,0x08,0x00,0x00,0x00,//飞139-142
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0C,0x10,0x21,0x40,0x78,0x00,
0x08,0x08,0x08,0xFF,0x88,0x48,0x02,0x42,0x62,0xD2,0x4A,0xC6,0x42,0x40,0xC0,0x00,//扬143-146
0x02,0x42,0x81,0x7F,0x00,0x08,0x48,0x44,0x23,0x10,0x0C,0x43,0x80,0x40,0x3F,0x00,
0x40,0x44,0x24,0x14,0xFF,0x94,0x64,0x40,0x24,0x14,0xFF,0x0C,0x34,0x64,0x24,0x00,//梦147-150
0x00,0x80,0x88,0x88,0x46,0x45,0x29,0x31,0x11,0x09,0x05,0x03,0x01,0x00,0x00,0x00,
0x08,0xC8,0x38,0xFF,0x18,0x68,0x08,0x00,0xFE,0x2A,0x2A,0x2A,0x2A,0xFE,0x00,0x00,//想151-154
0x01,0x40,0x70,0x01,0x38,0x40,0x40,0x44,0x59,0x41,0x41,0x61,0x01,0x09,0x30,0x00,
0xFE,0x02,0x12,0x2A,0xC6,0x02,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,//队155-158
0x7F,0x00,0x02,0x44,0x43,0x20,0x10,0x0C,0x03,0x00,0x03,0x0C,0x10,0x60,0x20,0x00,
};





//LCD_write_byte:使用SPI接口写数据到LCD.输入参数:dt:写入的数据;command:写数据/命令选择
void LCD_write_byte(unsigned char dat,unsigned char command){
	unsigned char ci;
	SCE=LCD_SCE_OFF;
	DC=command;
	for(ci=0;ci<8;ci++){
		if(dat&0x80)
			DIN=LCD_DIN_ON;
		else
			DIN=LCD_DIN_OFF;
			dat=dat<<1;
			_asm(nop);
			CLK=LCD_CLK_OFF;
			CLK=LCD_CLK_ON;
	}
	DC=LCD_DC_ON;
	SCE=LCD_SCE_ON;
	DIN=LCD_DIN_ON;
}
//LCD_init:5110,3310LCD初始化
void LCD_init(void){
	RST=LCD_RST_OFF;
	_asm(nop);
	_asm(nop);
	RST=LCD_RST_ON;
	_asm(nop);
	LCD_write_byte(LCD_EXT,0);//初始化Lcd,功能设定使用扩充指令
	LCD_write_byte(LCD_DC,0);//设定液晶偏置电压
	LCD_write_byte(LCD_BASE,0);//使用基本指令
	LCD_write_byte(LCD_MODE,0);//设定显示模式，正常显示
	_asm(nop);
}
//LCD_set_XY:设置LCD坐标函数.输入参数:X:0-83Y:0-5
void LCD_set_XY(unsigned char X, unsigned char Y){
	LCD_write_byte(LCD_Y | Y, 0);// column
	LCD_write_byte(LCD_X | X, 0);// row
}
//LCD_clear:LCD清屏函数
void LCD_clear(void){
	unsigned char t;
	unsigned char k;
	LCD_set_XY(0,0);
	for(t=0;t<6;t++){
		for(k=0;k<84;k++){
			LCD_write_byte(0x00,1);
		}
	}
}
//LCD_Write_char:显示8X8点阵列数字字母符号等半角类;输入参数:c;显示的字符
void LCD_Write_char(unsigned char row,unsigned char page,unsigned char c){
		unsigned char line;
		LCD_set_XY(row*6,page);		
		for (line=0;line<6;line++)
			LCD_write_byte(num[c][line],1);
}
//写汉字到LCD函数,row,page:写入汉字的地址 c:写入汉字在hanzi表格中的位置
void LCD_write_hanzi(unsigned char row,unsigned char page,unsigned char c){ //row:列 page:页 c:字符
	unsigned char i;  	
	LCD_set_XY(row*8,page);//列,页 
	for(i=0;i<16;i++){
		LCD_write_byte(hanzi[c*32+i],1); 
	}
  LCD_set_XY(row*8,page+1);//列,页 
	for(i=16;i<32;i++){
		LCD_write_byte(hanzi[c*32+i],1);
	}
}
//显示屏幕初始化
void LCD_DISP(void){
  //设置LCD显示中文初始值
  for(js=0;js<12;js=js+2){
	  LCD_write_hanzi(js,0,js/2);//北京联合大学	
	}
	for(js=12;js<19;js=js+2){
	  LCD_write_hanzi(js-10,2,(js)/2);//管理学院	
	}
	for(js=20;js<28;js=js+2){
	  LCD_write_hanzi(js-19,4,(js)/2);//极速奔驰	
	}
	LCD_write_hanzi(9,4,18);//队
  delay(8000);
  }
   /************显示多位数据******************************************************/
void xianshi(unsigned int a) {
  b[2]=a/100;
  b[1]=(a%100)/10;
  b[0]=a%10;
  LCD_Write_char(5,2,b[2]) ;
	LCD_Write_char(6,2,b[1]) ;
	LCD_Write_char(7,2,b[0]) ;
	//delay(1000);
  }
 void xianshi1(unsigned int a) {
  c[2]=a/100;
  c[1]=(a%100)/10;
  c[0]=a%10;
  LCD_Write_char(5,4,c[2]) ;
	LCD_Write_char(6,4,c[1]) ;
	LCD_Write_char(7,4,c[0]) ;
//	delay(1000);
  } 

 