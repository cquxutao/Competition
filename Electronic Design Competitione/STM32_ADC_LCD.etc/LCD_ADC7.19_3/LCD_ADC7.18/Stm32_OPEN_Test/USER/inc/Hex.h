#ifndef _HEX_H_
#define _HEX_H_

//π‹Ω≈∫Í∂®“Â
#define	HEX_D0 		        GPIO_Pin_14
#define	HEX_D1		        GPIO_Pin_13
#define	HEX_D2		        GPIO_Pin_12
#define	HEX_D3		        GPIO_Pin_11
#define	HEX_D4		        GPIO_Pin_1
#define	HEX_D5		        GPIO_Pin_0
#define	HEX_D6		        GPIO_Pin_5
#define	HEX_D7		        GPIO_Pin_4
#define	HEX_SCA		        GPIO_Pin_1
#define	HEX_SCB		        GPIO_Pin_0
#define	HEX_SCC		        GPIO_Pin_15

void Hex_test(u8 sel, u8 data);
void disp(u8 data);
void Display_LedScan();
void Display_LedNum(u16 leddata); 

#endif