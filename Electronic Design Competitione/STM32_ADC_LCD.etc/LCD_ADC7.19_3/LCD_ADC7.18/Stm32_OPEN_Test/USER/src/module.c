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
* �� �� �� :  void LED_open(void)
* ��    �� : �����е�LED
* ������� : None.
* ������� : None.
* ��   ��  : None.
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
* �� �� �� :  void LED_close(void)
* ��    �� : �ر����е�LED
* ������� : None.
* ������� : None.
* ��   ��  : None.
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
* �� �� �� :  void function1(void)
* ��    �� : ���ܺ���1����SWֵΪ0001ʱ,���LED5-8������Ƴ�����ʾ��������
* ������� : None.
* ������� : None.
* ��   ��  : None.
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
* �� �� �� :  void function1_close(void)
* ��    �� : �رչ��ܺ���1
* ������� : None.
* ������� : None.
* ��   ��  : None.
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
* �� �� �� :  void function2(void)
* ��    �� : ���ܺ���2����SWֵΪ0001ʱ,����ⲿ�жϲ���:KEY1-4Ϊ�ⲿ�ж�ÿ���ж��������Ӧ�ķ�������ܣ�1-4��ȡ����
* ������� : None.
* ������� : None.
* ��   ��  : None.
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
* �� �� �� :  void function2_close(void)
* ��    �� : �رչ��ܺ���1
* ������� : None.
* ������� : None.
* ��   ��  : None.
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
* �� �� �� :  void function3(void)
* ��    �� : ���ܺ���3����SWֵΪ0010ʱ,��ɴ��ڲ���
* ������� : None.
* ������� : None.
* ��   ��  : None.
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
* �� �� �� :  void function3_close(void)
* ��    �� : �رչ��ܺ���3
* ������� : None.
* ������� : None.
* ��   ��  : None.
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
* �� �� �� :  void function4(void)
* ��    �� : ���ܺ���4����SWֵΪ0011ʱ,���I2C����
* ������� : None.
* ������� : None.
* ��   ��  : None.
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
* �� �� �� :  void function4_close(void)
* ��    �� : �رչ��ܺ���4
* ������� : None.
* ������� : None.
* ��   ��  : None.
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
* �� �� �� :  void function5(void)
* ��    �� : ���ܺ���5����SWֵΪ0100ʱ,���PS2���ԣ������׼PS2���̣���С���̰������������������ʾ��Ӧ�İ���
* ������� : None.
* ������� : None.
* ��   ��  : None.
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
* �� �� �� :  void function5_close(void)
* ��    �� : �رչ��ܺ���5
* ������� : None.
* ������� : None.
* ��   ��  : None.
********************************************************************************************************/
void function5_close(void)
{   
    BitCnt=0;
    PS2_ReFlag=0;
    openfun5=0;
}
/********************************************************************************************************
* �� �� �� :  void function6(void)
* ��    �� : ���ܺ���6����SWֵΪ0101ʱ,��ɷ��������ԣ���1Khz���źŽ��в��ԣ�������Ӧ����
* ������� : None.
* ������� : None.
* ��   ��  : None.
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
* �� �� �� :  void function6_close(void)
* ��    �� : �رչ��ܺ���6
* ������� : None.
* ������� : None.
* ��   ��  : None.
********************************************************************************************************/
void function6_close(void)
{
   TIM_Cmd(TIM3, DISABLE);
   TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
   GPIO_ResetBits(GPIOA, GPIO_Pin_4);
   openfun6=0;
}
/********************************************************************************************************
* �� �� �� :  void function7(void)
* ��    �� : ���ܺ���7����SWֵΪ0110ʱ,���LCD���ԣ�3��LCDͼƬ������ʾ�����ʱ��Ϊ2-3��
* ������� : None.
* ������� : None.
* ��   ��  : None.
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
* �� �� �� :  void function7_close(void)
* ��    �� : �رչ��ܺ���7
* ������� : None.
* ������� : None.
* ��   ��  : None.
********************************************************************************************************/
void function7_close(void)
{
   //ili9320_Clear(0xffff);
   Lcd_Light_OFF;
   openfun7=0;
}
/********************************************************************************************************
* �� �� �� :  void function8(void)
* ��    �� : ���ܺ���8��ADC���Գ���
* ������� : None.
* ������� : None.
* ��   ��  : None.
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
* �� �� �� :  void function8_close(void)
* ��    �� : �رչ��ܺ���8
* ������� : None.
* ������� : None.
* ��   ��  : None.
********************************************************************************************************/
void function8_close(void)
{
   ADC_Cmd(ADC2, DISABLE);
   ADC_SoftwareStartConvCmd(ADC2, DISABLE);
   ADC_ITConfig(ADC2, ADC_IT_EOC, DISABLE);
   openfun8=0;
}
/*******************************************************************
�������ƣ�delay_nus
�������ܣ���ʱ����
���������ʱ��us
����˵��������ʾ�������Ե������д˺���������Ϊ1us
����Ϊi--,��i=7ʱԼΪ1us
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
