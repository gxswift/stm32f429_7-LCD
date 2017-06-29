/***
	***************************************************************************
	*	@file  	timer.c
	*	@brief   ��ʱ����ʼ�����ж�����
   ******************************************************************************
   *  
	* 
	* 
	* 
	***************************************************************************
***/
#include "timer.h"

// �������жϷ��鼰���ȼ�����
//
void NVIC_TimerConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//���� timer �ж�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

// ��������ʱ��4��ʼ��
//	������Period - ��ʱ������ֵ
//       frequency - ����Ƶ��
//	˵��������TIM4������APB1ʱ�����ϣ�����TIM4��ʱ��Ƶ��Ϊ90M����ʱ���ķ�Ƶϵ���� 1-65536 ֮�䣬
//			���Զ�ʱ����ʱ��Ƶ�ʷ�ΧΪ 90M - 1373 Hz����ʵ��Ӧ�������ȡ�ܱ�90M������Ƶ��ֵ��
//
void	TIM3_Init(u16 period,u32 frequency)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period = period; 	//����ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler= TimerClkAPB1 / frequency - 1;  //��Ƶϵ��
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��ʼ��
	
	NVIC_TimerConfig(); //�ж�����
	TIM_Cmd(TIM3,DISABLE); //ʹ�ܶ�ʱ��	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //�����ж�
	

	
}

