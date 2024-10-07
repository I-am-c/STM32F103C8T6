#ifndef __TTP223_H
#define __TTP223_H

#include "stm32f10x.h"
#define TTP223_IN GPIO_ReadInputDataBit(TTP223_GPIO_Port, TTP223_GPIO_Pin)
#define TTP223_GPIO_CLK RCC_APB2Periph_GPIOB
#define TTP223_GPIO_Mode GPIO_Mode_IN_FLOATING  
#define TTP223_GPIO_Pin GPIO_Pin_7
#define TTP223_GPIO_Port GPIOB

void TTP223_Init(void);

#endif
