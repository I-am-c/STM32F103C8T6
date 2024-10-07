/*
AHT10 
1306���� ���IIC
1.c8t6һ���ò���PA15��PB3��PB4������SW��
2.3.3V-5V����
3.ʹ�ã�����AHT10.h 
        ��ʼ��AHT10_Init();
				AHT10_Data(&temp,&humi);��ȡdouble������
*/

#include "AHT10.h"

/*-------------------------------------------------*/
/*����������ʼ��IIC�ӿ�                            */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void AHT10_IIC_Init(void)
{			
	GPIO_InitTypeDef  GPIO_InitStructure;                      //����һ������IO�ı���

	RCC_APB2PeriphClockCmd(AHT10_SDA_GPIO_CLK|AHT10_SCL_GPIO_CLK, ENABLE);    //ʹ��GPIOBʱ��
	GPIO_InitStructure.GPIO_Pin = AHT10_SDA_GPIO_Pin | AHT10_SCL_GPIO_Pin ;    //׼����������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;           //���������ʽ  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;          //IO����50M
	GPIO_Init(AHT10_SDA_GPIO_Port, &GPIO_InitStructure);
	GPIO_Init(AHT10_SCL_GPIO_Port, &GPIO_InitStructure);
	
	AHT10_IIC_SCL_H;   //SCL����
	AHT10_IIC_SDA_H;   //SDA����
}

/*-------------------------------------------------*/
/*��������SDA���ģʽ����                          */
/*��  ������                                       */
/*����ֵ����                                       */
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
/*��������SDA����ģʽ����                          */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void AHT10_SDA_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = AHT10_SDA_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(AHT10_SDA_GPIO_Port,&GPIO_InitStructure);
}

/*-------------------------------------------------*/
/*��������IIC��ʼ�ź�                              */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void AHT10_IIC_Start(void)
{
	AHT10_SDA_OUT();     //SDA�����ģʽ
  AHT10_IIC_SDA_H;	   //SDA����  
	AHT10_IIC_SCL_H;     //SCL����	  
	delay_us(4);   //��ʱ
 	AHT10_IIC_SDA_L;     //SCL�ߵ�ƽ��ʱ��SDA�ɸߵ��ͣ���ʼ�ź�
}
/*-------------------------------------------------*/
/*��������IICֹͣ�ź�                              */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void AHT10_IIC_Stop(void)
{
	AHT10_SDA_OUT();     //SDA�����ģʽ
	AHT10_IIC_SDA_L;     //SDA����
	AHT10_IIC_SCL_H;     //SCL����
 	delay_us(4);   //��ʱ
	AHT10_IIC_SDA_H;     //SCL�ߵ�ƽ��ʱ��SDA�ɵ͵��ߣ�����ֹͣ�ź�					   	
}
/*-------------------------------------------------*/
/*���������ȴ�Ӧ��                                 */
/*��  ������                                       */
/*����ֵ��0���ɹ�  1��ʧ��                         */
/*-------------------------------------------------*/
char AHT10_IIC_Wait_Ack(void)
{
	unsigned char timeout=0; //����һ�����������ڼ��㳬ʱʱ��
	
	AHT10_IIC_SDA_H;	             //SDA����
	AHT10_SDA_IN();                //SDA������ģʽ 
	AHT10_IIC_SCL_H;	             //SCL����
	 
	while(AHT10_READ_SDA){         //�ȴ�SDA��͵�ƽ����ʾӦ��������Ȼһֱwhileѭ����ֱ����ʱ	
		timeout++;           //��ʱ����+1
		if(timeout>250){     //�������250	
			AHT10_IIC_Stop();      //����ֹͣ�ź�
			return 1;        //����1����ʾʧ��
		}
		delay_us(2);         //��ʱ
	}
	AHT10_IIC_SCL_L;               //SCL����
	delay_us(20);            //��ʱ	
	return 0;                //����0����ʾ�ɹ�
} 	
/*-------------------------------------------------*/
/*������������һ���ֽ�                             */
/*��  ����txd�����͵��ֽ�                          */
/*����ֵ����                                       */
/*-------------------------------------------------*/ 			  
void AHT10_IIC_Send_Byte(unsigned char txd)
{                        
  unsigned char t;                   //����һ����������forѭ�� 
	
	AHT10_SDA_OUT(); 	                       //SDA�����ģʽ 
  AHT10_IIC_SCL_L;                         //SCL���ͣ���ʼ���ݴ���
  for(t=0;t<8;t++)                   //forѭ����һλһλ�ķ��ͣ������λ λ7��ʼ  
	{                                 
    AHT10_IIC_SDA_OUT(((txd&0x80)>>7));  //��SDA������
    txd<<=1; 	                   //����һλ��׼����һ�η���
		delay_us(2);                   //��ʱ
		AHT10_IIC_SCL_H;                     //SCL����
		delay_us(2);                   //��ʱ
		AHT10_IIC_SCL_L;	                   //SCL����
  }	 
} 	    
/*-------------------------------------------------*/
/*����������ȡһ���ֽ�                             */
/*��  ����ack���Ƿ���Ӧ�� 1:�� 0������           */
/*����ֵ����ȡ������                               */
/*-------------------------------------------------*/   
unsigned char AHT10_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i;           //����һ����������forѭ�� 
	unsigned char receive;     //����һ���������ڱ�����յ�������
		
	receive = 0;               //���receive��׼����������
	AHT10_SDA_IN();                  //SDA����Ϊ����
  AHT10_IIC_SCL_L;                 //SCL����
  delay_us(20);               //��ʱ	
	for(i=0;i<8;i++)           //forѭ����һλһλ�Ķ�ȡ	
	{           
		AHT10_IIC_SCL_H;             //SCL���� 
		delay_us(20);           //��ʱ
		receive<<=1;           //����һλ��׼���´εĶ�ȡ
		if(AHT10_READ_SDA)receive++; //��ȡ����
		delay_us(20);           //��ʱ
		AHT10_IIC_SCL_L;             //SCL����  
		delay_us(20);           //��ʱ 		
  }					 
  if(!ack)									//����Ҫ����
	{        
		AHT10_SDA_OUT();   //SDA�����ģʽ 
		AHT10_IIC_SDA_H;   //ʱ������ĸߵ�ƽ�ڼ䱣���ȶ��ĸߵ�ƽ
		AHT10_IIC_SCL_H;   //SCL����
		delay_us(2); //��ʱ
		AHT10_IIC_SCL_L;   //SCL���� 
	}
	else							//��Ҫ����
	{           
		AHT10_SDA_OUT();   //SDA�����ģʽ 
		AHT10_IIC_SDA_L;   //ʱ������ĸߵ�ƽ�ڼ䱣���ȶ��ĵ͵�ƽ
		AHT10_IIC_SCL_H;   //SCL����
		delay_us(2); //��ʱ
		AHT10_IIC_SCL_L;   //SCL����
		AHT10_IIC_SDA_H;   //SDA����
	}
  
	return receive;
}









