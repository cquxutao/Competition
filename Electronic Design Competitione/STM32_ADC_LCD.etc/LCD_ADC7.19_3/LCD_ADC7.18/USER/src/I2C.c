
#include "includes.h"

#define SDA_H GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define SDA_L GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define SCL_H GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define SCL_L GPIO_ResetBits(GPIOB,GPIO_Pin_6)

u8 Tempdata;

/****************************************************************************
函数原型：void Delay_uS(uint16 uS)
功能：	   uS级延时
入口参数：无
出口参数：无
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
* Description    : 启动I2C 总线,即发送I2C 起始条件.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_Start()
{
    SDA_H; /*发送起始条件的数据信号*/
    Delay_uS(1);
    SCL_H;
    Delay_uS(2);
    SDA_L; /*发送起始信号*/
    Delay_uS(2); /* 起始条件锁定时间大于4μs*/
    SCL_L; /*钳住I2C 总线，准备发送或接收数据 */
    Delay_uS(1);
}
/*******************************************************************************
* Function Name  : I2C_Stop
* Description    : 结束I2C 总线,即发送I2C 结束条件.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_Stop()
{
    SDA_L; /*发送结束条件的数据信号*/
    Delay_uS(1); /*发送结束条件的时钟信号*/
    SCL_H; /*结束条件建立时间大于4μs*/
    Delay_uS(2);
    SDA_H; /*发送I2C 总线结束信号*/
    Delay_uS(1);
}
/*******************************************************************************
* Function Name  : I2C_SendByte
* Description    : 将数据c 发送出去,可以是地址,也可以是数据,发完后等待应答,并对
                    此状态位进行操作.(不应答或非应答都使ack=0 假)
* Input          : c: 发送数据
* Output         : None
* Return         : 发送数据正常，返回1;返回0 表示被控器无应答或损坏。
*******************************************************************************/
u8 I2C_SendByte(u8 c)
{
    u8 BitCnt,ack;
    for(BitCnt=0;BitCnt<8;BitCnt++) /*要传送的数据长度为8 位*/
    {
        if((c<<BitCnt)&0x80)
            SDA_H; /*判断发送位*/
        else 
            SDA_L;
        Delay_uS(1);
        SCL_H; /*置时钟线为高，通知被控器开始接收数据位*/
        Delay_uS(1); /*保证时钟高电平周期大于4μs*/       
        SCL_L;
    }
    Delay_uS(1);
    SDA_H; /*8 位发送完后释放数据线，准备接收应答位*/
    Delay_uS(1);
    SCL_H;
    Delay_uS(1);
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==1)
        ack=0;
    else 
        ack=1; /*判断是否接收到应答信号*/
    SCL_L;
    Delay_uS(1);
    return ack;
}
/*******************************************************************************
* Function Name  : I2C_RcvByte
* Description    : 用来接收从器件传来的数据,并判断总线错误(不发应答信号)，
                    发完后请用应答函数。
* Input          : 
* Output         : None
* Return         : I2C上的数据
*******************************************************************************/
u8 I2C_RcvByte()
{
    u8 retc;
    u8 BitCnt;
    retc=0;
    SDA_H; /*置数据线为输入方式*/
    for(BitCnt=0;BitCnt<8;BitCnt++)
    {
        Delay_uS(1);
        SCL_L; /*置时钟线为低，准备接收数据位*/
        Delay_uS(2);
        SCL_H; /*置时钟线为高使数据线上数据有效*/
        Delay_uS(1);
        retc=retc<<1;
        SDA_H;
        Delay_uS(1);
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==1)
            retc=retc+1; /*读数据位,接收的数据位放入retc 中 */
        Delay_uS(1);
    }
    SCL_L;
    Delay_uS(1);
    return(retc);
}
/*******************************************************************************
* Function Name  : I2C_Ack
* Description    : 主控器进行应答信号,(可以是应答或非应答信号)
* Input          : a：0表示应答，1表示不应答
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_Ack(u8 a)
{
    if(a==0)
        SDA_L; /*在此发出应答或信号 */
    else 
        SDA_H;/*在此发出非应答信号 */
    Delay_uS(1);
    SCL_H;
    Delay_uS(2);
    SCL_L; /*清时钟线，钳住I2C 总线以便继续接收*/
    Delay_uS(1);
}
/*******************************************************************************
* Function Name  : LM75A_SendByte
* Description    : 向无子地址的LM75A发送一个字节数据
* Input          : sla：I2C地址
                   C:数据
* Output         : None
* Return         : 如果返回1 表示操作成功，否则操作有误。
注意： 使用前必须已结束总线。
*******************************************************************************/
u8 LM75A_SendByte(u8 sla,u8 c)
{
    u8 ack;
    I2C_Start(); /*启动总线*/
    ack=I2C_SendByte(sla); /*发送器件地址*/
    if(ack==0)
        return(0);
    ack=I2C_SendByte(c); /*发送数据*/
    if(ack==0)
        return(0);
    I2C_Stop(); /*结束总线*/
    return(1);
}

