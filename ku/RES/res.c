/*
��������ģ��
1.c8t6һ���ò���PA15��PB3��PB4������SW��
2.3.3V-5V����
3.�������������ǿ����͵�ƽ����������ߵ�ƽ
4.ʹ�ã�����res.h 
        ��ʼ��Res_Init();
*/

#include "res.h"

void Res_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RES_GPIO_CLK,ENABLE);//ʹ��PORTA
	GPIO_InitStructure.GPIO_Pin  = RES_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = RES_GPIO_Mode; //���ó���������
 	GPIO_Init(RES_GPIO_Port, &GPIO_InitStructure);
}