/*-------------------------------------------------*/
/*����������AHT10������λ����                    */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void AHT10_Reset(void)
{
	AHT10_IIC_Start();                    //IIC��ʼ�ź�
	AHT10_IIC_Send_Byte(0x70);            //����������ַ+д����	   	
	AHT10_IIC_Wait_Ack();                 //�ȴ�Ӧ��
  AHT10_IIC_Send_Byte(0xBA);            //���͸�λ���� 
	AHT10_IIC_Wait_Ack();	                //�ȴ�Ӧ�� 
  AHT10_IIC_Stop();                     //ֹͣ�ź�
}

/*-------------------------------------------------*/
/*����������AHT10���Ͷ���ʪ�����ݵ�����            */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void AHT10_ReadData(void) 
{
	AHT10_IIC_Start();                    //IIC��ʼ�ź�
	AHT10_IIC_Send_Byte(0x70);            //����������ַ+д����	   	
	AHT10_IIC_Wait_Ack();                 //�ȴ�Ӧ��
  AHT10_IIC_Send_Byte(0xAC);            //��������
	AHT10_IIC_Wait_Ack();	                //�ȴ�Ӧ�� 
	AHT10_IIC_Send_Byte(0x33);            //��������	   	
	AHT10_IIC_Wait_Ack();                 //�ȴ�Ӧ��
  AHT10_IIC_Send_Byte(0x00);            //������Ҫ�����ݵĵ�ַ 
	AHT10_IIC_Wait_Ack();	                //�ȴ����� 
  AHT10_IIC_Stop();                     //ֹͣ�ź�
}

/*-------------------------------------------------*/
/*����������ȡAHT10��״̬�Ĵ���                    */
/*��  ������                                       */
/*����ֵ���Ĵ���ֵ                                 */
/*-------------------------------------------------*/
char AHT10_ReadStatus(void)
{
	char Status;
	
	AHT10_IIC_Start();                    //IIC��ʼ�ź�
	AHT10_IIC_Send_Byte(0x71);            //����������ַ+������
	AHT10_IIC_Wait_Ack();	                //�ȴ�Ӧ�� 
	Status = AHT10_IIC_Read_Byte(0);      //��һ�ֽ����ݣ�������ACK�ź� 
  AHT10_IIC_Stop();                     //ֹͣ�ź�

	return Status;                  //����״̬�Ĵ�����ֵ
}

