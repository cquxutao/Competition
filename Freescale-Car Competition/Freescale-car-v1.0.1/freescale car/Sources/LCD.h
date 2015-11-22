#pragma LINK_INFO DERIVATIVE "MC9S12XS128"

#ifndef _5110t
#define _5110t
#include "derivative.h"	//derivative-specific definitions

#define uchar unsigned char
#define uint unsigned int
//LCD Pins���ӷ�ʽ�Ͷ���
#define SCE PORTB_PB0
#define RST PORTB_PB1
#define DC PORTB_PB2
#define DIN PORTB_PB3
#define CLK PORTB_PB4
//LCD initize
#define LCD_EXT 0x21	//��ʼ��LCD,�����趨ʹ������ָ��
#define LCD_DC  0xD0	//�趨Һ��ƫ�õ�ѹ,����ǿɵ����ȵĸ�ֵ��
#define LCD_BASE 0x20	//ʹ�û���ָ��
#define LCD_MODE 0x0C	//�趨��ʾģʽ��������ʾ
#define LCD_Y 0x40	  //�趨LCD��ʾ��
#define LCD_X 0x80	  //�趨LCD��ʾ��
//LCD On/Off
#define LCD_DIN_OFF 0	//LCD���뿪��
#define LCD_DIN_ON 1
#define LCD_CLK_OFF 0	//LCDʱ�ӿ���
#define LCD_CLK_ON 1
#define LCD_SCE_OFF 0	//LCDƬѡ
#define LCD_SCE_ON 1
#define LCD_RST_OFF 0	//LCD��λ
#define LCD_RST_ON 1
#define LCD_DC_OFF 0	//LCD��������
#define LCD_DC_ON 1

//ECT����
#define TSCR2_Db 0x06;//��ֹ����жϣ���Ƶϵ��Ϊ64
#define TCTL4_Db 0x01;//��׽������
#define TSCR1_Db 0x80;//ʹ�ܶ�ʱ��

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
