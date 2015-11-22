//ͷ�ļ�����
#include "usually.h"
#include "usart.h"
#include "lcd12864.h"
#include "adc.h"

//��������
//�ڲ��¶Ȳɼ��а����ı���
volatile uint16_t  ADC_ConvertedValue_Temper_LocalValue;	 //�ڲ��¶Ȳɼ�ֵ
extern volatile uint16_t  ADC_ConvertedValue;			     //��adc.c��ת�ƹ����ı���
uint16_t  inter_temper;               //�ڲ��¶�
unsigned char  a,b,c;
//USART�а����ı���

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

	lcd12864_WaitBusy();	       //lcd12864
	lcd12864_WriteCmd();	       //lcd12864
	lcd12864_WriteData();	       //lcd12864
	lcd12864_InitDis();		       //lcd12864
//	lcd12864_locate16(1,1);	       //lcd12864
//	lcd12864_DisStr("abcdefg");	   //lcd12864

    ADC1_GPIO_Config();	           //�¶�ADC1
    ADC1_MODE_Config();			   //�¶�ADC1


//	printf(menu);					//����ַ���
//	printf("��һ�����㿪��STM32����,�����������ţ���\n\r");
//	printf("����������ϵ������ַ������ڽ���ʮ���������������ַ�\n\r");		   
	while(1)													
	{  
		LED1=~LED1;	   				
		Delay_Ms(200);				 //LED1��˸��ϵͳ��������
		ADC_ConvertedValue_Temper_LocalValue=ADC_ConvertedValue;
		Delay_Ms(200);
		inter_temper=(1.43-ADC_ConvertedValue_Temper_LocalValue*3.3/4096)/0.0043+25;
	    printf("��ǰ�¶�=%d\tADC1�Ĳɼ�ֵ=%3d",inter_temper,ADC_ConvertedValue_Temper_LocalValue);
		lcd12864_WriteCmd(0x80);
	    lcd12864_DisStr("��ǰ�¶�=");
		lcd12864_WriteCmd(0x87);
	    lcd12864_DisStr("��");
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
** ��������: Init_LED
** ��������: LED IO��������
** ������������
** ��  ����: xt
** �ա�  ��: 2011��6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_LED(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;					//����һ��GPIO�ṹ�����

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOG | RCC_APB2Periph_GPIOE,ENABLE);	//ʹ�ܸ����˿�ʱ�ӣ���Ҫ������
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;										
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   	//ͨ���������
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   	//���ö˿��ٶ�Ϊ50M
  	GPIO_Init(GPIOG, &GPIO_InitStructure);				   	//���ݲ�����ʼ��GPIOD�Ĵ���
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

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			//���ô���1Ϊ�ж�Դ
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 	//����ռ�����ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  	//���ø����ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  	//ʹ�ܴ���1�ж�
	NVIC_Init(&NVIC_InitStructure);							  	//���ݲ�����ʼ���жϼĴ���
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
