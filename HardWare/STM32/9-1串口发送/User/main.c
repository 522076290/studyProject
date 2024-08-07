#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t KeyNum;

int main(void)
{
	OLED_Init();
	
	Serial_Init();
	
//	uint8_t MyArray[] = {'H','e','l','l','o',' ',' ','W','o','r','d','!'};
//	Serial_SendArray(MyArray,12);
	
	
//	Serial_SendString("Hello  Word!");
//	Serial_SendString("\r\n");
	
//	Serial_SendNumber(1001,4);
//	Serial_SendString("\r\n");
	
//	printf("Num=%d\r\n",666);
	
//	char String[100];
//	sprintf(String,"Num=%d\r\n",666);
//	Serial_SendString(String);
	
	Serial_Printf("你好，世界");
	
	while(1)
	{
		
	}
	
	
}
