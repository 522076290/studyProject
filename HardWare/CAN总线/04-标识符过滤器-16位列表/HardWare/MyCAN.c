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
	CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;
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
	CAN_FilterInitSturcture.CAN_FilterIdHigh = 0x234 << 5;
	CAN_FilterInitSturcture.CAN_FilterIdLow = 0x345 << 5;
	CAN_FilterInitSturcture.CAN_FilterMaskIdHigh = 0x567 << 5;
	CAN_FilterInitSturcture.CAN_FilterMaskIdLow = 0x000 << 5;
	CAN_FilterInitSturcture.CAN_FilterScale = CAN_FilterScale_16bit;
	CAN_FilterInitSturcture.CAN_FilterMode = CAN_FilterMode_IdList;
	CAN_FilterInitSturcture.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;
	CAN_FilterInitSturcture.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitSturcture);
}

void MyCAN_Transmit(CanTxMsg *TxMessage)
{
	uint8_t TransmitMailbox =  CAN_Transmit(CAN1,TxMessage);
	
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

void MyCAN_Receive(CanRxMsg *RxMessage)
{
	CAN_Receive(CAN1,CAN_FIFO0,RxMessage);
}
