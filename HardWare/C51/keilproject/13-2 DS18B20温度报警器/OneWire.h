#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__

unsigned char OneWire_Init(void);
void OneWire_SendBit(unsigned char Bit);
unsigned char OneWire_ReciveBit(void);
void OneWire_SendByte(unsigned char Byte);
unsigned char OneWire_ReciveByte(void);

#endif