#include "includes.h"
#include "12864.h"

unsigned char table[]="0x38,0x44,0x04,0x18,0x18,0x04,0x44,0x38";
unsigned char data[];
/*************************************************************/
/*************LCD显示函数************************************/

/*******ns级别延时********************************************/
void Delay_nus(unsigned int nCount)
{
 unsigned int j;
 while(nCount--)
 { 
    j=8;
    while(j--);
 }
}
/*******ms级别延时********************************************/ 
void Delay_mus(unsigned int nCount)
{
    while(nCount--)
    Delay_nus(1100);
}
/*******转接函数********************************************/
void data_change(unsigned char u){
    if(u&0x01)GPIO_SetBits(GPIOC, GPIO_Pin_0); else GPIO_ResetBits(GPIOC, GPIO_Pin_0);
    if(u&0x02)GPIO_SetBits(GPIOC, GPIO_Pin_1); else GPIO_ResetBits(GPIOC, GPIO_Pin_1);
    if(u&0x04)GPIO_SetBits(GPIOC, GPIO_Pin_2); else GPIO_ResetBits(GPIOC, GPIO_Pin_2);
    if(u&0x08)GPIO_SetBits(GPIOC, GPIO_Pin_3); else GPIO_ResetBits(GPIOC, GPIO_Pin_3);
    if(u&0x10)GPIO_SetBits(GPIOC, GPIO_Pin_4); else GPIO_ResetBits(GPIOC, GPIO_Pin_4);
    if(u&0x20)GPIO_SetBits(GPIOC, GPIO_Pin_5); else GPIO_ResetBits(GPIOC, GPIO_Pin_5);
    if(u&0x40)GPIO_SetBits(GPIOC, GPIO_Pin_6); else GPIO_ResetBits(GPIOC, GPIO_Pin_6);
    if(u&0x80)GPIO_SetBits(GPIOC, GPIO_Pin_7); else GPIO_ResetBits(GPIOC, GPIO_Pin_7);
}
    
/**************数据口浮空输入************************************/
void DDRC_IN(){
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3
      |GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}
/**************数据口推挽输出************************************/
void DDRC_OUT(){
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3
      |GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}
/*******读忙态函数********************************************/
void check_busy(){
  DDRC_IN();
  RS_CLR;
  RW_SET;
  EN_SET;
  //busy=GPIO_ReadInputData(GPIOC) & 0x0080;
  while(GPIO_ReadInputData(GPIOC)&0x0080);
  EN_CLR;
  DDRC_OUT();
}
/*******写命令函数********************************************/
void write_12864com(unsigned char com)
{  check_busy();
   RW_CLR;
   RS_CLR;
  // Delay_nus(500);
   //DATA_IO=com;
   data_change(com);
   EN_SET;
  // Delay_nus(1000);
   EN_CLR;
  // Delay_nus(1000);
}

/*******写数据函数********************************************/
void write_12864dat(unsigned char dat)
{  check_busy();
   RW_CLR;
   RS_SET;
  // Delay_nus(500);
   //DATA_IO=dat;
   data_change(dat);
   EN_SET;
  // Delay_nus(1000);
   EN_CLR;
 //  Delay_nus(1000);
}

/****读数据函数*************************************************/
unsigned char u8_Lcd12864ReadByte_f( void )
{
    unsigned char byReturnValue ;
    check_busy();
    DDRC_IN();
    RS_SET;
    RW_SET;
    EN_CLR;
   // Delay_nus(10);
    EN_SET;
    byReturnValue=(unsigned char)(GPIO_ReadInputData(GPIOC)&0x00ff);
    EN_CLR;
    DDRC_OUT();

    return byReturnValue ;    
}

   
     
        
  
  
         
     

/*******12864初始化函数********************************************/
void init12864lcd(void)
{   GPIO_SetBits(GPIOE, GPIO_Pin_3);   //PSB_SET;
   Delay_mus(500);
   write_12864com(0x30);
   Delay_nus(500);
   write_12864com(0x30);
   Delay_nus(500);
   write_12864com(0x0c);
   Delay_nus(500);
   write_12864com(0x01);
   Delay_nus(25);
  // write_12864com(0x06);
 //  Delay_nus(2500);
  // write_12864com(0x0c);
   Delay_nus(500);
}

/*******显示函数********************************************/
void display(u8 *s)
{
   /*unsigned char i;
    //write_12864com(0x80);
   for(i=0;i<14;i++)
    {
       write_12864dat(table[i]);
       Delay_mus(50);
      }*/
    while(*s )
    {
        write_12864dat(*s);
        s++;
        Delay_mus(2);
    }
  
}



