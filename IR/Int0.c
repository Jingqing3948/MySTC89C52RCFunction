/*
 * @Author: Jingqing3948 2351290287@qq.com
 * @Date: 2023-03-28 11:57:50
 * @LastEditors: Jingqing3948 2351290287@qq.com
 * @LastEditTime: 2023-03-28 18:14:42
 * @Description: external interrupt 0 configuration
 * 
 * Copyright (c) 2023 by Jingqing3948 2351290287@qq.com, All Rights Reserved. 
 */
#include "Int0.h"

/** @brief external interrupt 0 configuration.
  * @return {*}
*/
void Int0_Init()
{
    IT0 = 1;
    IE0 = 0;
    EX0 = 1;
    EA = 1;
    PX0 = 1;
}
