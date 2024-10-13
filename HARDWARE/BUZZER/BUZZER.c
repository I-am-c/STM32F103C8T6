/*
无源蜂鸣器  
PWM控制
1.c8t6一般用不了PA15、PB3、PB4（用作SW）
2.3.3V-5V供电
3.使用：引用BUZZER.h 
        初始化 TIM3_PWM_Init(14399,10);
        播放音乐 musicPlay
*/

#include "BUZZER.h"

void TIM3_PWM_Init(u16 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStr;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能定时器3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO ,ENABLE);//RCC_APB2Periph_AFIO 
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);//TIM3部分重映射
	
	GPIO_InitStr.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStr.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStr.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStr);//初始化GPIO
	
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;//设置时钟分割
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInitStrue.TIM_Period=arr;//自动重装载值
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc;// 预分频值
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStrue);//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM2;//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStruct.TIM_OCNPolarity=TIM_OCPolarity_Low;//输出极性:TIM输出比较极性低
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStruct.TIM_Pulse=0;
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);//根据T指定的参数初始化外设TIM3 OC2
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);//使能TIM3在CCR2上的预装载寄存器
	TIM_ARRPreloadConfig(TIM3,ENABLE);//使能TIM3在ARR上的预装载寄存器
	TIM_Cmd(TIM3,ENABLE);//使能TIM3
}

//蜂鸣器停止发声
void buzzerQuiet(void)
{
    GPIO_InitTypeDef GPIO_InitStr;
    TIM_Cmd(TIM3,DISABLE);//不使能TIM3

    GPIO_InitStr.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStr.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStr.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStr);//初始化GPIO
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);//PB.5输出低
}

//蜂鸣器发出指定频率声音
void buzzerSound(unsigned short usFrep)
{
    GPIO_InitTypeDef GPIO_InitStr;
    unsigned long ulVal;
	if((usFrep<=8000000/65536UL)||(usFrep>20000))
	{
	    buzzerQuiet();//静音
	}
    else
	{
		GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);//TIM3部分重映射
	
	    GPIO_InitStr.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	    GPIO_InitStr.GPIO_Pin=GPIO_Pin_5;
	    GPIO_InitStr.GPIO_Speed=GPIO_Speed_50MHz;
        GPIO_Init(GPIOB,&GPIO_InitStr);//初始化GPIO
        ulVal=8000000/usFrep;
        TIM3->ARR=ulVal;//设置自动重装载寄存器周期的值（音调）
        TIM_SetCompare2(TIM3,ulVal/2);//设置比较值，调节占空比（音量）
        TIM_Cmd(TIM3,ENABLE);//使能TIM3
	 }
}

