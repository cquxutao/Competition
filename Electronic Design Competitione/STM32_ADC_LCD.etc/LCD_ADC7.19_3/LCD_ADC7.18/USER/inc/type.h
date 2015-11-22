#ifndef __TYPE_H
#define __TYPE_H

typedef unsigned char  uint8;                   /* defined for unsigned 8-bits integer variable 	无符号8位整型变量  */
typedef signed   char  int8;                    /* defined for signed 8-bits integer variable		有符号8位整型变量  */
typedef unsigned short uint16;                  /* defined for unsigned 16-bits integer variable 	无符号16位整型变量 */
typedef signed   short int16;                   /* defined for signed 16-bits integer variable 		有符号16位整型变量 */
typedef unsigned int   uint32;                  /* defined for unsigned 32-bits integer variable 	无符号32位整型变量 */
typedef signed   int   int32;                   /* defined for signed 32-bits integer variable 		有符号32位整型变量 */
typedef float          fp32;                    /* single precision floating point variable (32bits) 单精度浮点数（32位长度） */
typedef double         fp64;                    /* double precision floating point variable (64bits) 双精度浮点数（64位长度） */

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
    u32  milsec;//定时器2计数(以ms为单位)
}CSW;

#endif