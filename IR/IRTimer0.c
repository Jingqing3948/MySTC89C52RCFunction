/*
 * @Author: Jingqing3948 2351290287@qq.com
 * @Date: 2023-02-08 09:56:01
 * @LastEditors: Jingqing3948 2351290287@qq.com
 * @LastEditTime: 2023-03-28 18:16:07
 * @Description: control timer0 interrupt for IR usage.
 *
 * Copyright (c) 2023 by Jingqing3948 2351290287@qq.com, All Rights Reserved.
 */
#include "IRtimer0.h"

/**
 * @brief  init timer@11.0592MHz
 * @return {*}
 */
void Timer0_Init(void)
{
  TMOD &= 0xF0; // set timer mode
  TMOD |= 0X01; // TMOD is non-addressable, it includes timer1 and timer0 register, but cannot be assigned separately.
  // So we use or operation to clear low 4 bits without influencing high 4 bits.

  // IE, IT in TCON, which is also means INT0, because GATE =0, TR=1, so we don't need to set IE/IT.

  // TH TL = 65535,interrupt happens.
  // set 1ms trigger 1 interrupt:
  //@12MHZ: 1us = 1 machine cycle, so init value = 64535.
  //@11.0592MHz: 11.0592/12=921600Hz, 1us = 0.9216 machine cycle, so init value = 65535-922=64613.
  TH0 = 0XFC; // 64613/256=252=0xFC, @11.0592 MHZ
  TL0 = 0X65; // 64613%256=0x65

  TF0 = 0; // set init interrupt, to avoid interrupt when start system
  TR0 = 0; // enable timer0
}

/*Timer interrupt function template
void Timer0_Routine() interrupt 1
{
  static unsigned int T0Count;
  TL0 = 0x18;
  TH0 = 0xFC;
  T0Count++;
  if(T0Count>=1000)
  {
    T0Count=0;
  }
}
*/

/** @brief set timer0 init value.
 * @param timer init value, 8+8 bit.
 * @return {*}
 */
void Timer0_SetCounter(unsigned int val)
{
  TH0 = val / 256;
  TL0 = val % 256;
}

/** @brief get timer0 count value.
 * @return TH(8 bit) and TL(8 bit) value.
 */
unsigned int Timer0_GetCount()
{
  return (TH0 << 8) | TL0;
}

/** @brief start or terminate timer counting.
 * @param 0: disable; 1: enable.
 * @return {*}
 */
void Timer0_Run(unsigned char flag)
{
  TR0 = flag;
}
