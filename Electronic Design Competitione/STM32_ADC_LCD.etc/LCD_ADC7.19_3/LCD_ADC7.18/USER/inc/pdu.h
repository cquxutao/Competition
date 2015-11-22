#ifndef __PDU_H
#define __PDU_H

#define GSM_7BIT 0x00
#define GSM_UCS2 0x08
#define GSM_8BIT
typedef struct _PDUTYPE
{
    u8 SCA[12];//Sevice Center Address�������ĵĵ绰����
    u8 PDU_Type;//Protocol Data Unit Type Э�鵥Ԫ��������
    u8 MR;//Message Reference ���гɹ���SMS_SUBMIT�ο���Ŀ
    u8 OA[12];//Originator Adrress���ͷ���SME��ַ
    u8 DA[12];//Destination Address ���շ���SME��ַ
    u8 PID;//Protocol Identifier  ������ʾSMSC�Ժ��ַ�ʽ����SM(����FAx,Voice��)
    u8 DCS;//Data Coding Scheme  ������ʾ�û����ݣ�UD������ʲô���뷽��
    u8 SCTS[7];//Service Center Timd Stamp  SMCS����ʱ���ʱ���
    u8 VP;//Validity Period ��Ϣ��SMSC�в�����Ч��ʱ��
    u8 UDL;//User Data Length�û����ݳ���
    u8 UD;//User Data  SM����
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