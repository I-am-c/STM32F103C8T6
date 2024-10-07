#ifndef __AHT10_H
#define __AHT10_H

#include "stm32f10x.h"  //������Ҫ��ͷ�ļ�
#include "delay.h" 	    //������Ҫ��ͷ�ļ�			 

#define AHT10_SDA_GPIO_Pin    GPIO_Pin_7
#define AHT10_SCL_GPIO_Pin    GPIO_Pin_6
#define AHT10_SDA_GPIO_Port   GPIOB
#define AHT10_SCL_GPIO_Port   GPIOB
#define AHT10_SDA_GPIO_CLK    RCC_APB2Periph_GPIOB
#define AHT10_SCL_GPIO_CLK    RCC_APB2Periph_GPIOB
  		   
#define AHT10_READ_SDA        GPIO_ReadInputDataBit(AHT10_SDA_GPIO_Port, AHT10_SDA_GPIO_Pin)       //��ȡSDA 
#define AHT10_IIC_SDA_OUT(x)  GPIO_WriteBit(AHT10_SDA_GPIO_Port, AHT10_SDA_GPIO_Pin, (BitAction)x) //����SDA��ƽ 

#define	AHT10_IIC_SCL_H    GPIO_SetBits(AHT10_SCL_GPIO_Port, AHT10_SCL_GPIO_Pin)    //SCL����
#define	AHT10_IIC_SDA_H    GPIO_SetBits(AHT10_SDA_GPIO_Port, AHT10_SDA_GPIO_Pin)    //SDA����

#define	AHT10_IIC_SCL_L    GPIO_ResetBits(AHT10_SCL_GPIO_Port, AHT10_SCL_GPIO_Pin)  //SCL����
#define	AHT10_IIC_SDA_L    GPIO_ResetBits(AHT10_SDA_GPIO_Port, AHT10_SDA_GPIO_Pin)  //SDA����

void AHT10_IIC_Init(void);
void AHT10_SDA_IN(void);
void AHT10_SDA_OUT(void);
void AHT10_IIC_Start(void);
void AHT10_IIC_Stop(void);
char AHT10_IIC_Wait_Ack(void);
void AHT10_IIC_Send_Byte(unsigned char);
unsigned char AHT10_IIC_Read_Byte(unsigned char);

void AHT10_Reset(void);
void AHT10_ReadData(void);
char AHT10_ReadStatus(void);
char AHT10_Read_CalEnable(void); 
char AHT10_Init(void);
void AHT10_Data(double *temp, double *humi);	

#endif
















