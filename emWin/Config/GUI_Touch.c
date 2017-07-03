/***
	***************************************************************************
	*	@file  	GUI_Touch.c
	*	@brief   emWin触摸移植
   ******************************************************************************
   *  
	* 
	* 
	* 
	***************************************************************************
***/
#include	"GUI_Touch.h"

//	函数：emWin触摸扫描
//	说明：通过 GUI_TOUCH_StoreState() 将触摸坐标传递到emWin，实现emwin触摸识别，
//			需要在定时调用触摸扫描函数，以检测触摸操作
//
void	GUI_TouchScan(void){
		GUI_PID_STATE State;
	Touch_Scan(); //触摸扫描
	//	GUI_TOUCH_StoreState(touchInfo.x[0],touchInfo.y[0]);	//若有触摸，则将坐标传递给emwin

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
//		GUI_TOUCH_StoreState(touchInfo.x[0],touchInfo.y[0]);	//若有触摸，则将坐标传递给emwin
//	}
//	else
//	{
//		GUI_TOUCH_StoreState(0,0);	//若无触摸，写入-1
//	}	
}
