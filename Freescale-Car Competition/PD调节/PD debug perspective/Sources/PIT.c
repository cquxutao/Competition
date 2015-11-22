#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Common.h"
#include "LCD.h"
#include "PIT.h"


/*************************************************************/
/*                     PITģ���ʼ������                     */
/*************************************************************/
 void INIT_PIT(void){
 
 PITMTLD0=199;     //Ϊ΢��ʱ��0��������ֵ
 PITLD0=399;      //Ϊ16λ��ʱ��0��������ֵ (199+1)*(1999+1)=2000000����������=1ms  //1ms
 PITMUX_PMUX0=0;   //��0ͨ��ʹ��΢������0
 PITCE_PCE0=1;     //��0ͨ������������ 
 PITCFLMT=0x80;    //ʹ�������ж϶�ʱ��
 PITINTE_PINTE0=1; //0ͨ����ʱ����ʱ�жϱ�ʹ��
 }



