
#include "includes.h"
 
/********************************************************************************************************
* 函 数 名 :  void main(void)
* 描    述 : main
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void main(void)
{ 
    u16 i,j;
    u16 swdata;
    u32 sngtmp;
    u16 Dutyfactor = 0; 
    
    
    //目标板初化,
    Target_Init();   
    /********开机扫描*******/
    GPIO_SetBits(LED_2_GRP, LED2);
    
    while(1)
    {
                Dutyfactor++;
		if(Dutyfactor<7200)
		{
		    TIM_SetCompare2(TIM4,Dutyfactor);	 //LED D5慢慢变亮
			
		}
		if(Dutyfactor>=7200)
		{
		    Dutyfactor=0;
		}	
		delay_nus(200000);
      
      
      /*swdata=GPIO_ReadInputData(SW_GRP)&0x000f;
        switch(swdata)
        {
          case 0:  function1_close();
                   function2_close();
                   function3_close();
                   function4_close();
                   function5_close();
                   function6_close();
                   function7_close();
                   function8_close();
                   Hex_test(1,0);
                   break;
          case 1:  function1();
                   break;
          case 2:  function2();
                   break;
          case 3:  function3();
                   break;
          case 4:  function4();
                   break;
          case 5:  function5();
                   break;
          case 6:  function6();
                   break;
          case 7:  function7();
                   break;
          case 8:  function8();
                   break;
          default: function1_close();
                   function2_close();
                   function3_close();
                   function4_close();
                   function5_close();
                   function6_close();
                   function7_close();
                   function8_close();
                   break;
        }*/
    }
    
}
