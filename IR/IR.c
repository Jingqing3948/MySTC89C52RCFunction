/*
 * @Author: Jingqing3948 2351290287@qq.com
 * @Date: 2023-03-28 13:50:01
 * @LastEditors: Jingqing3948 2351290287@qq.com
 * @LastEditTime: 2023-03-28 18:30:33
 * @Description: IR control function.
 *
 * Copyright (c) 2023 by Jingqing3948 2351290287@qq.com, All Rights Reserved.
 */
#include "regx52.h"
#include "IRtimer0.h"
#include "Int0.h"

unsigned int IR_time;
unsigned char IR_State;   // 0: await interrupt. 1: await start signals. 2: accepting data.
unsigned char IR_Data[4]; // address, address inverse code, command, command code
unsigned char curPtr;
unsigned char IR_DataFlag;
unsigned char IR_RepeatFlag;
unsigned char IR_Address;
unsigned char IR_Command;

/** @brief init IRTimer0 and Int0.
 * @return {*}
 */
void IR_Init()
{
    Timer0_Init();
    Int0_Init();
}

/** @brief return IR_DataFlag, and set IR_DataFlag=0
 * @return IR_DataFlag
 */
unsigned char IR_GetDataFlag()
{
    if (IR_DataFlag)
    {
        IR_DataFlag = 0;
        return 1;
    }
    return 0;
}

/** @brief return IR_RepeatFlag, and set IR_RepeatFlag=0
 * @return IR_RepeatFlag
 */
unsigned char IR_GetRepeatFlag()
{
    if (IR_RepeatFlag)
    {
        IR_RepeatFlag = 0;
        return 1;
    }
    return 0;
}

/** @brief return IR_Address
 * @return IR_Address
 */
unsigned char IR_GetAddress()
{
    return IR_Address;
}

/** @brief return IR_Command
 * @return IR_Command
 */
unsigned char IR_GetCommand()
{
    return IR_Command;
}

/** @brief Infrared reception and processing.
 * @return {*}
 */
void Int0_Routine() interrupt 0
{
    if (IR_State == 0) // await interrupt
    {
        // P2=0;              //debug: whether Interrupt is working
        Timer0_SetCounter(0); // recount
        Timer0_Run(1);        // start IRtimer0
        IR_State = 1;         // turn to state 1
    }
    else if (IR_State == 1) // search start signal: 9ms low + 4.5ms high
    {
        IR_time = Timer0_GetCount();
        Timer0_SetCounter(0);
        if (IR_time > 11980 && IR_time < 12910) // 12MHz:13500+-500. 11.0592MHz:*(11.0592/12).
        {
            P2 = 0;       // debug: whether reveiver can receive start signal
            IR_State = 2; // turn to state 2
        }
        else if (IR_time > 9900 && IR_time < 10830) // 12MHz:11250+-500. 11.0592MHz:*(11.0592/12).
        {
            IR_RepeatFlag = 1;
            Timer0_Run(0);
            IR_State = 0;
        }
        else
        {
            IR_State = 1;
        }
    }
    else if (IR_State == 2)//receiving data. 560us low +560us high: 0. 560us low + 1690us high: 1.
    {
        IR_time = Timer0_GetCount();
        Timer0_SetCounter(0);
        if (IR_time > 571 && IR_time < 1493) // 12MHz:1120+-500. 11.0592MHz:*(11.0592/12).
        {
            // IR_RepeatFlag=1;
            IR_Data[curPtr / 8] &= ~(0x01 << (curPtr % 8)); // only that bit = 0
            curPtr++;
        }
        else if (IR_time > 1611 && IR_time < 2535) // 12MHz:2250+-500. 11.0592MHz:*(11.0592/12).
        {
            // IR_RepeatFlag=1;
            IR_Data[curPtr / 8] |= (0x01 << (curPtr % 8)); // only that bit = 1
            curPtr++;
        }
        else // error
        {
            IR_State = 1; // wait for next signal
        }
        if (curPtr >= 32) // judge whether the receive code is correct
        {
            curPtr = 0;
            if (IR_Data[0] == ~IR_Data[1] && IR_Data[2] == ~IR_Data[3])
            {
                IR_DataFlag = 1;
                IR_Address = IR_Data[0];
                IR_Command = IR_Data[2];
            }
            Timer0_Run(0);
            IR_State = 0;
        }
    }
}