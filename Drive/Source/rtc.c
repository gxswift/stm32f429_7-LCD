/***
	***************************************************************************
	*	@file  	rtc.c
	*	@brief   实时时钟相关函数
   ******************************************************************************
   *  使用了RTC的闹钟A并打开了中断，中断服务函数为 RTC_Alarm_IRQHandler();
	* 
	* 
	* 
	***************************************************************************
***/
#include "rtc.h" 
#include "adc.h"

extern RTC_TimeTypeDef 	TimeSet;

//	函数：RTC时钟初始化
//
void RTC_Initialize(void)	
{
	RTC_InitTypeDef RTC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;	
	NVIC_InitTypeDef NVIC_InitStructure;	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); //打开时钟
	PWR_BackupAccessCmd(ENABLE);	//后背区域读写使能

	if(RTC_ReadBackupRegister(RTC_BKP_DR0)!=0xAAAA)		//检测是否第一次配置RTC
	{	
		RCC_LSEConfig(RCC_LSE_ON);  //启动LSE时钟，即外接的32.768K晶振
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET); //等待时钟配置完毕
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);	//配置RTC时钟为LSE时钟
		
		RTC_InitStructure.RTC_AsynchPrediv = 0x7F;	//异步分频系数，根据手册的推荐，设置为最大
		RTC_InitStructure.RTC_SynchPrediv  = 0xFF;	//同步分频系数
		RTC_InitStructure.RTC_HourFormat   = RTC_HourFormat_24;	//时间格式为24小时制
		RTC_Init(&RTC_InitStructure);		
		RCC_RTCCLKCmd(ENABLE);	 //使能RTC	

		RTC_SetTime(RTC_Format_BIN,&TimeSet);
		RTC_WriteBackupRegister(RTC_BKP_DR0,0xAAAA);
	}	
	//RTC闹钟中断线配置
	EXTI_ClearITPendingBit(EXTI_Line17);
	EXTI_InitStructure.EXTI_Line = EXTI_Line17;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	
	
	//中断优先级配置
	NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	RTC_ITConfig(RTC_IT_ALRA, ENABLE);	//开启中断
	RTC_AlarmCmd(RTC_Alarm_A, ENABLE);	//开启闹钟
 	
}
//	函数：设置闹钟
// 
void RTC_AlarmSet(RTC_AlarmSetTypeDef *_AlarmStruct)
{

	RTC_AlarmTypeDef RTC_AlarmStructure;

	RTC_AlarmCmd(RTC_Alarm_A, DISABLE); //在重新设置闹钟之前，一定要先关闭闹钟，不然无法写入
	
	//设置闹钟与日期或星期无关,如果需要闹钟匹配日期或星期，此处应配置为	RTC_AlarmMask_None	
	RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay; 
	//设置闹钟按星期的方式循环，若要按月循环，应设置为 RTC_AlarmDateWeekDaySel_Date
	RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_WeekDay;		
	//设置星期，若上面已配置为与日期或星期无关，此处的配置不起作用
	RTC_AlarmStructure.RTC_AlarmDateWeekDay = _AlarmStruct->Week;	
	//设置闹钟的时分秒
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = _AlarmStruct->Hour;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = _AlarmStruct->Min;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = _AlarmStruct->Sec;
	RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStructure); //初始化闹钟A，设置为二进制格式

	RTC_AlarmCmd(RTC_Alarm_A, ENABLE);	//使能闹钟
}





