#include "Includes.h"
const u8  ascii[]="柏勾好锦你润童";
const u16  unicode[]={0x67cf,0x52fe,0x597d,0x9526,0x4f60,0x6da6,0x7ae5};
/*******************************************************************************
* Function Name  : GsmDecode8bit
* Description    : 解析8位码
* Input          : pSrc:源字符串
                   pDest:目的字符串
                   nSrcLength:源字符串长度
* Output         : 
* Return         : 目的字符串长度
*******************************************************************************/
u16 GsmDecode8bit(const u8 *pSrc, u8 *pDst, u16 nSrcLength)
{
    // 简单复制
    for(u16 m=0;m<nSrcLength;m++)
        *pDst++=*pSrc++;
    // 输出字符串加个结束符
    *pDst = '\0';
    return nSrcLength;
}
/*******************************************************************************
* Function Name  : GsmEncode8bit
* Description    : 8位码编码
* Input          : pSrc:源字符串
                   pDest:目的字符串
                   nSrcLength:源字符串长度
* Output         : 
* Return         : 目的字符串长度
*******************************************************************************/
u16 GsmEncode8bit(const u8 *pSrc, u8 *pDst, u16 nSrcLength)
{
    // 简单复制
    for(u16 m=0;m<nSrcLength;m++)
        *pDst++=*pSrc++;
    
    return nSrcLength;
}
/*******************************************************************************
* Function Name  : GsmDecodeUcs2
* Description    : Ucs2码解码
* Input          : pSrc:源字符串
                   pDest:目的字符串
                   nSrcLength:源字符串长度
* Output         : 
* Return         : 目的字符串长度
*******************************************************************************/
u16 GsmDecodeUcs2(const u8* pSrc, u8* pDst, u16 nSrcLength)
{
    u16 nDstLength=nSrcLength;        // UNICODE宽字符数目
    
    // 高低字节对调，拼成UNICODE
    for(u16 i=0; i<nSrcLength; i+=2)
    {
        // 先高位字节,因为是数据。高字节为0
        pSrc++;
        // 后低位字节
        *pDst++= *pSrc++;        
    }
    // 返回目标字符串长度
    return (nDstLength>>1);
}
/*******************************************************************************
* Function Name  : GsmEncodeUcs2
* Description    : Ucs2码编码
* Input          : pSrc:源字符串
                   pDest:目的字符串
                   nSrcLength:源字符串长度
* Output         : 
* Return         : 目的字符串长度
*******************************************************************************/
u16 GsmEncodeUcs2(const u8* pSrc, u8* pDst)
{
    u16 nDstLength=0;        // UNICODE宽字符数目
    u16 i=0;   
    u16 left,right,middle;
    u16 word;	
    u16 tempword;

    // 高低字节对调，输出
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
            while(left<=right)//二分法查找算法
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
//        *pDst++ = 0x00;// 先输出高位字节
//        *pDst++ = * pSrc++;// 后输出低位字节        
//    }    
//    return (nDstLength <<1);// 返回目标编码串长度
    return nDstLength;
}
/*******************************************************************************
* Function Name  : GsmDecode7bit
* Description    : 7位码解码
* Input          : pSrc:源字符串
                   pDest:目的字符串
                   nSrcLength:源字符串长度
* Output         : 
* Return         : 目的字符串长度
*******************************************************************************/
u16  GsmDecode7bit(const u8* pSrc, u8* pDst, u16 nSrcLength)
{
    u16 nSrc;        // 源字符串的计数值
    u16 nDst;        // 目标解码串的计数值
    u16 nByte;       // 当前正在处理的组内字节的序号，范围是0-6
    u8 nLeft;    // 上一字节残余的数据
    
    // 计数值初始化
    nSrc = 0;
    nDst = 0;
    
    // 组内字节序号和残余数据初始化
    nByte = 0;
    nLeft = 0;
    
    // 将源数据每7个字节分为一组，解压缩成8个字节
    // 循环该处理过程，直至源数据被处理完
    // 如果分组不到7字节，也能正确处理
    while(nSrc<nSrcLength)
    {
        // 将源字节右边部分与残余数据相加，去掉最高位，得到一个目标解码字节
        *pDst = ((*pSrc << nByte) | nLeft) & 0x7f;
        // 将该字节剩下的左边部分，作为残余数据保存起来
        nLeft = *pSrc >> (7-nByte);
        
        // 修改目标串的指针和计数值
        pDst++;
        nDst++;
        // 修改字节计数值
        nByte++;
        
        // 到了一组的最后一个字节
        if(nByte == 7)
        {
            // 额外得到一个目标解码字节
            *pDst = nLeft;
            
            // 修改目标串的指针和计数值
            pDst++;
            nDst++;
            
            // 组内字节序号和残余数据初始化
            nByte = 0;
            nLeft = 0;
        }
        
        // 修改源串的指针和计数值
        pSrc++;
        nSrc++;
    }    
    *pDst = 0;
    return nDst;   // 返回目标串长度 
}
/*******************************************************************************
* Function Name  : GsmEncode7bit
* Description    : 7位码编码，将每个ascii8位编码的Bit8去掉，
                   依次将下7位编码的后几位逐次移到前面，形成新的8位编码。
* Input          : pSrc:源字符串
                   pDest:目的字符串
                   nSrcLength:源字符串长度
* Output         : 
* Return         : 目的字符串长度
*******************************************************************************/ 
u16  GsmEncode7bit(const u8* pSrc, u8* pDst, u16 nSrcLength)
{
    u16 nSrc;        // 源字符串的计数值
    u16 nDst;        // 目标编码串的计数值
    u16 nChar;       // 当前正在处理的组内字符字节的序号，范围是0-7
    u8 nLeft;    // 上一字节残余的数据
    
    // 计数值初始化
    nSrc = 0;
    nDst = 0;
    
    // 将源串每8个字节分为一组，压缩成7个字节
    // 循环该处理过程，直至源串被处理完
    // 如果分组不到8字节，也能正确处理
    while(nSrc<nSrcLength+1)
    {
        // 取源字符串的计数值的最低3位
        nChar = nSrc & 7;
        // 处理源串的每个字节
        if(nChar == 0)
        {
            // 组内第一个字节，只是保存起来，待处理下一个字节时使用
            nLeft = *pSrc;
        }
        else
        {
            // 组内其它字节，将其右边部分与残余数据相加，得到一个目标编码字节
            *pDst = (*pSrc << (8-nChar)) | nLeft;
            // 将该字节剩下的左边部分，作为残余数据保存起来
            nLeft = *pSrc >> nChar;
            // 修改目标串的指针和计数值 pDst++;
            pDst++;
            nDst++; 
        } 
        
        // 修改源串的指针和计数值
        pSrc++; nSrc++;
    }
    
    // 返回目标串长度
    return nDst; 
    
}
/*******************************************************************************
* Function Name  : Ascii_To_Hex
* Description    : 将Ascii码转化成16进制数
* Input          : pSrc:源字符串
                   pDest:目的字符串
                   nSrcLength:源字符串长度
* Output         : 
* Return         : 目的字符串长度
*******************************************************************************/ 
u16  Ascii_To_Hex(const u8* pSrc, u8* pDst, u16 nSrcLength)
{
    for(u16 i=0; i<nSrcLength; i+=2)
    {
        // 输出高4位
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
        // 输出低4位
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
    
    // 返回目标数据长度
    return (nSrcLength >> 1);
    
}
/*******************************************************************************
* Function Name  : Hex_To_Ascii
* Description    : 将16进制数转化成Ascii码
* Input          : pSrc:源字符串
                   pDest:目的字符串
                   nSrcLength:源字符串长度
* Output         : 
* Return         : 目的字符串长度
*******************************************************************************/ 
u16 Hex_To_Ascii(const u8* pSrc, u8* pDst, u16 nSrcLength)
{
    
    const u8 tab[]="0123456789ABCDEF";    // 0x0-0xf的字符查找表
    
    for(u16 i=0; i<nSrcLength; i++)
    {
        // 输出低4位
        *pDst++ = tab[*pSrc >> 4];
        
        // 输出高4位
        *pDst++ = tab[*pSrc & 0x0f];
        
        pSrc++;
    }
    
    // 输出字符串加个结束符
    *pDst = '\0';
    
    // 返回目标字符串长度
    return (nSrcLength << 1);
}
/*******************************************************************************
* Function Name  : Hex_Num_Encode
* Description    : 两两颠倒的字符串转换为正常顺序的字符串
                   如："8613693092030" -. "683196032930F0"
* Input          : pSrc:源字符串
                   pDest:目的字符串
                   nSrcLength:源字符串长度
* Output         : 
* Return         : 目的字符串长度
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
* Description    : 两两颠倒的字符串转换为正常顺序的字符串
                   如："8613693092030" -. "683196032930F0"
* Input          : pSrc:源字符串
                   pDest:目的字符串
                   nSrcLength:源字符串长度
* Output         : 
* Return         : 目的字符串长度
*******************************************************************************/ 
u8 Hex_Num_Decode(const u8 *pSrc,u8 *pDst,u8 nSrcLength)
{
    return Hex_Num_Encode(pSrc,pDst,nSrcLength);
}
///*******************************************************************************
//* Function Name  : GsmDecodePdu
//* Description    : PDU解码
//* Input          : pSrc:源字符串
//                   pSrcLength:源字符串长度
//
//* Output         : 
//* Return         : 目的字符串长度
//*******************************************************************************/ 
//u16  GsmDecodePdu(const u8* pSrc,u16 pSrcLength,SMSTYPE *pSmstype,u8 *DataDst)
//{
//    
//    u8 nDstLength=0;          // 目标PDU串长度
//    u8 tmp;       // 内部用的临时字节变量
//    u8 buf[256];  // 内部用的缓冲区
//    u16 templen=0;
//    u16 tmp16;
//    
//    //---SCA
//    // SMSC地址信息段
//    Ascii_To_Hex(pSrc, &tmp, 2);    // 取长度
//    if(tmp>0&&tmp<=12)
//    {
//        tmp = (tmp - 1) * 2;    // SMSC号码串长度,去掉了91;
//        pSrc += 4;              // 指针后移,长度两个字节，91两个字节。共4个字节
//        templen+=4;
//        Ascii_To_Hex(pSrc, buf, tmp);    // 转换SMSC号码到目标PDU串
//        Hex_Num_Decode(buf,&pSmstype->SCA,tmp);//取短信中心号码,保存，回复时用,是HEX码保存的  
//        pSrc += tmp;        // 指针后移,此时到了PDUType
//        templen+=tmp;
//        
//        
//        // TPDU段基本参数、回复地址等
//        //--PDUType
//        Ascii_To_Hex(pSrc, &tmp, 2);    // 取基本参数
//        pSrc += 2;        // 指针后移
//        templen+=2;
//        //--OA----star
//        // 包含回复地址，取回复地址信息
//        Ascii_To_Hex(pSrc, &tmp, 2);    // 取长度,OA的长度是指具体的号码长度，
//        if(tmp & 1) tmp += 1;    // 调整奇偶性
//        pSrc += 4;          // 指针后移，除去长度，和91,共4个字节
//        templen+=4;
//        if(tmp>0&&tmp<=12*2)
//        {
//            Ascii_To_Hex(pSrc, buf, tmp); 
//            Hex_Num_Decode(buf,(*pSmstype).TPA,tmp) ;  // 取TP-RA号码,保存回复地址
//            pSrc += tmp;        // 指针后移
//            templen+=tmp;
//            //--OA---End-------
//            
//            
//            // TPDU段协议标识、编码方式、用户信息等
//            Ascii_To_Hex(pSrc, (u8*)&(*pSmstype).TP_PID, 2);    // 取协议标识(TP-PID)
//            pSrc += 2;
//            templen+=2;       // 指针后移
//            Ascii_To_Hex(pSrc, (u8*)&(*pSmstype).TP_DCS, 2);    // 取编码方式(TP-DCS),这个解码时和回复时用
//            pSrc += 2;        // 指针后移
//            templen+=2;
//            //GsmSerializeNumbers(pSrc, m_SmsType.TP_SCTS, 14);        // 服务时间戳字符串(TP_SCTS) 
//            pSrc += 14;       // 指针后移
//            templen+=14;
//            Ascii_To_Hex(pSrc, &tmp, 2);    // 用户信息长度(TP-UDL)
//            pSrc += 2;        // 指针后移
//            templen+=2;
//            // pDst.TP_DCS=8;
//            if(((*pSmstype).TP_DCS&0x0c) == GSM_7BIT)    
//            {
//                // 7-bit解码
//                tmp16=tmp%8 ? ((u16)tmp * 7 / 8 + 1) : ((u16)tmp * 7 / 8);
//                tmp16*=2;
//                if((templen+tmp16<=pSrcLength)&&(tmp16<400))
//                { 
//                    nDstLength = Ascii_To_Hex(pSrc, buf,tmp16);  // 格式转换
//                    GsmDecode7bit(buf, DataDst, nDstLength);    // 转换到TP-DU
//                    nDstLength = tmp;
//                }
//            }
//            else if(((*pSmstype).TP_DCS&0x0c) == GSM_UCS2)
//            {
//                // UCS2解码
//                tmp16=tmp * 2;
//                if((templen+tmp16<=pSrcLength)&&(tmp16<400))
//                {
//                    nDstLength = Ascii_To_Hex(pSrc, buf,tmp16);        // 格式转换
//                    nDstLength = GsmDecodeUcs2(buf, DataDst, nDstLength);    // 转换到TP-DU
//                }
//            }
//            else
//            {
//                // 8-bit解码
//                tmp16=tmp * 2;
//                if((templen+tmp16<=pSrcLength)&&(tmp16<512))
//                {
//                    nDstLength = Ascii_To_Hex(pSrc, buf,tmp16);        // 格式转换
//                    nDstLength = GsmDecode8bit(buf, DataDst, nDstLength);    // 转换到TP-DU
//		}
//		
//            }
//        }
//    }
//    // 返回目标字符串长度
//    return nDstLength;
//}
//返回号码长度
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
* Description    : PDU编码,不加短信中心号码
* Input          : pSrc:SMSTYPE数据指针
                   DataSrc:发送数据指针
                   datalen:发送数据长度
                   pDest:目的字符串
* Output         : 
* Return         : 目的字符串长度
*******************************************************************************/ 
u16  GsmEncodePdu_NoCenter(const SMSTYPE *pSrc,const u8 *DataSrc,u16 datalen, u8* pDst)
{
    
    u16 nLength;             // 内部用的串长度
    u16 nDstLength=0;          // 目标PDU串长度
    u8 buf[256];  // 内部用的缓冲区
    
    // SMSC地址信息段
    buf[0]=0;//SCA
    nDstLength += Hex_To_Ascii(buf, pDst, 1);
    // TPDU段基本参数、目标地址等 
    buf[0]=0x11;//PDUTYPE
    buf[1]=0x00;//MR
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength], 2);
    // SMSC地址信息段
    nLength = Que_Number_Length(pSrc->DA);// TP-DA地址字符串的长度
    buf[0] = (u8)nLength;   // 目标地址数字个数(TP-DA地址字符串真实长度)
    buf[1] = 0x91;            // 固定: 用国际格式号码
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength], 2);
    nLength=Hex_Num_Encode(pSrc->DA,buf,nLength);
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength],nLength);  // 转换TP-DA到目标PDU串
    
    // TPDU段协议标识、编码方式、用户信息等
    buf[0] = 0;        // 协议标识(TP-PID)
    buf[1] = pSrc->TP_DCS&0x0c;        // 用户信息编码方式(TP-DCS)
    buf[2] = 0x8f;           // 有效期(TP-VP)为12小时
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength],3);
    if((pSrc->TP_DCS&0x0c) == GSM_7BIT) // 7-bit编码方式   
    {
        buf[0] = datalen;            // 编码前长度.7位方式表示编码前的长度
        nLength = GsmEncode7bit(DataSrc, &buf[1], datalen); 
        nLength+=1;
        // 转换		TP-DA到目标PDU串
    }
    else if((pSrc->TP_DCS&0x0c)  == GSM_UCS2)// UCS2编码方式
    {
        buf[0] = GsmEncodeUcs2(DataSrc, &buf[1]);    // 转换TP-DA到目标PDU串
        nLength = buf[0] + 1;        // nLength等于该段数据长度
    }
    else// 8-bit编码方式
    {
        buf[0] = GsmEncode8bit(DataSrc, &buf[1], datalen);    // 转换TP-DA到目标PDU串
        nLength = buf[0] + 1;        // nLength等于该段数据长度
    }
    //nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength], nLength);        // 转换该段数据到目标PDU串
    Hex_To_Ascii(buf, &pDst[nDstLength], nLength); 
    nDstLength=nLength-1+15;
    // 返回目标字符串长度
    return nDstLength;
}
/*******************************************************************************
* Function Name  : GsmEncodePdu_Center
* Description    : PDU编码
* Input          : pSrc:SMSTYPE数据指针
                   DataSrc:发送数据指针
                   datalen:发送数据长度
                   pDest:目的字符串
* Output         : 
* Return         : 目的字符串长度
*******************************************************************************/ 
u16 GsmEncodePdu_Center(const SMSTYPE *pSrc,const u8 *DataSrc,u16 datalen, u8* pDst)
{
    
    u16 nLength;             // 内部用的串长度
    u16 nDstLength=0;          // 目标PDU串长度
    u8 buf[256];  // 内部用的缓冲区
    
    // SMSC地址信息段
    nLength = Que_Number_Length(pSrc->SCA);    // SMSC地址字符串的长度    
    buf[0] = (u8)((nLength & 1) == 0 ? nLength : nLength + 1) / 2 + 1;    // SMSC地址信息长度
    buf[1] = 0x91;        // 固定: 用国际格式号码
    nDstLength = Hex_To_Ascii(buf, pDst, 2);        // 转换2个字节到目标PDU串
    nLength=Hex_Num_Encode(pSrc->SCA,buf,nLength);
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength],nLength);     // 转换SMSC到目标PDU串
    // TPDU段基本参数、目标地址等
    buf[0]=0x11;//PDUTYPE
    buf[1]=0x00;//MR
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength], 2);
    // SMSC地址信息段
    nLength = Que_Number_Length(pSrc->DA);// TP-DA地址字符串的长度
    buf[0] = (u8)nLength;   // 目标地址数字个数(TP-DA地址字符串真实长度)
    buf[1] = 0x91;            // 固定: 用国际格式号码
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength], 2);
    nLength=Hex_Num_Encode(pSrc->DA,buf,nLength);
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength],nLength);  // 转换TP-DA到目标PDU串
    
    // TPDU段协议标识、编码方式、用户信息等
    buf[0] = 0;        // 协议标识(TP-PID)
    buf[1] = pSrc->TP_DCS&0x0c;        // 用户信息编码方式(TP-DCS)
    buf[2] = 0x8f;            // 有效期(TP-VP)为12小时
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength],3);
    if((pSrc->TP_DCS&0x0c) == GSM_7BIT) // 7-bit编码方式   
    {
        buf[0] = datalen;            // 编码前长度.7位方式表示编码前的长度
        nLength = GsmEncode7bit(DataSrc, &buf[1], datalen); 
        nLength+=1;
        // 转换		TP-DA到目标PDU串
    }
    else if((pSrc->TP_DCS&0x0c)== GSM_UCS2)// UCS2编码方式
    {
        buf[0] = GsmEncodeUcs2(DataSrc, &buf[1]);    // 转换TP-DA到目标PDU串
        nLength = buf[0] + 1;        // nLength等于该段数据长度
    }
    else// 8-bit编码方式
    {
        buf[0] = GsmEncode8bit(DataSrc, &buf[1], datalen);    // 转换TP-DA到目标PDU串
        nLength = buf[0] + 1;        // nLength等于该段数据长度
    }
    nDstLength += Hex_To_Ascii(buf, &pDst[nDstLength], nLength);        // 转换该段数据到目标PDU串
    
    // 返回目标字符串长度
    return nDstLength;
}



