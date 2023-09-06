#include <REGX52.H>

/**
  * @brief 串口初始化 4800bps@11.0592MHz
  * @param 无
  * @retval 无
  */
void UartInit(void)		
{
	SCON = 0x50;		//8位数据,可变波特率
	PCON |= 0x80;		//使能波特率倍速位SMOD
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xF4;		//设定定时初值
	TH1 = 0xF4;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA=1;				//启动串口中断
	ES=1;
}

/**
  * @brief 串口发送一个字节数据
  * @param Byte 要发送的一个字节数据
  * @retval 无
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}

/**
  * @brief 串口中断函数模板
  * @param 无
  * @retval 无
  */
//void UART_Routine() interrupt 4
//{
//	if(RI==1)
//	{
//		RI=0;
//	}
//}