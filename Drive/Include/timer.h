#ifndef  _TIMER_H
#define	_TIMER_H

#include "stm32f4xx.h"

/*-------------------- �� ----------------------*/

#define TimerClkAPB1 90000000		//������ APB1 ʱ�����ϵĶ�ʱ��ʱ��Ƶ��Ϊ 90M

/*-------------------- �������� ----------------------*/

void	TIM3_Init(u16 period,u32 frequency);

#endif 

