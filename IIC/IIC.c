/*
 * @Author: Jingqing3948 2351290287@qq.com
 * @Date: 2023-03-02 12:10:56
 * @LastEditors: Jingqing3948 2351290287@qq.com
 * @LastEditTime: 2023-03-03 08:01:51
 * @Description: functions about basic operations on I2C.
 * SDA can only change value during SCL low level. During SCL high level, SDA can't change value.
 * SCL low to high: SDA sends value.
 * SCL high to low: SDA gets value.
 * 
 * Copyright (c) 2023 by Jingqing3948 2351290287@qq.com, All Rights Reserved. 
 */
#include "reg52.h"
#include "IIC.h"

/**
 * @brief: start I2C. when SCL is high, SDA from high to low, I2C start.
 * @return {*}
 */
void I2C_Start(){
	I2C_SDA=1;
	I2C_SCL=1;
	I2C_SDA=0;
	I2C_SCL=0;
}

/**
 * @brief: stop I2C. when SCL is high, SDA from low to high, I2C stop.
 * @return {*}
 */
void I2C_Stop(){
	I2C_SDA=0;
	I2C_SCL=1;
	I2C_SDA=1;
}

/**
 * @brief: send a byte on I2C. When SCL is low level, SDA is allowed to change data, and SCL turn to high level to send this bit, and repeat it.
 * @param {unsigned char} Byte
 * @return {*}
 */
void I2C_SendData(unsigned char Byte){
	unsigned char i;
	for(i=0;i<8;i++){
		I2C_SDA=Byte&(0x80>>i);
		I2C_SCL=1;
		I2C_SCL=0;
	}
}

/**
 * @brief: Receive a byte on I2C. When SCL is high level, we read one bit from I2C_SDA, and repeat it.
 * @return {*}
 */
unsigned char I2C_ReceiveData(){
	unsigned char i, Byte=0x00;
	I2C_SDA=1;
	for(i=0;i<8;i++){
		I2C_SCL=1;
		if(I2C_SDA)Byte|=(0x80>>i);
		I2C_SCL=0;
	}
	return Byte;
}

/**
 * @brief: send a ack bit
 * @param {unsigned char} ackBit
 * @return {*}
 */
void I2C_SendAck(unsigned char ackBit){//0:ack; 1:nack
	I2C_SDA=ackBit;
	I2C_SCL=1;
	I2C_SCL=0;
}

/**
 * @brief: receive a ack bit
 * @return {*}
 */
unsigned char I2C_ReceiveAck(){//0:ack; 1:nack
	unsigned char ackBit=0;
	I2C_SDA=1;
	I2C_SCL=1;
	if(I2C_SDA)ackBit=1;
	I2C_SCL=0;
	return ackBit;
}