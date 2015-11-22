
#include "usually.h"
#include "lcd12864.h"

/********** ������������Ŷ��塣**************/

#define DisIO GPIOD                 //����12864Ҫʹ�õ�I/O�˿ڡ�
#define DisClk RCC_APB2Periph_GPIOD  //����12864Ҫʹ�õ�I/O�˿ڵ�ʱ�ӡ�
#define Data GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7
                                       //����12864ʹ�õ���������,GPIO_Pin_0����12864��DB0,GPIO_Pin_1
									   //����12864��DB1,�������ơ�
#define RS GPIO_Pin_8
#define RW GPIO_Pin_9
#define EN GPIO_Pin_10       //����ʹ�ܶ�ʹ�õ����š�
#define PSB GPIO_Pin_11      //���岢����������ģʽ��ѡ��˿�ʹ�õ����š�

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Delay_Ms_Ms
** ��������: ��ʱ1MS (��ͨ���������ж�����׼ȷ��)			
** ����������time (ms) ע��time<65535
** ��  ����: Dream
** �ա�  ��: 2011��6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void delay_ms(uint16_t time)  //��ʱ����
{ 
	uint16_t i,j;
	for(i=0;i<time;i++)
  		for(j=0;j<10260;j++);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Delay_Ms_Us
** ��������: ��ʱ1us (��ͨ���������ж�����׼ȷ��)
** ����������time (us) ע��time<65535				 
** ��  ����: Dream
** �ա�  ��: 2011��6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void delay_us(uint16_t time)  //��ʱ����
{ 
	uint16_t i,j;
	for(i=0;i<time;i++)
  		for(j=0;j<9;j++);
}

                					    
void lcd12864_IOInitOut(void)           //�����ж˿ڳ�ʼ��Ϊ�������ģʽ�ĺ�����
{
    GPIO_InitTypeDef  GPIO_InitStructure;  //�������ڶ�����������Ϊ����ı�����

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������е�����Ϊ��������ı�����ʼ����
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = Data|RS|RW|EN|PSB;

    RCC_APB2PeriphClockCmd(DisClk,ENABLE);
    GPIO_Init(DisIO,&GPIO_InitStructure);	
}

void lcd12864_IOInitIn(void)           //���������ų�ʼ��Ϊ��������ĺ�����
{
    GPIO_InitTypeDef  GPIO_InitStructure;  //�������ڶ�����������Ϊ����ı�����

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//������������Ϊ��������ı�����ʼ����
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = Data;

    RCC_APB2PeriphClockCmd(DisClk,ENABLE);   //�����ж˿ڳ�ʼ��Ϊ���ģʽ�ĺ�����   
    GPIO_Init(DisIO,&GPIO_InitStructure);	
}

void lcd12864_WaitBusy(void)          //�ȴ�12864��æ״̬�����ĺ�����
{
    lcd12864_IOInitIn();        //���������Ŷ���Ϊ�������룻
    GPIO_ResetBits(DisIO,RS);  //RS = 0.
    GPIO_SetBits(DisIO,RW);    //RW = 1.
    GPIO_SetBits(DisIO,EN);    //EN = 1.
//  while(GPIO_ReadInputData(DisIO) & 0x0080); //ֻҪλ7��ֵ��λ7��æ��־λ��
    GPIO_ResetBits(DisIO,EN);  //EN = 0;
    lcd12864_IOInitOut();      //���������Ŷ���Ϊ�����
}

void lcd12864_WriteCmd(uint8_t cmd)    //д�������
{
  	lcd12864_WaitBusy(); 
    GPIO_ResetBits(DisIO,RS);  //RS = 0.
    GPIO_ResetBits(DisIO,RW);  //RW = 0. 
    GPIO_SetBits(DisIO,EN);    //EN = 1.
    DisIO->ODR=((DisIO->ODR & 0xff00)|cmd); //�˴���ֻ��ֱ�Ӳ����Ĵ�������
                  //�ﵽ��ֻ�ı�������ݼĴ���ODR�ĵ�8λ������λ
                  //�����Ŀ�ġ���Ϊ��ֻ�е�8λ���������ţ�
                  //����λ�����ǿ������ţ����ܸı䡣
    delay_ms(2);
    GPIO_ResetBits(DisIO,EN);  //EN = 0;
    delay_ms(2); 	
}

void lcd12864_WriteData(uint8_t data)  //д���ݺ�����
{
	lcd12864_WaitBusy(); 
    GPIO_SetBits(DisIO,RS);  //RS = 1. 
    GPIO_ResetBits(DisIO,RW);  //RW = 0. 
    GPIO_SetBits(DisIO,EN);    //EN = 1.
    DisIO->ODR=((DisIO->ODR & 0xff00)|data);  
    delay_ms(2);
    GPIO_ResetBits(DisIO,EN);  //EN = 0;
    delay_ms(2); 
}
/****�����ݺ���*************************************************/
unsigned char lcd12864_readbyte(void)		 //���������Ҫ���ڴ��ʱ���������ݣ��������ڰ������ͻ�ȥ��
{ 	
	unsigned char byReturnValue ;
	lcd12864_WaitBusy();
	lcd12864_IOInitIn();
	GPIO_SetBits(DisIO,RS);    //RS = 1.
    GPIO_SetBits(DisIO,RW);    //RW = 1.
    GPIO_ResetBits(DisIO,EN);    //EN = 0.
	delay_us(10);
	GPIO_SetBits(DisIO,EN);    //EN = 1.
    byReturnValue=(unsigned char)(GPIO_ReadInputData(GPIOD)&0x0080);
	GPIO_ResetBits(DisIO,EN);    //EN = 0.
    lcd12864_IOInitOut();
	return byReturnValue ;
    
}
/****�����ʾ*************************************************/
void lcd12864_clear(void)				//ȱ�㣺�����е���
{
   unsigned char x,y;
   lcd12864_WriteCmd(0x34);
   lcd12864_WriteCmd(0x36);		 //��Ҫ���Σ�����������չָ���
   for(y=0;y<32;y++)
   {
     lcd12864_WriteCmd(0x80+y);	  //����y=1000+00xx��y+1������һ��
	 lcd12864_WriteCmd(0x80); 	   //����x=1000 0000
     for(x=0;x<16;x++)
	 {
	   lcd12864_WriteData(0x00);    //���ֽ�����
	   lcd12864_WriteData(0x00);	 //���ֽ�����	    
	 }
   }  
}
//��ʼ��lcd12864
void lcd12864_InitDis(void)   //��ʼ�� 12864 ��Ҫ�õ��� STM 32 �����š�//�򵥳�ʼ��
{
    lcd12864_IOInitOut(); 	
//    delay_init(72);   //��ʼ����ʱ������΢�����������  
    GPIO_SetBits(DisIO,PSB);  //��PSB=1������Ϊ��������ģʽ��
    delay_ms(2); 
    lcd12864_WriteCmd(0x30);  //ѡ�����ָ����ͣ�8λ����ģʽ��
    delay_ms(2);
    lcd12864_WriteCmd(0x30);  //����ʾ,���α�,������.
    delay_ms(2); 
    lcd12864_WriteCmd(0x01);  //�����ʾ������ DDRAM �ĵ�ַ������ AC ��Ϊ 00H.
    delay_ms(2);
    lcd12864_WriteCmd(0x06);  //���ã��ⲿ��д���ݺ�,��ַ������ AC ���Զ��� 1��
    delay_ms(2);
    lcd12864_WriteCmd(0x0c);  //�� DDRAM ��ַ������ AC ��Ϊ 0.
    delay_ms(2);	
}
//lcd12864��ʾ�ַ���
void lcd12864_DisStr(uint8_t *s)    //��ʾ�ַ����ĺ�����
{
    while(*s != '\0')
    {
        lcd12864_WriteData(*s);
        s++;
        delay_ms(2);
    }
}
/*��궨λ��������һ������Ϊ�����꣬�ڶ���Ϊ�����꣬���������ֵ����0��ʼ���С�
ֻ����16����Ŀ��Ϊ��λ�ƶ���*/
void lcd12864_locate16(uint8_t row, uint8_t col) 
{
	switch(row)
	{
		case 1: lcd12864_WriteCmd(0x80+col-1); break;
		case 2: lcd12864_WriteCmd(0x90+col-1); break;
		case 3: lcd12864_WriteCmd(0x88+col-1); break;
		case 4: lcd12864_WriteCmd(0x98+col-1); break;
	}
}


/****���㺯��1,�κκ����㶼���Դ�*************************************************/
void lcd12864_DrawPoint_f(unsigned char x,unsigned char y,unsigned char Color )	  //0Ϊȡ���õ㣻1Ϊ��õ㣻2Ϊ���õ㣻
{
    unsigned char Y,Row , Tier , Tier_bit    ;
    unsigned char  ReadOldH, ReadOldL  ;
    lcd12864_WriteCmd(0x34);
    Y=y;
    Tier=x>>4;    
    Tier_bit=x&0x0f;
    if(Y<32)
    {
        Row=Y;
    }
    else
    {
        Row=Y-32;
        Tier+=8;
    }
    lcd12864_WriteCmd( Row+0x80);
    lcd12864_WriteCmd( Tier+0x80);
 //   u8_Lcd12864ReadByte_f();
	lcd12864_readbyte();
    ReadOldH=lcd12864_readbyte(); 
    ReadOldL=lcd12864_readbyte(); 
    lcd12864_WriteCmd(Row+0x80);
    lcd12864_WriteCmd(Tier+0x80);
    if(Tier_bit<8)
    {
        switch(Color)
        {
            case 0 : ReadOldH&=(~(0x01<<(7-Tier_bit))); break;
            case 1 : ReadOldH|=(0x01<<(7-Tier_bit));  break;
            case 2 : ReadOldH^=(0x01<<(7-Tier_bit)); break;
            default : break ;    
        }
        lcd12864_WriteData( ReadOldH ) ;
        lcd12864_WriteData( ReadOldL ) ;
    }
    else
    {
        switch(Color)
        {
            case 0 : ReadOldL &= (~( 0x01 << ( 15 - Tier_bit ))) ;  break ;
            case 1 : ReadOldL |= ( 0x01 << ( 15 - Tier_bit ))    ;  break ;
            case 2 : ReadOldL ^= ( 0x01 << ( 15 - Tier_bit ))  ;  break ;
            default : break ;
        }
        lcd12864_WriteData( ReadOldH ) ;
        lcd12864_WriteData( ReadOldL ) ;
    }
    
    lcd12864_WriteCmd(0x36);
    lcd12864_WriteCmd(0x30);
}

/****���㺯��2*************************************************/
void lcd12864_LCD_set_dot(unsigned char px,unsigned char py)  //Ҳ������㶼���Դ�
{
 unsigned char x,y,x_byte,x_bit,y_byte,y_bit,tmph,tmpl;
  x=px&0x7f;
  y=py&0x3f;
  x_byte=x/16;
  x_bit=x&0x0f;
  y_byte=y/32;
  y_bit=y&0x1f;
  lcd12864_WriteCmd(0x36);

  lcd12864_WriteCmd(0x80+y_bit);
  lcd12864_WriteCmd(0x80+x_byte+8*y_byte);
  
 // u8_Lcd12864ReadByte_f();
  lcd12864_readbyte();
  //Delay(2);
  tmph=lcd12864_readbyte();
  tmpl=lcd12864_readbyte();
  //Delay(20);
  lcd12864_WriteCmd(0x80+y_bit);
  lcd12864_WriteCmd(0x80+x_byte+8*y_byte);
  //Delay(20);
  if(x_bit<8)
	{ lcd12864_WriteData(tmph|(0x01<<(7-x_bit)));
           lcd12864_WriteData(tmpl);
	}
	else
	{ lcd12864_WriteData(tmph);
          lcd12864_WriteData(tmpl|(0x01<<(15-x_bit)));
	}
//	write_12864com(0x36);
	lcd12864_WriteCmd(0x30);
}

/*******�����ߺ���*******************************************/ 
void lcd12864_draw_horizontal_line(unsigned char px,unsigned char py,unsigned char n,unsigned char xu)	//0Ϊʵ�ߣ�1Ϊ����
{
      unsigned char i,j,x,y,x_byte,x_bit,y_byte,y_bit;
      lcd12864_WriteCmd(0x36);				   //���뻭ͼ/���ģʽ
          x=px&0x7f;                           //��ѡ����ʼ�㣬���ȣ����߻���ʵ��
          y=py&0x3f;
          x_byte=x/16;
          x_bit=x&0x0f;
          y_byte=y/32;
          y_bit=y&0x1f;
  lcd12864_WriteCmd(0x80+y_bit);
  lcd12864_WriteCmd(0x80+8*y_byte+x_byte);
  for(i=0;i<n;i++){
    if(xu) lcd12864_WriteData(0x55);
      else  lcd12864_WriteData(0xff);
  }
  lcd12864_WriteCmd(0x30);		               //����д��ģʽ���˳����ģʽ
}

/*******�����ߺ���*******************************************/ 
/*
void lcd12864_draw_Rline(unsigned char px,unsigned char py,unsigned char n,unsigned char xu)
{
      unsigned char i,j,x,y,x_byte,x_bit,y_byte,y_bit;
      lcd12864_WriteCmd(0x36);
          x=px&0x7f;                           //��ѡ����ʼ�㣬���ȣ����߻���ʵ��
          y=py&0x3f;
          x_byte=x/16;
          x_bit=x&0x0f;
          y_byte=y/32;
          y_bit=y&0x1f;
  lcd12864_WriteCmd(0x80+y_bit);
  lcd12864_WriteCmd(0x80+8*y_byte+x_byte);
  for(i=0;i<n;i++){
    if(xu) lcd12864_WriteData(0x55);
      else  lcd12864_WriteData(0xff);
  }
}
*/
/*******���߿���*******************************************/
void lcd12864_draw_frame()
{
  unsigned char i,j;
   lcd12864_WriteCmd(0x80);
   for(i=0;i<16;i++){lcd12864_WriteData(0x55);}   //�ϱ߿�߿�
    
    lcd12864_draw_horizontal_line(0,63,16,1);   //�±߿�
    
   // lcd12864_WriteCmd(0x98);
   // for(i=0;i<16;i++){lcd12864_WriteData(0x55);}   //�±߿�
  
} 