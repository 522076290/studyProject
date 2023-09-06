#include <REGX52.H>

void Delay1ms(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
	while(xms){
			i = 2;
			j = 239;
			do
			{
				while (--j);
			} while (--i);
			xms-=1;
	}

}

unsigned char LEDNum = 0;

main(){
	
	P2 = ~(0x01);
	while(1){
		if(P3_1==0){
			Delay1ms(20);
			while(P3_1==0);
			Delay1ms(20);
			
			LEDNum++;
			if(LEDNum==8){LEDNum=0;}
			P2 = ~(0x01 << LEDNum);
		}
		
		if(P3_0==0){
			Delay1ms(20);
			while(P3_0==0);
			Delay1ms(20);
			
			if(LEDNum==0){
				LEDNum=7;
			}else{
				LEDNum--;
			}
			P2 = ~(0x01 << LEDNum);
		}
		
	}
}