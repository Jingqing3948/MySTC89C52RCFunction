#ifndef __DS18B20_H__
#define __DS18B20_H__

#include "regx52.h"
#include "LCD1602.h"
#include "public.h"
#include "delay.h"

sbit DS18B20_PORT = P3 ^ 7;

void DS18B20Reset();
u8 DS18B20Check();
u8 DS18B20Init();
void DS18B20WriteByte(u8 dat);
u8 DS18B20ReadBit();
u8 DS18B20ReadByte();
void DS18B20Start();
float DS18B20ReadTemperature();

#endif