/****清除显示*************************************************/
void Clean_12864_GDRAM(void)
{
    unsigned char x,y;
    write_12864com(0x34);
    write_12864com(0x36);        //需要两次，本次设置扩展指令集。
    for (y=0;y<32;y++)
    {
        write_12864com(0x80+y);  //设置y=1000+00xx，y+1则往下一行
        write_12864com(0x80);        //设置x=1000 0000
        for (x=0;x<16;x++)
        {
            write_12864dat(0x00);   //高字节数据
            write_12864dat(0x00);        //低字节数据
        }
    }
    
} 
/****画点函数1*************************************************/
void v_Lcd12864DrawPoint_f(unsigned char x,unsigned char y,unsigned char Color )
{
    unsigned char Y,Row , Tier , Tier_bit    ;
    unsigned char  ReadOldH, ReadOldL  ;
    write_12864com(0x34);
    Y=y;
    Tier=x>>4;    
    Tier_bit=x&0x0f;
    if(Y<32)
    {
        Row=Y;
    }
    else
    {
        Row=Y-32;
        Tier+=8;
    }
    write_12864com( Row+0x80);
    write_12864com( Tier+0x80);
    u8_Lcd12864ReadByte_f();
    ReadOldH=u8_Lcd12864ReadByte_f(); 
    ReadOldL=u8_Lcd12864ReadByte_f(); 
    write_12864com(Row+0x80);
    write_12864com(Tier+0x80);
    if(Tier_bit<8)
    {
        switch(Color)
        {
            case 0 : ReadOldH&=(~(0x01<<(7-Tier_bit))); break;
            case 1 : ReadOldH|=(0x01<<(7-Tier_bit));  break;
            case 2 : ReadOldH^=(0x01<<(7-Tier_bit)); break;
            default : break ;    
        }
        write_12864dat( ReadOldH ) ;
        write_12864dat( ReadOldL ) ;
    }
    else
    {
        switch(Color)
        {
            case 0 : ReadOldL &= (~( 0x01 << ( 15 - Tier_bit ))) ;  break ;
            case 1 : ReadOldL |= ( 0x01 << ( 15 - Tier_bit ))    ;  break ;
            case 2 : ReadOldL ^= ( 0x01 << ( 15 - Tier_bit ))  ;  break ;
            default : break ;
        }
        write_12864dat( ReadOldH ) ;
        write_12864dat( ReadOldL ) ;
    }
    
    write_12864com(0x36);
    write_12864com(0x30);
}
/****画点函数2*************************************************/
void LCD_set_dot(unsigned char px,unsigned char py) {
 unsigned char x,y,x_byte,x_bit,y_byte,y_bit,tmph,tmpl;
  x=px&0x7f;
  y=py&0x3f;
  x_byte=x/16;
  x_bit=x&0x0f;
  y_byte=y/32;
  y_bit=y&0x1f;
  write_12864com(0x36);

  write_12864com(0x80+y_bit);
  write_12864com(0x80+x_byte+8*y_byte);
  
  u8_Lcd12864ReadByte_f();
  //Delay(2);
  tmph=u8_Lcd12864ReadByte_f();
  tmpl=u8_Lcd12864ReadByte_f();
  //Delay(20);
  write_12864com(0x80+y_bit);
  write_12864com(0x80+x_byte+8*y_byte);
  //Delay(20);
  if(x_bit<8)
	{ write_12864dat(tmph|(0x01<<(7-x_bit)));
           write_12864dat(tmpl);
	}
	else
	{ write_12864dat(tmph);
          write_12864dat(tmpl|(0x01<<(15-x_bit)));
	}
//	write_12864com(0x36);
	write_12864com(0x30);
}
/*******画横线函数*******************************************/ 
void draw_Rline(unsigned char px,unsigned char py,unsigned char n,unsigned char line){
      unsigned char i,x,y,x_byte,x_bit,y_byte,y_bit;
      write_12864com(0x36);
          x=px&0x7f;                           //可选择起始点，长度，虚线或者实线
          y=py&0x3f;
          x_byte=x/16;
          x_bit=x&0x0f;
          y_byte=y/32;
          y_bit=y&0x1f;
  write_12864com(0x80+y_bit);
  write_12864com(0x80+8*y_byte+x_byte);
  if(line==1)
  {
    for(i=0;i<n/8;i++){
      write_12864dat(0xff);}
  }
  else if(line==2)
  {
    for(i=0;i<n/8;i++){
      write_12864dat(0x55);}
  }
  else if(line==4)
  {
    for(i=0;i<n/8;i++){
      write_12864dat(0x11);}
  }
  else{
  for(i=0;i<n;i++){

       if(!(px%line))
       {
         //write_12864dat('1');
         LCD_set_dot(px,py);
       }
       px++;
      //else  write_12864dat(0xff);
  }
  }
}

