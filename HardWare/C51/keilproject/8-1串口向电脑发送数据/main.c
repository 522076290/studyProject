#include <REGX52.H>
#include <INTRINS.H>
#include "Delay.h"
#include "UART.h"

unsigned char Sec;

void main(){
	UartInit();
	while(1){
		UART_SendByte(Sec);
		Sec++;
		Delay(1000);
	}
}

