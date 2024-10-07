/*
MQ2�������� 
AO��ģ��������   DO�ڸߵ͵�ƽ���������ȾΪ1��
��һ��ʹ��ҪԤ�Ⱥܾã�����Сʱ��
ͨ���Ԥ��2����
1.AO����ADCͨ��
2.5V����
3.ʹ�ã�����MQ2.h 
        AO:��ʼ��OLED_Init();
				   ��ʼ��delay_init();
           float quality;
				   quality=MQ2_Getvalue();
				DO:MQ2_value=0����������
*/

#include "MQ2.h"

#if AO
/*��ʼ��MQ2*/
void MQ2_Init(void)
{
	ADC_InitTypeDef  ADC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);        //ʹ��ADC1ͨ��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);        //ʹ��GPIOAͨ��ʱ��
    
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);    //����ADC��Ƶ��������Ϊ6��Ƶ
    
  //����ṹ��
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;        //ģ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;        //GPIOA.0����
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //�ٶ�50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);        //��ʼ��gpioa
    
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);//ADC1,ͨ��0(GPIOA.0)������˳��Ϊ1����������Ϊ55.5������
    
  //����ADC�ṹ��
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;        //��ͨ��ģʽ    
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;        //����ת��ģʽ    
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        //ADC����ģʽ
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;        //ADC�����Ҷ���
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;        //ת�����������
  ADC_InitStructure.ADC_NbrOfChannel = 1;        //˳����й���ת����ADCͨ����Ŀ
  ADC_Init(ADC1, &ADC_InitStructure);        //��ʼ��ADC1����
    
  ADC_Cmd(ADC1, ENABLE);        //ʹ��ADC1
    
  ADC_ResetCalibration(ADC1);        //������λУ׼
  while (ADC_GetResetCalibrationStatus(ADC1) == SET);        //�ȴ���λУ׼����
  ADC_StartCalibration(ADC1);        //����ADУ׼
  while (ADC_GetCalibrationStatus(ADC1) == SET);        //�ȴ�У׼����
}

uint16_t MQ2_adc_GetValue(void)
{
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);        //ʹ�����ת������
  while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);        //�ȴ�ת������
  return ADC_GetConversionValue(ADC1);        //�������һ��ADC1�������ת�����
}

//ȡƽ��ֵ
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

//������ֵ
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
 
 	RCC_APB2PeriphClockCmd(MQ2_GPIO_CLK,ENABLE);//ʹ��PORTA
	GPIO_InitStructure.GPIO_Pin  = MQ2_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = MQ2_GPIO_Mode; //���ó���������
 	GPIO_Init(MQ2_GPIO_Port, &GPIO_InitStructure);
}

#endif
