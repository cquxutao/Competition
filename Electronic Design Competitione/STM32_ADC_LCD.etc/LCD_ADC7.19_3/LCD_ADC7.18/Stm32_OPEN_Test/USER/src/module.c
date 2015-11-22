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
  GPIO_SetBits(LED_1_GRP, LED1);
  GPIO_SetBits(LED_2_GRP, LED2);
  GPIO_SetBits(LED_3_6_GRP, LED3);
  GPIO_SetBits(LED_3_6_GRP, LED4);
  GPIO_SetBits(LED_3_6_GRP, LED5);
  GPIO_SetBits(LED_3_6_GRP, LED6);
  GPIO_SetBits(LED_7_8_GRP, LED7);
  GPIO_SetBits(LED_7_8_GRP, LED8);
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
  GPIO_ResetBits(LED_1_GRP, LED1);
  GPIO_ResetBits(LED_2_GRP, LED2);
  GPIO_ResetBits(LED_3_6_GRP, LED3);
  GPIO_ResetBits(LED_3_6_GRP, LED4);
  GPIO_ResetBits(LED_3_6_GRP, LED5);
  GPIO_ResetBits(LED_3_6_GRP, LED6);
  GPIO_ResetBits(LED_7_8_GRP, LED7);
  GPIO_ResetBits(LED_7_8_GRP, LED8);
}

