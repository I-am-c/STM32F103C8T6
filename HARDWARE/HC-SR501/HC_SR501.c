/*
HC-SR501������⴫����
1.c8t6һ���ò���PA15��PB3��PB4������SW��
2.3.3V-5V����
3.�������������⵽���忿������ߵ�ƽ
  501�����������ƶ�������ǰ���Ƿ����ˣ����һ����һ������Ҳ�ǲ���������ġ�
  501���һ�θߵ�ƽ��ʱ������ӳ�
	501�����롢��ʱʱ���ģʽ�����Ե���
        ��ʼ��HC_SR501_Init();
*/

#include "HC_SR501.h"

void HC_SR501_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(HC_SR501_GPIO_CLK,ENABLE);//ʹ��PORTA
	GPIO_InitStructure.GPIO_Pin  = HC_SR501_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = HC_SR501_GPIO_Mode; //���ó���������
 	GPIO_Init(HC_SR501_GPIO_Port, &GPIO_InitStructure);
}

