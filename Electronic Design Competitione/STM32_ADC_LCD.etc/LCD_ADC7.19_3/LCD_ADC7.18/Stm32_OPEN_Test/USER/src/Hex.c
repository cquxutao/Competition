
#include "includes.h"

/********************************************************************************************************
* 函 数 名 :  void Hex_test(u8 sel, u8 data)
* 描    述 : 数码管显示程序
* 输入参数 : sel：选择1~8数码管，data：待显示的数据
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void Hex_test(u8 sel, u8 data)
{
  switch(sel)
  {
    case 1:  GPIO_ResetBits(GPIOG, HEX_SCA);
             GPIO_ResetBits(GPIOG, HEX_SCB);
             GPIO_ResetBits(GPIOF, HEX_SCC);
             disp(data);
             break;
    case 2:  GPIO_SetBits(GPIOG, HEX_SCA);
             GPIO_ResetBits(GPIOG, HEX_SCB);
             GPIO_ResetBits(GPIOF, HEX_SCC);
             disp(data);
             break;
    case 3:  GPIO_ResetBits(GPIOG, HEX_SCA);
             GPIO_SetBits(GPIOG, HEX_SCB);
             GPIO_ResetBits(GPIOF, HEX_SCC);
             disp(data);
             break;
    case 4:  GPIO_SetBits(GPIOG, HEX_SCA);
             GPIO_SetBits(GPIOG, HEX_SCB);
             GPIO_ResetBits(GPIOF, HEX_SCC);
             disp(data);
             break;
    case 5:  GPIO_ResetBits(GPIOG, HEX_SCA);
             GPIO_ResetBits(GPIOG, HEX_SCB);
             GPIO_SetBits(GPIOF, HEX_SCC);
             disp(data);
             break;
    case 6:  GPIO_SetBits(GPIOG, HEX_SCA);
             GPIO_ResetBits(GPIOG, HEX_SCB);
             GPIO_SetBits(GPIOF, HEX_SCC);
             disp(data);
             break;
    case 7:  GPIO_ResetBits(GPIOG, HEX_SCA);
             GPIO_SetBits(GPIOG, HEX_SCB);
             GPIO_SetBits(GPIOF, HEX_SCC);
             disp(data);
             break;
    case 8:  GPIO_SetBits(GPIOG, HEX_SCA);
             GPIO_SetBits(GPIOG, HEX_SCB);
             GPIO_SetBits(GPIOF, HEX_SCC);
             disp(data);
             break;
    default: break;
  }

}
/********************************************************************************************************
* 函 数 名 :  void disp(u8 data)
* 描    述 : 数码管显示程序
* 输入参数 : data：待显示的数据
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void disp(u8 data)
{
  switch(data)
  {
    case 0:  GPIO_SetBits(GPIOF, HEX_D0); 
             GPIO_SetBits(GPIOF, HEX_D1);
             GPIO_SetBits(GPIOF, HEX_D2);
             GPIO_SetBits(GPIOF, HEX_D3);
             GPIO_SetBits(GPIOB, HEX_D4);
             GPIO_SetBits(GPIOB, HEX_D5);
             GPIO_ResetBits(GPIOC, HEX_D6);
             GPIO_ResetBits(GPIOC, HEX_D7);
             break;
    case 1:  GPIO_ResetBits(GPIOF, HEX_D0); 
             GPIO_SetBits(GPIOF, HEX_D1);
             GPIO_SetBits(GPIOF, HEX_D2);
             GPIO_ResetBits(GPIOF, HEX_D3);
             GPIO_ResetBits(GPIOB, HEX_D4);
             GPIO_ResetBits(GPIOB, HEX_D5);
             GPIO_ResetBits(GPIOC, HEX_D6);
             GPIO_ResetBits(GPIOC, HEX_D7);
             break;
    case 2:  GPIO_SetBits(GPIOF, HEX_D0); 
             GPIO_SetBits(GPIOF, HEX_D1);
             GPIO_ResetBits(GPIOF, HEX_D2);
             GPIO_SetBits(GPIOF, HEX_D3);
             GPIO_SetBits(GPIOB, HEX_D4);
             GPIO_ResetBits(GPIOB, HEX_D5);
             GPIO_SetBits(GPIOC, HEX_D6);
             GPIO_ResetBits(GPIOC, HEX_D7);
             break;
    case 3:  GPIO_SetBits(GPIOF, HEX_D0); 
             GPIO_SetBits(GPIOF, HEX_D1);
             GPIO_SetBits(GPIOF, HEX_D2);
             GPIO_SetBits(GPIOF, HEX_D3);
             GPIO_ResetBits(GPIOB, HEX_D4);
             GPIO_ResetBits(GPIOB, HEX_D5);
             GPIO_SetBits(GPIOC, HEX_D6);
             GPIO_ResetBits(GPIOC, HEX_D7);
             break;
    case 4:  GPIO_ResetBits(GPIOF, HEX_D0); 
             GPIO_SetBits(GPIOF, HEX_D1);
             GPIO_SetBits(GPIOF, HEX_D2);
             GPIO_ResetBits(GPIOF, HEX_D3);
             GPIO_ResetBits(GPIOB, HEX_D4);
             GPIO_SetBits(GPIOB, HEX_D5);
             GPIO_SetBits(GPIOC, HEX_D6);
             GPIO_ResetBits(GPIOC, HEX_D7);
             break;
    case 5:  GPIO_SetBits(GPIOF, HEX_D0); 
             GPIO_ResetBits(GPIOF, HEX_D1);
             GPIO_SetBits(GPIOF, HEX_D2);
             GPIO_SetBits(GPIOF, HEX_D3);
             GPIO_ResetBits(GPIOB, HEX_D4);
             GPIO_SetBits(GPIOB, HEX_D5);
             GPIO_SetBits(GPIOC, HEX_D6);
             GPIO_ResetBits(GPIOC, HEX_D7);
             break;
    case 6:  GPIO_SetBits(GPIOF, HEX_D0); 
             GPIO_ResetBits(GPIOF, HEX_D1);
             GPIO_SetBits(GPIOF, HEX_D2);
             GPIO_SetBits(GPIOF, HEX_D3);
             GPIO_SetBits(GPIOB, HEX_D4);
             GPIO_SetBits(GPIOB, HEX_D5);
             GPIO_SetBits(GPIOC, HEX_D6);
             GPIO_ResetBits(GPIOC, HEX_D7);
             break;
    case 7:  GPIO_SetBits(GPIOF, HEX_D0); 
             GPIO_SetBits(GPIOF, HEX_D1);
             GPIO_SetBits(GPIOF, HEX_D2);
             GPIO_ResetBits(GPIOF, HEX_D3);
             GPIO_ResetBits(GPIOB, HEX_D4);
             GPIO_ResetBits(GPIOB, HEX_D5);
             GPIO_ResetBits(GPIOC, HEX_D6);
             GPIO_ResetBits(GPIOC, HEX_D7);
             break;
    case 8:  GPIO_SetBits(GPIOF, HEX_D0); 
             GPIO_SetBits(GPIOF, HEX_D1);
             GPIO_SetBits(GPIOF, HEX_D2);
             GPIO_SetBits(GPIOF, HEX_D3);
             GPIO_SetBits(GPIOB, HEX_D4);
             GPIO_SetBits(GPIOB, HEX_D5);
             GPIO_SetBits(GPIOC, HEX_D6);
             GPIO_ResetBits(GPIOC, HEX_D7);
             break;
    case 9:  GPIO_SetBits(GPIOF, HEX_D0); 
             GPIO_SetBits(GPIOF, HEX_D1);
             GPIO_SetBits(GPIOF, HEX_D2);
             GPIO_SetBits(GPIOF, HEX_D3);
             GPIO_ResetBits(GPIOB, HEX_D4);
             GPIO_SetBits(GPIOB, HEX_D5);
             GPIO_SetBits(GPIOC, HEX_D6);
             GPIO_ResetBits(GPIOC, HEX_D7);
             break;
    default: break;
  }
  
}
/********************************************************************************************************
* 函 数 名 :  void Hex_close(void)
* 描    述 : 关闭数码管显示
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void Hex_close(void)
{
   GPIO_ResetBits(GPIOF, HEX_D0); 
   GPIO_ResetBits(GPIOF, HEX_D1);
   GPIO_ResetBits(GPIOF, HEX_D2);
   GPIO_ResetBits(GPIOF, HEX_D3);
   GPIO_ResetBits(GPIOB, HEX_D4);
   GPIO_ResetBits(GPIOB, HEX_D5);
   GPIO_ResetBits(GPIOC, HEX_D6);
   GPIO_ResetBits(GPIOC, HEX_D7);
}

/********************************************************************************************************
* 函 数 名 :  void Hex_close(void)
* 描    述 : 开机扫描数码管
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void Display_LedScan(void)  
{
  u32 i,j=0,k=0,sngtmp=0;
  
  while(1)
  {
    for(i=1;i<9;i++)
    {
      if(sngtmp%500==0)
      {
        if(j==9)
          j=0;
        else
          j++;
      }
      Hex_test(i,j);
      delay_nus(1000);
      sngtmp++;
    }
     if(sngtmp>4500)
        break;
  }
  
}
/********************************************************************************************************
* 函 数 名 :  void Display_LedNum(u8 leddata) 
* 描    述 : 数码管显示数字
* 输入参数 : 待显示数据.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void Display_LedNum(u16 LedData)  
{
  u32 i=9,j=0,k=0,sngtmp=0;
  
  if(LedData==0)
  {
    Hex_test(8,0);
  }
  else
  {
      while(LedData>0)
      {
        if(sngtmp%500==0)
        {
          j=LedData%10;
          LedData=LedData/10;
          i--;
        }
        Hex_test(i,j);
        sngtmp++;
        k++;
      }
      delay_nus(2000);
  }
}