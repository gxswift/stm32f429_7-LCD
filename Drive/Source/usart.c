/***
	***************************************************************************
	*	@file  	usart.c
	*	@brief   串口初始化，中断配置，fput重定向
   ******************************************************************************
   *  
	* 
	* 
	* 
	***************************************************************************
***/
#include "usart.h"


// 函数：usart IO口初始化
//
void  USART_GPIO_Config	(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//IO口时钟配置
	RCC_AHB1PeriphClockCmd ( USART1_TX_CLK|USART1_RX_CLK, ENABLE); 

	//IO引脚复用
	GPIO_PinAFConfig(USART1_TX_PORT,USART1_TX_PinSource, USART1_TX_AF);
	GPIO_PinAFConfig(USART1_RX_PORT,USART1_RX_PinSource, USART1_RX_AF);
	
	//IO配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;   
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //推挽
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //速度

	//初始化 TX	RX 引脚
	GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN;	 
	GPIO_Init(USART1_TX_PORT, &GPIO_InitStructure);	
													   
	GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;	
	GPIO_Init(USART1_RX_PORT, &GPIO_InitStructure);		
	
}

// 函数：中断分组及优先级配置
//
void NVIC_UsartConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//配置 USART1 中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

// 函数：usart初始化
// 参数：baudRate - 串口波特率
//			
void UsartConfig_Init(u32 baudRate)
{
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//IO配置初始化
	USART_GPIO_Config();
		
	//配置串口各项参数
	USART_InitStructure.USART_BaudRate 	 = baudRate; //波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位
	USART_InitStructure.USART_StopBits   = USART_StopBits_1; //停止位1位
	USART_InitStructure.USART_Parity     = USART_Parity_No ; //无校验
	USART_InitStructure.USART_Mode 	     = USART_Mode_Rx | USART_Mode_Tx; //发送和接受模式
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 硬件流控制
	
	USART_Init(USART1,&USART_InitStructure); 
	
	USART_Cmd(USART1,ENABLE);
	
//	NVIC_UsartConfig();
//	USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);
}

// 函数：重定向fput函数
//
int fputc(int ch, FILE *f)
{

	USART_SendData(USART1, (uint8_t) ch);	// 发送单字节数据
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	//等待发送完毕 

	return (ch);
}


