#include "reg52.h"
#include "IIC.h"

void I2C_Start(){//
	I2C_SDA=1;
	I2C_SCL=1;
	I2C_SDA=0;
	I2C_SCL=0;
}

void I2C_Stop(){
	I2C_SDA=0;
	I2C_SCL=1;
	I2C_SDA=1;
}

void I2C_SendData(unsigned char Byte){
	unsigned char i;
	for(i=0;i<8;i++){
		I2C_SDA=Byte&(0x80>>i);
		I2C_SCL=1;
		I2C_SCL=0;
	}
}

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

void I2C_SendAck(unsigned char ackBit){//0:ack; 1:nack
	I2C_SDA=ackBit;
	I2C_SCL=1;
	I2C_SCL=0;
}

unsigned char I2C_ReceiveAck(){//0:ack; 1:nack
	unsigned char ackBit=0;
	I2C_SDA=1;//接收前，主机要先释放 SDA
	I2C_SCL=1;
	if(I2C_SDA)ackBit=1;
	I2C_SCL=0;
	return ackBit;
}