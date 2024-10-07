#ifndef __MQ135_H
#define __MQ135_H

#include "stm32f10x.h"

#define AO 0

#if AO
#include "math.h"
#include "delay.h"

void MQ135_Init(void);
uint16_t MQ135_adc_GetValue(void);
u16 MQ135_adc_Average(u8 times);
float MQ135_Getvalue(void);

#else
#define MQ135_value GPIO_ReadInputDataBit(MQ135_GPIO_Port,MQ135_GPIO_Pin)
#define MQ135_GPIO_Pin GPIO_Pin_7
#define MQ135_GPIO_Port GPIOB
#define MQ135_GPIO_CLK RCC_APB2Periph_GPIOB
#define MQ135_GPIO_Mode GPIO_Mode_IPU
void MQ135_Init(void);

#endif
	
#endif
