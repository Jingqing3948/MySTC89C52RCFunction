#include "reg52.h"
#include "Key.h"


void delay_10us(u16 ten_us)
{
while(ten_us--);
}

u8 key_scan(u8 mode)
{
	static u8 key=1;
	if(mode)key=1;//连续扫描按键
	if(key==1&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0))//任意按键按下
	{
		delay_10us(1000);//10ms 消抖
        /*另一种消抖的方法：
        if(KEY==0){
        	delay_ms(20);
        	while(KEY==0);
        	delay(20ms);
        }
        这个是针对按下按钮又抬起按钮之后的执行。*/
		key=0;
		if(KEY1==0)
		return KEY1_PRESS;
		else if(KEY2==0)
		return KEY2_PRESS;
		else if(KEY3==0)
		return KEY3_PRESS;
		else if(KEY4==0)
		return KEY4_PRESS;
	}
	else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1) //无按键按下
	{
		key=1;
	}
	return KEY_UNPRESS;
}