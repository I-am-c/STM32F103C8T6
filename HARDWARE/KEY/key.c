/*
4������  
1.c8t6һ���ò���PA15��PB3��PB4������SW��
2.3.3V-5V����
3.ʹ�ã�����key.h 
        ��ʼ��KEY_Init();
				int keynum;
        void Key_task(void)
        {
	        keynum=KEY_Scan();
	        if(keynum==1) //�л���ʾ����
        }
*/

#include "key.h"		

//������ʼ��
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(KEY_GPIO_CLK,ENABLE);//ʹ��PORTA
	GPIO_InitStructure.GPIO_Pin  = KEY1_GPIO_Pin|KEY2_GPIO_Pin|KEY3_GPIO_Pin|KEY4_GPIO_Pin;//KEY0-KEY3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(KEY_GPIO_Port, &GPIO_InitStructure);//��ʼ��
}

//����ɨ��
u8 KEY_Scan(void)
{	 
	if(KEY0==0){delay_ms(10);while(KEY0==0){};return KEY0_PRES;}
	if(KEY1==0){delay_ms(10);while(KEY1==0){};return KEY1_PRES;}
	if(KEY2==0){delay_ms(10);while(KEY2==0){};return KEY2_PRES;}
	if(KEY3==0){delay_ms(10);while(KEY3==0){};return KEY3_PRES;}
	else return 0;// �ް�������
}

