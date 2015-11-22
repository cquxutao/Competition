//ͷ�ļ�����
#include "usually.h"
#include "usart.h"

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int Data, FILE *f)
{   
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TXE));	  //USART_GetFlagStatus���õ�����״̬λ
														  //USART_FLAG_TXE:���ͼĴ���Ϊ�� 1��Ϊ�գ�0��æ״̬
	USART_SendData(USART1,Data);						  //����һ���ַ�
	   
	return Data;										  //����һ��ֵ
}
#endif 

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: USART1_Send_Byte
** ��������: ���ڷ���һ���ַ���
** ����������Data Ҫ���͵�����
** ��  ����: xt
** �ա�  ��: 2011��6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void USART1_Send_Byte(uint16_t Data)
{ 
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TXE));	  //USART_GetFlagStatus���õ�����״̬λ
														  //USART_FLAG_TXE:���ͼĴ���Ϊ�� 1��Ϊ�գ�0��æ״̬
	USART_SendData(USART1,Data);						  //����һ���ַ�
}

uint8_t USART1_Receive_Byte(void)
{ 
   	while(!(USART_GetFlagStatus(USART1,USART_FLAG_RXNE))); //USART_GetFlagStatus���õ�����״̬λ
														   //USART_FLAG_RXNE:�������ݼĴ����ǿձ�־λ 
														   //1��æ״̬  0������(û�յ����ݣ��ȴ�������)
	return USART_ReceiveData(USART1);					   //����һ���ַ�
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Usart_Init
** ��������: �������ų�ʼ��
** ��������: ��
** ��  ����: Dream
** �ա�  ��: 2011��6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_Usart(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;					//����һ��GPIO�ṹ�����

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);	
															//ʹ�ܸ����˿�ʱ�ӣ���Ҫ������

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 				//���ô��ڽ��ն˿ڹҽӵ�9�˿�
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   		//���ù��������©
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   	//���ö˿��ٶ�Ϊ50M
  	GPIO_Init(GPIOA, &GPIO_InitStructure);				   	//���ݲ�����ʼ��GPIOA�Ĵ���	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//��������(��λ״̬);	   				
  	GPIO_Init(GPIOA, &GPIO_InitStructure);				   	//���ݲ�����ʼ��GPIOA�Ĵ���	
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: Usart_Configuration
** ��������: �������ú���
** ��������: BaudRate���ò����� 
** ��  ����: Dream
** �ա�  ��: 2011��6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Usart_Configuration(uint32_t BaudRate)
{
	USART_InitTypeDef USART_InitStructure;							    	//����һ�����ڽṹ��

	USART_InitStructure.USART_BaudRate            =BaudRate ;	  			//������115200
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b; 	//���������ʹ��8λ����
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;	 	//��֡��β����1λֹͣλ
	USART_InitStructure.USART_Parity              = USART_Parity_No ;	 	//��żʧ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ����ʧ��
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx; //���պͷ���ģʽ
	USART_Init(USART1, &USART_InitStructure);								//���ݲ�����ʼ�����ڼĴ���
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);							//ʹ�ܴ����жϽ���
	USART_Cmd(USART1, ENABLE);     											//ʹ�ܴ�������
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** ��������: USART1_IRQHandler
** ��������: �����жϺ���
** ��������: �� 
** ��  ����: xt
** �ա�  ��: 2011��6��20��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void USART1_IRQHandler()
{
	uint8_t ReceiveDate;								//����һ��������Ž��յ�����
	if(!(USART_GetITStatus(USART1,USART_IT_RXNE))); 	//��ȡ�����жϱ�־λUSART_IT_RXNE 
														//USART_FLAG_RXNE:�������ݼĴ����ǿձ�־λ 
														//1��æ״̬  0������(û�յ����ݣ��ȴ�������)
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);	//����жϱ�־λ
		ReceiveDate=USART_ReceiveData(USART1);			//�����ַ���������
		printf("%d",(char*)ReceiveDate);				//��ʮ������������ֵ,���������ǿ��Կ������������еļ�ֵ��Ӧ��ʮ������
														//��������"1"��Ӧ�����49 �� ����"A" ��Ӧ��ֵΪ65
		printf("\n\r");									//�����ö�
	}  
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
End:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D:-D
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
