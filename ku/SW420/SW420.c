/*
�𶯿���SW-420 �����ʹ�����
1.c8t6һ���ò���PA15��PB3��PB4������SW��
2.3.3V-5V����
3.���������������ʱ����͵�ƽ��ָʾ����
4.ʹ�ã�����SW420.h 
        ��ʼ��SW420_Init();
*/

#include "SW420.h"

void SW420_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(SW420_GPIO_CLK,ENABLE);//ʹ��PORTA
	GPIO_InitStructure.GPIO_Pin  = SW420_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = SW420_GPIO_Mode; //���ó���������
 	GPIO_Init(SW420_GPIO_Port, &GPIO_InitStructure);
}
