
#include "includes.h"
 
/********************************************************************************************************
* 函 数 名 :  void main(void)
* 描    述 : main
* 输入参数 : None.
* 输出参数 : None.
* 返   回  : None.
********************************************************************************************************/
   



void main(void)
{ 
    
    u8 x,y[104],y1;
    extern u8 save_y[104];
    u32 count=0;
    extern u8 flag_dma,pulse;
    extern unsigned char stop,send,save;
    extern signed char y_shift;
    int a,b,c,d,f,i,j,save_a,save_b; 
    extern volatile unsigned short ADCConvertedValue[104];
    unsigned char e;
    u16 V0_value,V0_flag=0,s=0,V0_temp[104],Vmax,Vmin,Vpp,Vmax1,Vmin1,Vpp1;;
    extern unsigned char AD_dis_buffer[],dis_x_y_buffer[],AD_dis_save[];
    //目标板初化,

    Target_Init();  
    init12864lcd(); 
    Clean_12864_GDRAM();
    draw_side();
    dis_AD_dis_buffer(dis_x_y_buffer);
    write_12864com(0x30);
    Vmin=62;
    Vmax=0;
    y_shift=0;
    pulse=1;
    while(1)
    {
      if(flag_dma)
      {
       if(i<104)
       {
         i++;
       }
       else
       {
         //TIM_Cmd(TIM2, DISABLE); 
         pulse=0;
         for(i=0;i<104;)
         {
           if(stop==1);
           else{
           V0_value=ADCConvertedValue[i++];
           
           c=(int)(V0_value*3.3/4096)%10;
           d=(int)(V0_value*3.3/4096*10)%10;

           y[i]=(u8)(31-(c*10+d)*2*4/5+26+y_shift);
           y1=(u8)(31-(c*10+d)*2*4/5+26+y_shift);
           if(Vmin1>=V0_value)
           {
             Vmin1=V0_value;
           }
           if(Vmax1<=V0_value){
             Vmax1=V0_value;
           }
           
           if(Vmin>=y[i])
           {
             Vmin=y[i];
           }
           if(Vmax<=y[i]){
             Vmax=y[i];
           }
           Vpp=(Vmax-Vmin)*90/100;
           Vpp1=(Vmax1-Vmin1)*60/100;
           b=(int)((Vpp)*5/4)%10;
           a=(int)((Vpp)*5/4)/10;
           f=(int)((Vpp1*3.3/4096)*100)%10;
           
           dis_define_dot(y1,x++);
           if(x==104)x=0;
           }
         }
  
         Vmax=0;
         Vmin=62;
         
         if(GPIO_ReadInputDataBit(GPIOF,KEY7)==0){
           delay_nus(50000);
           count++;
         }
         if(count%2==0){
         dis_AD();
         
         delay_nus(10000);
         write_12864com(0x30);
         locate16(1, 1);
         write_12864dat('V');
         write_12864dat('=');
         if(GPIO_ReadInputDataBit(SW_GRP,SW1)==0){
         e=(unsigned char)a+0x30;  
         write_12864dat(e);
         write_12864dat('.');
         e=(unsigned char)b+0x30;
         write_12864dat(e);
         e=(unsigned char)f+0x30;
         write_12864dat(e);
         }
         else if(GPIO_ReadInputDataBit(SW_GRP,SW2)==0){
         write_12864dat('0');  
         write_12864dat('.');
         e=(unsigned char)a+0x30;  
         write_12864dat(e);
         e=(unsigned char)b+0x30;
         write_12864dat(e);
         }
         else if(GPIO_ReadInputDataBit(SW_GRP,SW3)==0){
         e=(unsigned char)a+0x30;  
         write_12864dat(e);
         e=(unsigned char)b+0x30;
         write_12864dat(e);
         write_12864dat('m');
         write_12864dat('v');
         }
         //e=(unsigned char)f+0x30;
         //write_12864dat(e);
         }
         if(save==1){
           save_a=a;
           save_b=b;
           for(i=0;i<992;i++)
           {
             AD_dis_save[i]=AD_dis_buffer[i];
           }
           for(i=0;i<104;i++){
             save_y[i]=y[i];
           }
           save=0;
         }
         
         if(count%2==1){
           dis_AD_dis_buffer(AD_dis_save);
           //delay_nus(10000);
           write_12864com(0x30);
           locate16(1, 1);
           write_12864dat('V');
           write_12864dat('=');
           e=(unsigned char)save_a+0x30;  
           write_12864dat(e);
           write_12864dat('.');
           e=(unsigned char)save_b+0x30;
           write_12864dat(e);
           
         }
         
         if(send==1){
         function3();
         }
         
         for(i=0;i<992;i++)
         {
          AD_dis_buffer[i]=0x00; 
         }
        
         pulse=1;
         //TIM_Cmd(TIM2, ENABLE);
       }
       DMAReConfig();
       flag_dma=0; 
      }
   
   }
}
