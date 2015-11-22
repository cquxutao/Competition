
#include "usually.h"
#include "lcd12864.h"

/********** 以下是相关引脚定义。**************/

#define DisIO GPIOD                 //定义12864要使用的I/O端口。
#define DisClk RCC_APB2Periph_GPIOD  //定义12864要使用的I/O端口的时钟。
#define Data GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7
                                       //定义12864使用的数据引脚,GPIO_Pin_0连接12864的DB0,GPIO_Pin_1
									   //连接12864的DB1,依次类推。
#define RS GPIO_Pin_8
#define RW GPIO_Pin_9
#define EN GPIO_Pin_10       //定义使能端使用的引脚。
#define PSB GPIO_Pin_11      //定义并，串行数据模式的选择端口使用的引脚。

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: Delay_Ms_Ms
** 功能描述: 延时1MS (可通过仿真来判断他的准确度)			
** 参数描述：time (ms) 注意time<65535
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void delay_ms(uint16_t time)  //延时函数
{ 
	uint16_t i,j;
	for(i=0;i<time;i++)
  		for(j=0;j<10260;j++);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: Delay_Ms_Us
** 功能描述: 延时1us (可通过仿真来判断他的准确度)
** 参数描述：time (us) 注意time<65535				 
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void delay_us(uint16_t time)  //延时函数
{ 
	uint16_t i,j;
	for(i=0;i<time;i++)
  		for(j=0;j<9;j++);
}

                					    
void lcd12864_IOInitOut(void)           //把所有端口初始化为推挽输出模式的函数。
{
    GPIO_InitTypeDef  GPIO_InitStructure;  //定义用于定义所有引脚为输出的变量。

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//定义所有的引脚为推挽输出的变量初始化。
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = Data|RS|RW|EN|PSB;

    RCC_APB2PeriphClockCmd(DisClk,ENABLE);
    GPIO_Init(DisIO,&GPIO_InitStructure);	
}

void lcd12864_IOInitIn(void)           //把数据引脚初始化为浮空输入的函数。
{
    GPIO_InitTypeDef  GPIO_InitStructure;  //定义用于定义所有引脚为输出的变量。

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//定义数据引脚为浮空输入的变量初始化。
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = Data;

    RCC_APB2PeriphClockCmd(DisClk,ENABLE);   //把所有端口初始化为输出模式的函数。   
    GPIO_Init(DisIO,&GPIO_InitStructure);	
}

void lcd12864_WaitBusy(void)          //等待12864的忙状态结束的函数。
{
    lcd12864_IOInitIn();        //把数据引脚定义为浮空输入；
    GPIO_ResetBits(DisIO,RS);  //RS = 0.
    GPIO_SetBits(DisIO,RW);    //RW = 1.
    GPIO_SetBits(DisIO,EN);    //EN = 1.
//  while(GPIO_ReadInputData(DisIO) & 0x0080); //只要位7的值，位7是忙标志位。
    GPIO_ResetBits(DisIO,EN);  //EN = 0;
    lcd12864_IOInitOut();      //把所有引脚定义为输出。
}

void lcd12864_WriteCmd(uint8_t cmd)    //写命令函数。
{
  	lcd12864_WaitBusy(); 
    GPIO_ResetBits(DisIO,RS);  //RS = 0.
    GPIO_ResetBits(DisIO,RW);  //RW = 0. 
    GPIO_SetBits(DisIO,EN);    //EN = 1.
    DisIO->ODR=((DisIO->ODR & 0xff00)|cmd); //此处，只有直接操作寄存器才能
                  //达到，只改变输出数据寄存器ODR的低8位，其它位
                  //不变的目的。因为，只有低8位是数据引脚，
                  //其它位可能是控制引脚，不能改变。
    delay_ms(2);
    GPIO_ResetBits(DisIO,EN);  //EN = 0;
    delay_ms(2); 	
}

void lcd12864_WriteData(uint8_t data)  //写数据函数。
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
/****读数据函数*************************************************/
unsigned char lcd12864_readbyte(void)		 //这个函数主要用于打点时，读回数据，打完点后在把数据送回去；
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
/****清除显示*************************************************/
void lcd12864_clear(void)				//缺点：清屏有点慢
{
   unsigned char x,y;
   lcd12864_WriteCmd(0x34);
   lcd12864_WriteCmd(0x36);		 //需要两次，本次设置扩展指令集。
   for(y=0;y<32;y++)
   {
     lcd12864_WriteCmd(0x80+y);	  //设置y=1000+00xx，y+1则往下一行
	 lcd12864_WriteCmd(0x80); 	   //设置x=1000 0000
     for(x=0;x<16;x++)
	 {
	   lcd12864_WriteData(0x00);    //高字节数据
	   lcd12864_WriteData(0x00);	 //低字节数据	    
	 }
   }  
}
//初始化lcd12864
void lcd12864_InitDis(void)   //初始化 12864 和要用到的 STM 32 的引脚。//简单初始化
{
    lcd12864_IOInitOut(); 	
//    delay_init(72);   //初始化延时函数的微妙计数基数。  
    GPIO_SetBits(DisIO,PSB);  //令PSB=1，设置为并行数据模式。
    delay_ms(2); 
    lcd12864_WriteCmd(0x30);  //选择基本指令集，和，8位数据模式。
    delay_ms(2);
    lcd12864_WriteCmd(0x30);  //开显示,无游标,不反白.
    delay_ms(2); 
    lcd12864_WriteCmd(0x01);  //清除显示，并将 DDRAM 的地址计数器 AC 设为 00H.
    delay_ms(2);
    lcd12864_WriteCmd(0x06);  //设置，外部读写数据后,地址记数器 AC 会自动加 1。
    delay_ms(2);
    lcd12864_WriteCmd(0x0c);  //将 DDRAM 地址计数器 AC 设为 0.
    delay_ms(2);	
}
//lcd12864显示字符串
void lcd12864_DisStr(uint8_t *s)    //显示字符串的函数。
{
    while(*s != '\0')
    {
        lcd12864_WriteData(*s);
        s++;
        delay_ms(2);
    }
}
/*光标定位函数，第一个参数为行坐标，第二个为列坐标，行列坐标的值都从0开始排列。
只能以16个点的宽度为单位移动。*/
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


/****画点函数1,任何函数点都可以打*************************************************/
void lcd12864_DrawPoint_f(unsigned char x,unsigned char y,unsigned char Color )	  //0为取消该点；1为打该点；2为异或该点；
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

/****画点函数2*************************************************/
void lcd12864_LCD_set_dot(unsigned char px,unsigned char py)  //也是任意点都可以打
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

/*******画横线函数*******************************************/ 
void lcd12864_draw_horizontal_line(unsigned char px,unsigned char py,unsigned char n,unsigned char xu)	//0为实线，1为虚线
{
      unsigned char i,j,x,y,x_byte,x_bit,y_byte,y_bit;
      lcd12864_WriteCmd(0x36);				   //进入画图/打点模式
          x=px&0x7f;                           //可选择起始点，长度，虚线或者实线
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
  lcd12864_WriteCmd(0x30);		               //进入写作模式，退出打点模式
}

/*******画竖线函数*******************************************/ 
/*
void lcd12864_draw_Rline(unsigned char px,unsigned char py,unsigned char n,unsigned char xu)
{
      unsigned char i,j,x,y,x_byte,x_bit,y_byte,y_bit;
      lcd12864_WriteCmd(0x36);
          x=px&0x7f;                           //可选择起始点，长度，虚线或者实线
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
/*******画边框函数*******************************************/
void lcd12864_draw_frame()
{
  unsigned char i,j;
   lcd12864_WriteCmd(0x80);
   for(i=0;i<16;i++){lcd12864_WriteData(0x55);}   //上边框边框
    
    lcd12864_draw_horizontal_line(0,63,16,1);   //下边框
    
   // lcd12864_WriteCmd(0x98);
   // for(i=0;i<16;i++){lcd12864_WriteData(0x55);}   //下边框
  
} 