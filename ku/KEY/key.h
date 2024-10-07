#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
#include "delay.h"

#define KEY_GPIO_CLK    RCC_APB2Periph_GPIOB
#define KEY1_GPIO_Pin   GPIO_Pin_12
#define KEY2_GPIO_Pin   GPIO_Pin_13
#define KEY3_GPIO_Pin   GPIO_Pin_14
#define KEY4_GPIO_Pin   GPIO_Pin_15
#define KEY_GPIO_Port   GPIOB

#define KEY0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//��ȡ����2 
#define KEY3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//��ȡ����3

#define KEY0_PRES 	1	//KEY0����
#define KEY1_PRES	  2	//KEY1����
#define KEY2_PRES	  3	//KEY2����
#define KEY3_PRES   4	//KEY3����

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(void);  	//����ɨ�躯��	

#endif
