/*
有源蜂鸣器（低电平触发）
1.c8t6一般用不了PA15、PB3、PB4（用作SW）
2.使用：引用beep.h 
        初始化Beep_Init();
        BEEP=0/1；
*/

#include "beep.h"

void Beep_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;   //初始化
	
  RCC_APB2PeriphClockCmd(BEEP_GPIO_CLK,ENABLE);
  GPIO_InitStructure.GPIO_Pin = BEEP_GPIO_Pin;
  GPIO_InitStructure.GPIO_Mode = BEEP_GPIO_Mode;        
  GPIO_InitStructure.GPIO_Speed = BEEP_GPIO_Speed;   //速度为50M
  GPIO_Init(BEEP_GPIO_Port, &GPIO_InitStructure);   //端口初始化
  
	GPIO_SetBits(BEEP_GPIO_Port,BEEP_GPIO_Pin);   //高电平
}

