/*
 * @Author: Jingqing3948 2351290287@qq.com
 * @Date: 2023-02-08 01:16:03
 * @LastEditors: Jingqing3948 2351290287@qq.com
 * @LastEditTime: 2023-03-26 22:52:05
 * @Description: some delay function generated by STC-ISP.(based on 11.0592 MHZ STC-Y1 singlechip)
 *
 * Copyright (c) 2023 by Jingqing3948 2351290287@qq.com, All Rights Reserved.
 */
#include "Delay.h"

/**
 * @brief: delay us*1us.
 * @param {unsigned char} us
 * @return {*}
 */
void delay10Us(unsigned char us) //@11.0592MHz STC-Y1
{
	unsigned char i, j;
	for (i = 0; i < us; i++)
	{
		j = 2;
		while (--j)
			;
	}
}

/**
 * @brief: delay ms*1ms.
 * @param {unsigned char} ms
 * @return {*}
 */
void delayMs(unsigned char ms) //@11.0592MHz STC-Y1
{
	unsigned char i, j, k;
	for (k = 0; k < ms; k++)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j)
				;
		} while (--i);
	}
}
