/*
HC_SR04���������ģ�� 
1.c8t6һ���ò���PA15��PB3��PB4������SW��
2.3.3V-5V����
3.ʹ�ã�����HC_SR04.h 
        ��ʼ��HC_SR04_Init();
				�����������޸��жϼ���ʱ����
				(float) length����Get_Length();
4.���ܴ��ڿ���bug
*/

#include "HC_SR04.h"

uint16_t mscount=0;

//HC_SR04��ʼ��
void HC_SR04_Init(void)
{
	GPIO_InitTypeDef GPIOinitStructure;
	TIM_TimeBaseInitTypeDef TIMInitStructure;
	NVIC_InitTypeDef NVICinitStructure;
		
	//1.ʹ��GPIOʱ�ӡ���ʱ��ʱ��
	RCC_APB2PeriphClockCmd(HC_SR04_GPIO_CLK, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	//2.����GPIO
		
	//Trig 
	GPIOinitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIOinitStructure.GPIO_Pin   = Trig_GPIO_Pin;
	GPIOinitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Trig_GPIO_Port, &GPIOinitStructure);
	
	//Echo 
  GPIOinitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIOinitStructure.GPIO_Pin   = Echo_GPIO_Pin;
	GPIO_Init(Echo_GPIO_Port, &GPIOinitStructure);
		
	//3.����TIM
	TIMInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIMInitStructure.TIM_CounterMode   = TIM_CounterMode_Up;
	TIMInitStructure.TIM_Period        = 1000-1;
	TIMInitStructure.TIM_Prescaler     = 72-1;
		
	TIM_TimeBaseInit(TIM4, &TIMInitStructure);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM4, DISABLE);
		
	//�����ж����ȼ�
	NVICinitStructure.NVIC_IRQChannel                   = TIM4_IRQn;
	NVICinitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVICinitStructure.NVIC_IRQChannelSubPriority        = 0;
	NVICinitStructure.NVIC_IRQChannelCmd                = ENABLE;
		
	NVIC_Init(&NVICinitStructure);
}

void TIM4_Open(void)
{
		TIM_SetCounter(TIM4, 0);
		mscount=0;
		TIM_Cmd(TIM4, ENABLE);
}

void TIM4_Close(void)
{
		TIM_Cmd(TIM4, DISABLE);
}

void TIM4_IRQHandler(void)
{
		if( TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET )
		{
				TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
			
				mscount++;
		}
}

int Get_Echo_TIM(void)
{
		uint32_t t=0;
		
		t=mscount*1000;
		t+=TIM_GetCounter(TIM4);
		
		TIM4->CNT = 0;
		
		delay_us(50);
		
		return t;
}

float Get_Length(void)
{
	uint32_t t=0;
	float length=0;
		
	Trig_Send_Open;
	delay_us(40);
	Trig_Send_Close;		
	while( Echo_Receive == 0 );
	TIM4_Open();		
	while( Echo_Receive == 1 );
	TIM4_Close();
	t=Get_Echo_TIM();
	length=((float) t/58.0);

	return length;
}

