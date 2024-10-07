/*
HC-SR505С�������Ӧģ��
1.c8t6һ���ò���PA15��PB3��PB4������SW��
2.5V����
3.�������������⵽��������ߵ�ƽ
  505�����������ƶ�������ǰ���Ƿ����ˣ����һ����һ������Ҳ�ǲ���������ġ�
  505���һ�θߵ�ƽ���ӳ�8s��30%��Ҳ����˵�����⵽һ���ƶ�����һֱ����ߵ�ƽ���������Ѿ����ˡ�����ӳ�ʱ���޷��ı䣬����502�����޸ġ�
4.ʹ�ã�����HC_SR505.h 
        ��ʼ��HC_SR505_Init();
*/

#include "HC_SR505.h"

void HC_SR505_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(HC_SR505_GPIO_CLK,ENABLE);//ʹ��PORTA
	GPIO_InitStructure.GPIO_Pin  = HC_SR505_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = HC_SR505_GPIO_Mode; //���ó���������
 	GPIO_Init(HC_SR505_GPIO_Port, &GPIO_InitStructure);
}
