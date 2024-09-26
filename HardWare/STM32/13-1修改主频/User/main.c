#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

uint8_t KeyNum;

int main(void)
{
	OLED_Init();
	
	OLED_ShowNum(1,1,SystemCoreClock,8);
	
	
	while(1)
	{
		OLED_ShowString(2,1,"Running");
		Delay_ms(500);
		OLED_ShowString(2,1,"       ");
		Delay_ms(500);
	}
	
	
}
