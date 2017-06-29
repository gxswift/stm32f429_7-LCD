#ifndef  _PWM_H
#define	_PWM_H

#include "stm32f4xx.h"

/*---------------------- ÅäÖÃ ------------------------*/

#define	LCD_PWM_PORT			GPIOB
#define	LCD_PWM_CLK				RCC_AHB1Periph_GPIOB
#define  LCD_PWM_PIN				GPIO_Pin_7
#define  LCD_PWM_AF           GPIO_AF_TIM4
#define  LCD_PWM_PinSource    GPIO_PinSource7

#define	LCD_TIM_CLK		RCC_APB1Periph_TIM4
#define  LCD_TIM  	   TIM4

/*-------------------- º¯ÊýÉùÃ÷ ----------------------*/

void LCD_PWMinit(u8 pulse);
void LCD_PwmSetPulse (u8 pulse);
	
#endif 

