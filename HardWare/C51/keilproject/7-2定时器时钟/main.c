#include <REGX52.H>
#include "Delay.h"
#include "Nixie.h"
#include "LCD1602.h"
#include "MatrixKey.h"
#include "Timer0.h"
#include "Key.h"
#include <INTRINS.H>


unsigned char Sec=55,Min=59,Hour=23;


/**
  * @brief 定时器中断函数
  * @param 
  * @retval 
  */
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
  T0Count++;
  if(T0Count>=1000){
	  T0Count=0;
	  Sec++;
		if(Sec>=60){
			Sec=0;
			Min++;
			if(Min>=60){
				Min=0;
				Hour++;
				if(Hour>=24){
					Hour=0;
				}
			}
		}
  }
}

void main(){
	LCD_Init();
	Timer0Init();
	
	LCD_ShowString(1,1,"Clock:");
	LCD_ShowString(2,1,"  :  :");
	
	while(1){
		LCD_ShowNum(2,1,Hour,2);
		LCD_ShowNum(2,4,Min,2);
		LCD_ShowNum(2,7,Sec,2);
	}
}

