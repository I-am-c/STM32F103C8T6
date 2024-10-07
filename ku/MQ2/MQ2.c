/*
MQ2烟雾传感器 
AO口模拟量采样   DO口高低电平输出（无污染为1）
第一次使用要预热很久（几个小时）
通电后预热2分钟
1.AO采用ADC通道
2.5V供电
3.使用：引用MQ2.h 
        AO:初始化OLED_Init();
				   初始化delay_init();
           float quality;
				   quality=MQ2_Getvalue();
				DO:MQ2_value=0空气质量差
*/

#include "MQ2.h"

#if AO
/*初始化MQ2*/
void MQ2_Init(void)
{
	ADC_InitTypeDef  ADC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);        //使能ADC1通道时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);        //使能GPIOA通道时钟
    
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);    //设置ADC分频因子这里为6分频
    
  //定义结构体
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;        //模拟输入
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;        //GPIOA.0引脚
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //速度50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化gpioa
    
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);//ADC1,通道0(GPIOA.0)，采样顺序为1，采样周期为55.5个周期
    
  //定义ADC结构体
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;        //单通道模式    
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;        //单次转换模式    
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC独立模式
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC数据右对齐
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //转换由软件启动
  ADC_InitStructure.ADC_NbrOfChannel = 1;        //顺序进行规则转换的ADC通道数目
  ADC_Init(ADC1, &ADC_InitStructure);        //初始化ADC1外设
    
  ADC_Cmd(ADC1, ENABLE);        //使能ADC1
    
  ADC_ResetCalibration(ADC1);        //开启复位校准
  while (ADC_GetResetCalibrationStatus(ADC1) == SET);        //等待复位校准结束
  ADC_StartCalibration(ADC1);        //开启AD校准
  while (ADC_GetCalibrationStatus(ADC1) == SET);        //等待校准结束
}

uint16_t MQ2_adc_GetValue(void)
{
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);        //使能软件转换功能
  while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);        //等待转换结束
  return ADC_GetConversionValue(ADC1);        //返回最近一次ADC1规则组的转换结果
}

//取平均值
u16 MQ2_adc_Average(u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=MQ2_adc_GetValue();
		delay_ms(5);
	}
	return temp_val/times;
} 	

//计算数值
float MQ2_Getvalue(void)
{
	u16 adcx;
  float temp;
  float quality;
	
	adcx=MQ2_adc_Average(10);
	temp=(float)adcx*(3.3/4096);
	quality=pow(11.5428 * 35.904 * temp/(25.5-5.1* temp),0.6549);

	return quality;
}
	
#else
void MQ2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(MQ2_GPIO_CLK,ENABLE);//使能PORTA
	GPIO_InitStructure.GPIO_Pin  = MQ2_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = MQ2_GPIO_Mode; //设置成上拉输入
 	GPIO_Init(MQ2_GPIO_Port, &GPIO_InitStructure);
}

#endif