/********************************************************************************************************
* 函 数 名 :  void function1(void)
* 描    述 : 功能函数1，当SW值为0001时,完成LED5-8的跑马灯程序及显示按键程序
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void function1(void)
{
  openfun1++;
  if(openfun1==1)
  {
   function2_close();
   function3_close();
   function4_close();
   function5_close();
   function6_close();
   function7_close();
   function8_close();
   Hex_test(1,1);
   TIM_Cmd(TIM2, ENABLE);
   TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
   TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	
   TIM2->CNT = 0;
  }
   
  if(GPIO_ReadInputDataBit(KEY_1_5_GRP, KEY1)==0)
  {
    delay_nus(5000);
    if(GPIO_ReadInputDataBit(KEY_1_5_GRP, KEY1)==0)
    {
      Hex_test(8,1);
    }
  }
  if(GPIO_ReadInputDataBit(KEY_1_5_GRP, KEY2)==0)
  {
    delay_nus(5000);
    if(GPIO_ReadInputDataBit(KEY_1_5_GRP, KEY2)==0)
    {
      Hex_test(8,2);
    }
  }
  if(GPIO_ReadInputDataBit(KEY_1_5_GRP, KEY3)==0)
  {
    delay_nus(5000);
    if(GPIO_ReadInputDataBit(KEY_1_5_GRP, KEY3)==0)
    {
      Hex_test(8,3);
    }
  }
  if(GPIO_ReadInputDataBit(KEY_1_5_GRP, KEY4)==0)
  {
    delay_nus(5000);
    if(GPIO_ReadInputDataBit(KEY_1_5_GRP, KEY4)==0)
    {
      Hex_test(8,4);
    }
  }
   if(GPIO_ReadInputDataBit(KEY_1_5_GRP, KEY5)==0)
  {
    delay_nus(5000);
    if(GPIO_ReadInputDataBit(KEY_1_5_GRP, KEY5)==0)
    {
      Hex_test(8,5);
    }
  }
   if(GPIO_ReadInputDataBit(KEY_6_8_GRP, KEY6)==0)
  {
    delay_nus(5000);
    if(GPIO_ReadInputDataBit(KEY_6_8_GRP, KEY6)==0)
    {
      Hex_test(8,6);
    }
  }
   if(GPIO_ReadInputDataBit(KEY_6_8_GRP, KEY7)==0)
  {
    delay_nus(5000);
    if(GPIO_ReadInputDataBit(KEY_6_8_GRP, KEY7)==0)
    {
      Hex_test(8,7);
    }
  }
   if(GPIO_ReadInputDataBit(KEY_6_8_GRP, KEY8)==0)
  {
    delay_nus(5000);
    if(GPIO_ReadInputDataBit(KEY_6_8_GRP, KEY8)==0)
    {
      Hex_test(8,8);
    }
  }
}
/********************************************************************************************************
* 函 数 名 :  void function1_close(void)
* 描    述 : 关闭功能函数1
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void function1_close(void)
{
   TIM_Cmd(TIM2, DISABLE);
   TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
    
   Hex_close(); 
   GPIO_ResetBits(LED_3_6_GRP, LED5);
   GPIO_ResetBits(LED_3_6_GRP, LED6);
   GPIO_ResetBits(LED_7_8_GRP, LED7);
   GPIO_ResetBits(LED_7_8_GRP, LED8);
   
   openfun1=0;
}
/********************************************************************************************************
* 函 数 名 :  void function2(void)
* 描    述 : 功能函数2，当SW值为0001时,完成外部中断测试:KEY1-4为外部中断每个中断来了其对应的发光二极管（1-4）取反。
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void function2(void)
{
  openfun2++;
  if(openfun2==1)
  {
   function1_close();
   function3_close();
   function4_close();
   function5_close();
   function6_close();
   function7_close();
   function8_close();
   Hex_test(1,2);
  }
   EXTI4_Configuration();
   EXTI5_Configuration();
   EXTI6_Configuration();
}
/********************************************************************************************************
* 函 数 名 :  void function2_close(void)
* 描    述 : 关闭功能函数1
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void function2_close(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
  
    EXTI_InitStructure.EXTI_Line = EXTI_Line4;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = DISABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line5;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = DISABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line6;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = DISABLE;
    EXTI_Init(&EXTI_InitStructure);
   
    GPIO_ResetBits(LED_3_6_GRP, LED4);
    GPIO_ResetBits(LED_3_6_GRP, LED5);
    GPIO_ResetBits(LED_3_6_GRP, LED6);
    
    openfun2=0;
}
/********************************************************************************************************
* 函 数 名 :  void function3(void)
* 描    述 : 功能函数3，当SW值为0010时,完成串口测试
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void function3(void)
{
  u16 i;
  u16 len1,len2,len3;
  char buf1[]="Hello! I am uast1.";
  char buf2[]="Hello! I am uast1.";
  char buf3[]="Hello! I am uast485.";
  
  openfun3++;
  if(openfun3==1)
  {
    function1_close();
    function2_close();
    function4_close();
    function5_close();
    function6_close();
    function7_close();
    function8_close();
    Hex_test(1,3);
    delay_nus(1000000);
    /* Enable the USART Receive interrupt: this interrupt is generated when the
    USART1 receive data register is not empty */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    /* Enable USART1 */
    USART_Cmd(USART1, ENABLE); 
    
    /* Enable the USART Receive interrupt: this interrupt is generated when the
    USART2 receive data register is not empty */
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    /* Enable USART2 */
    USART_Cmd(USART2, ENABLE); 
    
    /* Enable the USART Receive interrupt: this interrupt is generated when the
    USART3 receive data register is not empty */
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    /* Enable USART3 */
    USART_Cmd(USART3, ENABLE); 
  }
  
  len1=strlen(buf1);
  len2=strlen(buf2);
  len3=strlen(buf3);
  
  for(i=0;i<len1;i++)
  {
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1,buf1[i]);
  }
  
   for(i=0;i<len1;i++)
  {
    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    USART_SendData(USART2,buf2[i]);
  }
  
  GPIO_SetBits(UART3_GRP,UART3_485_DIR);	//RS_485 RE=1,to send 
  for(i=0;i<len3;i++)
  {
    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    USART_SendData(USART3,buf3[i]);
  }
  while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
  GPIO_ResetBits(UART3_GRP,UART3_485_DIR);	//RS_485 RE=0,to receive
  
  Display_LedNum(UsartReData);
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
/********************************************************************************************************
* 函 数 名 :  void function4(void)
* 描    述 : 功能函数4，当SW值为0011时,完成I2C测试
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
u8 Sedata=0;
u8 Findata;
u8 SeAddr=50;
u8 ReAddr;
u8 Secnt=0;
void function4(void)
{ 
  openfun4++;
  if(openfun4==1)
  {
    function1_close();
    function2_close();
    function3_close();
    function5_close();
    function6_close();
    function7_close();
    function8_close();
    Hex_test(1,4);
    delay_nus(1000000);
  }
  
//  LM75A_RcvTemp();
//  Display_LedNum(Tempdata); 
//  delay_nus(1000000);
//  
  ReAddr=SeAddr;
  // Transmitte
  AT24C64_WByte(SeAddr,Sedata+Secnt);
  
  delay_nus(5000);
  
  //Receive
  Findata=AT24C64_RByte(ReAddr);
  
  Hex_test(8,Findata);
  
  if(Findata==Sedata+Secnt)
  {
    GPIO_SetBits(LED_1_GRP, LED1);
  }   
  else
  {
    GPIO_ResetBits(LED_1_GRP, LED1);
  }
  Secnt++;
  if(Secnt==10)
  {
  Secnt=0;
  } 
  delay_nus(2000000);
}
/********************************************************************************************************
* 函 数 名 :  void function4_close(void)
* 描    述 : 关闭功能函数4
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void function4_close(void)
{
   /* Disable I2C1 */
   I2C_Cmd(I2C1, DISABLE);
   GPIO_ResetBits(LED_1_GRP, LED1);
   Secnt=0;
   openfun4=0;
}
/********************************************************************************************************
* 函 数 名 :  void function5(void)
* 描    述 : 功能函数5，当SW值为0100时,完成PS2测试：接入标准PS2键盘，按小键盘按键可以在数码管上显示相应的按键
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
u8 Hexdata;
void function5(void)
{
  openfun5++;
  if(openfun5==1)
  {
   function1_close();
   function2_close();
   function3_close();
   function4_close();
   function6_close();
   function7_close();
   function8_close();
   Hex_test(1,5);
  }
   PS2_Disp();
}/********************************************************************************************************
* 函 数 名 :  void function5_close(void)
* 描    述 : 关闭功能函数5
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void function5_close(void)
{   
    BitCnt=0;
    PS2_ReFlag=0;
    openfun5=0;
}
/********************************************************************************************************
* 函 数 名 :  void function6(void)
* 描    述 : 功能函数6，当SW值为0101时,完成蜂鸣器测试：给1Khz的信号进行测试，蜂鸣器应发声
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void function6(void)
{
  openfun6++;
  if(openfun6==1)
  {
   function1_close();
   function2_close();
   function3_close();
   function4_close();
   function5_close();
   function7_close();
   function8_close();
   Hex_test(1,6);
   TIM_Cmd(TIM3, ENABLE);
   TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
   TIM_ClearITPendingBit(TIM3, TIM_IT_Update);	
   TIM3->CNT = 0;
  }
}
/********************************************************************************************************
* 函 数 名 :  void function6_close(void)
* 描    述 : 关闭功能函数6
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void function6_close(void)
{
   TIM_Cmd(TIM3, DISABLE);
   TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
   GPIO_ResetBits(GPIOA, GPIO_Pin_4);
   openfun6=0;
}
/********************************************************************************************************
* 函 数 名 :  void function7(void)
* 描    述 : 功能函数7，当SW值为0110时,完成LCD测试：3张LCD图片轮流显示。间隔时间为2-3秒
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void function7(void)
{
  u8 i;
  u16 len;
  char buf[]="Welcom to uCOS2 System!";
  
  openfun7++;
  if(openfun7==1)
  {
    function1_close();
    function2_close();
    function3_close();
    function4_close();
    function5_close();
    function6_close();
    function8_close();
    Hex_test(1,7);
    ili9320_Initializtion();
    ili9320_Test();
    delay_nus(2000000);
    len=strlen(buf);
    
    for(i=0;i<len;i++)
    {
      ili9320_PutChar(30+i*8,150,buf[i],black,white);
    }
  }
  
}
/********************************************************************************************************
* 函 数 名 :  void function7_close(void)
* 描    述 : 关闭功能函数7
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void function7_close(void)
{
   //ili9320_Clear(0xffff);
   Lcd_Light_OFF;
   openfun7=0;
}
/********************************************************************************************************
* 函 数 名 :  void function8(void)
* 描    述 : 功能函数8，ADC测试程序
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void function8(void)
{ 
  openfun8++;
  if(openfun8==1)
  {
    function1_close();
    function2_close();
    function3_close();
    function4_close();
    function5_close();
    function6_close();
    function7_close();
    Hex_test(1,8);
    ADC_Configuration();
  }
  
}
/********************************************************************************************************
* 函 数 名 :  void function8_close(void)
* 描    述 : 关闭功能函数8
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void function8_close(void)
{
   ADC_Cmd(ADC2, DISABLE);
   ADC_SoftwareStartConvCmd(ADC2, DISABLE);
   ADC_ITConfig(ADC2, ADC_IT_EOC, DISABLE);
   openfun8=0;
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
