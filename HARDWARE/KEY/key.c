/*
4按键组  
1.c8t6一般用不了PA15、PB3、PB4（用作SW）
2.3.3V-5V供电
3.使用：引用key.h 
        初始化KEY_Init();
				int keynum;
        void Key_task(void)
        {
	        keynum=KEY_Scan();
	        if(keynum==1) //切换显示界面
        }
*/

#include "key.h"		

//按键初始化
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(KEY_GPIO_CLK,ENABLE);//使能PORTA
	GPIO_InitStructure.GPIO_Pin  = KEY1_GPIO_Pin|KEY2_GPIO_Pin|KEY3_GPIO_Pin|KEY4_GPIO_Pin;//KEY0-KEY3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(KEY_GPIO_Port, &GPIO_InitStructure);//初始化
}

//按键扫描
u8 KEY_Scan(void)
{	 
	if(KEY0==0){delay_ms(10);while(KEY0==0){};return KEY0_PRES;}
	if(KEY1==0){delay_ms(10);while(KEY1==0){};return KEY1_PRES;}
	if(KEY2==0){delay_ms(10);while(KEY2==0){};return KEY2_PRES;}
	if(KEY3==0){delay_ms(10);while(KEY3==0){};return KEY3_PRES;}
	else return 0;// 无按键按下
}

