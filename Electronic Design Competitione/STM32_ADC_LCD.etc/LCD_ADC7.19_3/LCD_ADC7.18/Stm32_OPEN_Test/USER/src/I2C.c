
#include "includes.h"

#define SDA_H GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define SDA_L GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define SCL_H GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define SCL_L GPIO_ResetBits(GPIOB,GPIO_Pin_6)

u8 Tempdata;

/****************************************************************************
����ԭ�ͣ�void Delay_uS(uint16 uS)
���ܣ�	   uS����ʱ
��ڲ�������
���ڲ�������
****************************************************************************/
void Delay_uS(uint16 uS)
{
    uint16 i;
    while(uS--)
    {
        i=40;
        while(i--);
    }
}
/*******************************************************************************
* Function Name  : I2C_Start
* Description    : ����I2C ����,������I2C ��ʼ����.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_Start()
{
    SDA_H; /*������ʼ�����������ź�*/
    Delay_uS(1);
    SCL_H;
    Delay_uS(2);
    SDA_L; /*������ʼ�ź�*/
    Delay_uS(2); /* ��ʼ��������ʱ�����4��s*/
    SCL_L; /*ǯסI2C ���ߣ�׼�����ͻ�������� */
    Delay_uS(1);
}
/*******************************************************************************
* Function Name  : I2C_Stop
* Description    : ����I2C ����,������I2C ��������.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_Stop()
{
    SDA_L; /*���ͽ��������������ź�*/
    Delay_uS(1); /*���ͽ���������ʱ���ź�*/
    SCL_H; /*������������ʱ�����4��s*/
    Delay_uS(2);
    SDA_H; /*����I2C ���߽����ź�*/
    Delay_uS(1);
}
/*******************************************************************************
* Function Name  : I2C_SendByte
* Description    : ������c ���ͳ�ȥ,�����ǵ�ַ,Ҳ����������,�����ȴ�Ӧ��,����
                    ��״̬λ���в���.(��Ӧ����Ӧ��ʹack=0 ��)
* Input          : c: ��������
* Output         : None
* Return         : ������������������1;����0 ��ʾ��������Ӧ����𻵡�
*******************************************************************************/
u8 I2C_SendByte(u8 c)
{
    u8 BitCnt,ack;
    for(BitCnt=0;BitCnt<8;BitCnt++) /*Ҫ���͵����ݳ���Ϊ8 λ*/
    {
        if((c<<BitCnt)&0x80)
            SDA_H; /*�жϷ���λ*/
        else 
            SDA_L;
        Delay_uS(1);
        SCL_H; /*��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ*/
        Delay_uS(1); /*��֤ʱ�Ӹߵ�ƽ���ڴ���4��s*/       
        SCL_L;
    }
    Delay_uS(1);
    SDA_H; /*8 λ��������ͷ������ߣ�׼������Ӧ��λ*/
    Delay_uS(1);
    SCL_H;
    Delay_uS(1);
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==1)
        ack=0;
    else 
        ack=1; /*�ж��Ƿ���յ�Ӧ���ź�*/
    SCL_L;
    Delay_uS(1);
    return ack;
}
/*******************************************************************************
* Function Name  : I2C_RcvByte
* Description    : �������մ���������������,���ж����ߴ���(����Ӧ���ź�)��
                    ���������Ӧ������
* Input          : 
* Output         : None
* Return         : I2C�ϵ�����
*******************************************************************************/
u8 I2C_RcvByte()
{
    u8 retc;
    u8 BitCnt;
    retc=0;
    SDA_H; /*��������Ϊ���뷽ʽ*/
    for(BitCnt=0;BitCnt<8;BitCnt++)
    {
        Delay_uS(1);
        SCL_L; /*��ʱ����Ϊ�ͣ�׼����������λ*/
        Delay_uS(2);
        SCL_H; /*��ʱ����Ϊ��ʹ��������������Ч*/
        Delay_uS(1);
        retc=retc<<1;
        SDA_H;
        Delay_uS(1);
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==1)
            retc=retc+1; /*������λ,���յ�����λ����retc �� */
        Delay_uS(1);
    }
    SCL_L;
    Delay_uS(1);
    return(retc);
}
/*******************************************************************************
* Function Name  : I2C_Ack
* Description    : ����������Ӧ���ź�,(������Ӧ����Ӧ���ź�)
* Input          : a��0��ʾӦ��1��ʾ��Ӧ��
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_Ack(u8 a)
{
    if(a==0)
        SDA_L; /*�ڴ˷���Ӧ����ź� */
    else 
        SDA_H;/*�ڴ˷�����Ӧ���ź� */
    Delay_uS(1);
    SCL_H;
    Delay_uS(2);
    SCL_L; /*��ʱ���ߣ�ǯסI2C �����Ա��������*/
    Delay_uS(1);
}
/*******************************************************************************
* Function Name  : LM75A_SendByte
* Description    : �����ӵ�ַ��LM75A����һ���ֽ�����
* Input          : sla��I2C��ַ
                   C:����
* Output         : None
* Return         : �������1 ��ʾ�����ɹ��������������
ע�⣺ ʹ��ǰ�����ѽ������ߡ�
*******************************************************************************/
u8 LM75A_SendByte(u8 sla,u8 c)
{
    u8 ack;
    I2C_Start(); /*��������*/
    ack=I2C_SendByte(sla); /*����������ַ*/
    if(ack==0)
        return(0);
    ack=I2C_SendByte(c); /*��������*/
    if(ack==0)
        return(0);
    I2C_Stop(); /*��������*/
    return(1);
}

