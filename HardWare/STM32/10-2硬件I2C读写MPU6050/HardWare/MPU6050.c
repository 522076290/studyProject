#include "stm32f10x.h"                  // Device header
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS  0xD0

/**
  * 函    数：MPU6050等待事件
  * 参    数：同I2C_CheckEvent
  * 返 回 值：无
  */
void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
	uint32_t Timeout;
	Timeout = 10000;									//给定超时计数时间
	while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)	//循环等待指定事件
	{
		Timeout --;										//等待时，计数值自减
		if (Timeout == 0)								//自减到0后，等待超时
		{
			/*超时的错误处理代码，可以添加到此处*/
			break;										//跳出等待，不等了
		}
	}
}

void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data)
{
	I2C_GenerateSTART(I2C2,ENABLE);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
	
	I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Transmitter);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);	//等待EV6
	
	I2C_SendData(I2C2,RegAddress);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);			//等待EV8

	I2C_SendData(I2C2,Data);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);				//等待EV8_2

	I2C_GenerateSTOP(I2C2,ENABLE);
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	
	I2C_GenerateSTART(I2C2,ENABLE);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);					//等待EV5

	I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Transmitter);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);	//等待EV6

	I2C_SendData(I2C2,RegAddress);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);				//等待EV8_2

	I2C_GenerateSTART(I2C2,ENABLE);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);					//等待EV5

	I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Receiver);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);		//等待EV6

	I2C_AcknowledgeConfig(I2C2,DISABLE);
	I2C_GenerateSTOP(I2C2,ENABLE);
	
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED);				//等待EV7

	Data = I2C_ReceiveData(I2C2);
	
	I2C_AcknowledgeConfig(I2C2,ENABLE);
	
	return Data;
}

/**
  * 函    数：MPU6050获取ID号
  * 参    数：无
  * 返 回 值：MPU6050的ID号
  */
uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);		//返回WHO_AM_I寄存器的值
}


void MPU6050_Init(void){
	
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);		//开启I2C2的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOB的时钟

	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					//将PB10和PB11引脚初始化为复用开漏输出

	
	/*I2C初始化*/
	I2C_InitTypeDef I2C_InitStructure;						//定义结构体变量
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;				//模式，选择为I2C模式
	I2C_InitStructure.I2C_ClockSpeed = 50000;				//时钟速度，选择为50KHz
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;		//时钟占空比，选择Tlow/Thigh = 2
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;				//应答，选择使能
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;	//应答地址，选择7位，从机模式下才有效
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;				//自身地址，从机模式下才有效
	I2C_Init(I2C2, &I2C_InitStructure);						//将结构体变量交给I2C_Init，配置I2C2
	
	/*I2C使能*/
	I2C_Cmd(I2C2, ENABLE);									//使能I2C2，开始运行
	
	/*MPU6050寄存器初始化，需要对照MPU6050手册的寄存器描述配置，此处仅配置了部分重要的寄存器*/
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);		//电源管理寄存器1，取消睡眠模式，选择时钟源为X轴陀螺仪
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);		//电源管理寄存器2，保持默认值0，所有轴均不待机
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);		//采样率分频寄存器，配置采样率
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);			//配置寄存器，配置DLPF
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);	//陀螺仪配置寄存器，选择满量程为±2000°/s
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);	//加速度计配置寄存器，选择满量程为±16g
}


void MPU6050_GetData(int16_t *AccX,int16_t *AccY,int16_t *AccZ,
						int16_t *GyroX,int16_t *GyroY,int16_t *GyroZ)
{
	uint8_t Data_H, Data_L;
	Data_H = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	Data_L = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (Data_H << 8) | Data_L;
	
	Data_H = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	Data_L = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (Data_H << 8) | Data_L;
	
	Data_H = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	Data_L = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (Data_H << 8) | Data_L;
	
	Data_H = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	Data_L = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (Data_H << 8) | Data_L;
	
	Data_H = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	Data_L = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (Data_H << 8) | Data_L;
	
	Data_H = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	Data_L = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (Data_H << 8) | Data_L;
}
