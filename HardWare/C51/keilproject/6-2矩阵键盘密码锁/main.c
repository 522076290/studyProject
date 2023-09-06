#include <REGX52.H>
#include "Delay.h"
#include "Nixie.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum;
unsigned int Password,Count;

main(){
	LCD_Init();
	LCD_ShowString(1,1,"PassWord");

	while(1){
		KeyNum = MatrixKey();
		if(KeyNum){
			
			if(KeyNum<=10) //如果S1~S10按键按下 输入密码
			{
				if(Count<4){  //如果输入次数小于4
					Password*=10;						//密码左移一位
					Password += KeyNum%10;  //获取一位密码
					Count++; //计次加一 
				}
				LCD_ShowNum(2,1,Password,4);	//更新显示
			}
			
			
			if(KeyNum==11){  //如果按下S11按键 则确认
				if(Password==2345){ //如果密码正确
					Delay(20)
					LCD_ShowString(1,14,"OK ");
					Delay(20);
					Password = 0;  //密码清零
					Count=0; 			//计次清零
					LCD_ShowNum(2,1,Password,4);	//更新显示
				}
				else{						//如果密码错误
					Delay(20);
					LCD_ShowString(1,14,"ERR");
					Delay(20);
					Password = 0;  //密码清零
					Count=0; 			//计次清零
					LCD_ShowNum(2,1,Password,4);	//更新显示
				}
		}
			
		
			if(KeyNum==12){		//如果按下S12 取消
				Password = 0;  //密码清零
				Count=0; 			//计次清零
				LCD_ShowString(1,14,"   ");
				LCD_ShowNum(2,1,Password,4);	//更新显示
			}
			
			
		}
	}
}