#ifndef  _TIMER_H
#define	_TIMER_H

#include "stm32f4xx.h"

/*-------------------- 宏 ----------------------*/

#define TimerClkAPB1 90000000		//挂载在 APB1 时钟线上的定时器时钟频率为 90M

/*-------------------- 函数声明 ----------------------*/

void	TIM3_Init(u16 period,u32 frequency);

#endif 

