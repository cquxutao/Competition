#ifndef _PS2_H_
#define _PS2_H_

#define	PS2_CLK    		GPIO_Pin_12
#define	PS2_DATA		GPIO_Pin_11
#define	PS2_GRP		        GPIOG

extern u8 BitCnt;
extern u8 PS2_ReFlag;

void PS2_Disp(void);
void PS2_Driver(void);
u8 PS2_Conver(u8 keycode);

#endif