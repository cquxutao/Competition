#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "IO.h"


void IO_init(void){
  DDRB=DDRM_IO;
  PORTB_PB5=1;
  PORTB_PB7=0;
  DDRA=0x00;
  PORTA=0x00;
  DDRT_DDRT1=1;
  PTT_PTT1=1;
  asm(nop);
  asm(nop);
  PTT_PTT1=0;
  asm(nop);
  asm(nop);
  PACTL=0x50;
  PACNT=0; 
}