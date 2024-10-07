/*
AHT10 
1306驱动 软件IIC
1.c8t6一般用不了PA15、PB3、PB4（用作SW）
2.3.3V-5V供电
3.使用：引用AHT10.h 
        初始化AHT10_Init();
				AHT10_Data(&temp,&humi);获取double型数据
*/

#include "AHT10.h"

/*-------------------------------------------------*/
/*函数名：初始化IIC接口                            */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void AHT10_IIC_Init(void)
{			
	GPIO_InitTypeDef  GPIO_InitStructure;                      //定义一个设置IO的变量

	RCC_APB2PeriphClockCmd(AHT10_SDA_GPIO_CLK|AHT10_SCL_GPIO_CLK, ENABLE);    //使能GPIOB时钟
	GPIO_InitStructure.GPIO_Pin = AHT10_SDA_GPIO_Pin | AHT10_SCL_GPIO_Pin ;    //准备设置引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;           //推免输出方式  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;          //IO速率50M
	GPIO_Init(AHT10_SDA_GPIO_Port, &GPIO_InitStructure);
	GPIO_Init(AHT10_SCL_GPIO_Port, &GPIO_InitStructure);
	
	AHT10_IIC_SCL_H;   //SCL拉高
	AHT10_IIC_SDA_H;   //SDA拉高
}

/*-------------------------------------------------*/
/*函数名：SDA输出模式配置                          */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void AHT10_SDA_OUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = AHT10_SDA_GPIO_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(AHT10_SDA_GPIO_Port,&GPIO_InitStructure);
}
 
/*-------------------------------------------------*/
/*函数名：SDA输入模式配置                          */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void AHT10_SDA_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = AHT10_SDA_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(AHT10_SDA_GPIO_Port,&GPIO_InitStructure);
}

/*-------------------------------------------------*/
/*函数名：IIC起始信号                              */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void AHT10_IIC_Start(void)
{
	AHT10_SDA_OUT();     //SDA线输出模式
  AHT10_IIC_SDA_H;	   //SDA拉高  
	AHT10_IIC_SCL_H;     //SCL拉高	  
	delay_us(4);   //延时
 	AHT10_IIC_SDA_L;     //SCL高电平的时候，SDA由高到低，起始信号
}
/*-------------------------------------------------*/
/*函数名：IIC停止信号                              */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void AHT10_IIC_Stop(void)
{
	AHT10_SDA_OUT();     //SDA线输出模式
	AHT10_IIC_SDA_L;     //SDA拉低
	AHT10_IIC_SCL_H;     //SCL拉高
 	delay_us(4);   //延时
	AHT10_IIC_SDA_H;     //SCL高电平的时候，SDA由低到高，发出停止信号					   	
}
/*-------------------------------------------------*/
/*函数名：等待应答                                 */
/*参  数：无                                       */
/*返回值：0：成功  1：失败                         */
/*-------------------------------------------------*/
char AHT10_IIC_Wait_Ack(void)
{
	unsigned char timeout=0; //定义一个变量，用于计算超时时间
	
	AHT10_IIC_SDA_H;	             //SDA拉高
	AHT10_SDA_IN();                //SDA线输入模式 
	AHT10_IIC_SCL_H;	             //SCL拉高
	 
	while(AHT10_READ_SDA){         //等待SDA变低电平，表示应答到来，不然一直while循环，直到超时	
		timeout++;           //超时计数+1
		if(timeout>250){     //如果大于250	
			AHT10_IIC_Stop();      //发送停止信号
			return 1;        //返回1，表示失败
		}
		delay_us(2);         //延时
	}
	AHT10_IIC_SCL_L;               //SCL拉低
	delay_us(20);            //延时	
	return 0;                //返回0，表示成功
} 	
/*-------------------------------------------------*/
/*函数名：发送一个字节                             */
/*参  数：txd：发送的字节                          */
/*返回值：无                                       */
/*-------------------------------------------------*/ 			  
void AHT10_IIC_Send_Byte(unsigned char txd)
{                        
  unsigned char t;                   //定义一个变量用于for循环 
	
	AHT10_SDA_OUT(); 	                       //SDA线输出模式 
  AHT10_IIC_SCL_L;                         //SCL拉低，开始数据传输
  for(t=0;t<8;t++)                   //for循环，一位一位的发送，从最高位 位7开始  
	{                                 
    AHT10_IIC_SDA_OUT(((txd&0x80)>>7));  //给SDA数据线
    txd<<=1; 	                   //左移一位，准备下一次发送
		delay_us(2);                   //延时
		AHT10_IIC_SCL_H;                     //SCL拉高
		delay_us(2);                   //延时
		AHT10_IIC_SCL_L;	                   //SCL拉低
  }	 
} 	    
/*-------------------------------------------------*/
/*函数名：读取一个字节                             */
/*参  数：ack：是否发送应答 1:发 0：不发           */
/*返回值：读取的数据                               */
/*-------------------------------------------------*/   
unsigned char AHT10_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i;           //定义一个变量用于for循环 
	unsigned char receive;     //定义一个变量用于保存接收到的数据
		
	receive = 0;               //清除receive，准备接收数据
	AHT10_SDA_IN();                  //SDA设置为输入
  AHT10_IIC_SCL_L;                 //SCL拉低
  delay_us(20);               //延时	
	for(i=0;i<8;i++)           //for循环，一位一位的读取	
	{           
		AHT10_IIC_SCL_H;             //SCL拉高 
		delay_us(20);           //延时
		receive<<=1;           //左移一位，准备下次的读取
		if(AHT10_READ_SDA)receive++; //读取数据
		delay_us(20);           //延时
		AHT10_IIC_SCL_L;             //SCL拉低  
		delay_us(20);           //延时 		
  }					 
  if(!ack)									//不需要发送
	{        
		AHT10_SDA_OUT();   //SDA线输出模式 
		AHT10_IIC_SDA_H;   //时钟脉冲的高电平期间保持稳定的高电平
		AHT10_IIC_SCL_H;   //SCL拉高
		delay_us(2); //延时
		AHT10_IIC_SCL_L;   //SCL拉低 
	}
	else							//需要发送
	{           
		AHT10_SDA_OUT();   //SDA线输出模式 
		AHT10_IIC_SDA_L;   //时钟脉冲的高电平期间保持稳定的低电平
		AHT10_IIC_SCL_H;   //SCL拉高
		delay_us(2); //延时
		AHT10_IIC_SCL_L;   //SCL拉低
		AHT10_IIC_SDA_H;   //SDA拉高
	}
  
	return receive;
}









