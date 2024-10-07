#ifndef __BEEP_H
#define __BEEP_H
#include "stm32f10x.h"
#include "sys.h"

#define BEEP PBout(7)
#define BEEP_GPIO_Pin GPIO_Pin_7
#define BEEP_GPIO_Mode GPIO_Mode_Out_PP   //ÍÆÍìÊä³ö
#define BEEP_GPIO_Port GPIOB
#define BEEP_GPIO_Speed GPIO_Speed_50MHz
#define BEEP_GPIO_CLK RCC_APB2Periph_GPIOB

void Beep_Init(void);

#endif
