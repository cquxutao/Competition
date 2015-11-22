
#include "usually.h"
#include "adc.h"
#include "stm32f10x_adc.h"

#define ADC1_DR_Address    ((uint32_t)0x4001244C)
volatile uint16_t  ADC_ConvertedValue;


 void ADC1_GPIO_Config(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;					//����һ��GPIO�ṹ�����
   RCC_AHBPeriphClockCmd( RCC_AHBPeriph_DMA1,ENABLE);	//ʹ�ܸ����˿�ʱ�ӣ���Ҫ������
   RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1,ENABLE);	//ʹ�ܸ����˿�ʱ�ӣ���Ҫ������
}

 void ADC1_MODE_Config(void)
{

  DMA_InitTypeDef DMA_InitStructure;					//����һ��DMA�ṹ�����
  ADC_InitTypeDef ADC_InitStructure;					//����һ��ADC�ṹ�����

  DMA_DeInit(DMA1_Channel1);		  //����DMA1�ĵ�һͨ��
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)&ADC_ConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	//DMA��ת��ģʽΪSRCģʽ����������Ƶ��ڴ�
  DMA_InitStructure.DMA_BufferSize = 1; //DMA�����С��1��
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//����һ�����ݺ��豸��ַ��ֹ����
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;	//�رս���һ�����ݺ�Ŀ���ڴ��ַ����
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //�����������ݿ��Ϊ16λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;  //DMA�������ݳߴ磬HalfWord����Ϊ16λ
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;   //ת��ģʽ��ѭ������ģʽ��
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;	//DMA���ȼ���
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;		  //M2Mģʽ����
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);          
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);

  ADC_TempSensorVrefintCmd(ENABLE);

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		//������ת��ģʽ
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode  = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv  = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel14 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_239Cycles5);

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibaration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);

}