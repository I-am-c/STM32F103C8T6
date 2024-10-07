/*
光敏电阻模块
1.c8t6一般用不了PA15、PB3、PB4（用作SW）
2.3.3V-5V供电
3.数字量输出，光强输出低电平，光弱输出高电平
4.使用：引用res.h 
        初始化Res_Init();
*/

#include "res.h"

void Res_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RES_GPIO_CLK,ENABLE);//使能PORTA
	GPIO_InitStructure.GPIO_Pin  = RES_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = RES_GPIO_Mode; //设置成上拉输入
 	GPIO_Init(RES_GPIO_Port, &GPIO_InitStructure);
}
