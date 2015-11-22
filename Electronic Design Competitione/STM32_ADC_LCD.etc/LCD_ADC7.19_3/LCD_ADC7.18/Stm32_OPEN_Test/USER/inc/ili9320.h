#ifndef _ILI9320_H_
#define _ILI9320_H_

//硬件相关的子函数
#define Set_Cs  GPIO_SetBits(GPIOD,GPIO_Pin_15);
#define Clr_Cs  GPIO_ResetBits(GPIOD,GPIO_Pin_15);

#define Set_Rs  GPIO_SetBits(GPIOG,GPIO_Pin_2);
#define Clr_Rs  GPIO_ResetBits(GPIOG,GPIO_Pin_2);

#define Set_nWr GPIO_SetBits(GPIOG,GPIO_Pin_3);
#define Clr_nWr GPIO_ResetBits(GPIOG,GPIO_Pin_3);

#define Set_nRd GPIO_SetBits(GPIOG,GPIO_Pin_4);
#define Clr_nRd GPIO_ResetBits(GPIOG,GPIO_Pin_4);

#define Set_Rst GPIO_SetBits(GPIOG,GPIO_Pin_5);
#define Clr_Rst GPIO_ResetBits(GPIOG,GPIO_Pin_5);

#define Lcd_Light_ON   GPIO_SetBits(GPIOG,GPIO_Pin_6);
#define Lcd_Light_OFF  GPIO_ResetBits(GPIOG,GPIO_Pin_6);


u16 CheckController(void);
void Lcd_Configuration(void);
void ili9320_Initializtion(void);
void ili9320_Reset(void);
void ili9320_WriteRegister(u16 index,u16 dat);
void ili9320_SetCursor(u16 x,u16 y);
void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY);
void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic);
void ili9320_SetPoint(u16 x,u16 y,u16 point);
void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor);
void ili9320_Clear(u16 dat);
void ili9320_Delay(u32 nCount);
void ili9320_Test(void);
u16 ili9320_GetCode(void);
void ili9320_WriteData(u16 dat);
void ili9320_WriteIndex(u16 idx);

void ili9320_BackLight(u8 status);

u16 ili9320_BGR2RGB(u16 c);

u16 ili9320_GetPoint(u16 x,u16 y);
u16 ili9320_ReadData(void);
u16 ili9320_ReadRegister(u16 index);

u16 GUI_Color565(u32 RGB);  // RGB颜色转为16位(565)

void GUI_Text(u16 x, u16 y, u8 *str, u16 len,u16 Color, u16 bkColor);
void GUI_Line(u16 x0, u16 y0, u16 x1, u16 y1,u16 color);  // 画线
void GUI_Circle(u16 cx,u16 cy,u16 r,u16 color,u8 fill);  // 画园
void GUI_Rectangle(u16 x0, u16 y0, u16 x1, u16 y1,u16 color,u8 fill); // 画矩形
void GUI_Square(u16 x0, u16 y0, u16 with, u16 color,u8 fill);  // 画正方形


void Touch_Initializtion(void);
u16  Touch_GetPhyX(void);
u16  Touch_GetPhyY(void);
u16  Touch_MeasurementX(void);
u16  Touch_MeasurementY(void);

/*定义常见颜色*/
#define red 0x001f
#define blue 0xf800
#define green 0x07e0
#define black 0x0000
#define white 0xffff
#define yellow 0x07ff
#define orange 0x05bf
#define Chocolate4 0x4451
#define Grey 0xefbd//灰色

#endif

