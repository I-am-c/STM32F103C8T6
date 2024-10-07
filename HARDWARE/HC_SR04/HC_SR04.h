#ifndef __HC_SR04_H
#define __HC_SR04_H
#include "stm32f10x.h"
#include "delay.h"

#define HC_SR04_GPIO_CLK RCC_APB2Periph_GPIOB
#define Trig_GPIO_Pin    GPIO_Pin_7
#define Trig_GPIO_Port   GPIOB
#define Echo_GPIO_Pin    GPIO_Pin_6
#define Echo_GPIO_Port   GPIOB

#define	Trig_Send_Open GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define	Trig_Send_Close GPIO_ResetBits(GPIOB, GPIO_Pin_7) 
#define Echo_Receive GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)

void HC_SR04_Init(void);
float Get_Length(void);
void TIM4_Open(void);
void TIM4_Close(void);
int Get_Echo_TIM(void);

#endif
