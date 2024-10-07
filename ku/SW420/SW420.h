#ifndef __SW420_H
#define __SW420_H

#include "sys.h"
#define SW420 GPIO_ReadInputDataBit(SW420_GPIO_Port,SW420_GPIO_Pin)
#define SW420_GPIO_Pin GPIO_Pin_7
#define SW420_GPIO_Port GPIOB
#define SW420_GPIO_CLK RCC_APB2Periph_GPIOB
#define SW420_GPIO_Mode GPIO_Mode_IPU

void SW420_Init(void);

#endif
