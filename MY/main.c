/***
	***************************************************************************
	*	@file  	main.c
	*	@brief   
	*				
   ******************************************************************************
   *  
	* 
	* 
	* 
	***************************************************************************
***/

#include <includes.h>
#include  "main.h" 
#include  "led.h" 
#include  "usart.h" 
#include  "sdram.h" 
#include  "rtc.h" 
#include  "GUI.h"
#include  "MyGui.h"
#include	 "GUI_Touch.h"
#include  "adc.h"
#include  "timer.h"

static  OS_TCB   Start_TaskTCB;

static  OS_TCB   emWinDemo_TaskTCB;
static  OS_TCB   Touch_TaskTCB;
static  OS_TCB   LED0_TaskTCB;
static  OS_TCB   LED1_TaskTCB;

/*---------------------- STACKS ------------------------*/

static  CPU_STK  Start_TaskStk[Start_Task_STK_SIZE];

static  CPU_STK  emWinDemo_TaskStk[emWinDemo_Task_STK_SIZE];
static  CPU_STK  Touch_TaskStk[Touch_Task_STK_SIZE];
static  CPU_STK  LED0_TaskStk[LED0_Task_STK_SIZE];
static  CPU_STK  LED1_TaskStk[LED1_Task_STK_SIZE];

/*------------------ FUNCTION PROTOTYPES ---------------*/

static  void  Start_Task   (void *p_arg);

static  void  emWinDemo_Task		(void *p_arg);
static  void  Touch_Task		(void *p_arg);
static  void  LED0_Task		(void *p_arg);
static  void  LED1_Task		(void *p_arg);

/*----------------------- main() -----------------------*/

int  main (void)
{
	OS_ERR  err;

	// 底层驱动初始化
	LED_Init();	
	UsartConfig_Init(115200);
	SDRAM_Init(); //sdram要先于emwin之前初始化
	Touch_Init();	
	RTC_Initialize();	
	ADC_Initialize();
	TIM3_Init(1000,100000);
	//emwin初始化
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);		

	WM_MULTIBUF_Enable(1);
	GUI_Init();

	// UCOS初始化化，并创建开始任务
	OSInit(&err);                                               /* Init uC/OS-III.                                      */

	OSTaskCreate((OS_TCB     *)&Start_TaskTCB,                /* Create the start task                                */
				  (CPU_CHAR   *)" Task Start",
				  (OS_TASK_PTR ) Start_Task,
				  (void       *) 0,
				  (OS_PRIO     ) Start_Task_PRIO,
				  (CPU_STK    *)&Start_TaskStk[0],
				  (CPU_STK_SIZE) Start_Task_STK_SIZE / 10,
				  (CPU_STK_SIZE) Start_Task_STK_SIZE,
				  (OS_MSG_QTY  ) 5u,
				  (OS_TICK     ) 0u,
				  (void       *) 0,
				  (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
				  (OS_ERR     *)&err);

	OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */

		
}


/*---------------------- STARTUP TASK ------------------------*/

static  void  Start_Task (void *p_arg)
{
    CPU_INT32U  cpu_clk_freq;
    CPU_INT32U  cnts;
    OS_ERR      err;


   (void)p_arg;

    CPU_Init();

    cpu_clk_freq = BSP_CPU_ClkFreq();                           /* Determine SysTick reference freq.                    */
    cnts = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;        /* Determine nbr SysTick increments                     */
    OS_CPU_SysTickInit(cnts);                                   /* Init uC/OS periodic time src (SysTick).              */

    Mem_Init();                                                 /* Initialize Memory Management Module                  */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif

    OSTaskCreate((OS_TCB     *)&emWinDemo_TaskTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"emWinDemo Task ",
                 (OS_TASK_PTR ) emWinDemo_Task,
                 (void       *) 0,
                 (OS_PRIO     ) emWinDemo_Task_PRIO,
                 (CPU_STK    *)&emWinDemo_TaskStk[0],
                 (CPU_STK_SIZE) emWinDemo_Task_STK_SIZE / 10,
                 (CPU_STK_SIZE) emWinDemo_Task_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
					  
    OSTaskCreate((OS_TCB     *)&Touch_TaskTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"Touch Task ",
                 (OS_TASK_PTR ) Touch_Task,
                 (void       *) 0,
                 (OS_PRIO     ) Touch_Task_PRIO,
                 (CPU_STK    *)&Touch_TaskStk[0],
                 (CPU_STK_SIZE) Touch_Task_STK_SIZE / 10,
                 (CPU_STK_SIZE) Touch_Task_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
					  
    OSTaskCreate((OS_TCB     *)&LED0_TaskTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"Led0 Task ",
                 (OS_TASK_PTR ) LED0_Task,
                 (void       *) 0,
                 (OS_PRIO     ) LED0_Task_PRIO,
                 (CPU_STK    *)&LED0_TaskStk[0],
                 (CPU_STK_SIZE) LED0_Task_STK_SIZE / 10,
                 (CPU_STK_SIZE) LED0_Task_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);

    OSTaskCreate((OS_TCB     *)&LED1_TaskTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"Led1 Task ",
                 (OS_TASK_PTR ) LED1_Task,
                 (void       *) 0,
                 (OS_PRIO     ) LED1_Task_PRIO,
                 (CPU_STK    *)&LED1_TaskStk[0],
                 (CPU_STK_SIZE) LED1_Task_STK_SIZE / 10,
                 (CPU_STK_SIZE) LED1_Task_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
					  
	OSTaskDel ( & Start_TaskTCB, & err );                     //删除起始任务本身，该任务不再运行
			
}

/*---------------------- emWinDemo TASK ------------------------*/

static	void	emWinDemo_Task (void *p_arg)
{	
	(void)p_arg;
	
	APP_Time();

}
/*---------------------- Touch TASK ------------------------*/

// 任务：触摸扫描
//
static	void	Touch_Task (void *p_arg)
{
	OS_ERR      err;
	(void)p_arg;
	
	while(DEF_TRUE)
	{	
		GUI_TouchScan();	
		OSTimeDly ( 20, OS_OPT_TIME_DLY, & err );	
	}
}

/*---------------------- LED TASK ------------------------*/

static	void	LED0_Task (void *p_arg)
{
	OS_ERR      err;
	(void)p_arg;

	while(DEF_TRUE)
	{
		LED0(1);
		OSTimeDly ( 200, OS_OPT_TIME_DLY, & err );
		LED0(0);
		OSTimeDly ( 200, OS_OPT_TIME_DLY, & err );			
	}
			
}

static	void	LED1_Task (void *p_arg)
{
	OS_ERR      err;
	(void)p_arg;

	while(DEF_TRUE)
	{
		LED1(1);
		OSTimeDly ( 500, OS_OPT_TIME_DLY, & err );
		LED1(0);
		OSTimeDly ( 500, OS_OPT_TIME_DLY, & err );			
	}
			
}

