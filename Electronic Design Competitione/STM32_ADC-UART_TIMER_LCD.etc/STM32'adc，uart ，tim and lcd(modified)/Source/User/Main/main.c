//ͷ�ļ�����
#include "usually.h"
#include "usart.h"
#include "lcd12864.h"
#include "adc.h"
#include "tim.h"

//��������
//�ڲ��¶Ȳɼ��а����ı���
volatile uint16_t  ADC_ConvertedValue_LocalValue=0;	
extern volatile uint16_t  ADC_ConvertedValue;			     //��adc.c��ת�ƹ����ı���
uint16_t  q,p,o,r;           
uint16_t TIM2_IRQHandler_Flag=0,TIM3_IRQHandler_Flag=0,TIM4_IRQHandler_Flag=0;	//TIM2��3��4���жϱ�־
//USART�а����ı���
const char menu[] =
   "\n\r"
   "+********************* STM32������  ********************+\n\r"	   //"\n"���ڳ����ն˵������ǻ���
   "|                                                       |\n\r"	   //"\r" :�ڳ����ն˵��������ö�
   "|                  USART �첽ͨ������                   |\n\r"
   "|                   www.scdbit.com                      |\n\r"
   "|                   �ɶ���һ�ؿƼ�                      |\n\r"
   "|                      2012.5.15                        |\n\r"
   "|                ����֧��QQ��406795003                  |\n\r"
   "+-------------------------------------------------------+\n\r";

//��������
void Init_LED(void);	
void Init_NVIC(void);
void Delay_Ms(uint16_t time);  
void Delay_Us(uint16_t time); 
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: main
** ��������: ���������
** �������������������ʾ�˴����շ����� �������ǲ����жϷ�ʽ
				�������������ϵ�����ֵ ���Գ����ն˽���ʮ����������������ֵ 
				���磺1��Ӧʮ������49��2��Ӧ��50��a��Ӧ��97������㶮������
