/*
DHT11��ʪ�ȴ�����
������ͨ��
1.c8t6һ���ò���PA15��PB3��PB4������SW��
2.3.3V-5V����
3.ʹ�ã�����dht11.h 
        ��ʼ��DHT11_Init();
				�������������������ʪ������
				      u8 humidityH;       //ʪ����������
              u8 humidityL;       //ʪ��С������
              u8 temperatureH;    //�¶���������
              u8 temperatureL;    //�¶�С������
*/

#include "dht11.h"

/*******************************************************************************
* �� �� ��         : DHT11_IO_OUT
* ��������		     : DHT11_IO�������	   
* ��    ��         : ��
* ��    ��         : ��
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
* �� �� ��         : DHT11_IO_IN
* ��������		     : DHT11_IO��������	   
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void DHT11_IO_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=DHT11_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(DHT11_GPIO_Port,&GPIO_InitStructure);
}

/*******************************************************************************
* �� �� ��         : DHT11_Reset
* ��������		     : ��λDHT11
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void DHT11_Reset(void)	   
{                 
	DHT11_IO_OUT(); 		//����io��Ϊ���ģʽ
  DHT11_DQ_OUT=0; 		//����DQ
  delay_ms(20);    		//��������18ms
	DHT11_DQ_OUT=1; 		//DQ=1 
  delay_us(30);     	//��������20~40us
}

/*******************************************************************************
* �� �� ��         : DHT11_Check
* ��������		     : ���DHT11�Ƿ����
* ��    ��         : ��
* ��    ��         : 1:δ��⵽DHT11�Ĵ��ڣ�0:����
*******************************************************************************/
u8 DHT11_Check(void) 	   
{   
	u8 retry=0;
	DHT11_IO_IN();//SET PG11 INPUT	 
	
	while (DHT11_DQ_IN&&retry<100)//�ߵ�ƽѭ�����͵�ƽ����
	{
		retry++;
		delay_us(1);
	};
	
	if(retry>=100)
		return 1;
	else 
		retry=0;
	
	while (!DHT11_DQ_IN&&retry<100)//DHT11���ͺ���ٴ�����40~50us
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)
		return 1;	 
	
	return 0;
}

/*******************************************************************************
* �� �� ��         : DHT11_Init()
* ��������		     : DHT11��ʼ�� 
* ��    ��         : ��
* ��    ��         : ����0����ʼ���ɹ���1��ʧ��
*******************************************************************************/
u8 DHT11_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
	RCC_APB2PeriphClockCmd(DHT11_GPIO_CLK,ENABLE);
 
	GPIO_InitStructure.GPIO_Pin=DHT11_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(DHT11_GPIO_Port,&GPIO_InitStructure);
	GPIO_SetBits(DHT11_GPIO_Port,DHT11_GPIO_Pin);	   //����
 
	DHT11_Reset();	  
	return DHT11_Check();	
}
 
/*******************************************************************************
* �� �� ��         : DHT11_Read_Bit(void) 
* ��������		     : ��DHT11��ȡһ��λ
* ��    ��         : ��
* ��    ��         :����ֵ��1/0
*******************************************************************************/
u8 DHT11_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(DHT11_DQ_IN&&retry<100)//�ȴ���Ϊ�͵�ƽ 12-14us ��ʼ
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT11_DQ_IN&&retry<100)//�ȴ���ߵ�ƽ	 26-28us��ʾ0,116-118us��ʾ1
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);//�ȴ�40us
	if(DHT11_DQ_IN)
		return 1;
	else 
		return 0;		   
}

/*******************************************************************************
* �� �� ��         : DHT11_Read_Byte(void��
* ��������		     : ��DHT11��ȡһ���ֽ�
* ��    ��         : ��
* ��    ��         :����ֵ������������
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
* �� �� ��         : DHT11_Read_Data(u8 *temp,u8 *humi) 
* ��������		     : ��DHT11��ȡһ������
* ��    ��         : humidityH\humidityL\temperatureH\temperatureL
* ��    ��         : ����ֵ��0,����;1,��ȡʧ��
*******************************************************************************/
u8 DHT11_Read_Data(u8 *humidityH,u8 *humidityL,u8 *temperatureH,u8 *temperatureL)    
{        
 	u8 buf[5];
	u8 i;
	DHT11_Reset();
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)//��ȡ40λ����
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


 