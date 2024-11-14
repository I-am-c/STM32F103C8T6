/*
HC-SR501人体红外传感器
1.c8t6一般用不了PA15、PB3、PB4（用作SW）
2.3.3V-5V供电
3.数字量输出，检测到人体靠近输出高电平
  501检测的是物体移动，不是前面是否有人，如果一个人一动不动也是不会检测出来的。
  501输出一次高电平的时间可以延迟
	501检测距离、延时时间和模式都可以调整
        初始化HC_SR501_Init();
*/

#include "HC_SR501.h"

void HC_SR501_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(HC_SR501_GPIO_CLK,ENABLE);//使能PORTA
	GPIO_InitStructure.GPIO_Pin  = HC_SR501_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = HC_SR501_GPIO_Mode; //设置成上拉输入
 	GPIO_Init(HC_SR501_GPIO_Port, &GPIO_InitStructure);
}

