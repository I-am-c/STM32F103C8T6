#ifndef __MQ2_H
#define __MQ2_H

#include "stm32f10x.h"

#define AO 1

#if AO
#include "math.h"
#include "delay.h"

void MQ2_Init(void);
uint16_t MQ2_adc_GetValue(void);
u16 MQ2_adc_Average(u8 times);
float MQ2_Getvalue(void);

#else
#define MQ2_value GPIO_ReadInputDataBit(MQ2_GPIO_Port,MQ2_GPIO_Pin)
#define MQ2_GPIO_Pin GPIO_Pin_7
#define MQ2_GPIO_Port GPIOB
#define MQ2_GPIO_CLK RCC_APB2Periph_GPIOB
#define MQ2_GPIO_Mode GPIO_Mode_IPU
void MQ2_Init(void);

#endif
	
#endif