/*******************************************************************************
* Function Name  : LM75A_SendStr
* Description    : 向有子地址器件发送多字节数据函数
* Input          : sla：I2C地址
                   suba:LM75A子地址
                   s:发送数据缓冲区
                   no:字节数
* Output         : None
* Return         : 如果返回1 表示操作成功，否则操作有误。
注意： 使用前必须已结束总线。
*******************************************************************************/
u8 LM75A_SendStr(u8 sla,u8 suba,u8 *s,u8 no)
{
    u8 i,ack;
    
    I2C_Start(); /*启动总线*/
    ack=I2C_SendByte(sla); /*发送器件地址*/
    if(ack==0)
    {
        return 0;
    }
    ack=I2C_SendByte(suba); /*发送器件子地址*/
    if(ack==0)
    {
        return 0;
    }
    for(i=0;i<no;i++)
    {
        ack=I2C_SendByte(*s); /*发送数据*/
        if(ack==0)
        {
            return 0;
        }
        s++;
    }
    I2C_Stop(); /*结束总线*/
    return(1);
}

/*******************************************************************************
* Function Name  : LM75A_RcvByte
* Description    : 向无子地址的LM75A发送一个字节数据
* Input          : sla：I2C地址
                   C:数据
* Output         : None
* Return         : 如果返回1 表示操作成功，否则操作有误。
注意： 使用前必须已结束总线。
*******************************************************************************/
u8 LM75A_RcvByte(u8 sla,u8 *c)
{
    u8 ack;
    I2C_Start(); /*启动总线*/
    ack=I2C_SendByte(sla+1); /*发送器件地址*/
    if(ack==0)
        return(0);
    *c=I2C_RcvByte(); /*读取数据*/
    I2C_Ack(1); /*发送非就答位*/
    I2C_Stop(); /*结束总线*/
    return(1);
}
/*******************************************************************************
* Function Name  : LM75A_RcvStr
* Description    : 向有子地址器件接收多字节数据函数
* Input          : sla：I2C地址
                   suba:LM75A子地址
                   s:发送数据缓冲区
                   no:字节数
* Output         : None
* Return         : 如果返回1 表示操作成功，否则操作有误。
注意： 使用前必须已结束总线。
*******************************************************************************/
u8 LM75A_RcvStr(u8 sla,u8 suba,u8 *s,u8 no)
{
    u8 i,ack;
    I2C_Start(); /*启动总线*/
    ack=I2C_SendByte(sla); /*发送器件地址*/
    if(ack==0)
    {
        return 0;
    }
    ack=I2C_SendByte(suba); /*发送器件子地址*/
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
        *s=I2C_RcvByte(); /*发送数据*/
        I2C_Ack(0); /*发送就答位*/
        s++;
    }
    *s=I2C_RcvByte();
    I2C_Ack(1); /*发送非应位*/
    I2C_Stop(); /*结束总线*/
    return(1);
}
/*******************************************************************************
* Function Name  : AT24C64_W
* Description    : 向24C64写数据（分页写）
* Input          : 
                    sla:从器件地址
                    AT24C64_address:E2PROM地址
                    buf:发送缓冲区指针
                    count:发送数据长度
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
* Description    : 向24C64读数据（分页读）
* Input          : 
                    sla:从器件地址
                    AT24C64_address:E2PROM地址
                    buf:接收缓冲区指针
                    count:读取数据长度
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
* Description    : 向24C64写数据(1个字节写)
* Input          : 
                    sla:从器件地址
                    AT24C64_address:E2PROM地址
                    buf:接收缓冲区指针
                    count:读取数据长度
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
* Description    : 向24C64读数据（一个字节读）
* Input          : 
                    sla:从器件地址
                    AT24C64_address:E2PROM地址
                    buf:接收缓冲区指针
                    count:读取数据长度
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
* Description    : 向24C64写数据（分页写）
* Input          : 
                    AT24C64_address:E2PROM地址
                    data:发送数据
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
* Description    : 向24C64读数据（分页读）
* Input          : 
                    AT24C64_address:E2PROM地址
* Output         : 从AT24C64接收到的数据
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
* Description    : 接收temp寄存器中的温度值
* Input          : sla：I2C地址
                   suba:LM75A子地址
                   s:发送数据缓冲区
                   no:字节数
* Output         : None
* Return         : 如果返回1 表示操作成功，否则操作有误。
注意： 使用前必须已结束总线。
*******************************************************************************/
u8 LM75A_RcvTemp()
{
    u8 i,ack;
    u16 tmp,tmp1,tmp2;
    
    I2C_Start(); /*启动总线*/
    I2C_SendByte(LM75A_ADDR); /*发送器件地址*/
    Delay_uS(1); 
   
    I2C_SendByte(0); /*发送器件子地址*/
    Delay_uS(1); 
    
    I2C_Start();
    ack=I2C_SendByte(LM75A_ADDR+1);
    Delay_uS(1); 
    
    tmp1=I2C_RcvByte(); /*发送数据*/
    Delay_uS(1); 
    I2C_Ack(0); /*发送就答位*/
    
    tmp2=I2C_RcvByte();
    Delay_uS(1); 
    I2C_Ack(1); /*发送非应位*/
    I2C_Stop(); /*结束总线*/
    
    tmp=((tmp1<<8)|tmp2);
    
    Tempdata=(tmp&0x03ff)*0.125;
    return(1);
}