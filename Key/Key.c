/*
 * @Author: Jingqing3948 2351290287@qq.com
 * @Date: 2023-02-08 01:08:08
 * @LastEditors: Jingqing3948 2351290287@qq.com
 * @LastEditTime: 2023-03-26 23:11:50
 * @Description: control 4 independent key.
 *
 * Copyright (c) 2023 by Jingqing3948 2351290287@qq.com, All Rights Reserved.
 */
#include "regx52.h"
#include "Key.h"
#include "Delay.h"

/**
 * @brief: scan which key is pressed, and return it.
 * @param {u8} mode
 * @return {*}
 */
unsigned char key_scan(unsigned char mode)
{
	static unsigned char key = 1;
	if (mode) // continuous scan. If press key for a while, it represents this key has been pressed for many times.
		key = 1;
	if (key == 1 && (KEY1 == 0 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0)) // gage which key is pressed
	{
		delayMs(10); // 10ms elimination buffeting of keystroke
		key = 0;
		if (KEY1 == 0)
			return KEY1_PRESS;
		else if (KEY2 == 0)
			return KEY2_PRESS;
		else if (KEY3 == 0)
			return KEY3_PRESS;
		else if (KEY4 == 0)
			return KEY4_PRESS;
	}
	else if (KEY1 == 1 && KEY2 == 1 && KEY3 == 1 && KEY4 == 1) // no key pressed
	{
		key = 1;
	}
	return KEY_UNPRESS;
}