/*******************************************************************************
* Function Name  : LM75A_SendStr
* Description    : �����ӵ�ַ�������Ͷ��ֽ����ݺ���
* Input          : sla��I2C��ַ
                   suba:LM75A�ӵ�ַ
                   s:�������ݻ�����
                   no:�ֽ���
* Output         : None
* Return         : �������1 ��ʾ�����ɹ��������������
ע�⣺ ʹ��ǰ�����ѽ������ߡ�
*******************************************************************************/
u8 LM75A_SendStr(u8 sla,u8 suba,u8 *s,u8 no)
{
    u8 i,ack;
    
    I2C_Start(); /*��������*/
    ack=I2C_SendByte(sla); /*����������ַ*/
    if(ack==0)
    {
        return 0;
    }
    ack=I2C_SendByte(suba); /*���������ӵ�ַ*/
    if(ack==0)
    {
        return 0;
    }
    for(i=0;i<no;i++)
    {
        ack=I2C_SendByte(*s); /*��������*/
        if(ack==0)
        {
            return 0;
        }
        s++;
    }
    I2C_Stop(); /*��������*/
    return(1);
}

/*******************************************************************************
* Function Name  : LM75A_RcvByte
* Description    : �����ӵ�ַ��LM75A����һ���ֽ�����
* Input          : sla��I2C��ַ
                   C:����
* Output         : None
* Return         : �������1 ��ʾ�����ɹ��������������
ע�⣺ ʹ��ǰ�����ѽ������ߡ�
*******************************************************************************/
u8 LM75A_RcvByte(u8 sla,u8 *c)
{
    u8 ack;
    I2C_Start(); /*��������*/
    ack=I2C_SendByte(sla+1); /*����������ַ*/
    if(ack==0)
        return(0);
    *c=I2C_RcvByte(); /*��ȡ����*/
    I2C_Ack(1); /*���ͷǾʹ�λ*/
    I2C_Stop(); /*��������*/
    return(1);
}
/*******************************************************************************
* Function Name  : LM75A_RcvStr
* Description    : �����ӵ�ַ�������ն��ֽ����ݺ���
* Input          : sla��I2C��ַ
                   suba:LM75A�ӵ�ַ
                   s:�������ݻ�����
                   no:�ֽ���
* Output         : None
* Return         : �������1 ��ʾ�����ɹ��������������
ע�⣺ ʹ��ǰ�����ѽ������ߡ�
*******************************************************************************/
u8 LM75A_RcvStr(u8 sla,u8 suba,u8 *s,u8 no)
{
    u8 i,ack;
    I2C_Start(); /*��������*/
    ack=I2C_SendByte(sla); /*����������ַ*/
    if(ack==0)
    {
        return 0;
    }
    ack=I2C_SendByte(suba); /*���������ӵ�ַ*/
    if(ack==0)
    {
        return 0;
    }
    I2C_Start();
    ack=I2C_SendByte(sla+1);
    if(ack==0)
    {
        return 0;
    }
    for(i=0;i<no-1;i++)
    {
        *s=I2C_RcvByte(); /*��������*/
        I2C_Ack(0); /*���;ʹ�λ*/
        s++;
    }
    *s=I2C_RcvByte();
    I2C_Ack(1); /*���ͷ�Ӧλ*/
    I2C_Stop(); /*��������*/
    return(1);
}
/*******************************************************************************
* Function Name  : AT24C64_W
* Description    : ��24C64д���ݣ���ҳд��
* Input          : 
                    sla:��������ַ
                    AT24C64_address:E2PROM��ַ
                    buf:���ͻ�����ָ��
                    count:�������ݳ���
* Output         : None
* Return         : None
*******************************************************************************/
u8 AT24C64_W(u8 sla,u16 AT24C64_address,u8 *buf,u32 count)
{
    u8 status;
    I2C_Start();
    status=I2C_SendByte( sla );
    if(status==0)
    {
        return 0;
    }
    Delay_uS(1); 
    status=I2C_SendByte(  AT24C64_address/256 );
    if(status==0)
    {
        return 0;
    }
    Delay_uS(1); 
    status=I2C_SendByte( AT24C64_address %256 );
    if(status==0)
    {
        return 0;
    }
    Delay_uS(1); 
    while(count--)
    {        
        status=I2C_SendByte( *buf );
        if(status==0)
        {
            return 0;
        }
        buf++;        
    }
    I2C_Stop();
    Delay_uS(10);
    return 1;
}
/*******************************************************************************
* Function Name  : AT24C64_R
* Description    : ��24C64�����ݣ���ҳ����
* Input          : 
                    sla:��������ַ
                    AT24C64_address:E2PROM��ַ
                    buf:���ջ�����ָ��
                    count:��ȡ���ݳ���
* Output         : None
* Return         : None
*******************************************************************************/
void AT24C64_R(u8 sla,u16 AT24C64_address,u8 *buf,u32 count)
{
    I2C_Start();
    /*I2C_Send_Byte( 0xa0 + AT24C64_address / 256 *2 );*/   /* 24C16 USE */
    I2C_SendByte( sla );
    Delay_uS(1); 
    I2C_SendByte( AT24C64_address/256 );
    Delay_uS(1); 
    I2C_SendByte( AT24C64_address % 256 );
    Delay_uS(1); 
    I2C_Start();
    /*I2C_Send_Byte( 0xa1 + AT24C64_address /256 *2 );*/
    I2C_SendByte( sla+1 );
    Delay_uS(1); 
    while(count--)
    {        
        *buf = I2C_RcvByte();
        if(count==0)
            I2C_Ack(1);
        else
            I2C_Ack(0);
        (buf)++;
    }
    I2C_Stop();
}
/*******************************************************************************
* Function Name  : E2PROM_W
* Description    : ��24C64д����(1���ֽ�д)
* Input          : 
                    sla:��������ַ
                    AT24C64_address:E2PROM��ַ
                    buf:���ջ�����ָ��
                    count:��ȡ���ݳ���
* Output         : None
* Return         : None
*******************************************************************************/
void E2PROM_W(u8 sla,u16 AT24C64_address,u8 *buf,u32 count)
{
    while(count--)
    {
        I2C_Start();
        /*I2C_Send_Byte( 0xa0 + AT24C64_address /256 *2);*/ /* 24C16 USE */
        I2C_SendByte( sla );
        I2C_SendByte( AT24C64_address/256 );
        I2C_SendByte( AT24C64_address %256 );
        I2C_SendByte( *buf );
        I2C_Stop();
        Delay_uS(15000) ;/* waiting for write cycle to be completed */
        buf++;
        AT24C64_address++;
    }
}
/*******************************************************************************
* Function Name  : E2PROM_R
* Description    : ��24C64�����ݣ�һ���ֽڶ���
* Input          : 
                    sla:��������ַ
                    AT24C64_address:E2PROM��ַ
                    buf:���ջ�����ָ��
                    count:��ȡ���ݳ���
* Output         : None
* Return         : None
*******************************************************************************/
void E2PROM_R(u8 sla,u16 AT24C64_address,u8 *buf,u32 count)
{
    while(count--)
    {
        I2C_Start();
        /*I2C_Send_Byte( 0xa0 + AT24C64_address / 256 *2 );*/ /* 24C16 USE */
        I2C_SendByte( sla );
        I2C_SendByte( AT24C64_address/256 );
        I2C_SendByte( AT24C64_address % 256 );
        I2C_Start();
        /*I2C_Send_Byte( 0xa1 + AT24C64_address /256 *2 );*/
        I2C_SendByte( sla+1 );
        *buf = I2C_RcvByte();
        I2C_Ack(1);
        I2C_Stop();
        buf++;
        AT24C64_address++;
    }
}

