#ifndef  _LED_H
#define	_LED_H

#include "stm32f4xx.h"

/*---------------------- LEDÅäÖÃºê ------------------------*/
#define LED0_PIN             GPIO_Pin_7                 
#define LED0_PORT            GPIOG                      
#define LED0_CLK             RCC_AHB1Periph_GPIOG

#define LED1_PIN             GPIO_Pin_12                 
#define LED1_PORT            GPIOD                     
#define LED1_CLK             RCC_AHB1Periph_GPIOD

/*---------------------- LED¿ØÖÆºê ------------------------*/

#define LED0(a)	if (a)	\
					GPIO_SetBits(LED0_PORT,LED0_PIN);\
					else		\
					GPIO_ResetBits(LED0_PORT,LED0_PIN)

#define LED1(a)	if (a)	\
					GPIO_SetBits(LED1_PORT,LED1_PIN);\
					else		\
					GPIO_ResetBits(LED1_PORT,LED1_PIN)

/*---------------------- º¯ÊýÉùÃ÷ ----------------------------*/
void LED_Init(void);
void LED_Flip(void);
	
#endif 
