#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "MYCAN.h"
#include "TIMER.h"

uint8_t KeyNum;

uint8_t TimingFlag; 
uint8_t TriggerFlag;
uint8_t RequestFlag;

CanRxMsg RxMsg;

CanTxMsg TxMsg_Timing = {
	.StdId = 0x100,
	.ExtId = 0x00000000,
	.IDE = CAN_Id_Standard,
	.RTR = CAN_RTR_Data,
	.DLC = 4,
	.Data = {0x11,0x22,0x33,0x44}
};

CanTxMsg TxMsg_Trigger = {
	.StdId = 0x200,
	.ExtId = 0x00000000,
	.IDE = CAN_Id_Standard,
	.RTR = CAN_RTR_Data,
	.DLC = 4,
	.Data = {0x11,0x22,0x33,0x44}
};

CanTxMsg TxMsg_Request = {
	.StdId = 0x300,
	.ExtId = 0x00000000,
	.IDE = CAN_Id_Standard,
	.RTR = CAN_RTR_Data,
	.DLC = 4,
	.Data = {0x11,0x22,0x33,0x44}
};

int main(void)
{
	OLED_Init();
	Key_Init();
	MyCAN_Init();
	Timer_Init();
	
	OLED_ShowString(1, 1, "Tx");
	OLED_ShowString(2, 1, "Tim:");
	OLED_ShowString(3, 1, "Tri:");
	OLED_ShowString(4 ,1, "Req:");
	
	while(1)
	{
		/*定时发送*/
		if(TimingFlag == 1)
		{
			TimingFlag = 0;
			
			TxMsg_Timing.Data[0]++;
			TxMsg_Timing.Data[1]++;
			TxMsg_Timing.Data[2]++;
			TxMsg_Timing.Data[3]++;
			
			MyCAN_Transmit(&TxMsg_Timing);
			
			OLED_ShowHexNum(2,5,TxMsg_Timing.Data[0],2);
			OLED_ShowHexNum(2,8,TxMsg_Timing.Data[1],2);
			OLED_ShowHexNum(2,11,TxMsg_Timing.Data[2],2);
			OLED_ShowHexNum(2,14,TxMsg_Timing.Data[3],2);
		}
		
		/*触发发送*/
		KeyNum = Key_GetNum();
		if(KeyNum == 1)
		{
			TriggerFlag = 1;
		}
		
		if(TriggerFlag == 1)
		{
			TriggerFlag = 0;
			
			TxMsg_Trigger.Data[0] ++;
			TxMsg_Trigger.Data[1] ++;
			TxMsg_Trigger.Data[2] ++;
			TxMsg_Trigger.Data[3] ++;
			
			MyCAN_Transmit(&TxMsg_Trigger);
			
			OLED_ShowHexNum(3,5,TxMsg_Trigger.Data[0],2);
			OLED_ShowHexNum(3,8,TxMsg_Trigger.Data[1],2);
			OLED_ShowHexNum(3,11,TxMsg_Trigger.Data[2],2);
			OLED_ShowHexNum(3,14,TxMsg_Trigger.Data[3],2);
		}
		
		/*请求发送*/
		if(MyCAN_ReceiveFlag())
		{
			MyCAN_Receive(&RxMsg);
			
			if(RxMsg.IDE == CAN_Id_Standard &&
			   RxMsg.RTR == CAN_RTR_Remote &&
			   RxMsg.StdId == 0x300)
			{
				RequestFlag = 1;
			}
			if(RxMsg.IDE == CAN_Id_Standard &&
			   RxMsg.RTR == CAN_RTR_Data &&
			   RxMsg.StdId == 0x3FF)
			{
				RequestFlag = 1;
			}
		}
		if(RequestFlag == 1)
		{
			RequestFlag = 0;
			
			TxMsg_Request.Data[0] ++;
			TxMsg_Request.Data[1] ++;
			TxMsg_Request.Data[2] ++;
			TxMsg_Request.Data[3] ++;
			
			MyCAN_Transmit(&TxMsg_Request);
			
			OLED_ShowHexNum(4,5,TxMsg_Request.Data[0],2);
			OLED_ShowHexNum(4,8,TxMsg_Request.Data[1],2);
			OLED_ShowHexNum(4,11,TxMsg_Request.Data[2],2);
			OLED_ShowHexNum(4,14,TxMsg_Request.Data[3],2);
		}
	}
	
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TimingFlag = 1;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
