#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

void INIT_AD(void);
unsigned int AD_once(unsigned char channel);
unsigned int sort(unsigned int *v);
unsigned int AD_ave(unsigned int *u);