/*******************************************************************************
* Function Name  : AT24C64_WByte
* Description    : ��24C64д���ݣ���ҳд��
* Input          : 
                    AT24C64_address:E2PROM��ַ
                    data:��������
* Output         : None
* Return         : None
*******************************************************************************/
u8 AT24C64_WByte(u16 AT24C64_address,u8 data)
{
  u8 status;
  I2C_Start();
  status=I2C_SendByte(0xa2);
  if(status==0)
  {
    return 0;
  }
  Delay_uS(1); 
  status=I2C_SendByte(  AT24C64_address/256 );
  if(status==0)
  {
    return 0;
  }
  Delay_uS(1); 
  status=I2C_SendByte( AT24C64_address %256 );
  if(status==0)
  {
    return 0;
  }
  Delay_uS(1);       
  status=I2C_SendByte(data);
  if(status==0)
  {
    return 0;
  }        
  I2C_Stop();
  Delay_uS(10);
  return 1;
}
/*******************************************************************************
* Function Name  : AT24C64_RByte
* Description    : ��24C64�����ݣ���ҳ����
* Input          : 
                    AT24C64_address:E2PROM��ַ
* Output         : ��AT24C64���յ�������
* Return         : None
*******************************************************************************/
u8 AT24C64_RByte(u16 AT24C64_address)
{
  u8 redata;
  I2C_Start();
  /*I2C_Send_Byte( 0xa0 + AT24C64_address / 256 *2 );*/   /* 24C16 USE */
  I2C_SendByte( 0xa2 );
  Delay_uS(1); 
  I2C_SendByte( AT24C64_address/256 );
  Delay_uS(1); 
  I2C_SendByte( AT24C64_address % 256 );
  Delay_uS(1); 
  I2C_Start();
  /*I2C_Send_Byte( 0xa1 + AT24C64_address /256 *2 );*/
  I2C_SendByte( 0xa2+1 );
  Delay_uS(1); 
  
  redata = I2C_RcvByte();
  I2C_Stop();
  return redata;
}
/*******************************************************************************
* Function Name  : LM75A_RcvTemp
* Description    : ����temp�Ĵ����е��¶�ֵ
* Input          : sla��I2C��ַ
                   suba:LM75A�ӵ�ַ
                   s:�������ݻ�����
                   no:�ֽ���
* Output         : None
* Return         : �������1 ��ʾ�����ɹ��������������
ע�⣺ ʹ��ǰ�����ѽ������ߡ�
*******************************************************************************/
u8 LM75A_RcvTemp()
{
    u8 i,ack;
    u16 tmp,tmp1,tmp2;
    
    I2C_Start(); /*��������*/
    I2C_SendByte(LM75A_ADDR); /*����������ַ*/
    Delay_uS(1); 
   
    I2C_SendByte(0); /*���������ӵ�ַ*/
    Delay_uS(1); 
    
    I2C_Start();
    ack=I2C_SendByte(LM75A_ADDR+1);
    Delay_uS(1); 
    
    tmp1=I2C_RcvByte(); /*��������*/
    Delay_uS(1); 
    I2C_Ack(0); /*���;ʹ�λ*/
    
    tmp2=I2C_RcvByte();
    Delay_uS(1); 
    I2C_Ack(1); /*���ͷ�Ӧλ*/
    I2C_Stop(); /*��������*/
    
    tmp=((tmp1<<8)|tmp2);
    
    Tempdata=(tmp&0x03ff)*0.125;
    return(1);
}