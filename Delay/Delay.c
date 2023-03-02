#include "Delay.h"
//@11.0592MHZ STC-Y1

void delay10Us(unsigned char us) //@11.0592MHz
{
	unsigned char i, j;
	for (i = 0; i < us; i++)
	{
		j = 2;
		while (--j)
			;
	}
}

void delayMs(unsigned char ms) //@11.0592MHz
{
	unsigned char i, j, k;
	for (k = 0; k < ms; k++)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j)
				;
		} while (--i);
	}
}