** ��  ����: xt
** �ա�  ��: 2011��6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
int main(void)
{
	SystemInit();					//ϵͳʱ������
	Init_NVIC();					//�ж�������ע�ắ��
	Init_LED();						//����������������

	Init_Usart();					//������������			//Usart
	Usart_Configuration(115200);	//�������� ���ò�����Ϊ115200    //Usart

	lcd12864_WaitBusy();	       //lcd12864���æ
	lcd12864_WriteCmd();	       //lcd12864д����
	lcd12864_WriteData();	       //lcd12864д����
	lcd12864_InitDis();		       //lcd12864��ʼ��
	lcd12864_clear();		       //lcd12864����	   
//	lcd12864_draw_frame();		   //���߿�
//  lcd12864_DrawPoint_f(90,50,1); //���
//	lcd12864_LCD_set_dot(30,35);   //���
//	lcd12864_draw_horizontal_line(50,50,5,1); //������

    ADC1_GPIO_Config();	           //ADC1
    ADC1_MODE_Config();			   //ADC1
   

	timer_init();	       //TIM��ʼ��������TIM2��TIM3��TIM3�������ж�


//	printf(menu);					//����ַ���
//	printf("��һ�����㿪��STM32����,�����������ţ���\n\r");
//	printf("����������ϵ������ַ������ڽ���ʮ���������������ַ�\n\r");		   
	while(1)													
	{  
	    LED1=~LED1;	   				
  	    Delay_Ms(200);				 //LED1��˸��ϵͳ��������
		ADC_ConvertedValue_LocalValue=ADC_ConvertedValue;
    	ADC_ConvertedValue_LocalValue=(ADC_ConvertedValue_LocalValue*3300/4096);		//�������1000��
	    q=ADC_ConvertedValue_LocalValue/1000;
	    p=ADC_ConvertedValue_LocalValue/100%10;
	    o=ADC_ConvertedValue_LocalValue/10%10;
	    r=ADC_ConvertedValue_LocalValue%10;
	    lcd12864_WriteCmd(0x30);	  //�˳���ͼģʽ
	    q=q+0x30;lcd12864_WriteCmd(0x98);lcd12864_WriteData(q);
	    p=p+0x30;;lcd12864_WriteData(p);
	    o=o+0x30;;lcd12864_WriteData(o);
		r=r+0x30;;lcd12864_WriteData(r);
	    lcd12864_DrawPoint_f(8,60,1); //���
        printf("ADC1�Ĳɼ�ֵ=%3d",ADC_ConvertedValue_LocalValue);
		LED2=~LED2;	
		ADC_ConvertedValue_LocalValue=0;
		   
	}	
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Init_LED
** ��������: LED IO��������
** ������������
** ��  ����: xt
** �ա�  ��: 2011��6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_LED(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;					//����һ��GPIO�ṹ�����

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOG | RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOD,ENABLE);	//ʹ�ܸ����˿�ʱ�ӣ���Ҫ������
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;										
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   	//ͨ���������	//D2
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   	//���ö˿��ٶ�Ϊ50M
  	GPIO_Init(GPIOG, &GPIO_InitStructure);				   	//���ݲ�����ʼ��GPIOG�Ĵ���

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;										
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   	//ͨ���������	 //D5
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   	//���ö˿��ٶ�Ϊ50M
  	GPIO_Init(GPIOD, &GPIO_InitStructure);				   	//���ݲ�����ʼ��GPIOD�Ĵ���
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Init_NVIC
** ��������: ϵͳ�ж�����  
** ������������
** ��  ����: xt
** �ա�  ��: 2011��5��14��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_NVIC(void)
{ 	
  	NVIC_InitTypeDef NVIC_InitStructure;			//����һ��NVIC������ṹ�����

	#ifdef  VECT_TAB_RAM  							//���������ַѡ��

	  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);  	//��0x20000000��ַ��Ϊ���������ַ(RAM)
	#else  

	  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0); //��0x08000000��ַ��Ϊ���������ַ(FLASH)  
	#endif

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�����ж��� Ϊ2 

	// ʹ��USART1�ж�
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			//���ô���1Ϊ�ж�Դ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0; 	//����ռ�����ȼ�Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  	//���ø����ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  	//ʹ�ܴ���1�ж�
    NVIC_Init(&NVIC_InitStructure);							  //���ݲ�����ʼ���жϼĴ���	
     // ʹ��TIM2�ж�
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure); 
    // ʹ��TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    // ʹ��TIM4�ж�
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);		 

}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: TIM���жϴ�������������TIM2��TIM3��TIM4
** ��ʱ��2���ã� 720��Ƶ��500ms�ж�һ�Σ����ϼ���
** ��ʱ��3���ã� 720��Ƶ��250ms�ж�һ�Σ����ϼ���
** ��ʱ��4���ã� 1440��Ƶ��1000ms�ж�һ�Σ����ϼ���
** ��������: ϵͳ�ж�����
** ������������
** ��  ����: xt
** �ա�  ��: 2011��5��14��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void TIM2_IRQHandler(void)
{ 
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
  {
    TIM2_IRQHandler_Flag=1;     //����һ���жϱ�־λ 
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	    /* ��� TIMx ���жϴ�����λ */
	//LED2=~LED2;	
  }    
}
void TIM3_IRQHandler(void)
{ 
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 
  {
    TIM3_IRQHandler_Flag=1;     //����һ���жϱ�־λ
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);	    /* ��� TIMx ���жϴ�����λ */
	//LED2=~LED2;	
  }    
}
void TIM4_IRQHandler(void)
{ 
 if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) 
   {
     TIM4_IRQHandler_Flag=1;     //����һ���жϱ�־λ
     TIM_ClearITPendingBit(TIM4, TIM_IT_Update);    /* ��� TIMx ���жϴ�����λ */
	// LED2=~LED2;	
   }  
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Delay_Ms_Ms
** ��������: ��ʱ1MS (��ͨ���������ж�����׼ȷ��)			
** ����������time (ms) ע��time<65535
** ��  ����: xt
** �ա�  ��: 2011��6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Delay_Ms(uint16_t time)  //��ʱ����
{ 
	uint16_t i,j;
	for(i=0;i<time;i++)
  		for(j=0;j<10260;j++);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Delay_Ms_Us
** ��������: ��ʱ1us (��ͨ���������ж�����׼ȷ��)
** ����������time (us) ע��time<65535				 
** ��  ����: xt
** �ա�  ��: 2011��6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Delay_Us(uint16_t time)  //��ʱ����
{ 
	uint16_t i,j;
	for(i=0;i<time;i++)
  		for(j=0;j<9;j++);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
