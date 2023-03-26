/*
 * @Author: Jingqing3948 2351290287@qq.com
 * @Date: 2023-01-09 10:30:01
 * @LastEditors: Jingqing3948 2351290287@qq.com
 * @LastEditTime: 2023-03-26 23:40:05
 * @Description: control temperature sensor. 
 *
 * Copyright (c) 2023 by Jingqing3948 2351290287@qq.com, All Rights Reserved.
 */
#include "ds18b20.h"

/** @brief reset ds18b20
  * @return {*}
*/
void DS18B20Reset()
{
	DS18B20_PORT = 0;
	delay10Us(75);
	DS18B20_PORT = 1;
	delay10Us(2);
}

/** @brief check whether ds18b20 is normally resetted.
  * @return 0: success; 1: fail
*/
u8 DS18B20Check()
{
	int time_temp = 0;
	while (!DS18B20_PORT && time_temp < 20)
	{
		time_temp++;
		delay10Us(1);
	}
	if (time_temp >= 20)
		return 1;
	time_temp = 0;
	while (DS18B20_PORT && time_temp < 20)
	{
		time_temp++;
		delay10Us(1);
	}
	if (time_temp >= 20)
		return 1;
	return 0;
}

/** @brief init ds18b20
  * @return 0: success; 1: fail
*/
u8 DS18B20Init()
{
	DS18B20Reset();
	return DS18B20Check();
}

/** @brief write a command to ds18b20
  * @param the command need to be written
  * @return {*}
*/
void DS18B20WriteByte(u8 dat)
{
	u8 i;
	u8 temp;
	for (i = 0; i < 8; i++)
	{
		temp = dat & 0x01;
		dat >>= 1;
		if (temp)
		{
			DS18B20_PORT = 0;
			_nop_();
			_nop_();
			DS18B20_PORT = 1;
			delay10Us(6);
		}
		else
		{
			DS18B20_PORT = 0;
			delay10Us(6);
			DS18B20_PORT = 1;
			_nop_();
			_nop_();
		}
	}
}

/** @brief read one bit from ds18b20
  * @return the bit
*/
u8 DS18B20ReadBit()
{
	u8 dat;
	DS18B20_PORT = 0;
	_nop_();
	_nop_();
	DS18B20_PORT = 1;
	_nop_();
	_nop_();
	if (DS18B20_PORT == 1)
		dat = 1;
	else
		dat = 0;
	delay10Us(5);
	return dat;
}

/** @brief read one byte from ds18b20
  * @return the byte
*/
u8 DS18B20ReadByte()
{
	u8 i = 0;
	u8 ans = 0;
	for (i = 0; i < 8; i++)
	{
		ans = (DS18B20ReadBit() << 7) | (ans >> 1);
	}
	return ans;
}

/** @brief init ds18b20, skip rom, convert temperature
  * @return {*}
*/
void DS18B20Start()
{
	DS18B20Init();
	DS18B20WriteByte(0xCC);
	DS18B20WriteByte(0x44);
}

/** @brief read temperature from ds18b20
  * @return the float type temperature (***.****)
*/
float DS18B20ReadTemperature()
{
	u8 lowTemp;
	u8 highTemp;
	u16 temp;
	float ans;
	DS18B20Init();
	DS18B20WriteByte(0xCC);
	DS18B20WriteByte(0xBE);
	lowTemp = DS18B20ReadByte();
	highTemp = DS18B20ReadByte();
	temp = (highTemp << 8) | (lowTemp);
	if ((lowTemp & 0XF800) == 0XF800)
		ans = ((~temp) + 1) * (-0.0625);
	else
		ans = temp * 0.0625;
	return ans;
}