#include "reg52.h"
typedef unsigned int u16; //��ϵͳĬ���������ͽ����ض���
typedef unsigned char u8;
//��������������ƽ�
sbit KEY1=P3^1;
sbit KEY2=P3^0;
sbit KEY3=P3^2;
sbit KEY4=P3^3;
//���� LED1 ���ƽ�
sbit LED1=P2^0;
sbit LED2=P2^1;
sbit LED3=P2^2;
sbit LED4=P2^3;
//ʹ�ú궨������������µļ�ֵ
#define KEY1_PRESS 1
#define KEY2_PRESS 2
#define KEY3_PRESS 3
#define KEY4_PRESS 4
#define KEY_UNPRESS 0

void delay_10us(u16 ten_us);
u8 key_scan(u8 mode);