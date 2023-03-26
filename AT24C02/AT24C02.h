#include "regx52.h"
#include "IIC.h"

#ifndef __AT24C02_H__
#define __AT24C02_H__
#define AT24C02_ADDRESS 0XA0
void AT24C02_WriteByte(unsigned char WordAddress, unsigned char Data);
unsigned char AT24C02_ReadByte(unsigned char WordAddress);

#endif