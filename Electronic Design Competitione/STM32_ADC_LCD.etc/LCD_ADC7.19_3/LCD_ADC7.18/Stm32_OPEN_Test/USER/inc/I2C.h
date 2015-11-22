
#ifndef _I2C_H_
#define _I2C_H_


#define LM75A_ADDR  0x90

#define E2PROM_ADDR  0xA2

extern u8 Tempdata;

void I2C_Start();
void I2C_Stop();
u8 I2C_SendByte(u8 c);
u8 I2C_RcvByte();
void I2C_Ack(u8 a);
u8 LM75A_SendByte(u8 sla,u8 c);
u8 LM75A_SendStr(u8 sla,u8 suba,u8 *s,u8 no);
u8 LM75A_RcvByte(u8 sla,u8 *c);
u8 LM75A_RcvStr(u8 sla,u8 suba,u8 *s,u8 no);
u8 AT24C64_W(u8 sla,u16 AT24C64_address,u8 *buf,u32 count);
void AT24C64_R(u8 sla,u16 AT24C64_address,u8 *buf,u32 count);
void E2PROM_W(u8 sla,u16 AT24C64_address,u8 *buf,u32 count);
void E2PROM_R(u8 sla,u16 AT24C64_address,u8 *buf,u32 count);
u8 AT24C64_WByte(u16 AT24C64_address,u8 data);
u8 AT24C64_RByte(u16 AT24C64_address);
u8 LM75A_RcvTemp();

#endif