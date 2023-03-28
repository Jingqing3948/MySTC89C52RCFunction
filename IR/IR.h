#ifndef __IR_H__
#define __IR_H__

#include "regx52.h"

void IR_Init();
unsigned char IR_GetCommand();
unsigned char IR_GetAddress();
unsigned char IR_GetRepeatFlag();
unsigned char IR_GetDataFlag();

#endif
