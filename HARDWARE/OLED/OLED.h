#ifndef __OLED_H
#define __OLED_H

#include "sys.h"

#define OLED_GPIO_Speed GPIO_Speed_50MHz
#define OLED_GPIO_Mode GPIO_Mode_Out_OD  
#define SDA_GPIO_Pin GPIO_Pin_9
#define SCL_GPIO_Pin GPIO_Pin_8
#define SDA_GPIO_Port GPIOB
#define SCL_GPIO_Port GPIOB
#define SDA_GPIO_CLK RCC_APB2Periph_GPIOB
#define SCL_GPIO_CLK RCC_APB2Periph_GPIOB

void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);

#endif
