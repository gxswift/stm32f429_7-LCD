#ifndef __ADC_H
#define __ADC_H	

#include "stm32f4xx.h" 
#include "usart.h"

void ADC_Initialize(void);
float	ADC_GetTemp(void);

#endif 

