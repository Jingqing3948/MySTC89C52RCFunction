#include "regx52.h"
#ifndef __IIC_H__
#define __IIC_H__
sbit I2C_SCL = P2 ^ 1;
sbit I2C_SDA = P2 ^ 0;

void I2C_Start();
void I2C_Stop();
void I2C_SendData(unsigned char Byte);
unsigned char I2C_ReceiveData();
void I2C_SendAck(unsigned char ackBit);
unsigned char I2C_ReceiveAck();

#endif