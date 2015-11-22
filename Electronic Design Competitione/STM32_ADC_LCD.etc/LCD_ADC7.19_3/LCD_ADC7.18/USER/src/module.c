#include "includes.h"

u32 openfun1=0;
u32 openfun2=0;
u32 openfun3=0;
u32 openfun4=0;
u32 openfun5=0;
u32 openfun6=0;
u32 openfun7=0;
u32 openfun8=0;
u16 UsartReData;
/********************************************************************************************************
* 函 数 名 :  void LED_open(void)
* 描    述 : 打开所有的LED
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void LED_open(void)
{
  GPIO_SetBits(LED_2_GRP, LED2);
  GPIO_SetBits(LED_5_GRP, LED5);
}

/********************************************************************************************************
* 函 数 名 :  void LED_close(void)
* 描    述 : 关闭所有的LED
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void LED_close(void)
{
  GPIO_SetBits(LED_2_GRP, LED2);
  GPIO_SetBits(LED_5_GRP, LED5);
}

/********************************************************************************************************
* 函 数 名 :  void function3(void)
* 描    述 : 功能函数3，当SW值为0010时,完成串口测试
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
unsigned char AD_dis_save[992];
u8 save_y[104];
void function3(void)
{ 
    u16 i;
    extern unsigned char send;
    /* Enable the USART Receive interrupt: this interrupt is generated when the
    USART1 receive data register is not empty */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    /* Enable USART1 */
    USART_Cmd(USART1, ENABLE); 

    for(i=0;i<104;i++)
    {
      while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
      USART_SendData(USART1,save_y[i]);
      delay_nus(100000);
      
    }
    send=0;

}
/********************************************************************************************************
* 函 数 名 :  void function3_close(void)
* 描    述 : 关闭功能函数3
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void function3_close(void)
{  
   /* Disable USART1 */
   USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
   USART_Cmd(USART1, DISABLE); 
   
   /* Disable USART2 */
   USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
   USART_Cmd(USART1, DISABLE);
   
   /* Disable USART3 */
   USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
   USART_Cmd(USART3, DISABLE);
   
   UsartReData=0;
   
   openfun3=0;
}

/*******************************************************************
函数名称：X_change
函数功能：
输入参数：
函数说明：通过读取开关状态E0 E1 E2  显示X的档位
*******************************************************************/
/*void X_change(void)
{
    u8 flag_x1,flag_x2,flag_x3;
    if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0))
        flag_x1=0;
    else
        flag_x1=1;
    else if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1))
        flag_x2=0;
    else
        flag_x2=1;
    else if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2))
        flag_x3=0;
    else
        flag_x3=1;
    
    if(flag_x1==1)      //1V/DIV
        
    else if(flag_x2==1) //0.1V/DIV
      
    else if(flag_x3==1) //0.01V/DIV
}

/*******************************************************************
函数名称：delay_nus
函数功能：延时函数
输入参数：时长us
函数说明：经过示波器测试单独运行此函数其周期为1us
若改为i--,则i=7时约为1us
*******************************************************************/
void delay_nus(u32 us)
{
    unsigned char i;
    while(--us)
    {
        i=8;             //1us
        while(--i);
    } 
}

void delay_nms(u32 ms)
{
    unsigned char i;
    while(--ms)
    {
        i=8000;             //1ms
        while(--i);
    } 
}