/*-------------------------------------------------*/
/*函数名：向AHT10发送软复位命令                    */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void AHT10_Reset(void)
{
	AHT10_IIC_Start();                    //IIC开始信号
	AHT10_IIC_Send_Byte(0x70);            //发送器件地址+写操作	   	
	AHT10_IIC_Wait_Ack();                 //等待应答
  AHT10_IIC_Send_Byte(0xBA);            //发送复位命令 
	AHT10_IIC_Wait_Ack();	                //等待应答 
  AHT10_IIC_Stop();                     //停止信号
}

/*-------------------------------------------------*/
/*函数名：向AHT10发送读温湿度数据的命令            */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void AHT10_ReadData(void) 
{
	AHT10_IIC_Start();                    //IIC开始信号
	AHT10_IIC_Send_Byte(0x70);            //发送器件地址+写操作	   	
	AHT10_IIC_Wait_Ack();                 //等待应答
  AHT10_IIC_Send_Byte(0xAC);            //发送命令
	AHT10_IIC_Wait_Ack();	                //等待应答 
	AHT10_IIC_Send_Byte(0x33);            //发送数据	   	
	AHT10_IIC_Wait_Ack();                 //等待应答
  AHT10_IIC_Send_Byte(0x00);            //发送需要读数据的地址 
	AHT10_IIC_Wait_Ack();	                //等待数据 
  AHT10_IIC_Stop();                     //停止信号
}

/*-------------------------------------------------*/
/*函数名：读取AHT10的状态寄存器                    */
/*参  数：无                                       */
/*返回值：寄存器值                                 */
/*-------------------------------------------------*/
char AHT10_ReadStatus(void)
{
	char Status;
	
	AHT10_IIC_Start();                    //IIC开始信号
	AHT10_IIC_Send_Byte(0x71);            //发送器件地址+读操作
	AHT10_IIC_Wait_Ack();	                //等待应答 
	Status = AHT10_IIC_Read_Byte(0);      //读一字节数据，不发送ACK信号 
  AHT10_IIC_Stop();                     //停止信号

	return Status;                  //返回状态寄存器的值
}

