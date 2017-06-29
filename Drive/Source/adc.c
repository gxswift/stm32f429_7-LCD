/***
	***************************************************************************
	*	@file  	adc.c
	*	@brief   内部温度传感器接口相关函数
   ******************************************************************************
   *  
	* 
	* 
	* 
	***************************************************************************
***/
#include "adc.h"


void ADC_Initialize(void)
{
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8; 	
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; 	
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_TempSensorVrefintCmd(ENABLE);
	ADC_Cmd(ADC1, ENABLE);

}

//
//
float	ADC_GetTemp(void)
{	
	u16 Temp_AdVaule;
	float	Temp_Vaule;
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_18, 1, ADC_SampleTime_480Cycles );	
	ADC_SoftwareStartConv(ADC1);	
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
	Temp_AdVaule = ADC_GetConversionValue(ADC1);
	
	Temp_Vaule = Temp_AdVaule * 0.00081f;
	Temp_Vaule = ( Temp_Vaule - 0.76f ) /0.0025f +25; 
	
	return Temp_Vaule;
}






