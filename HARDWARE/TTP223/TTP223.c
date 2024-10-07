/*
TTP223触摸传感器
1.c8t6一般用不了PA15、PB3、PB4（用作SW）
2.3.3V-5V供电
3.使用：引用TTP223.h 
        初始化TTP223_Init();
				TTP223_IN读取高低电平，触摸时为高电平，其余时为低电平
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

