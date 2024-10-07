#ifndef __HC_SR505_H
#define __HC_SR505_H

#include "sys.h"
#define HC_SR505 GPIO_ReadInputDataBit(HC_SR505_GPIO_Port,HC_SR505_GPIO_Pin)
#define HC_SR505_GPIO_Pin GPIO_Pin_7
#define HC_SR505_GPIO_Port GPIOB
#define HC_SR505_GPIO_CLK RCC_APB2Periph_GPIOB
#define HC_SR505_GPIO_Mode GPIO_Mode_IPD

void HC_SR505_Init(void);

#endif
