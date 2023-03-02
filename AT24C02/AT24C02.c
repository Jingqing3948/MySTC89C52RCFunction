/*
 * @Author: Jingqing3948 2351290287@qq.com
 * @Date: 2023-03-02 12:10:56
 * @LastEditors: Jingqing3948 2351290287@qq.com
 * @LastEditTime: 2023-03-02 21:38:19
 * @Description: functions about read and write in at24c02 using I2C.
 * 
 * Copyright (c) 2023 by Jingqing3948 2351290287@qq.com, All Rights Reserved. 
 */
#include "reg52.h"
#include "IIC.h"
#include "AT24C02.H"


/**
 * @brief: write dat into given address.
 * @param {unsigned char} WordAddress
 * @param {unsigned char} Dat
 * @return {*}
 */
void AT24C02_WriteByte(unsigned char WordAddress, unsigned char Dat){
	unsigned char Ack=0;
	I2C_Start();
	I2C_SendData(AT24C02_ADDRESS);
	Ack=I2C_ReceiveAck();
	I2C_SendData(WordAddress);
	Ack=I2C_ReceiveAck();
	I2C_SendData(Dat);
	Ack=I2C_ReceiveAck();
	I2C_Stop();
}

/**
 * @brief: read dat from given address.
 * @param {unsigned char} WordAddress
 * @return {*}
 */
unsigned char AT24C02_ReadByte(unsigned char WordAddress){
	unsigned char Dat,Ack;
	I2C_Start();
	I2C_SendData(AT24C02_ADDRESS);
	Ack=I2C_ReceiveAck();
	I2C_SendData(WordAddress);
	Ack=I2C_ReceiveAck();
	I2C_Start();
	I2C_SendData(AT24C02_ADDRESS|0x01);
	Ack=I2C_ReceiveAck();
	Dat=I2C_ReceiveData();
	Ack=I2C_ReceiveAck();
	I2C_Stop();
	return Dat;
}