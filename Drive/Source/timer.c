/***
	***************************************************************************
	*	@file  	timer.c
	*	@brief   定时器初始化，中断配置
   ******************************************************************************
   *  
	* 
	* 
	* 
	***************************************************************************
***/
#include "timer.h"

// 函数：中断分组及优先级配置
//
void NVIC_TimerConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//配置 timer 中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

// 函数：定时器4初始化
//	参数：Period - 定时器重载值
//       frequency - 计数频率
//	说明：由于TIM4挂载在APB1时钟线上，所以TIM4的时钟频率为90M，定时器的分频系数在 1-65536 之间，
//			所以定时器的时钟频率范围为 90M - 1373 Hz，在实际应用中最好取能被90M整除的频率值。
//
void	TIM3_Init(u16 period,u32 frequency)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能时钟
	
	TIM_TimeBaseInitStructure.TIM_Period = period; 	//重载值
	TIM_TimeBaseInitStructure.TIM_Prescaler= TimerClkAPB1 / frequency - 1;  //分频系数
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化
	
	NVIC_TimerConfig(); //中断配置
	TIM_Cmd(TIM3,DISABLE); //使能定时器	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //更新中断
	

	
}

