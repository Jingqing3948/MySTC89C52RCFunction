#include "reg52.h"
#include "IIC.h"
#include "AT24C02.H"


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