#include <REGX52.H>

sbit DS1302_SCLK=P3^6;  //移位控制地址
sbit DS1302_IO=P3^4;		//IO口地址
sbit DS1302_CE=P3^5;		//命令控制逻辑地址

#define DS1302_SECOND  0x80	//秒地址
#define DS1302_MINUTE  0x82 //分钟地址
#define DS1302_HOUR  	 0x84 //时地址
#define DS1302_DATE  	 0x86 //日地址
#define DS1302_MONTH   0x88 //月地址
#define DS1302_DAY  	 0x8A //星期地址
#define DS1302_YEAR  	 0x8C //年地址
#define DS1302_WP  	   0x8E	//写保护地址

//保存年月日时分秒的数组
unsigned char DS1302_Time[]={23,1,28,23,9,0,6};

/**
  * @brief DS1302初始化
  * @param 无
  * @retval 无
  */
void DS1302_Init(void)
{
	DS1302_CE=0;
	DS1302_SCLK=0;
}

/**
  * @brief DS1302写入字节
  * @param Command 要写入数据的地址
	* @param Data 要写入的数据
  * @retval 无
  */
void DS1302_WriteByte(unsigned char Command,Data)
{
	unsigned char i;
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}
	for(i=0;i<8;i++)
	{
		DS1302_IO=Data&(0x01<<i);
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}
	DS1302_CE=0;
}


/**
  * @brief DS1302读出函数
  * @param Command 要读出数据的地址
  * @retval Data 返回读出的数据
  */
unsigned char DS1302_ReaedByte(unsigned char Command)
{
	unsigned char i,Data=0x00;
	Command|=0x01;
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=0;
		DS1302_SCLK=1;
	}
	for(i=0;i<8;i++)
	{
		DS1302_SCLK=1;
		DS1302_SCLK=0;
		if(DS1302_IO){Data|=(0x01<<i);}
	}
	DS1302_CE=0;
	DS1302_IO=0;
	return Data;
}


/**
  * @brief DS1302设置时间
  * @param 无
  * @retval 无
  */
void DS1302_SetTime(void)
{
	DS1302_WriteByte(DS1302_WP,0x00);
	
	DS1302_WriteByte(DS1302_YEAR,DS1302_Time[0]/10*16+DS1302_Time[0]%10);
	DS1302_WriteByte(DS1302_MONTH,DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_Time[6]/10*16+DS1302_Time[6]%10);
	
	DS1302_WriteByte(DS1302_WP,0x80);
}


/**
  * @brief DS1302读出时间
  * @param 无
  * @retval 无
  */
void DS1302_ReadTime(void)
{
	unsigned char Temp;
	Temp = DS1302_ReaedByte(DS1302_YEAR);
	DS1302_Time[0] = Temp/16*10+Temp%16;
	Temp = DS1302_ReaedByte(DS1302_MONTH);
	DS1302_Time[1] = Temp/16*10+Temp%16;
	Temp = DS1302_ReaedByte(DS1302_DATE);
	DS1302_Time[2] = Temp/16*10+Temp%16;
	Temp = DS1302_ReaedByte(DS1302_HOUR);
	DS1302_Time[3] = Temp/16*10+Temp%16;
	Temp = DS1302_ReaedByte(DS1302_MINUTE);
	DS1302_Time[4] = Temp/16*10+Temp%16;
	Temp = DS1302_ReaedByte(DS1302_SECOND);
	DS1302_Time[5] = Temp/16*10+Temp%16;
	Temp = DS1302_ReaedByte(DS1302_DAY);
	DS1302_Time[6] = Temp/16*10+Temp%16;
}