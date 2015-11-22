//头文件调用
#include "usually.h"
#include "usart.h"
#include "lcd12864.h"
#include "adc.h"
#include "tim.h"

//变量定义
//内部温度采集中包含的变量
volatile uint16_t  ADC_ConvertedValue_LocalValue=0;	
extern volatile uint16_t  ADC_ConvertedValue;			     //从adc.c中转移过来的变量
uint16_t  q,p,o,r;           
uint16_t TIM2_IRQHandler_Flag=0,TIM3_IRQHandler_Flag=0,TIM4_IRQHandler_Flag=0;	//TIM2，3，4的中断标志
//USART中包含的变量
const char menu[] =
   "\n\r"
   "+********************* STM32开发板  ********************+\n\r"	   //"\n"：在超级终端的作用是换行
   "|                                                       |\n\r"	   //"\r" :在超级终端的作用是置顶
   "|                  USART 异步通信试验                   |\n\r"
   "|                   www.scdbit.com                      |\n\r"
   "|                   成都贝一特科技                      |\n\r"
   "|                      2012.5.15                        |\n\r"
   "|                技术支持QQ：406795003                  |\n\r"
   "+-------------------------------------------------------+\n\r";

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

	lcd12864_WaitBusy();	       //lcd12864检查忙
	lcd12864_WriteCmd();	       //lcd12864写命令
	lcd12864_WriteData();	       //lcd12864写数据
	lcd12864_InitDis();		       //lcd12864初始化
	lcd12864_clear();		       //lcd12864清屏	   
//	lcd12864_draw_frame();		   //画边框
//  lcd12864_DrawPoint_f(90,50,1); //打点
//	lcd12864_LCD_set_dot(30,35);   //打点
//	lcd12864_draw_horizontal_line(50,50,5,1); //画横线

    ADC1_GPIO_Config();	           //ADC1
    ADC1_MODE_Config();			   //ADC1
   

	timer_init();	       //TIM初始化，包含TIM2，TIM3，TIM3，包含中断


//	printf(menu);					//输出字符串
//	printf("贝一特助你开启STM32大门,让你轻松入门！！\n\r");
//	printf("请输入键盘上的任意字符，串口将以十进制输出你输入的字符\n\r");		   
	while(1)													
	{  
	    LED1=~LED1;	   				
  	    Delay_Ms(200);				 //LED1闪烁，系统正在运行
		ADC_ConvertedValue_LocalValue=ADC_ConvertedValue;
    	ADC_ConvertedValue_LocalValue=(ADC_ConvertedValue_LocalValue*3300/4096);		//结果扩大1000倍
	    q=ADC_ConvertedValue_LocalValue/1000;
	    p=ADC_ConvertedValue_LocalValue/100%10;
	    o=ADC_ConvertedValue_LocalValue/10%10;
	    r=ADC_ConvertedValue_LocalValue%10;
	    lcd12864_WriteCmd(0x30);	  //退出作图模式
	    q=q+0x30;lcd12864_WriteCmd(0x98);lcd12864_WriteData(q);
	    p=p+0x30;;lcd12864_WriteData(p);
	    o=o+0x30;;lcd12864_WriteData(o);
		r=r+0x30;;lcd12864_WriteData(r);
	    lcd12864_DrawPoint_f(8,60,1); //打点
        printf("ADC1的采集值=%3d",ADC_ConvertedValue_LocalValue);
		LED2=~LED2;	
		ADC_ConvertedValue_LocalValue=0;
		   
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

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOG | RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOD,ENABLE);	//使能各个端口时钟，重要！！！
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;										
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   	//通用输出推挽	//D2
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   	//配置端口速度为50M
  	GPIO_Init(GPIOG, &GPIO_InitStructure);				   	//根据参数初始化GPIOG寄存器

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;										
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   	//通用输出推挽	 //D5
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   	//配置端口速度为50M
  	GPIO_Init(GPIOD, &GPIO_InitStructure);				   	//根据参数初始化GPIOD寄存器
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

	// 使能USART1中断
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			//配置串口1为中断源
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0; 	//设置占先优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  	//设置副优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  	//使能串口1中断
    NVIC_Init(&NVIC_InitStructure);							  //根据参数初始化中断寄存器	
     // 使能TIM2中断
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 
    // 使能TIM3中断
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    // 使能TIM4中断
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);		 

}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: TIM的中断处理函数，包含了TIM2，TIM3，TIM4
** 定时器2设置： 720分频，500ms中断一次，向上计数
** 定时器3设置： 720分频，250ms中断一次，向上计数
** 定时器4设置： 1440分频，1000ms中断一次，向上计数
** 功能描述: 系统中断配置
** 参数描述：无
** 作  　者: xt
** 日　  期: 2011年5月14日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM2_IRQHandler(void)
{ 
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
  {
    TIM2_IRQHandler_Flag=1;     //设置一个中断标志位 
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	    /* 清除 TIMx 的中断待处理位 */
	//LED2=~LED2;	
  }    
}
void TIM3_IRQHandler(void)
{ 
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 
  {
    TIM3_IRQHandler_Flag=1;     //设置一个中断标志位
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);	    /* 清除 TIMx 的中断待处理位 */
	//LED2=~LED2;	
  }    
}
void TIM4_IRQHandler(void)
{ 
 if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) 
   {
     TIM4_IRQHandler_Flag=1;     //设置一个中断标志位
     TIM_ClearITPendingBit(TIM4, TIM_IT_Update);    /* 清除 TIMx 的中断待处理位 */
	// LED2=~LED2;	
   }  
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
