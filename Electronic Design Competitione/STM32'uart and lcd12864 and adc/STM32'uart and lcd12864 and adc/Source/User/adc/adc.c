
#include "usually.h"
#include "adc.h"
#include "stm32f10x_adc.h"

#define ADC1_DR_Address    ((uint32_t)0x4001244C)
volatile uint16_t  ADC_ConvertedValue;


 void ADC1_GPIO_Config(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;					//定义一个GPIO结构体变量
   RCC_AHBPeriphClockCmd( RCC_AHBPeriph_DMA1,ENABLE);	//使能各个端口时钟，重要！！！
   RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1,ENABLE);	//使能各个端口时钟，重要！！！
}

 void ADC1_MODE_Config(void)
{

  DMA_InitTypeDef DMA_InitStructure;					//定义一个DMA结构体变量
  ADC_InitTypeDef ADC_InitStructure;					//定义一个ADC结构体变量

  DMA_DeInit(DMA1_Channel1);		  //开启DMA1的第一通道
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)&ADC_ConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	//DMA的转换模式为SRC模式，由外设搬移到内存
  DMA_InitStructure.DMA_BufferSize = 1; //DMA缓存大小，1个
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	//接收一次数据后，设备地址禁止后移
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;	//关闭接收一次数据后，目标内存地址后移
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //定义外设数据宽度为16位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;  //DMA搬移数据尺寸，HalfWord就是为16位
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;   //转换模式，循环缓存模式。
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;	//DMA优先级高
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;		  //M2M模式禁用
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);          
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);

  ADC_TempSensorVrefintCmd(ENABLE);

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		//独立的转换模式
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