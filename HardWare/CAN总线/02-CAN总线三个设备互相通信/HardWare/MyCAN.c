#include "stm32f10x.h"                  // Device header


void MyCAN_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	CAN_InitTypeDef CAN_InitStructure;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	CAN_InitStructure.CAN_Prescaler = 48;   //波特率 = 36M / 48 /(1+2+3)= 125K
	CAN_InitStructure.CAN_BS1 = CAN_BS1_2tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
	CAN_InitStructure.CAN_SJW = CAN_SJW_2tq;
	CAN_InitStructure.CAN_NART = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = DISABLE;
	CAN_Init(CAN1, &CAN_InitStructure);
	
	CAN_FilterInitTypeDef CAN_FilterInitSturcture;
	CAN_FilterInitSturcture.CAN_FilterNumber = 0;
	CAN_FilterInitSturcture.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitSturcture.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitSturcture.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitSturcture.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitSturcture.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitSturcture.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitSturcture.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;
	CAN_FilterInitSturcture.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitSturcture);
}

void MyCAN_Transmit(uint32_t ID, uint8_t Length, uint8_t *Data)
{
	CanTxMsg TxMessage;
	TxMessage.StdId = ID;
	TxMessage.ExtId = ID;
	TxMessage.IDE = CAN_Id_Standard; //CAN_ID_STD
	TxMessage.RTR = CAN_RTR_Data;   
	TxMessage.DLC = Length;
	for(uint8_t i = 0; i<Length; i++)
	{
		TxMessage.Data[i] = Data[i];
	}
	uint8_t TransmitMailbox =  CAN_Transmit(CAN1,&TxMessage);
	
	uint32_t Timeout = 0;
	while(CAN_TransmitStatus(CAN1,TransmitMailbox) != CAN_TxStatus_Ok)
	{
		Timeout++;
		if(Timeout > 100000)
		{
			break;
		}
	}
}

uint8_t MyCAN_ReceiveFlag(void)
{
	if(CAN_MessagePending(CAN1,CAN_FIFO0)>0)
	{
		return 1;
	}
	return 0;
}

void MyCAN_Receive(uint32_t *ID, uint8_t *Length, uint8_t *Data)
{
	CanRxMsg RxMessage;
	CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);
	if(RxMessage.IDE == CAN_Id_Standard)
	{
		 *ID = RxMessage.StdId;
	}
	else{
		*ID = RxMessage.ExtId;
	}
	
	if(RxMessage.RTR == CAN_RTR_Data)
	{
		*Length = RxMessage.DLC;
		for(uint8_t i = 0; i < *Length; i++)
		{
			Data[i] = RxMessage.Data[i];
		}
	}else{
		//''''
	}
}
