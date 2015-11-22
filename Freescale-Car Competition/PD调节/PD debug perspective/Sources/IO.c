#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "IO.h"


void IO_init(void){
  DDRB=DDRM_IO;
  PORTB_PB5=1;
  DDRA=0x00;
  PORTA=0x00;
  DDRB_DDRB7=1;
  PORTB_PB7=1;
  asm(nop);
  asm(nop);
  PORTB_PB7=0;
  asm(nop);
  asm(nop);
  PACTL=0x50;
  PACNT=0; 
}