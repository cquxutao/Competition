
#include "usually.h"
#include "lcd12864.h"

/********** ������������Ŷ��塣**************/

#define DisIO GPIOD                 //����12864Ҫʹ�õ�I/O�˿ڡ�
#define DisClk RCC_APB2Periph_GPIOD  //����12864Ҫʹ�õ�I/O�˿ڵ�ʱ�ӡ�
#define Data GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7
                                       //����12864ʹ�õ���������,GPIO_Pin_0����12864��DB0,GPIO_Pin_1
									   //����12864��DB1,�������ơ�
#define RS GPIO_Pin_8
#define RW GPIO_Pin_9
#define EN GPIO_Pin_10       //����ʹ�ܶ�ʹ�õ����š�
#define PSB GPIO_Pin_11      //���岢����������ģʽ��ѡ��˿�ʹ�õ����š�

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Delay_Ms_Ms
** ��������: ��ʱ1MS (��ͨ���������ж�����׼ȷ��)			
** ����������time (ms) ע��time<65535
** ��  ����: XT
** �ա�  ��: 2011��6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void delay_ms(uint16_t time)  //��ʱ����
{ 
	uint16_t i,j;
	for(i=0;i<time;i++)
  		for(j=0;j<10260;j++);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Delay_Ms_Us
** ��������: ��ʱ1us (��ͨ���������ж�����׼ȷ��)
** ����������time (us) ע��time<65535				 
** ��  ����: XT
** �ա�  ��: 2011��6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void delay_us(uint16_t time)  //��ʱ����
{ 
	uint16_t i,j;
	for(i=0;i<time;i++)
  		for(j=0;j<9;j++);
}

                					    
void lcd12864_IOInitOut(void)           //�����ж˿ڳ�ʼ��Ϊ�������ģʽ�ĺ�����
{
    GPIO_InitTypeDef  GPIO_InitStructure;  //�������ڶ�����������Ϊ����ı�����

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������е�����Ϊ��������ı�����ʼ����
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = Data|RS|RW|EN|PSB;

    RCC_APB2PeriphClockCmd(DisClk,ENABLE);
    GPIO_Init(DisIO,&GPIO_InitStructure);	
}

void lcd12864_IOInitIn(void)           //���������ų�ʼ��Ϊ��������ĺ�����
{
    GPIO_InitTypeDef  GPIO_InitStructure;  //�������ڶ�����������Ϊ����ı�����

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//������������Ϊ��������ı�����ʼ����
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = Data;

    RCC_APB2PeriphClockCmd(DisClk,ENABLE);   //�����ж˿ڳ�ʼ��Ϊ���ģʽ�ĺ�����   
    GPIO_Init(DisIO,&GPIO_InitStructure);	
}

void lcd12864_WaitBusy(void)          //�ȴ�12864��æ״̬�����ĺ�����
{
    lcd12864_IOInitIn();        //���������Ŷ���Ϊ�������룻
    GPIO_ResetBits(DisIO,RS);  //RS = 0.
    GPIO_SetBits(DisIO,RW);    //RW = 1.
    GPIO_SetBits(DisIO,EN);    //EN = 1.
//    while(GPIO_ReadInputData(DisIO) & 0x0080); //ֻҪλ7��ֵ��λ7��æ��־λ��
    GPIO_ResetBits(DisIO,EN);  //EN = 0;
    lcd12864_IOInitOut();      //���������Ŷ���Ϊ�����
}

void lcd12864_WriteCmd(uint8_t cmd)    //д�������
{
  	lcd12864_WaitBusy(); 
    GPIO_ResetBits(DisIO,RS);  //RS = 0.
    GPIO_ResetBits(DisIO,RW);  //RW = 0. 
    GPIO_SetBits(DisIO,EN);    //EN = 1.
    DisIO->ODR=((DisIO->ODR & 0xff00)|cmd); //�˴���ֻ��ֱ�Ӳ����Ĵ�������
                  //�ﵽ��ֻ�ı�������ݼĴ���ODR�ĵ�8λ������λ
                  //�����Ŀ�ġ���Ϊ��ֻ�е�8λ���������ţ�
                  //����λ�����ǿ������ţ����ܸı䡣
    delay_ms(2);
    GPIO_ResetBits(DisIO,EN);  //EN = 0;
    delay_ms(2); 	
}

void lcd12864_WriteData(uint8_t data)  //д���ݺ�����
{
	lcd12864_WaitBusy(); 
    GPIO_SetBits(DisIO,RS);  //RS = 1. 
    GPIO_ResetBits(DisIO,RW);  //RW = 0. 
    GPIO_SetBits(DisIO,EN);    //EN = 1.
    DisIO->ODR=((DisIO->ODR & 0xff00)|data);  
    delay_ms(2);
    GPIO_ResetBits(DisIO,EN);  //EN = 0;
    delay_ms(2); 
}

void lcd12864_InitDis(void)   //��ʼ�� 12864 ��Ҫ�õ��� STM 32 �����š�
{
    lcd12864_IOInitOut(); 	
//    delay_init(72);   //��ʼ����ʱ������΢�����������  
    GPIO_SetBits(DisIO,PSB);  //��PSB=1������Ϊ��������ģʽ��
    delay_ms(2); 
    lcd12864_WriteCmd(0x30);  //ѡ�����ָ����ͣ�8λ����ģʽ��
    delay_ms(2);
    lcd12864_WriteCmd(0x0c);  //����ʾ,���α�,������.
    delay_ms(2); 
    lcd12864_WriteCmd(0x01);  //�����ʾ������ DDRAM �ĵ�ַ������ AC ��Ϊ 00H.
    delay_ms(2);
    lcd12864_WriteCmd(0x06);  //���ã��ⲿ��д���ݺ�,��ַ������ AC ���Զ��� 1��
    delay_ms(2);
    lcd12864_WriteCmd(0x80);  //�� DDRAM ��ַ������ AC ��Ϊ 0.
    delay_ms(2);	
}

void lcd12864_DisStr(uint8_t *s)    //��ʾ�ַ����ĺ�����
{
    while(*s != '\0')
    {
        lcd12864_WriteData(*s);
        s++;
        delay_ms(2);
    }
}