/*******写字*******************************************/ 
void draw_word(unsigned char px,unsigned char py,unsigned char n,unsigned char line){
      unsigned char i,x,y,x_byte,x_bit,y_byte,y_bit;
      write_12864com(0x36);
          x=px&0x7f;                           //可选择起始点，长度，虚线或者实线
          y=py&0x3f;
          x_byte=x/16;
          x_bit=x&0x0f;
          y_byte=y/32;
          y_bit=y&0x1f;
  write_12864com(0x80+y_bit);
  write_12864com(0x80+8*y_byte+x_byte);
  for(i=0;i<n;i++){
       write_12864dat(line);
  }
  
}
/*******画竖线函数*******************************************/ 
void draw_Lline(unsigned char px,unsigned char py,unsigned char n,unsigned char line){
     unsigned char i;
     for(i=0;i<n;i++){
       if(!(py%line))
       {
         LCD_set_dot(px,py);
       }
       py++;
      // if(xu)py++;
     }
}
/*******画边框函数*******************************************/
void draw_side(){
    //write_12864com(0x80);
    //for(i=0;i<16;i++){write_12864dat(0xff);}   //上边框边框
    draw_Rline(0,0,128,2);
    //draw_Rline(1,14,15,0xff);
    draw_Rline(0,63,128,2);   //下边框
    
    /*draw_Rline(0,31,104,10);  //X轴
    //draw_Rline(1,30,103,2);
    draw_Rline(0,32,104,1);
    //draw_Rline(1,32,103,2);
    draw_Rline(0,33,104,10);
    
    draw_Lline(49,1,62,8);
    draw_Lline(50,1,62,1);
    draw_Lline(51,1,62,8);
    
    draw_Lline(104,1,62,3);
    draw_Lline(0,1,62,2);   //左边框
    draw_Lline(127,1,62,2);   //右边框
    
    /*draw_word(80,20,1,0x38);
    draw_word(80,21,1,0x44);

    draw_word(80,22,1,0x04);
    draw_word(80,23,1,0x18);
    draw_word(80,24,1,0x18);
    draw_word(80,25,1,0x04);
    draw_word(80,26,1,0x44);
    draw_word(80,27,1,0x38);*/
  
}   
    
    
/*******12864端口配置函数*******************************************/ 
void LCD12864_Config(void)
{  
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOC , ENABLE);
  //E口2 3 4 6口做RS PSB RW EN信号线   推挽输出
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_6;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);  
  //C口0~7 做8位数据线  推挽输出
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3
      |GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  
}

void locate16(int row, int col) 
{
	switch(row)
	{
		case 1: write_12864com(0x80+col-1); break;
		case 2: write_12864com(0x90+col-1); break;
		case 3: write_12864com(0x88+col-1); break;
		case 4: write_12864com(0x98+col-1); break;
	}
}

