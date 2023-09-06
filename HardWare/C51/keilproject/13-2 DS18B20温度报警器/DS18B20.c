#include <REGX52.H>
#include "OneWire.h"

#define Ds18B20_SKIP_ROM 				0xCC
#define Ds18B20_CONVERT_T 			0x44
#define Ds18B20_READ_SCRATCHPAD 0xBE

void DS18B20_ConverT(void)
{
	OneWire_Init();
	OneWire_SendByte(Ds18B20_SKIP_ROM);
	OneWire_SendByte(Ds18B20_CONVERT_T);
}

float DS18B20_ReadT(void)
{
	unsigned char TLSB,TMSB;
	int Temp;
	float T;
	OneWire_Init();
	OneWire_SendByte(Ds18B20_SKIP_ROM);
	OneWire_SendByte(Ds18B20_READ_SCRATCHPAD);
	TLSB = OneWire_ReciveByte();
	TMSB = OneWire_ReciveByte();
	
	
	Temp=(TMSB<<8)|TLSB;
	T = Temp/16.0;
	return T;
}
