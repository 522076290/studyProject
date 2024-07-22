#include "stm32f10x.h"                  // Device header

uint16_t MyDMA_Size;

void MyDMA_Init(uint32_t AddrA,uint32_t AddrB,uint16_t Size)
{
	MyDMA_Size = Size;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitTypeDef DMAInitStructure;
	DMAInitStructure.DMA_PeripheralBaseAddr = AddrA;
	DMAInitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMAInitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	DMAInitStructure.DMA_MemoryBaseAddr = AddrB;
	DMAInitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMAInitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMAInitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMAInitStructure.DMA_BufferSize = Size;
	DMAInitStructure.DMA_Mode = DMA_Mode_Normal;
	DMAInitStructure.DMA_M2M = DMA_M2M_Enable;
	DMAInitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1,&DMAInitStructure);
	
	DMA_Cmd(DMA1_Channel1,DISABLE);
}

void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1,MyDMA_Size);
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);
}
