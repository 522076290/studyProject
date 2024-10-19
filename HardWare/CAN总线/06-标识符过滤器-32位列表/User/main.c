#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "MYCAN.h"

uint8_t KeyNum;

CanTxMsg TxMsgArray[] = {
/* 	StdId	  ExtId			  IDE			  RTR	    DLC		    Data[8]			*/
	{0x123, 0x00000000, CAN_Id_Standard, CAN_RTR_DATA,   4,  {0x11,0x22,0x33,0x44}},
	{0x234, 0x00000000, CAN_Id_Standard, CAN_RTR_DATA,   4,  {0x11,0x22,0x33,0x44}},
	{0x345, 0x00000000, CAN_Id_Standard, CAN_RTR_DATA,   4,  {0x11,0x22,0x33,0x44}},
	{0x456, 0x00000000, CAN_Id_Standard, CAN_RTR_DATA,   4,  {0x11,0x22,0x33,0x44}},
	
	{0x000, 0x12345678, CAN_Id_Extended, CAN_RTR_DATA,   4,  {0x11,0x22,0x33,0x44}},
	{0x000, 0x0789ABCD, CAN_Id_Extended, CAN_RTR_DATA,   4,  {0x11,0x22,0x33,0x44}},
};

uint8_t pTxMsgArray = 0;

CanRxMsg RxMsg;

int main(void)
{
	OLED_Init();
	Key_Init();
	MyCAN_Init();
	
	OLED_ShowString(1,1," Rx :");
	OLED_ShowString(2,1,"RxID:");
	OLED_ShowString(3,1,"Leng:");
	OLED_ShowString(4,1,"Data:");
	
	while(1)
	{
		KeyNum = Key_GetNum();
		if(KeyNum == 1)
		{
			MyCAN_Transmit(&TxMsgArray[pTxMsgArray]);
			
			pTxMsgArray++;
			if(pTxMsgArray >= sizeof(TxMsgArray) / sizeof (CanTxMsg))
			{
				pTxMsgArray = 0;
			}
		}
		
		if(MyCAN_ReceiveFlag())
		{
			MyCAN_Receive(&RxMsg);
			
			if(RxMsg.IDE == CAN_Id_Standard)
			{
				OLED_ShowString(1,6,"Std");
				OLED_ShowHexNum(2,6,RxMsg.StdId,8);
			}else if(RxMsg.IDE ==  CAN_Id_Extended)
			{
				OLED_ShowString(1,6,"Ext");
				OLED_ShowHexNum(2,6,RxMsg.ExtId,8);
			}
			
			if(RxMsg.RTR == CAN_RTR_DATA)
			{
				OLED_ShowString(1,10,"Data  ");
				OLED_ShowHexNum(3,6,RxMsg.DLC,1);
				
				OLED_ShowHexNum(4,6,RxMsg.Data[0],2);
				OLED_ShowHexNum(4,9,RxMsg.Data[1],2);
				OLED_ShowHexNum(4,12,RxMsg.Data[2],2);
				OLED_ShowHexNum(4,15,RxMsg.Data[3],2);
			}else if(RxMsg.RTR == CAN_RTR_REMOTE)
			{
				OLED_ShowString(1,10,"Remote");
				OLED_ShowHexNum(3,6,RxMsg.DLC,1);
				
				OLED_ShowHexNum(4,6,0x00,2);
				OLED_ShowHexNum(4,9,0x00,2);
				OLED_ShowHexNum(4,12,0x00,2);
				OLED_ShowHexNum(4,15,0x00,2);
			}
			
			
		}
	}
	
	
}
