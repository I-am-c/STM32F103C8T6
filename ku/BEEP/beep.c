/*
��Դ���������͵�ƽ������
1.c8t6һ���ò���PA15��PB3��PB4������SW��
2.ʹ�ã�����beep.h 
        ��ʼ��Beep_Init();
        BEEP=0/1��
*/

#include "beep.h"

void Beep_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;   //��ʼ��
	
  RCC_APB2PeriphClockCmd(BEEP_GPIO_CLK,ENABLE);
  GPIO_InitStructure.GPIO_Pin = BEEP_GPIO_Pin;
  GPIO_InitStructure.GPIO_Mode = BEEP_GPIO_Mode;        
  GPIO_InitStructure.GPIO_Speed = BEEP_GPIO_Speed;   //�ٶ�Ϊ50M
  GPIO_Init(BEEP_GPIO_Port, &GPIO_InitStructure);   //�˿ڳ�ʼ��
  
	GPIO_SetBits(BEEP_GPIO_Port,BEEP_GPIO_Pin);   //�ߵ�ƽ
}

