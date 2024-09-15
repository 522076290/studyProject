#include "stm32f10x.h"                  // Device header
#include "MyI2C.h"
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS  0xD0

void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Data);
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);
	MyI2C_ReceiveAck();
	Data = MyI2C_ReceiveByte();
	MyI2C_SendAck(1);
	MyI2C_Stop();
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
	MyI2C_Init();
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
