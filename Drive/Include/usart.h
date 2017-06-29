#ifndef  _USART_H
#define	_USART_H

#include <stdio.h>
#include "stm32f4xx.h"

/*---------------------- ÅäÖÃ ------------------------*/

#define	USART1_TX_PORT				GPIOA
#define	USART1_TX_CLK				RCC_AHB1Periph_GPIOA
#define  USART1_TX_PIN				GPIO_Pin_9
#define  USART1_TX_AF            GPIO_AF_USART1
#define  USART1_TX_PinSource     GPIO_PinSource9

#define	USART1_RX_PORT				GPIOA
#define	USART1_RX_CLK				RCC_AHB1Periph_GPIOA
#define  USART1_RX_PIN				GPIO_Pin_10
#define  USART1_RX_AF            GPIO_AF_USART1
#define  USART1_RX_PinSource     GPIO_PinSource10


/*-------------------- º¯ÊýÉùÃ÷ ----------------------*/

void	UsartConfig_Init(u32 baudRate);

#endif 


