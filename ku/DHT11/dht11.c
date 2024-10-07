/*
DHT11温湿度传感器
单总线通信
1.c8t6一般用不了PA15、PB3、PB4（用作SW）
2.3.3V-5V供电
3.使用：引用dht11.h 
        初始化DHT11_Init();
				主函数定义变量接收温湿度数据
				      u8 humidityH;       //湿度整数部分
              u8 humidityL;       //湿度小数部分
              u8 temperatureH;    //温度整数部分
              u8 temperatureL;    //温度小数部分
*/

#include "dht11.h"

/*******************************************************************************
* 函 数 名         : DHT11_IO_OUT
* 函数功能		     : DHT11_IO输出配置	   
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void DHT11_IO_OUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=DHT11_GPIO_Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(DHT11_GPIO_Port,&GPIO_InitStructure);
}
 
/*******************************************************************************
* 函 数 名         : DHT11_IO_IN
* 函数功能		     : DHT11_IO输入配置	   
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void DHT11_IO_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=DHT11_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(DHT11_GPIO_Port,&GPIO_InitStructure);
}

/*******************************************************************************
* 函 数 名         : DHT11_Reset
* 函数功能		     : 复位DHT11
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void DHT11_Reset(void)	   
{                 
	DHT11_IO_OUT(); 		//配置io口为输出模式
  DHT11_DQ_OUT=0; 		//拉低DQ
  delay_ms(20);    		//拉低至少18ms
	DHT11_DQ_OUT=1; 		//DQ=1 
  delay_us(30);     	//主机拉高20~40us
}

/*******************************************************************************
* 函 数 名         : DHT11_Check
* 函数功能		     : 检测DHT11是否存在
* 输    入         : 无
* 输    出         : 1:未检测到DHT11的存在，0:存在
*******************************************************************************/
u8 DHT11_Check(void) 	   
{   
	u8 retry=0;
	DHT11_IO_IN();//SET PG11 INPUT	 
	
	while (DHT11_DQ_IN&&retry<100)//高电平循环，低电平跳出
	{
		retry++;
		delay_us(1);
	};
	
	if(retry>=100)
		return 1;
	else 
		retry=0;
	
	while (!DHT11_DQ_IN&&retry<100)//DHT11拉低后会再次拉高40~50us
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)
		return 1;	 
	
	return 0;
}

/*******************************************************************************
* 函 数 名         : DHT11_Init()
* 函数功能		     : DHT11初始化 
* 输    入         : 无
* 输    出         : 返回0：初始化成功，1：失败
*******************************************************************************/
u8 DHT11_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
	RCC_APB2PeriphClockCmd(DHT11_GPIO_CLK,ENABLE);
 
	GPIO_InitStructure.GPIO_Pin=DHT11_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(DHT11_GPIO_Port,&GPIO_InitStructure);
	GPIO_SetBits(DHT11_GPIO_Port,DHT11_GPIO_Pin);	   //拉高
 
	DHT11_Reset();	  
	return DHT11_Check();	
}
 
/*******************************************************************************
* 函 数 名         : DHT11_Read_Bit(void) 
* 函数功能		     : 从DHT11读取一个位
* 输    入         : 无
* 输    出         :返回值：1/0
*******************************************************************************/
u8 DHT11_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(DHT11_DQ_IN&&retry<100)//等待变为低电平 12-14us 开始
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT11_DQ_IN&&retry<100)//等待变高电平	 26-28us表示0,116-118us表示1
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);//等待40us
	if(DHT11_DQ_IN)
		return 1;
	else 
		return 0;		   
}

/*******************************************************************************
* 函 数 名         : DHT11_Read_Byte(void）
* 函数功能		     : 从DHT11读取一个字节
* 输    入         : 无
* 输    出         :返回值：读到的数据
*******************************************************************************/
u8 DHT11_Read_Byte(void)    
{        
  u8 i,dat;
  dat=0;
	for (i=0;i<8;i++) 
	{
   	dat<<=1; 
	  dat|=DHT11_Read_Bit();
  }						    
  return dat;
}

/*******************************************************************************
* 函 数 名         : DHT11_Read_Data(u8 *temp,u8 *humi) 
* 函数功能		     : 从DHT11读取一次数据
* 输    入         : humidityH\humidityL\temperatureH\temperatureL
* 输    出         : 返回值：0,正常;1,读取失败
*******************************************************************************/
u8 DHT11_Read_Data(u8 *humidityH,u8 *humidityL,u8 *temperatureH,u8 *temperatureL)    
{        
 	u8 buf[5];
	u8 i;
	DHT11_Reset();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)//读取40位数据
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humidityH    = buf[0];
			*humidityL    = buf[1];
			*temperatureH = buf[2];
			*temperatureL = buf[3];
		}
		
	}
  else 
		return 1;
	return 0;	   	
}


 