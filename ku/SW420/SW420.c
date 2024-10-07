/*
震动开关SW-420 常闭型传感器
1.c8t6一般用不了PA15、PB3、PB4（用作SW）
2.3.3V-5V供电
3.数字量输出，不震动时输出低电平，指示灯亮
4.使用：引用SW420.h 
        初始化SW420_Init();
*/

#include "SW420.h"

void SW420_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(SW420_GPIO_CLK,ENABLE);//使能PORTA
	GPIO_InitStructure.GPIO_Pin  = SW420_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = SW420_GPIO_Mode; //设置成上拉输入
 	GPIO_Init(SW420_GPIO_Port, &GPIO_InitStructure);
}
