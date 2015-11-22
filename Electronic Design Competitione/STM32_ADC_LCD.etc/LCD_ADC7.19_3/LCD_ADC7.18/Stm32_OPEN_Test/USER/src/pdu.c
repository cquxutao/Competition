#include "Includes.h"
const u8  ascii[]="�ع��ý�����ͯ";
const u16  unicode[]={0x67cf,0x52fe,0x597d,0x9526,0x4f60,0x6da6,0x7ae5};
/*******************************************************************************
* Function Name  : GsmDecode8bit
* Description    : ����8λ��
* Input          : pSrc:Դ�ַ���
                   pDest:Ŀ���ַ���
                   nSrcLength:Դ�ַ�������
* Output         : 
* Return         : Ŀ���ַ�������
*******************************************************************************/
u16 GsmDecode8bit(const u8 *pSrc, u8 *pDst, u16 nSrcLength)
{
    // �򵥸���
    for(u16 m=0;m<nSrcLength;m++)
        *pDst++=*pSrc++;
    // ����ַ����Ӹ�������
    *pDst = '\0';
    return nSrcLength;
}
/*******************************************************************************
* Function Name  : GsmEncode8bit
* Description    : 8λ�����
* Input          : pSrc:Դ�ַ���
                   pDest:Ŀ���ַ���
                   nSrcLength:Դ�ַ�������
* Output         : 
* Return         : Ŀ���ַ�������
*******************************************************************************/
u16 GsmEncode8bit(const u8 *pSrc, u8 *pDst, u16 nSrcLength)
{
    // �򵥸���
    for(u16 m=0;m<nSrcLength;m++)
        *pDst++=*pSrc++;
    
    return nSrcLength;
}
/*******************************************************************************
* Function Name  : GsmDecodeUcs2
* Description    : Ucs2�����
* Input          : pSrc:Դ�ַ���
                   pDest:Ŀ���ַ���
                   nSrcLength:Դ�ַ�������
* Output         : 
* Return         : Ŀ���ַ�������
*******************************************************************************/
u16 GsmDecodeUcs2(const u8* pSrc, u8* pDst, u16 nSrcLength)
{
    u16 nDstLength=nSrcLength;        // UNICODE���ַ���Ŀ
    
    // �ߵ��ֽڶԵ���ƴ��UNICODE
    for(u16 i=0; i<nSrcLength; i+=2)
    {
        // �ȸ�λ�ֽ�,��Ϊ�����ݡ����ֽ�Ϊ0
        pSrc++;
        // ���λ�ֽ�
        *pDst++= *pSrc++;        
    }
    // ����Ŀ���ַ�������
    return (nDstLength>>1);
}
/*******************************************************************************
* Function Name  : GsmEncodeUcs2
* Description    : Ucs2�����
* Input          : pSrc:Դ�ַ���
                   pDest:Ŀ���ַ���
                   nSrcLength:Դ�ַ�������
* Output         : 
* Return         : Ŀ���ַ�������
*******************************************************************************/
u16 GsmEncodeUcs2(const u8* pSrc, u8* pDst)
{
    u16 nDstLength=0;        // UNICODE���ַ���Ŀ
    u16 i=0;   
    u16 left,right,middle;
    u16 word;	
    u16 tempword;

    // �ߵ��ֽڶԵ������
    while(*pSrc!='\0')
    {
        if(*pSrc<=0x80)
        {
            *pDst++ = 0x00;
            *pDst++ = * pSrc++;
            nDstLength+=2;
        }
        else
        {
            left=0;
            word=((*(pSrc+1))+(*pSrc)*256);
            right=strlen((char *)ascii)/2-1;
            while(left<=right)//���ַ������㷨
            {
                middle=(left+right)/2;
                tempword=(u16)(ascii[middle*2]*256+ascii[middle*2+1]);
                if(word>tempword)
                {
                    left=middle+1;
                }
                else if(word<tempword)
                {
                    right=middle-1;
                }
                else if(tempword==word)
                {
                    i=middle;
                    break;
                }		
            }
            *pDst++= unicode[i]/256;
            *pDst++= unicode[i]%256;
            pSrc+=2;
            nDstLength+=2;
        }
    }
//    for(u16 i=0; i<nDstLength; i++)
//    {        
//        *pDst++ = 0x00;// �������λ�ֽ�
//        *pDst++ = * pSrc++;// �������λ�ֽ�        
//    }    
//    return (nDstLength <<1);// ����Ŀ����봮����
    return nDstLength;
}
/*******************************************************************************
* Function Name  : GsmDecode7bit
* Description    : 7λ�����
* Input          : pSrc:Դ�ַ���
                   pDest:Ŀ���ַ���
                   nSrcLength:Դ�ַ�������
* Output         : 
* Return         : Ŀ���ַ�������
*******************************************************************************/
u16  GsmDecode7bit(const u8* pSrc, u8* pDst, u16 nSrcLength)
{
    u16 nSrc;        // Դ�ַ����ļ���ֵ
    u16 nDst;        // Ŀ����봮�ļ���ֵ
    u16 nByte;       // ��ǰ���ڴ���������ֽڵ���ţ���Χ��0-6
    u8 nLeft;    // ��һ�ֽڲ��������
    
    // ����ֵ��ʼ��
    nSrc = 0;
    nDst = 0;
    
    // �����ֽ���źͲ������ݳ�ʼ��
    nByte = 0;
    nLeft = 0;
    
    // ��Դ����ÿ7���ֽڷ�Ϊһ�飬��ѹ����8���ֽ�
    // ѭ���ô�����̣�ֱ��Դ���ݱ�������
    // ������鲻��7�ֽڣ�Ҳ����ȷ����
    while(nSrc<nSrcLength)
    {
        // ��Դ�ֽ��ұ߲��������������ӣ�ȥ�����λ���õ�һ��Ŀ������ֽ�
        *pDst = ((*pSrc << nByte) | nLeft) & 0x7f;
        // �����ֽ�ʣ�µ���߲��֣���Ϊ�������ݱ�������
        nLeft = *pSrc >> (7-nByte);
        
        // �޸�Ŀ�괮��ָ��ͼ���ֵ
        pDst++;
        nDst++;
        // �޸��ֽڼ���ֵ
        nByte++;
        
        // ����һ������һ���ֽ�
        if(nByte == 7)
        {
            // ����õ�һ��Ŀ������ֽ�
            *pDst = nLeft;
            
            // �޸�Ŀ�괮��ָ��ͼ���ֵ
            pDst++;
            nDst++;
            
            // �����ֽ���źͲ������ݳ�ʼ��
            nByte = 0;
            nLeft = 0;
        }
        
        // �޸�Դ����ָ��ͼ���ֵ
        pSrc++;
        nSrc++;
    }    
    *pDst = 0;
    return nDst;   // ����Ŀ�괮���� 
}
/*******************************************************************************
* Function Name  : GsmEncode7bit
* Description    : 7λ����룬��ÿ��ascii8λ�����Bit8ȥ����
                   ���ν���7λ����ĺ�λ����Ƶ�ǰ�棬�γ��µ�8λ���롣
* Input          : pSrc:Դ�ַ���
                   pDest:Ŀ���ַ���
                   nSrcLength:Դ�ַ�������
* Output         : 
* Return         : Ŀ���ַ�������
*******************************************************************************/ 
u16  GsmEncode7bit(const u8* pSrc, u8* pDst, u16 nSrcLength)
{
    u16 nSrc;        // Դ�ַ����ļ���ֵ
    u16 nDst;        // Ŀ����봮�ļ���ֵ
    u16 nChar;       // ��ǰ���ڴ���������ַ��ֽڵ���ţ���Χ��0-7
    u8 nLeft;    // ��һ�ֽڲ��������
    
    // ����ֵ��ʼ��
    nSrc = 0;
    nDst = 0;
    
    // ��Դ��ÿ8���ֽڷ�Ϊһ�飬ѹ����7���ֽ�
    // ѭ���ô�����̣�ֱ��Դ����������
    // ������鲻��8�ֽڣ�Ҳ����ȷ����
    while(nSrc<nSrcLength+1)
    {
        // ȡԴ�ַ����ļ���ֵ�����3λ
        nChar = nSrc & 7;
        // ����Դ����ÿ���ֽ�
        if(nChar == 0)
        {
            // ���ڵ�һ���ֽڣ�ֻ�Ǳ�����������������һ���ֽ�ʱʹ��
            nLeft = *pSrc;
        }
        else
        {
            // ���������ֽڣ������ұ߲��������������ӣ��õ�һ��Ŀ������ֽ�
            *pDst = (*pSrc << (8-nChar)) | nLeft;
            // �����ֽ�ʣ�µ���߲��֣���Ϊ�������ݱ�������
            nLeft = *pSrc >> nChar;
            // �޸�Ŀ�괮��ָ��ͼ���ֵ pDst++;
            pDst++;
            nDst++; 
        } 
        
        // �޸�Դ����ָ��ͼ���ֵ
        pSrc++; nSrc++;
    }
    
    // ����Ŀ�괮����
    return nDst; 
    
}
/*******************************************************************************
* Function Name  : Ascii_To_Hex
* Description    : ��Ascii��ת����16������
* Input          : pSrc:Դ�ַ���
                   pDest:Ŀ���ַ���
                   nSrcLength:Դ�ַ�������
* Output         : 
* Return         : Ŀ���ַ�������
*******************************************************************************/ 
u16  Ascii_To_Hex(const u8* pSrc, u8* pDst, u16 nSrcLength)
{
    for(u16 i=0; i<nSrcLength; i+=2)
    {
        // �����4λ
        if(*pSrc>='0' && *pSrc<='9')
        {
            *pDst = (*pSrc - '0') << 4;
        }
        else if(*pSrc>='A' && *pSrc<='F')
        {
            *pDst = (*pSrc - 'A' + 10) << 4;
        }
        else  if(*pSrc>='a' && *pSrc<='f')
        {
            *pDst = (*pSrc - 'a' + 10) << 4;
            
        }
        else
            return FALSE;
        pSrc++;
        // �����4λ
        if(*pSrc>='0' && *pSrc<='9')
        {
            *pDst |= *pSrc - '0';
        }
        else if(*pSrc>='A' && *pSrc<='F')
        {
            *pDst |= *pSrc - 'A' + 10;
        }
        else  if(*pSrc>='a' && *pSrc<='f')
        {
            *pDst |= (*pSrc - 'a' + 10);
        }
        else
            return FALSE;
        pSrc++;
        pDst++;
    }
    
    // ����Ŀ�����ݳ���
    return (nSrcLength >> 1);
    
}
/*******************************************************************************
* Function Name  : Hex_To_Ascii
* Description    : ��16������ת����Ascii��
* Input          : pSrc:Դ�ַ���
                   pDest:Ŀ���ַ���
                   nSrcLength:Դ�ַ�������
* Output         : 
* Return         : Ŀ���ַ�������
*******************************************************************************/ 
u16 Hex_To_Ascii(const u8* pSrc, u8* pDst, u16 nSrcLength)
{
    
    const u8 tab[]="0123456789ABCDEF";    // 0x0-0xf���ַ����ұ�
    
    for(u16 i=0; i<nSrcLength; i++)
    {
        // �����4λ
        *pDst++ = tab[*pSrc >> 4];
        
        // �����4λ
        *pDst++ = tab[*pSrc & 0x0f];
        
        pSrc++;
    }
    
    // ����ַ����Ӹ�������
    *pDst = '\0';
    
    // ����Ŀ���ַ�������
    return (nSrcLength << 1);
}
/*******************************************************************************
* Function Name  : Hex_Num_Encode
* Description    : �����ߵ����ַ���ת��Ϊ����˳����ַ���
                   �磺"8613693092030" -. "683196032930F0"
* Input          : pSrc:Դ�ַ���
                   pDest:Ŀ���ַ���
                   nSrcLength:Դ�ַ�������
* Output         : 
* Return         : Ŀ���ַ�������
*******************************************************************************/ 
u8 Hex_Num_Encode(const u8 *pSrc,u8 *pDst,u8 nSrcLength)
{
    u8 nDstLength=nSrcLength;
    if(nDstLength&0x01)
        nDstLength+=1;
    for(u8 i=0;i<nDstLength;i+=2)
    {
        *pDst=(*pSrc<<4)|(*pSrc>>4);
        pDst++;
        pSrc++;
    }
    if(nSrcLength&1)
    {
        *(pDst-1)&=0x0f;
        *(pDst-1)|=0xf0;
    }
    return (nDstLength>>1);
}
/*******************************************************************************
* Function Name  : Hex_Num_Decode
* Description    : �����ߵ����ַ���ת��Ϊ����˳����ַ���
                   �磺"8613693092030" -. "683196032930F0"
* Input          : pSrc:Դ�ַ���
                   pDest:Ŀ���ַ���
                   nSrcLength:Դ�ַ�������
* Output         : 
* Return         : Ŀ���ַ�������
*******************************************************************************/ 
u8 Hex_Num_Decode(const u8 *pSrc,u8 *pDst,u8 nSrcLength)
{
    return Hex_Num_Encode(pSrc,pDst,nSrcLength);
}
///*******************************************************************************
//* Function Name  : GsmDecodePdu
//* Description    : PDU����
//* Input          : pSrc:Դ�ַ���
//                   pSrcLength:Դ�ַ�������
//
//* Output         : 
//* Return         : Ŀ���ַ�������
//*******************************************************************************/ 
//u16  GsmDecodePdu(const u8* pSrc,u16 pSrcLength,SMSTYPE *pSmstype,u8 *DataDst)
//{
//    
//    u8 nDstLength=0;          // Ŀ��PDU������
//    u8 tmp;       // �ڲ��õ���ʱ�ֽڱ���
//    u8 buf[256];  // �ڲ��õĻ�����
//    u16 templen=0;
//    u16 tmp16;
//    
//    //---SCA
//    // SMSC��ַ��Ϣ��
//    Ascii_To_Hex(pSrc, &tmp, 2);    // ȡ����
//    if(tmp>0&&tmp<=12)
//    {
//        tmp = (tmp - 1) * 2;    // SMSC���봮����,ȥ����91;
//        pSrc += 4;              // ָ�����,���������ֽڣ�91�����ֽڡ���4���ֽ�
//        templen+=4;
//        Ascii_To_Hex(pSrc, buf, tmp);    // ת��SMSC���뵽Ŀ��PDU��
//        Hex_Num_Decode(buf,&pSmstype->SCA,tmp);//ȡ�������ĺ���,���棬�ظ�ʱ��,��HEX�뱣���  
//        pSrc += tmp;        // ָ�����,��ʱ����PDUType
//        templen+=tmp;
//        
//        
//        // TPDU�λ����������ظ���ַ��
//        //--PDUType
//        Ascii_To_Hex(pSrc, &tmp, 2);    // ȡ��������
//        pSrc += 2;        // ָ�����
//        templen+=2;
//        //--OA----star
//        // �����ظ���ַ��ȡ�ظ���ַ��Ϣ
//        Ascii_To_Hex(pSrc, &tmp, 2);    // ȡ����,OA�ĳ�����ָ����ĺ��볤�ȣ�
//        if(tmp & 1) tmp += 1;    // ������ż��
//        pSrc += 4;          // ָ����ƣ���ȥ���ȣ���91,��4���ֽ�
//        templen+=4;
//        if(tmp>0&&tmp<=12*2)
//        {
//            Ascii_To_Hex(pSrc, buf, tmp); 
//            Hex_Num_Decode(buf,(*pSmstype).TPA,tmp) ;  // ȡTP-RA����,����ظ���ַ
//            pSrc += tmp;        // ָ�����
//            templen+=tmp;
//            //--OA---End-------
//            
//            
//            // TPDU��Э���ʶ�����뷽ʽ���û���Ϣ��
//            Ascii_To_Hex(pSrc, (u8*)&(*pSmstype).TP_PID, 2);    // ȡЭ���ʶ(TP-PID)
//            pSrc += 2;
//            templen+=2;       // ָ�����
//            Ascii_To_Hex(pSrc, (u8*)&(*pSmstype).TP_DCS, 2);    // ȡ���뷽ʽ(TP-DCS),�������ʱ�ͻظ�ʱ��
//            pSrc += 2;        // ָ�����
//            templen+=2;
//            //GsmSerializeNumbers(pSrc, m_SmsType.TP_SCTS, 14);        // ����ʱ����ַ���(TP_SCTS) 
//            pSrc += 14;       // ָ�����
//            templen+=14;
//            Ascii_To_Hex(pSrc, &tmp, 2);    // �û���Ϣ����(TP-UDL)
//            pSrc += 2;        // ָ�����
//            templen+=2;
//            // pDst.TP_DCS=8;
//            if(((*pSmstype).TP_DCS&0x0c) == GSM_7BIT)    
//            {
//                // 7-bit����
//                tmp16=tmp%8 ? ((u16)tmp * 7 / 8 + 1) : ((u16)tmp * 7 / 8);
//                tmp16*=2;
//                if((templen+tmp16<=pSrcLength)&&(tmp16<400))
//                { 
//                    nDstLength = Ascii_To_Hex(pSrc, buf,tmp16);  // ��ʽת��
//                    GsmDecode7bit(buf, DataDst, nDstLength);    // ת����TP-DU
//                    nDstLength = tmp;
//                }
//            }
//            else if(((*pSmstype).TP_DCS&0x0c) == GSM_UCS2)
//            {
//                // UCS2����
//                tmp16=tmp * 2;
//                if((templen+tmp16<=pSrcLength)&&(tmp16<400))
//                {
//                    nDstLength = Ascii_To_Hex(pSrc, buf,tmp16);        // ��ʽת��
//                    nDstLength = GsmDecodeUcs2(buf, DataDst, nDstLength);    // ת����TP-DU
//                }
//            }
//            else
//            {
//                // 8-bit����
//                tmp16=tmp * 2;
//                if((templen+tmp16<=pSrcLength)&&(tmp16<512))
//                {
//                    nDstLength = Ascii_To_Hex(pSrc, buf,tmp16);        // ��ʽת��
//                    nDstLength = GsmDecode8bit(buf, DataDst, nDstLength);    // ת����TP-DU
//		}
//		
//            }
//        }
//    }
//    // ����Ŀ���ַ�������
//    return nDstLength;
//}
//���غ��볤��
u8  Que_Number_Length(const u8 *Src)
{
    u8 n=0;
    for(u8 m=0;m<8;m++)
    {
        if((Src[m]&0xf0)==0xf0)
            break;
        n++;
        if((Src[m]&0x0f)==0x0f)
            break;
        n++;        
    }
    return n;    
}

