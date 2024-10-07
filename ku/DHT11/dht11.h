#ifndef _dht11_h
#define _dht11_h

#include "stm32f10x.h"   
#include "sys.h"
#include "delay.h"

#define DHT11_GPIO_CLK		RCC_APB2Periph_GPIOB
#define DHT11_GPIO_Pin    GPIO_Pin_7
#define DHT11_GPIO_Port   GPIOB

#define DHT11_DQ_IN       PBin(7)	  // ‰»Î
#define DHT11_DQ_OUT      PBout(7)  // ‰≥ˆ

void DHT11_IO_OUT(void);
void DHT11_IO_IN(void);
u8 DHT11_Init(void);
void DHT11_Reset(void);
u8 DHT11_Check(void);
u8 DHT11_Read_Bit(void);
u8 DHT11_Read_Byte(void);
u8 DHT11_Read_Data(u8 *humidityH,u8 *humidityL,u8 *temperatureH,u8 *temperatureL);    
 
#endif

