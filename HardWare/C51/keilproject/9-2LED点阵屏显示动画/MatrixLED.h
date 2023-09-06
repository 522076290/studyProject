#ifndef __MATRIXLED_H__
#define __MATRIXLED_H__

void _74HC595_WriteByte(unsigned char Byte);
void MatrixLED_ShowColum(unsigned char Column,Data);
void MatrixLED_Init();

#endif	