/***
	***************************************************************************
	*	@file  	usart.c
	*	@brief   ���ڳ�ʼ�����ж����ã�fput�ض���
   ******************************************************************************
   *  
	* 
	* 
	* 
	***************************************************************************
***/
#include "usart.h"


// ������usart IO�ڳ�ʼ��
//
void  USART_GPIO_Config	(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//IO��ʱ������
	RCC_AHB1PeriphClockCmd ( USART1_TX_CLK|USART1_RX_CLK, ENABLE); 

	//IO���Ÿ���
	GPIO_PinAFConfig(USART1_TX_PORT,USART1_TX_PinSource, USART1_TX_AF);
	GPIO_PinAFConfig(USART1_RX_PORT,USART1_RX_PinSource, USART1_RX_AF);
	
	//IO����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;   
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //�ٶ�

	//��ʼ�� TX	RX ����
	GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN;	 
	GPIO_Init(USART1_TX_PORT, &GPIO_InitStructure);	
													   
	GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;	
	GPIO_Init(USART1_RX_PORT, &GPIO_InitStructure);		
	
}

// �������жϷ��鼰���ȼ�����
//
void NVIC_UsartConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//���� USART1 �ж�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

// ������usart��ʼ��
// ������baudRate - ���ڲ�����
//			
void UsartConfig_Init(u32 baudRate)
{
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//IO���ó�ʼ��
	USART_GPIO_Config();
		
	//���ô��ڸ������
	USART_InitStructure.USART_BaudRate 	 = baudRate; //������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ
	USART_InitStructure.USART_StopBits   = USART_StopBits_1; //ֹͣλ1λ
	USART_InitStructure.USART_Parity     = USART_Parity_No ; //��У��
	USART_InitStructure.USART_Mode 	     = USART_Mode_Rx | USART_Mode_Tx; //���ͺͽ���ģʽ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // Ӳ��������
	
	USART_Init(USART1,&USART_InitStructure); 
	
	USART_Cmd(USART1,ENABLE);
	
//	NVIC_UsartConfig();
//	USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);
}

// �������ض���fput����
//
int fputc(int ch, FILE *f)
{

	USART_SendData(USART1, (uint8_t) ch);	// ���͵��ֽ�����
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	//�ȴ�������� 

	return (ch);
}


