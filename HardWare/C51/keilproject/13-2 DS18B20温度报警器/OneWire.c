#include <REGX52.H>

sbit OneWire_DQ=P3^7;

unsigned char OneWire_Init(void)
{
	unsigned char i;
	unsigned char AckBit;
	//屏蔽中断
	EA=0;
	OneWire_DQ=1;
	OneWire_DQ=0;
	
	//Delay 500us
	i = 227;while (--i);
	
	OneWire_DQ=1;
	
	//Delay 70us
	i = 29;while (--i);
	
	AckBit=OneWire_DQ;
	
	//Delay 500us
	i = 227;while (--i);
	
	EA=1;
	return AckBit;
}

void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	EA=0;
	OneWire_DQ=0;
	i = 3;while (--i); //Delay 10us
	OneWire_DQ=Bit;
	i = 22;while (--i);//Delay 50us
	OneWire_DQ=1;
	EA=1;
}

unsigned char OneWire_ReciveBit(void)
{
	unsigned char i;
	unsigned char Bit;
	EA=0;
	OneWire_DQ=0;
	i = 1;while (--i);//Delay 5us
	OneWire_DQ=1;
	i = 1;while (--i);//Delay 5us
	Bit=OneWire_DQ;
	i = 22;while (--i);//Delay 50us
	EA=1;
	return Bit;
}

void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i;
	EA=0;
	for(i=0;i<8;i++)
	{
		OneWire_SendBit(Byte&(0x01<<i));
	}
	EA=1;
}

unsigned char OneWire_ReciveByte(void)
{
	unsigned char i;
	unsigned char Byte=0x00;
	EA=0;
	for(i=0;i<8;i++)
	{
		if(OneWire_ReciveBit()){Byte|=(0x01<<i);}
	}
	EA=1;
	return Byte;
}