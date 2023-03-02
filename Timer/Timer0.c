#include <REGX52.H>

/**
  * @brief  init timer@12.000MHz
  * @param  none
  * @retval none
  */
void time0Init(void)
{
    TMOD&=0xF0;//set timer mode
    TMOD|=0X01;//TMOD is non-addressable, it includes timer1 and timer0 register, but cannot be assigned separately.
    //So we use or operation to clear low 4 bits without influencing high 4 bits.
    
    //IE, IT in TCON, which is also means INT0，because GATE =0, TR=1, so we don't need to set IE/IT.

    //TH TL = 65535,interrupt happens.
    //set 1ms trigger 1 interrupt:
    //@12MHZ: 1us = 1 machine cycle, so init value = 64535.
    //@11.0592MHz: 11.0592/12=921600Hz, 1us = 0.9216 machine cycle, so init value = 65535-922=64613.
    TH0=0XFC; //64613/256=252=0xFC，@11.0592 MHZ
    TL0=0X65;//64613%256=0x65
    
    TF0=0;//set init interrupt, to avoid interrupt when start system
    TR0=1;//enable timer0
    ET0=1;//enable timer0 interrupt
    EA=1;//enable interrupt
    PT0=0;//set interrupt priority = low. Default value is also low.
}

/*Timer interrupt function template
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;		
	TH0 = 0xFC;		
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
	}
}
*/
