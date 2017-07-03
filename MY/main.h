/***
	***************************************************************************
	*	@file  	main.h
	*	@brief   定义相关任务的宏
   ***************************************************************************
   *  
	* 
	* 
	* 
	***************************************************************************
***/

#ifndef __MAIN_H
#define __MAIN_H

                                           

/*---------------------- 任务优先级 ---------------------*/

#define   Start_Task_PRIO        2

#define	 emWinDemo_Task_PRIO		5
#define	 Touch_Task_PRIO			3
#define	 LED0_Task_PRIO			4
#define	 LED1_Task_PRIO			4

/*--------------------- 任务堆栈大小  --------------------*/

#define   Start_Task_STK_SIZE    128

#define	 emWinDemo_Task_STK_SIZE 		4096
#define	 Touch_Task_STK_SIZE 			512
#define	 LED0_Task_STK_SIZE 				512
#define	 LED1_Task_STK_SIZE 				512


#endif

