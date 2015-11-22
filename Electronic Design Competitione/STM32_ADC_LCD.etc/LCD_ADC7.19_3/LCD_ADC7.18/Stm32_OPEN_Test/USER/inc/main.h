#ifndef __MAIN_H
#define __MAIN_H

#define                 LED_STK_SIZE                  512
#define                 KEY_STK_SIZE                   512

#define                 TASK_LED_PRO                   2
#define                 TASK_KEY_PRO                    3

void Task_Key(void *pdata);
void Task_Led(void *pdata);

#endif