/*
TTP223����������
1.c8t6һ���ò���PA15��PB3��PB4������SW��
2.3.3V-5V����
3.ʹ�ã�����TTP223.h 
        ��ʼ��TTP223_Init();
				TTP223_IN��ȡ�ߵ͵�ƽ������ʱΪ�ߵ�ƽ������ʱΪ�͵�ƽ
*/

#include "TTP223.h"

void TTP223_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(TTP223_GPIO_CLK,ENABLE);
	GPIO_InitStruct.GPIO_Mode = TTP223_GPIO_Mode;
	GPIO_InitStruct.GPIO_Pin = TTP223_GPIO_Pin;
	GPIO_Init(TTP223_GPIO_Port,&GPIO_InitStruct);
}