/*-------------------------------------------------*/
/*函数名：查询工作模式和校准位正确与否             */
/*参  数：无                                       */
/*返回值：0正确 1失败                              */
/*-------------------------------------------------*/
char AHT10_Read_CalEnable(void)  
{
	char val = 0;
 
	val = AHT10_ReadStatus();  //读取状态寄存器
	if((val & 0x68)==0x08)     //判断工作模式和校准输出是否有效
		return 0;              //正确返回0
	else  
		return 1;              //失败返回1
}

/*-------------------------------------------------*/
/*函数名：初始化AHT10                              */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
char AHT10_Init(void)   
{	   
	char times;
	AHT10_IIC_Init();             //初始化IIC接口
	AHT10_IIC_Start();                    //IIC开始信号
	AHT10_IIC_Send_Byte(0x70);            //发送器件地址+写操作	   	
	AHT10_IIC_Wait_Ack();                 //等待应答
  AHT10_IIC_Send_Byte(0xE1);            //发送初始化命令 
	AHT10_IIC_Wait_Ack();	                //等待应答 
	AHT10_IIC_Send_Byte(0x08);            //发送数据	   	
	AHT10_IIC_Wait_Ack();                 //等待应答
  AHT10_IIC_Send_Byte(0x00);            //发送数据
	AHT10_IIC_Wait_Ack();	                //等待应答 
  AHT10_IIC_Stop();                     //停止信号
	delay_ms(500);                  //延时
	
	while(AHT10_Read_CalEnable()==1)   //查询工作模式和校准位正确与否 
	{   
		AHT10_Reset();                 //复位AHT10
		delay_ms(100);                 //延时

		AHT10_IIC_Send_Byte(0x70);           //发送器件地址+写操作	   	
		AHT10_IIC_Wait_Ack();                //等待应答
		AHT10_IIC_Send_Byte(0xE1);           //发送初始化命令 
		AHT10_IIC_Wait_Ack();	               //等待应答 
		AHT10_IIC_Send_Byte(0x08);           //发送数据	   	
		AHT10_IIC_Wait_Ack();                //等待应答
		AHT10_IIC_Send_Byte(0x00);           //发送数据
		AHT10_IIC_Wait_Ack();	               //等待应答 
		AHT10_IIC_Stop();                    //停止信号

		times++;	                   //重复次数+1
		delay_ms(500);                 //延时
		if(times>=10)return 1;         //重复此时超过10了，失败返回1
	}
	return 0;                          //正确返回0
}
/*-------------------------------------------------*/
/*函数名：读传感器数据                             */
/*参  数：temp 保存温度数据                        */
/*参  数：humi 保存湿度数据                        */
/*返回值：读到的数据                               */
/*-------------------------------------------------*/
void AHT10_Data(double *temp, double *humi)
{				  		
	int     tdata;
	char    Redata[6];
		
	AHT10_ReadData();                 //读数据
	delay_ms(500);                    //延迟	
	AHT10_IIC_Start();                      //IIC开始信号
	AHT10_IIC_Send_Byte(0x71);              //发送器件地址+读操作				   
	AHT10_IIC_Wait_Ack();	                  //等待应答
	Redata[0]=AHT10_IIC_Read_Byte(1);       //读一字节数据，发送ACK信号 
	Redata[1]=AHT10_IIC_Read_Byte(1);       //读一字节数据，发送ACK信号 
	Redata[2]=AHT10_IIC_Read_Byte(1);       //读一字节数据，发送ACK信号 
	Redata[3]=AHT10_IIC_Read_Byte(1);       //读一字节数据，发送ACK信号 
	Redata[4]=AHT10_IIC_Read_Byte(1);       //读一字节数据，发送ACK信号
	Redata[5]=AHT10_IIC_Read_Byte(0);       //读一字节数据，不发送ACK信号 	
  AHT10_IIC_Stop();                       //停止信号	
	delay_ms(5);                      //延迟
	
	tdata = (tdata|Redata[1])<<8;
	tdata = (tdata|Redata[2])<<8;
	tdata = (tdata|Redata[3]);
	tdata = (tdata >>4);
	*humi =  tdata*100.0/1024.0/1024.0;
	
	tdata = 0;
	tdata = (tdata|Redata[3])<<8;
	tdata = (tdata|Redata[4])<<8;
	tdata = (tdata|Redata[5]);
	tdata =  tdata&0xfffff;
	*temp =  tdata*200.0/1024.0/1024.0-50.0;
}


