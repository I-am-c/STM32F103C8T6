/*
HC-SR505小型人体感应模块
1.c8t6一般用不了PA15、PB3、PB4（用作SW）
2.5V供电
3.数字量输出，检测到人体输出高电平
  505检测的是物体移动，不是前面是否有人，如果一个人一动不动也是不会检测出来的。
  505输出一次高电平会延迟8s±30%，也就是说如果检测到一次移动，会一直输出高电平，哪怕人已经走了。这个延迟时间无法改变，但是502可以修改。
4.使用：引用HC_SR505.h 
        初始化HC_SR505_Init();
*/

#include "HC_SR505.h"

void HC_SR505_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(HC_SR505_GPIO_CLK,ENABLE);//使能PORTA
	GPIO_InitStructure.GPIO_Pin  = HC_SR505_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = HC_SR505_GPIO_Mode; //设置成上拉输入
 	GPIO_Init(HC_SR505_GPIO_Port, &GPIO_InitStructure);
}