/*-------------------------------------------------*/
/*����������ѯ����ģʽ��У׼λ��ȷ���             */
/*��  ������                                       */
/*����ֵ��0��ȷ 1ʧ��                              */
/*-------------------------------------------------*/
char AHT10_Read_CalEnable(void)  
{
	char val = 0;
 
	val = AHT10_ReadStatus();  //��ȡ״̬�Ĵ���
	if((val & 0x68)==0x08)     //�жϹ���ģʽ��У׼����Ƿ���Ч
		return 0;              //��ȷ����0
	else  
		return 1;              //ʧ�ܷ���1
}

/*-------------------------------------------------*/
/*����������ʼ��AHT10                              */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
char AHT10_Init(void)   
{	   
	char times;
	AHT10_IIC_Init();             //��ʼ��IIC�ӿ�
	AHT10_IIC_Start();                    //IIC��ʼ�ź�
	AHT10_IIC_Send_Byte(0x70);            //����������ַ+д����	   	
	AHT10_IIC_Wait_Ack();                 //�ȴ�Ӧ��
  AHT10_IIC_Send_Byte(0xE1);            //���ͳ�ʼ������ 
	AHT10_IIC_Wait_Ack();	                //�ȴ�Ӧ�� 
	AHT10_IIC_Send_Byte(0x08);            //��������	   	
	AHT10_IIC_Wait_Ack();                 //�ȴ�Ӧ��
  AHT10_IIC_Send_Byte(0x00);            //��������
	AHT10_IIC_Wait_Ack();	                //�ȴ�Ӧ�� 
  AHT10_IIC_Stop();                     //ֹͣ�ź�
	delay_ms(500);                  //��ʱ
	
	while(AHT10_Read_CalEnable()==1)   //��ѯ����ģʽ��У׼λ��ȷ��� 
	{   
		AHT10_Reset();                 //��λAHT10
		delay_ms(100);                 //��ʱ

		AHT10_IIC_Send_Byte(0x70);           //����������ַ+д����	   	
		AHT10_IIC_Wait_Ack();                //�ȴ�Ӧ��
		AHT10_IIC_Send_Byte(0xE1);           //���ͳ�ʼ������ 
		AHT10_IIC_Wait_Ack();	               //�ȴ�Ӧ�� 
		AHT10_IIC_Send_Byte(0x08);           //��������	   	
		AHT10_IIC_Wait_Ack();                //�ȴ�Ӧ��
		AHT10_IIC_Send_Byte(0x00);           //��������
		AHT10_IIC_Wait_Ack();	               //�ȴ�Ӧ�� 
		AHT10_IIC_Stop();                    //ֹͣ�ź�

		times++;	                   //�ظ�����+1
		delay_ms(500);                 //��ʱ
		if(times>=10)return 1;         //�ظ���ʱ����10�ˣ�ʧ�ܷ���1
	}
	return 0;                          //��ȷ����0
}
/*-------------------------------------------------*/
/*��������������������                             */
/*��  ����temp �����¶�����                        */
/*��  ����humi ����ʪ������                        */
/*����ֵ������������                               */
/*-------------------------------------------------*/
void AHT10_Data(double *temp, double *humi)
{				  		
	int     tdata;
	char    Redata[6];
		
	AHT10_ReadData();                 //������
	delay_ms(500);                    //�ӳ�	
	AHT10_IIC_Start();                      //IIC��ʼ�ź�
	AHT10_IIC_Send_Byte(0x71);              //����������ַ+������				   
	AHT10_IIC_Wait_Ack();	                  //�ȴ�Ӧ��
	Redata[0]=AHT10_IIC_Read_Byte(1);       //��һ�ֽ����ݣ�����ACK�ź� 
	Redata[1]=AHT10_IIC_Read_Byte(1);       //��һ�ֽ����ݣ�����ACK�ź� 
	Redata[2]=AHT10_IIC_Read_Byte(1);       //��һ�ֽ����ݣ�����ACK�ź� 
	Redata[3]=AHT10_IIC_Read_Byte(1);       //��һ�ֽ����ݣ�����ACK�ź� 
	Redata[4]=AHT10_IIC_Read_Byte(1);       //��һ�ֽ����ݣ�����ACK�ź�
	Redata[5]=AHT10_IIC_Read_Byte(0);       //��һ�ֽ����ݣ�������ACK�ź� 	
  AHT10_IIC_Stop();                       //ֹͣ�ź�	
	delay_ms(5);                      //�ӳ�
	
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


