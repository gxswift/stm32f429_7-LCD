/***
	***************************************************************************
	*	@file  	GUI_Touch.c
	*	@brief   emWin������ֲ
   ******************************************************************************
   *  
	* 
	* 
	* 
	***************************************************************************
***/
#include	"GUI_Touch.h"

//	������emWin����ɨ��
//	˵����ͨ�� GUI_TOUCH_StoreState() ���������괫�ݵ�emWin��ʵ��emwin����ʶ��
//			��Ҫ�ڶ�ʱ���ô���ɨ�躯�����Լ�ⴥ������
//
void	GUI_TouchScan(void){
		GUI_PID_STATE State;
	Touch_Scan(); //����ɨ��
	//	GUI_TOUCH_StoreState(touchInfo.x[0],touchInfo.y[0]);	//���д����������괫�ݸ�emwin

State.x = touchInfo.x[0];
State.y = touchInfo.y[0];
if (touchInfo.x[0]) {
State.Pressed = 1;
} else {
State.Pressed = 0;
}
GUI_TOUCH_StoreStateEx(&State);
//	if(touchInfo.flag == 1)// 
//	{
//		GUI_TOUCH_StoreState(touchInfo.x[0],touchInfo.y[0]);	//���д����������괫�ݸ�emwin
//	}
//	else
//	{
//		GUI_TOUCH_StoreState(0,0);	//���޴�����д��-1
//	}	
}