/*******************************************************************************
* Function Name  : GsmEncodePdu_NoCenter
* Description    : PDU����,���Ӷ������ĺ���
* Input          : pSrc:SMSTYPE����ָ��
                   DataSrc:��������ָ��
                   datalen:�������ݳ���
                   pDest:Ŀ���ַ���
* Output         : 
* Return         : Ŀ���ַ�������
*******************************************************************************/ 
u16  GsmEncodePdu_NoCenter(const SMSTYPE *pSrc,const u8 *DataSrc,u16 datalen, u8* pDst)
{
    
    u16 nLength;             // �ڲ��õĴ�����
    u16 nDstLength=0;          // Ŀ��PDU������
    u8 buf[256];  // �ڲ��õĻ�����
    
    // SMSC��ַ��Ϣ��
    buf[0]=0;//SCA
    nDstLength += Hex_To_Ascii(buf, pDst, 1);
    // TPDU�λ���������Ŀ���ַ�� 
    buf[0]=0x11;//PDUTYPE
    buf[1]=0x00;//MR
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength], 2);
    // SMSC��ַ��Ϣ��
    nLength = Que_Number_Length(pSrc->DA);// TP-DA��ַ�ַ����ĳ���
    buf[0] = (u8)nLength;   // Ŀ���ַ���ָ���(TP-DA��ַ�ַ�����ʵ����)
    buf[1] = 0x91;            // �̶�: �ù��ʸ�ʽ����
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength], 2);
    nLength=Hex_Num_Encode(pSrc->DA,buf,nLength);
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength],nLength);  // ת��TP-DA��Ŀ��PDU��
    
    // TPDU��Э���ʶ�����뷽ʽ���û���Ϣ��
    buf[0] = 0;        // Э���ʶ(TP-PID)
    buf[1] = pSrc->TP_DCS&0x0c;        // �û���Ϣ���뷽ʽ(TP-DCS)
    buf[2] = 0x8f;           // ��Ч��(TP-VP)Ϊ12Сʱ
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength],3);
    if((pSrc->TP_DCS&0x0c) == GSM_7BIT) // 7-bit���뷽ʽ   
    {
        buf[0] = datalen;            // ����ǰ����.7λ��ʽ��ʾ����ǰ�ĳ���
        nLength = GsmEncode7bit(DataSrc, &buf[1], datalen); 
        nLength+=1;
        // ת��		TP-DA��Ŀ��PDU��
    }
    else if((pSrc->TP_DCS&0x0c)  == GSM_UCS2)// UCS2���뷽ʽ
    {
        buf[0] = GsmEncodeUcs2(DataSrc, &buf[1]);    // ת��TP-DA��Ŀ��PDU��
        nLength = buf[0] + 1;        // nLength���ڸö����ݳ���
    }
    else// 8-bit���뷽ʽ
    {
        buf[0] = GsmEncode8bit(DataSrc, &buf[1], datalen);    // ת��TP-DA��Ŀ��PDU��
        nLength = buf[0] + 1;        // nLength���ڸö����ݳ���
    }
    //nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength], nLength);        // ת���ö����ݵ�Ŀ��PDU��
    Hex_To_Ascii(buf, &pDst[nDstLength], nLength); 
    nDstLength=nLength-1+15;
    // ����Ŀ���ַ�������
    return nDstLength;
}
/*******************************************************************************
* Function Name  : GsmEncodePdu_Center
* Description    : PDU����
* Input          : pSrc:SMSTYPE����ָ��
                   DataSrc:��������ָ��
                   datalen:�������ݳ���
                   pDest:Ŀ���ַ���
* Output         : 
* Return         : Ŀ���ַ�������
*******************************************************************************/ 
u16 GsmEncodePdu_Center(const SMSTYPE *pSrc,const u8 *DataSrc,u16 datalen, u8* pDst)
{
    
    u16 nLength;             // �ڲ��õĴ�����
    u16 nDstLength=0;          // Ŀ��PDU������
    u8 buf[256];  // �ڲ��õĻ�����
    
    // SMSC��ַ��Ϣ��
    nLength = Que_Number_Length(pSrc->SCA);    // SMSC��ַ�ַ����ĳ���    
    buf[0] = (u8)((nLength & 1) == 0 ? nLength : nLength + 1) / 2 + 1;    // SMSC��ַ��Ϣ����
    buf[1] = 0x91;        // �̶�: �ù��ʸ�ʽ����
    nDstLength = Hex_To_Ascii(buf, pDst, 2);        // ת��2���ֽڵ�Ŀ��PDU��
    nLength=Hex_Num_Encode(pSrc->SCA,buf,nLength);
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength],nLength);     // ת��SMSC��Ŀ��PDU��
    // TPDU�λ���������Ŀ���ַ��
    buf[0]=0x11;//PDUTYPE
    buf[1]=0x00;//MR
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength], 2);
    // SMSC��ַ��Ϣ��
    nLength = Que_Number_Length(pSrc->DA);// TP-DA��ַ�ַ����ĳ���
    buf[0] = (u8)nLength;   // Ŀ���ַ���ָ���(TP-DA��ַ�ַ�����ʵ����)
    buf[1] = 0x91;            // �̶�: �ù��ʸ�ʽ����
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength], 2);
    nLength=Hex_Num_Encode(pSrc->DA,buf,nLength);
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength],nLength);  // ת��TP-DA��Ŀ��PDU��
    
    // TPDU��Э���ʶ�����뷽ʽ���û���Ϣ��
    buf[0] = 0;        // Э���ʶ(TP-PID)
    buf[1] = pSrc->TP_DCS&0x0c;        // �û���Ϣ���뷽ʽ(TP-DCS)
    buf[2] = 0x8f;            // ��Ч��(TP-VP)Ϊ12Сʱ
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength],3);
    if((pSrc->TP_DCS&0x0c) == GSM_7BIT) // 7-bit���뷽ʽ   
    {
        buf[0] = datalen;            // ����ǰ����.7λ��ʽ��ʾ����ǰ�ĳ���
        nLength = GsmEncode7bit(DataSrc, &buf[1], datalen); 
        nLength+=1;
        // ת��		TP-DA��Ŀ��PDU��
    }
    else if((pSrc->TP_DCS&0x0c)== GSM_UCS2)// UCS2���뷽ʽ
    {
        buf[0] = GsmEncodeUcs2(DataSrc, &buf[1]);    // ת��TP-DA��Ŀ��PDU��
        nLength = buf[0] + 1;        // nLength���ڸö����ݳ���
    }
    else// 8-bit���뷽ʽ
    {
        buf[0] = GsmEncode8bit(DataSrc, &buf[1], datalen);    // ת��TP-DA��Ŀ��PDU��
        nLength = buf[0] + 1;        // nLength���ڸö����ݳ���
    }
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength], nLength);        // ת���ö����ݵ�Ŀ��PDU��
    
    // ����Ŀ���ַ�������
    return nDstLength;
}



