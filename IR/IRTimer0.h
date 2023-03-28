#include "regx52.h"

#ifndef __TIMER0_H__
#define __TIMER0_H__

void Timer0_Init(void);
void Timer0_SetCounter(unsigned int val);
void Timer0_Run(unsigned char flag);
unsigned int Timer0_GetCount();

#endif
