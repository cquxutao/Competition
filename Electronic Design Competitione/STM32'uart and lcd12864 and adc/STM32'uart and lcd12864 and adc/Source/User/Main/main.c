//头文件调用
#include "usually.h"
#include "usart.h"
#include "lcd12864.h"
#include "adc.h"

//变量定义
//内部温度采集中包含的变量
volatile uint16_t  ADC_ConvertedValue_Temper_LocalValue;	 //内部温度采集值
extern volatile uint16_t  ADC_ConvertedValue;			     //从adc.c中转移过来的变量
uint16_t  inter_temper;               //内部温度
unsigned char  a,b,c;
//USART中包含的变量

//函数申明
void Init_LED(void);	
void Init_NVIC(void);
void Delay_Ms(uint16_t time);  
void Delay_Us(uint16_t time); 
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: main
** 功能描述: 主函数入口
** 参数描述：这个程序演示了串口收发程序 ，接收是采用中断方式
				你可以输入键盘上的任意值 电脑超级终端将以十进制输出你输入的数值 
				比如：1对应十进制是49；2对应于50；a对应于97；这个你懂！！！
** 作  　者: xt
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
int main(void)
{
	SystemInit();					//系统时钟配置
	Init_NVIC();					//中断向量表注册函数
	Init_LED();						//各个外设引脚配置

	Init_Usart();					//串口引脚配置			//Usart
	Usart_Configuration(115200);	//串口配置 设置波特率为115200    //Usart

	lcd12864_WaitBusy();	       //lcd12864
	lcd12864_WriteCmd();	       //lcd12864
	lcd12864_WriteData();	       //lcd12864
	lcd12864_InitDis();		       //lcd12864
//	lcd12864_locate16(1,1);	       //lcd12864
//	lcd12864_DisStr("abcdefg");	   //lcd12864

    ADC1_GPIO_Config();	           //温度ADC1
    ADC1_MODE_Config();			   //温度ADC1


//	printf(menu);					//输出字符串
//	printf("贝一特助你开启STM32大门,让你轻松入门！！\n\r");
//	printf("请输入键盘上的任意字符，串口将以十进制输出你输入的字符\n\r");		   
	while(1)													
	{  
		LED1=~LED1;	   				
		Delay_Ms(200);				 //LED1闪烁，系统正在运行
		ADC_ConvertedValue_Temper_LocalValue=ADC_ConvertedValue;
		Delay_Ms(200);
		inter_temper=(1.43-ADC_ConvertedValue_Temper_LocalValue*3.3/4096)/0.0043+25;
	    printf("当前温度=%d\tADC1的采集值=%3d",inter_temper,ADC_ConvertedValue_Temper_LocalValue);
		lcd12864_WriteCmd(0x80);
	    lcd12864_DisStr("当前温度=");
		lcd12864_WriteCmd(0x87);
	    lcd12864_DisStr("度");
		a=(unsigned char)inter_temper/10;
		b=(unsigned char)inter_temper%10;
		c=a+0x30;
		lcd12864_WriteCmd(0x85);
		lcd12864_WriteData(c);
		c=b+0x30;
		lcd12864_WriteCmd(0x86);
    	lcd12864_WriteData(c);

	}
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: Init_LED
** 功能描述: LED IO引脚配置
** 参数描述：无
** 作  　者: xt
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_LED(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;					//定义一个GPIO结构体变量

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOG | RCC_APB2Periph_GPIOE,ENABLE);	//使能各个端口时钟，重要！！！
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;										
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   	//通用输出推挽
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   	//配置端口速度为50M
  	GPIO_Init(GPIOG, &GPIO_InitStructure);				   	//根据参数初始化GPIOD寄存器
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: Init_NVIC
** 功能描述: 系统中断配置
** 参数描述：无
** 作  　者: xt
** 日　  期: 2011年5月14日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_NVIC(void)
{ 	
  	NVIC_InitTypeDef NVIC_InitStructure;			//定义一个NVIC向量表结构体变量

	#ifdef  VECT_TAB_RAM  							//向量表基地址选择

	  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);  	//将0x20000000地址作为向量表基地址(RAM)
	#else  

	  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0); //将0x08000000地址作为向量表基地址(FLASH)  
	#endif

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置中断组 为2 

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			//配置串口1为中断源
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 	//设置占先优先级为2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  	//设置副优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  	//使能串口1中断
	NVIC_Init(&NVIC_InitStructure);							  	//根据参数初始化中断寄存器
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: Delay_Ms_Ms
** 功能描述: 延时1MS (可通过仿真来判断他的准确度)			
** 参数描述：time (ms) 注意time<65535
** 作  　者: xt
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Delay_Ms(uint16_t time)  //延时函数
{ 
	uint16_t i,j;
	for(i=0;i<time;i++)
  		for(j=0;j<10260;j++);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: Delay_Ms_Us
** 功能描述: 延时1us (可通过仿真来判断他的准确度)
** 参数描述：time (us) 注意time<65535				 
** 作  　者: xt
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Delay_Us(uint16_t time)  //延时函数
{ 
	uint16_t i,j;
	for(i=0;i<time;i++)
  		for(j=0;j<9;j++);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
