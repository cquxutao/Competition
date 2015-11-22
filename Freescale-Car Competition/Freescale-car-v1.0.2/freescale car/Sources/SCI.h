#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

void INIT_SCI0(void);
void SCI0_send(unsigned char data);
unsigned char SCI0_receive(void);
interrupt 20 void SCI_SHOW(void);
void CRC16(unsigned char *ARRAY,unsigned char *RCVBUF,unsigned int Len);