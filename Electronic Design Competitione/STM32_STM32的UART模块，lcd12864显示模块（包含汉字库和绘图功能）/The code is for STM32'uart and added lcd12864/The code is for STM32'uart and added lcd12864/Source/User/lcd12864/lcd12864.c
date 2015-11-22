
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
** 作  　者: XT
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
** 作  　者: XT
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
//    while(GPIO_ReadInputData(DisIO) & 0x0080); //只要位7的值，位7是忙标志位。
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

void lcd12864_InitDis(void)   //初始化 12864 和要用到的 STM 32 的引脚。
{
    lcd12864_IOInitOut(); 	
//    delay_init(72);   //初始化延时函数的微妙计数基数。  
    GPIO_SetBits(DisIO,PSB);  //令PSB=1，设置为并行数据模式。
    delay_ms(2); 
    lcd12864_WriteCmd(0x30);  //选择基本指令集，和，8位数据模式。
    delay_ms(2);
    lcd12864_WriteCmd(0x0c);  //开显示,无游标,不反白.
    delay_ms(2); 
    lcd12864_WriteCmd(0x01);  //清除显示，并将 DDRAM 的地址计数器 AC 设为 00H.
    delay_ms(2);
    lcd12864_WriteCmd(0x06);  //设置，外部读写数据后,地址记数器 AC 会自动加 1。
    delay_ms(2);
    lcd12864_WriteCmd(0x80);  //将 DDRAM 地址计数器 AC 设为 0.
    delay_ms(2);	
}

void lcd12864_DisStr(uint8_t *s)    //显示字符串的函数。
{
    while(*s != '\0')
    {
        lcd12864_WriteData(*s);
        s++;
        delay_ms(2);
    }
}




