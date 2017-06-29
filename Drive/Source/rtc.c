/***
	***************************************************************************
	*	@file  	rtc.c
	*	@brief   ʵʱʱ����غ���
   ******************************************************************************
   *  ʹ����RTC������A�������жϣ��жϷ�����Ϊ RTC_Alarm_IRQHandler();
	* 
	* 
	* 
	***************************************************************************
***/
#include "rtc.h" 
#include "adc.h"

extern RTC_TimeTypeDef 	TimeSet;

//	������RTCʱ�ӳ�ʼ��
//
void RTC_Initialize(void)	
{
	RTC_InitTypeDef RTC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;	
	NVIC_InitTypeDef NVIC_InitStructure;	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); //��ʱ��
	PWR_BackupAccessCmd(ENABLE);	//�������дʹ��

	if(RTC_ReadBackupRegister(RTC_BKP_DR0)!=0xAAAA)		//����Ƿ��һ������RTC
	{	
		RCC_LSEConfig(RCC_LSE_ON);  //����LSEʱ�ӣ�����ӵ�32.768K����
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET); //�ȴ�ʱ���������
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);	//����RTCʱ��ΪLSEʱ��
		
		RTC_InitStructure.RTC_AsynchPrediv = 0x7F;	//�첽��Ƶϵ���������ֲ���Ƽ�������Ϊ���
		RTC_InitStructure.RTC_SynchPrediv  = 0xFF;	//ͬ����Ƶϵ��
		RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;	//ʱ���ʽΪ24Сʱ��
		RTC_Init(&RTC_InitStructure);		
		RCC_RTCCLKCmd(ENABLE);	 //ʹ��RTC	

		RTC_SetTime(RTC_Format_BIN,&TimeSet);
		RTC_WriteBackupRegister(RTC_BKP_DR0,0xAAAA);
	}	
	//RTC�����ж�������
	EXTI_ClearITPendingBit(EXTI_Line17);
	EXTI_InitStructure.EXTI_Line = EXTI_Line17;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	
	
	//�ж����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	RTC_ITConfig(RTC_IT_ALRA, ENABLE);	//�����ж�
	RTC_AlarmCmd(RTC_Alarm_A, ENABLE);	//��������
 	
}
//	��������������
// 
void RTC_AlarmSet(RTC_AlarmSetTypeDef *_AlarmStruct)
{

	RTC_AlarmTypeDef RTC_AlarmStructure;

	RTC_AlarmCmd(RTC_Alarm_A, DISABLE); //��������������֮ǰ��һ��Ҫ�ȹر����ӣ���Ȼ�޷�д��
	
	//�������������ڻ������޹�,�����Ҫ����ƥ�����ڻ����ڣ��˴�Ӧ����Ϊ	RTC_AlarmMask_None	
	RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay; 
	//�������Ӱ����ڵķ�ʽѭ������Ҫ����ѭ����Ӧ����Ϊ RTC_AlarmDateWeekDaySel_Date
	RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_WeekDay;		
	//�������ڣ�������������Ϊ�����ڻ������޹أ��˴������ò�������
	RTC_AlarmStructure.RTC_AlarmDateWeekDay = _AlarmStruct->Week;	
	//�������ӵ�ʱ����
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = _AlarmStruct->Hour;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = _AlarmStruct->Min;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = _AlarmStruct->Sec;
	RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStructure); //��ʼ������A������Ϊ�����Ƹ�ʽ

	RTC_AlarmCmd(RTC_Alarm_A, ENABLE);	//ʹ������
}