/***********修改后显示缓冲区添加X Y轴*****************************/
void dis_ADbufaddxy(){
  u16 i;
  u16 swdata;
  extern u32 Exti1count;
  for(i=0;i<992;i++){
   if(((i-13)/16)<=30){
    if((i-13)%16==0){
    AD_dis_buffer[i]|=dis_x_y_buffer[i];

    if(GPIO_ReadInputDataBit(SW_GRP,SW1)==0)AD_dis_buffer[i]|=dis_1v[3*(i-13)/16];
    else if(GPIO_ReadInputDataBit(SW_GRP,SW2)==0)AD_dis_buffer[i]|=dis_01v[3*(i-13)/16];
    else if(GPIO_ReadInputDataBit(SW_GRP,SW3)==0)AD_dis_buffer[i]|=dis_001v[3*(i-13)/16];
    else ;
    }
    
    else if((i-14)%16==0){
     AD_dis_buffer[i]|=dis_x_y_buffer[i];

     if(GPIO_ReadInputDataBit(SW_GRP,SW1)==0)AD_dis_buffer[i]|=dis_1v[3*(i-13)/16+1];
     else if(GPIO_ReadInputDataBit(SW_GRP,SW2)==0)AD_dis_buffer[i]|=dis_01v[3*(i-13)/16+1];
     else if(GPIO_ReadInputDataBit(SW_GRP,SW3)==0)AD_dis_buffer[i]|=dis_001v[3*(i-13)/16+1];
     else ;
    } 
    
    else if((i-15)%16==0){
     AD_dis_buffer[i]|=dis_x_y_buffer[i];

     if(GPIO_ReadInputDataBit(SW_GRP,SW1)==0)AD_dis_buffer[i]|=dis_1v[3*(i-13)/16+2];
     else if(GPIO_ReadInputDataBit(SW_GRP,SW2)==0)AD_dis_buffer[i]|=dis_01v[3*(i-13)/16+2];
     else if(GPIO_ReadInputDataBit(SW_GRP,SW3)==0)AD_dis_buffer[i]|=dis_001v[3*(i-13)/16+2];
     else ;
    }
    
    else AD_dis_buffer[i]|=dis_x_y_buffer[i];
   }
   
   else if(((i-13)/16)>30){
     
    if((i-13)%16==0){
    AD_dis_buffer[i]|=dis_x_y_buffer[i];
    if(Exti1count%4==0){
     AD_dis_buffer[i]|=dis_10us[3*((i-13)/16-31)];
    }
    else if(Exti1count%4==1){
     AD_dis_buffer[i]|=dis_01ms[3*((i-13)/16-31)];
    }
    else if(Exti1count%4==2){
     AD_dis_buffer[i]|=dis_1ms[3*((i-13)/16-31)];
    }
    else if(Exti1count%4==3){
     AD_dis_buffer[i]|=dis_20ms[3*((i-13)/16-31)];
    }
    }
    
    else if((i-14)%16==0){
    AD_dis_buffer[i]|=dis_x_y_buffer[i];
    if(Exti1count%4==0){
     AD_dis_buffer[i]|=dis_10us[3*((i-13)/16-31)+1];
    }
    else if(Exti1count%4==1){
     AD_dis_buffer[i]|=dis_01ms[3*((i-13)/16-31)+1];
    }
    else if(Exti1count%4==2){
     AD_dis_buffer[i]|=dis_1ms[3*((i-13)/16-31)+1];
    }
    else if(Exti1count%4==3){
     AD_dis_buffer[i]|=dis_20ms[3*((i-13)/16-31)+1];
    }
    }
    
    else if((i-15)%16==0){
    AD_dis_buffer[i]|=dis_x_y_buffer[i];
    if(Exti1count%4==0){
     AD_dis_buffer[i]|=dis_10us[3*((i-13)/16-31)+2];
    }
    else if(Exti1count%4==1){
     AD_dis_buffer[i]|=dis_01ms[3*((i-13)/16-31)+2];
    }
    else if(Exti1count%4==2){
     AD_dis_buffer[i]|=dis_1ms[3*((i-13)/16-31)+2];
    }
    else if(Exti1count%4==3){
     AD_dis_buffer[i]|=dis_20ms[3*((i-13)/16-31)+2];
    }
    }
    
    else AD_dis_buffer[i]|=dis_x_y_buffer[i];
   }
  }
}
/***********显示缓冲区快速打点**********************************/
void dis_AD_dis_buffer(unsigned char *address){
  unsigned char i,y,y1,y_byte,y_bit;
  //  dis_ADbufaddxy();
  
  write_12864com(0x36); 
          y1=1;
          y=y1&0x3f;
     
  for(i=0;i<62;i++){
          y_byte=y/32;
          y_bit=y&0x1f;
       write_12864com(0x80+y_bit);
       write_12864com(0x80+8*y_byte);
       
       write_12864dat(*(address+i*16));
       write_12864dat(*(address+i*16+1));
       write_12864dat(*(address+i*16+2));
       write_12864dat(*(address+i*16+3));
       write_12864dat(*(address+i*16+4));
       write_12864dat(*(address+i*16+5));
       write_12864dat(*(address+i*16+6));
       write_12864dat(*(address+i*16+7));
       write_12864dat(*(address+i*16+8));
       write_12864dat(*(address+i*16+9));
       write_12864dat(*(address+i*16+10));
       write_12864dat(*(address+i*16+11));
       write_12864dat(*(address+i*16+12));
       write_12864dat(*(address+i*16+13));
       write_12864dat(*(address+i*16+14));
       write_12864dat(*(address+i*16+15));
       y++; 
    }   

}   

void dis_AD(){
  dis_ADbufaddxy();
  dis_AD_dis_buffer(AD_dis_buffer);
}
/***********根据AD值改变显示缓冲区**********************************/
void dis_define_dot(unsigned char v,unsigned t){
   unsigned char x_byte,x_bit,buf,buf1,*p=AD_dis_buffer;
   extern unsigned char send_save[104];
   //send_save[t]=v;
      x_byte=t/8;
      x_bit=t%8;
     buf1=0x80>>(x_bit); 
     buf= (*(p+v*16+x_byte));
     buf|=buf1;
     *(p+v*16+x_byte)=buf;
}
