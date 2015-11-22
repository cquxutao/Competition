
#include "includes.h"

/*******************************************************************************
* Function Name  : GPRS_SendData
* Description    : 通过USART1向GPRS发送数据
* Input          : buf:发送缓冲区指针
                   len:发送数据长度
* Output         : None
* Return         : None
*******************************************************************************/
void GPRS_SendData(u8 *buf,u16 len)
{
    u16 i;
    usart_data.gprs_rxflag=FALSE;
    usart_data.gprs_rxlen=0;
    for(i=0;i<len;i++)
    {
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
        USART_SendData(USART1,buf[i]);
    }
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

/*******************************************************************************
* Function Name  : GPRS_RecvData
* Description    : 通过USART1接收GPRS发送的数据
* Input          : buf:接收缓冲区指针
                   Timeout:接收超时时间
* Output         : 返回接收数据长度
* Return         : None
*******************************************************************************/
u16 GPRS_RecvData(u8 *buf,const u32 timeout)
{  
    OSTimeDly(10);
    u32 time_cnt,i,len;
    
    time_cnt=csw.milsec;
    while(1)
    {     
        if(usart_data.gprs_rxflag==TRUE)
        {
            if(fabs(csw.milsec-usart_data.gprs_rxtim)>100)
            {
                for(i=0;i<usart_data.gprs_rxlen;i++)
                {
                    buf[i]=usart_data.gprs_rxbuf[i];
                }
                buf[i]='\0';
                len=usart_data.gprs_rxlen;
                usart_data.gprs_rxlen=0;
                usart_data.gprs_rxflag=FALSE;
                break;
            }
            else
            {
                OSTimeDly(1);
            }
        }
        else if(fabs(csw.milsec-time_cnt)>timeout)
            return 0;
        OSTimeDly(1);
    }
    return len;
}

/*******************************************************************************
* Function Name  : send_sms
* Description    : 发送短信
* Input          : tele:电话号码
                   message:短信内容指针
* Output         : 
* Return         : None
*******************************************************************************/
void send_sms(u8 *tele,u8 *message)
{
    u8 buf[50],rxbuf[100];
    
    strcpy((char *)buf,"AT+CMGF=1\r\n");          
    GPRS_SendData(buf,strlen((char *)buf));  
    GPRS_RecvData(rxbuf,100);   //清接收
    
    strcpy((char *)buf,"AT+CSCS=\"GSM\"\r\n");
    GPRS_SendData(buf,strlen((char *)buf));  
    GPRS_RecvData(rxbuf,100);   //清接收
    
    strcpy((char *)buf,"AT+CMGS=\"");
    strcat((char *)buf,(char *)tele);
    strcat((char *)buf,"\"\r\n");
    GPRS_SendData(buf,strlen((char *)buf));  
    GPRS_RecvData(rxbuf,100);   //清接收
    
    strcpy((char *)buf,(char *)message);
    GPRS_SendData(buf,strlen((char *)buf));  
    GPRS_RecvData(rxbuf,100);   //清接收   
    
    buf[0]=0x1A;
    GPRS_SendData(buf,1);
    GPRS_RecvData(rxbuf,30000);   //清接收   
}
/********************************************************************************************************
* 函 数 名 : send_pdu_sms
* 描    述 : 中文短信测试
* 输入参数 : 
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
void send_pdu_sms(u8 *tele,u8 *message)
{
    SMSTYPE smsType;
    u8 buf[50];
    u8 buf1[50];
    u8 sendbuf[200];
//    u8 err;
    u16 len;
    strcpy((char *)buf1,"86");
    strcat((char *)buf1,(char *)tele);
    strcat((char *)buf1,"F");
    Ascii_To_Hex(buf1,smsType.DA,strlen((char *)buf1));
//    smsType.DA[0]=0x86;
//    smsType.DA[1]=0x13;
//    smsType.DA[2]=0x67;
//    smsType.DA[3]=0x84;
//    smsType.DA[4]=0x07;
//    smsType.DA[5]=0x65;
//    smsType.DA[6]=0x2F;
    smsType.TP_DCS=GSM_UCS2;                      
    len=GsmEncodePdu_NoCenter((SMSTYPE *)&smsType.SCA,message,strlen((char *)message),sendbuf);
    //OSSemPend(GprsSem,0,&err);//请求GPRS信号量
                
    strcpy((char *)buf,"AT+CMGF=0\r\n");          
    GPRS_SendData(buf,strlen((char *)buf));  
    GPRS_RecvData(buf,100);   //清接收
    
    strcpy((char *)buf,"AT+CSCS=\"GSM\"\r\n");
    GPRS_SendData(buf,strlen((char *)buf));  
    GPRS_RecvData(buf,100);   //清接收
    
    strcpy((char *)buf,"AT+CMGS=");
    sprintf((char *)buf1,"%d\r\n",len);
    strcat((char *)buf,(char *)buf1);
    GPRS_SendData(buf,strlen((char *)buf));  
    GPRS_RecvData(buf,100);   //清接收
        
    GPRS_SendData(sendbuf,strlen((char *)sendbuf));  
    GPRS_RecvData(buf,100);   //清接收   
    buf[0]=0x1A;
    GPRS_SendData(buf,1);
    GPRS_RecvData(buf,30000);   //清接收     
    //OSSemPost(GprsSem);//释放GPRS信号量
}
/*******************************************************************************
* Function Name  : delete_sms
* Description    : 删除短信
* Input          : addr:短信存储位置,如果是0xFF则删除全部短信
* Output         : 
* Return         : None
*******************************************************************************/
void delete_sms(u8 addr)
{
    u8 temp[20];
    u8 temp_buf[50];
    if(addr==0xFF)
        strcpy((char *)temp_buf,"AT+QMGDA=\"DEL ALL\"\r\n"); 
    else
    {
        strcpy((char *)temp_buf,"AT+CMGD=");
        sprintf((char *)temp,"%d\r\n",addr);
        strcat((char*)temp_buf,(char*)temp);
    }
    GPRS_SendData(temp_buf,strlen((char *)temp_buf));
}