//定义乐曲
const tNote MyScore[]=
{
	//纸短情长
{L5,T/2},
{M3,T/8},{M3,T/8},{M3,T/8},{M2,T/8},{M3,T/8},{M1,T/8},{0,T/8},{M2,T/8},
{M2,T/8},{M2,T/8},{M2,T/8},{M1,T/8},{M2,T/8},{M5,T/8},{0,T/4},
{M1,T/8},{M1,T/8},{M1,T/8},{L6,T/8},{M1,T/8},{L6,T/8},{0,T/8},{L5,T/8},

{M2,T/8},{M2,T/8},{M2,T/8},{M3,T/8},{L6,T/8},{L5,T/8},{0,T/4},
{M3,T/8},{M3,T/8},{M3,T/8},{M2,T/8},{M3,T/8},{M1,T/8},{0,T/8},{M2,T/8},
{M2,T/8},{M2,T/8},{M2,T/8},{M1,T/8},{M2,T/8},{M5,T/8},{0,T/4},
{M1,T/16},{M1,T/16},{M1,T/16},{M1,T/16},{M1,T/16},{M1,T/8+T/16},{0,T/2},

{M3,T/8},{M2,T/8},{M2,T/8},{M1,T/8},{M1,T/2},
{0,T/2},{0,T/8},{M1,T/8},{M1,T/8},{M2,T/8},
{M3,T/4},{M3,T/8},{M3,T/8},{0,T/8},{M3,T/8},{M2,T/8},{M1,T/8},
{L7,T/4},{M6,T/8},{M5,T/8},{0,T/8},{M5,T/8},{M6,T/8},{M7,T/8},

{H1,T/8},{M3,T/8},{M3,T/8},{M3,T/8},{0,T/8},{H1,T/8},{M7,T/8},{H1,T/8},
{M7,T/8},{M3,T/8},{M3,T/8},{M5,T/8},{0,T/4},{M5,T/8},{M6,T/8},
{H1,T/8},{M6,T/8},{M6,T/8},{M6,T/8},{0,T/8},{M6,T/8},{M5,T/8},{M3,T/8},
{M5,T/8},{M3,T/8},{0,T/8},{M2,T/8},{M1,T/4},{0,T/8},{L6,T/16},{M1,T/16},

{M3,T/8},{M2,T/8},{M2,T/8},{M1,T/8},{M2,T/8},{M5,T/8},{M5,T/8},{M1,T/8},
{M2,T/2},{0,T/2},
{M5,T},
{0,T/2},{0,T/8},{M1,T/8},{M1,T/8},{M2,T/8},
{M3,T/8},{M3,T/8},{M2,T/8},{M3,T/8},{0,T/8},{M3,T/8},{M2,T/8},{M1,T/8},

{M5,T/8},{M5,T/8},{M3,T/8},{M5,T/8},{0,T/8},{M5,T/8},{M6,T/8},{M7,T/8},
{H1,T/8},{H1,T/8},{H1,T/8},{H1,T/8},{H1,T/8},{M7,T/8},{M6,T/8},{M7,T/8},
{M6,T/8},{M3,T/8},{M3,T/8},{M5,T/8},{0,T/4},{M5,T/8},{M6,T/8},
{H1,T/8},{M6,T/8},{M6,T/8},{M6,T/8},{0,T/8},{M6,T/8},{M5,T/8},{M3,T/8},

{M5,T/8},{M3,T/8},{M3,T/8},{M2,T/8},{M1,T/8},{0,T/8},{L6,T/16},{M1,T/16},
{M1,T/2},{0,T/2},

{0,T},

{M1,T/2},{0,T/8},{M1,T/8},{M1,T/8},{M2,T/8},
{M3,T/4},{M3,T/8},{M3,T/8},{0,T/8},{M3,T/8},{M2,T/8},{M1,T/8},
{L7,T/4},{M6,T/8},{M5,T/8},{0,T/8},{M5,T/8},{M6,T/8},{M7,T/8},
{H1,T/8},{M3,T/8},{M3,T/8},{M3,T/8},{0,T/8},{H1,T/8},{M7,T/8},{H1,T/8},

{M7,T/8},{M3,T/8},{M3,T/8},{M5,T/8},{0,T/4},{M5,T/8},{M6,T/8},
{H1,T/8},{M6,T/8},{M6,T/8},{M6,T/8},{0,T/8},{M6,T/8},{M5,T/8},{M3,T/8},
{M5,T/8},{M3,T/8},{M3,T/8},{M2,T/8},{M1,T/4},{0,T/8},{L6,T/16},{M1,T/16},
{M3,T/8},{M2,T/8},{M2,T/8},{M1,T/8},{M2,T/8},{M5,T/8},{M5,T/8},{M1,T/8},

{M2,T/2},{0,T/8},{M1,T/8},{M1,T/8},{M2,T/8},
{M3,T/8},{M3,T/8},{M2,T/8},{M3,T/8},{0,T/8},{M3,T/8},{M2,T/8},{M1,T/8},
{M5,T/8},{M5,T/8},{M3,T/8},{M5,T/8},{0,T/8},{M5,T/8},{M6,T/8},{M7,T/8},
{H1,T/8},{H1,T/8},{H1,T/8},{H1,T/8},{H1,T/8},{M7,T/8},{M6,T/8},{M7,T/8},

{M6,T/8},{M3,T/8},{M3,T/8},{M5,T/8},{0,T/4},{M5,T/8},{M6,T/8},
{H1,T/8},{M6,T/8},{M6,T/8},{M6,T/8},{0,T/8},{M6,T/8},{M5,T/8},{M3,T/8},
{M5,T/8},{M3,T/8},{M3,T/8},{M2,T/8},{M1,T/4},{0,T/8},{L6,T/16},{M1,T/16},
{M3,T/8},{M2,T/8},{M2,T/8},{M1,T/8},{M2,T/8},{M1,T/8},{M1,T/8},{L6,T/8},

{M1,T/2},{0,T/4},{0,T/8},{L6,T/16},{M1,T/16},
{M3,T/8},{M2,T/8},{M2,T/4},{0,T/4},{0,T/8},{M2,T/16},{M1,T/16},
{M2,T/8+T/16},{M1,T/16},{M1,T/4},{0,T/4},{0,T/8},{L6,T/8},
{M1,T/2},{0,T/2},
             
{0, 0} //结束
};


//演奏乐曲
void musicPlay(void)
{
	u8 i=0;
	while(1)
	{
	    if(MyScore[i].mTime==0)break;
        buzzerSound(MyScore[i].mName);
        delay_ms(MyScore[i].mTime);
        i++;
        buzzerQuiet();
        delay_ms(10);
	}
}
