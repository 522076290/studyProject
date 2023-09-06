#include <REGX52.H>

void Timer0_Init(void)
{
	
	TMOD &= 0xF0;		//设置定时器模式 把TMOD的低四位清零 高四位保持不变
	TMOD |= 0x01;		//设置定时器模式 把TMOD的最低位置1 高四位保持不变
	TL0 = 0;		//设置定时初值
	TH0 = 0;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 0;		//定时器0不计时
}

void Timer0_setCounter(unsigned int Value)
{
	TH0=Value/256;
	TH0=Value%256;
}

unsigned int Timer0_GetCounter(void)
{
	return (TH0<<8)|TL0;
}

void Timer0_Run(unsigned char Flag)
{
	TR0=Flag;
}


