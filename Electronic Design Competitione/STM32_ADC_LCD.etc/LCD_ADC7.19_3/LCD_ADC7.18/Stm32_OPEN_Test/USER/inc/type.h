#ifndef __TYPE_H
#define __TYPE_H

typedef unsigned char  uint8;                   /* defined for unsigned 8-bits integer variable 	�޷���8λ���ͱ���  */
typedef signed   char  int8;                    /* defined for signed 8-bits integer variable		�з���8λ���ͱ���  */
typedef unsigned short uint16;                  /* defined for unsigned 16-bits integer variable 	�޷���16λ���ͱ��� */
typedef signed   short int16;                   /* defined for signed 16-bits integer variable 		�з���16λ���ͱ��� */
typedef unsigned int   uint32;                  /* defined for unsigned 32-bits integer variable 	�޷���32λ���ͱ��� */
typedef signed   int   int32;                   /* defined for signed 32-bits integer variable 		�з���32λ���ͱ��� */
typedef float          fp32;                    /* single precision floating point variable (32bits) �����ȸ�������32λ���ȣ� */
typedef double         fp64;                    /* double precision floating point variable (64bits) ˫���ȸ�������64λ���ȣ� */

#define  GPRS_RCV_LEN 512
#define  RS485_RCV_LEN 600

#define ON   1
#define OFF  0

typedef struct _USART_DATA
{
    u8    gprs_rxbuf[GPRS_RCV_LEN];
    u16   gprs_rxlen;
    u32   gprs_rxtim; 
    u8    gprs_rxflag;
    
}USART_DATA;


typedef struct _CSW
{
    u32  milsec;//��ʱ��2����(��msΪ��λ)
}CSW;

#endif