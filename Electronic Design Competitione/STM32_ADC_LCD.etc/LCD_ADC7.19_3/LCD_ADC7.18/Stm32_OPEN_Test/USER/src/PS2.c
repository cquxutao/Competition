#include "includes.h"

u8 BitCnt=0;
u8 PS2_ReFlag=0;
u8 PS2Redata;
u8 OutCode;
/*******************************************************************************
* Function Name  : void PS2_Driver()
* Description    : PS2驱动
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PS2_Driver(void)
{ 
    while(GPIO_ReadInputDataBit(PS2_GRP,PS2_CLK)==1);
    delay_nus(20);
    while(GPIO_ReadInputDataBit(PS2_GRP,PS2_CLK)==1);
    
    BitCnt++;
    
    if(BitCnt==1)
    {
      if(GPIO_ReadInputDataBit(PS2_GRP,PS2_DATA)==0)
      {
        PS2_ReFlag = 1;
      }
    }
    else if(BitCnt<10&&PS2_ReFlag==1)
    {
      PS2Redata=PS2Redata>>1;
      if(GPIO_ReadInputDataBit(PS2_GRP,PS2_DATA))
      {
        PS2Redata=PS2Redata | 0x80;                            //读数据位,接收的数据位放入retc 中 
      }
    }
    
    else if(BitCnt==10);
    
    else if(BitCnt==11)
    {
      if(GPIO_ReadInputDataBit(PS2_GRP,PS2_DATA)==1)
      {
        PS2_ReFlag = 0;
        BitCnt=0;
        OutCode=PS2Redata;
      }
    }
    delay_nus(20);
}
/*******************************************************************************
* Function Name  : u8 PS2_Conver(u8 keycode)
* Description    : PS2驱动
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 PS2_Conver(u8 keycode)
{
  u8 i=0;
  u8 PSNum[10]={0x70,0x69,0x72,0x7a,0x6b,0x73,0x74,0x6c,0x75,0x7d};  // 0~9键码
  while(keycode!=PSNum[i])
  i++;
  
  return i;
}
/*******************************************************************************
* Function Name  : void PS2_Disp(void)
* Description    : PS2驱动
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
 u8 DispNum;
void PS2_Disp(void)
{
 
  PS2_Driver();
  DispNum=PS2_Conver(OutCode);
  Hex_test(8,DispNum);
  
}