#ifndef __PDU_H
#define __PDU_H

#define GSM_7BIT 0x00
#define GSM_UCS2 0x08
#define GSM_8BIT
typedef struct _PDUTYPE
{
    u8 SCA[12];//Sevice Center Address服务中心的电话号码
    u8 PDU_Type;//Protocol Data Unit Type 协议单元数据类型
    u8 MR;//Message Reference 所有成功的SMS_SUBMIT参考数目
    u8 OA[12];//Originator Adrress发送方的SME地址
    u8 DA[12];//Destination Address 接收方的SME地址
    u8 PID;//Protocol Identifier  参数显示SMSC以何种方式处理SM(比如FAx,Voice等)
    u8 DCS;//Data Coding Scheme  参数表示用户数据（UD）采用什么编码方案
    u8 SCTS[7];//Service Center Timd Stamp  SMCS接收时间的时间戳
    u8 VP;//Validity Period 消息在SMSC中不再有效的时长
    u8 UDL;//User Data Length用户数据长度
    u8 UD;//User Data  SM数据
}PDUTYPE;

typedef struct _SMSTYPE
{
    u8 SCA[12];
    u8 OA[12];
    u8 DA[24];
    u8 TP_DCS;
}SMSTYPE;

u16  GsmDecode8bit(const u8 *pSrc, u8 *pDst, u16 nSrcLength);
u16  GsmEncode8bit(const u8 *pSrc, u8 *pDst, u16 nSrcLength);
u16  GsmDecodeUcs2(const u8* pSrc, u8* pDst, u16 nSrcLength);
u16  GsmEncodeUcs2(const u8* pSrc, u8* pDst);
u16  GsmDecode7bit(const u8* pSrc, u8* pDst, u16 nSrcLength);
u16  GsmEncode7bit(const u8* pSrc, u8* pDst, u16 nSrcLength);
u16  Ascii_To_Hex(const u8* pSrc, u8* pDst, u16 nSrcLength);
u16  Hex_To_Ascii(const u8* pSrc, u8* pDst, u16 nSrcLength);
u8   Hex_Num_Decode(const u8 *pSrc,u8 *pDst,u8 nSrcLength);
u8   Que_Number_Length(const u8 *Src);
u16  GsmEncodePdu_NoCenter(const SMSTYPE *pSrc,const u8 *DataSrc,u16 datalen, u8* pDst);
u16  GsmEncodePdu_Center(const SMSTYPE *pSrc,const u8 *DataSrc,u16 datalen, u8* pDst);

#endif