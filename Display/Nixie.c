/*
 * @Author: Jingqing3948 2351290287@qq.com
 * @Date: 2023-03-02 11:58:07
 * @LastEditors: Jingqing3948 2351290287@qq.com
 * @LastEditTime: 2023-03-26 23:07:41
 * @Description: control Nixie display led.
 *
 * Copyright (c) 2023 by Jingqing3948 2351290287@qq.com, All Rights Reserved.
 */
#include "Nixie.h"
#include "Delay.h"

// Nixie display buffer storage
unsigned char Nixie_Buf[9] = {0, 10, 10, 10, 10, 10, 10, 10, 10};

// Nixie segment table
unsigned char NixieTable[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00, 0x40};

/**
 * @brief  set buffer storage
 * @param  Location the location to be set (1~8)
 * @param  Number the number to be set (in Nixie table)
 * @return {*}
 */
void Nixie_SetBuf(unsigned char Location, Number)
{
	Nixie_Buf[Location] = Number;
}

/**
 * @brief  scan and display Nixie tube
 * @param  Location the location to be set (1~8)
 * @param  Number the number to be set (in Nixie table)
 * @return {*}
 */
void Nixie_Scan(unsigned char Location, Number)
{
	P0 = 0x00;		  // set segment code = 0 to avoid shaking
	switch (Location) // select nixie
	{
	case 1:
		P2_4 = 1;
		P2_3 = 1;
		P2_2 = 1;
		break;
	case 2:
		P2_4 = 1;
		P2_3 = 1;
		P2_2 = 0;
		break;
	case 3:
		P2_4 = 1;
		P2_3 = 0;
		P2_2 = 1;
		break;
	case 4:
		P2_4 = 1;
		P2_3 = 0;
		P2_2 = 0;
		break;
	case 5:
		P2_4 = 0;
		P2_3 = 1;
		P2_2 = 1;
		break;
	case 6:
		P2_4 = 0;
		P2_3 = 1;
		P2_2 = 0;
		break;
	case 7:
		P2_4 = 0;
		P2_3 = 0;
		P2_2 = 1;
		break;
	case 8:
		P2_4 = 0;
		P2_3 = 0;
		P2_2 = 0;
		break;
	}
	P0 = NixieTable[Number]; // set segment code
}

/**
 * @brief  Nixie drive function
 * @return {*}
 */
void Nixie_Loop(void)
{
	static unsigned char i = 1;
	Nixie_Scan(i, Nixie_Buf[i]);
	i++;
	if (i >= 9)
	{
		i = 1;
	}
}
