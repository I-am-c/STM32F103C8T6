#ifndef __RES_H
#define __RES_H

#include "sys.h"
#define RES GPIO_ReadInputDataBit(RES_GPIO_Port,RES_GPIO_Pin)
#define RES_GPIO_Pin GPIO_Pin_7
#define RES_GPIO_Port GPIOB
#define RES_GPIO_CLK RCC_APB2Periph_GPIOB
#define RES_GPIO_Mode GPIO_Mode_IPU

void Res_Init(void);

#endif
