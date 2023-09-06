#include <REGX52.H>
#include "I2C.h"

#define AT24C02_ADDRESS 0xA0

/**
  * @brief AT24C02写入一个字节
  * @param WordAddress 要写入字节的地址
	* @param Data 要写入的数据
  * @retval 无
  */
void AT24C02_WriteByte(unsigned char WordAddress,Data)
{
	I2C_Start();
	I2C_SentByte(AT24C02_ADDRESS);
	I2C_ReciveAck();
	I2C_SentByte(WordAddress);
	I2C_ReciveAck();
	I2C_SentByte(Data);
	I2C_ReciveAck();
	I2C_Stop();
}

/**
  * @brief AT24C02读取一个字节
  * @param WordAddress 要读出的字节的地址
  * @retval 读出的数据
  */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	I2C_Start();
	I2C_SentByte(AT24C02_ADDRESS);
	I2C_ReciveAck();
	I2C_SentByte(WordAddress);
	I2C_ReciveAck();
	I2C_Start();
	I2C_SentByte(AT24C02_ADDRESS|0x01);
	I2C_ReciveAck();
	Data = I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();
	return Data;
}