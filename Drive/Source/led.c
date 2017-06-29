/***
	***************************************************************************
	*	@file  	LED.c
	*	@brief   LED接口相关函数
   ******************************************************************************
   *  
	* 
	* 
	* 
	***************************************************************************
***/

  
#include "led.h"   

// 函数：LED IO口初始化
//
void LED_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	//IO口时钟配置
	RCC_AHB1PeriphClockCmd ( LED0_CLK|LED1_CLK, ENABLE); 
															   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   //输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //推挽
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //速度

	//初始化 LED0 引脚
	GPIO_InitStructure.GPIO_Pin = LED0_PIN;	 
	GPIO_Init(LED0_PORT, &GPIO_InitStructure);	

	//初始化 LED1 引脚														   
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;	
	GPIO_Init(LED1_PORT, &GPIO_InitStructure);	
 
}

// 函数：LED IO口翻转
//
void LED_Flip(void)
{		
	static u8 ledFlipFlag = 0; //翻转标志位
	
	ledFlipFlag =~ ledFlipFlag;	//标志取反
	
	if(ledFlipFlag == 0)	
	{
		LED0(0);
		LED1(0);
	}
	else
	{
		LED0(1);
		LED1(1);
	}
		
}

