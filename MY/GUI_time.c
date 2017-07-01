/***
	***************************************************************************
	*	@file  	time.c
	*	@brief  
   ******************************************************************************
	*	  
	*	  
	*
	*	  
	*	  
	*
	*	  
	***************************************************************************
***/
#include "MyGui.h"
#include "math.h"
#include "rtc.h" 
#include "adc.h"

extern GUI_CONST_STORAGE GUI_BITMAP Tianqi_Bitmap;
extern GUI_CONST_STORAGE GUI_BITMAP Back_Button_Bitmap;
extern GUI_CONST_STORAGE GUI_BITMAP OK_Button_Bitmap;
extern GUI_CONST_STORAGE GUI_BITMAP Alarm32_Button_Bitmap;
extern GUI_CONST_STORAGE GUI_BITMAP Timer_Button_Bitmap;
extern GUI_CONST_STORAGE GUI_BITMAP Adjust_Button_Bitmap;
extern GUI_CONST_STORAGE GUI_BITMAP Alarm50_Button_Bitmap;
extern GUI_CONST_STORAGE GUI_BITMAP Reset_Button_Bitmap;
extern GUI_CONST_STORAGE GUI_BITMAP Stop_Button_Bitmap;

/*------------------------------ Ƥ������ ------------------------------*/
_ButtonRedrawColor	 ButtonRedrawColor  = { 0,0x2C2C2C,0x787570 }; //buttonƤ�������ṹ�壺Բ�ǰ뾶�����µ���ɫ��δ���µ���ɫ
_SliderRedrawColor   SliderRedrawColor = {0xA47611,0xB9B9B9,0x2C2C2C,0,4}; //sliderƤ�������ṹ�壺 �������ɫ�������ɫ���۽������ɫ���̶ȳߴ�С����Ĵ�С
/*----------------------------- ���Ʊ��� ----------------------------*/
//extern GUI_CONST_STORAGE GUI_BITMAP bmp_tianqi;
//extern GUI_CONST_STORAGE GUI_BITMAP bmp_naozhong;
//extern GUI_CONST_STORAGE GUI_BITMAP bmp_timer;
//extern GUI_CONST_STORAGE GUI_BITMAP bmp_adjust;

RTC_TimeTypeDef  		Time_Struct,TimeSet;
RTC_AlarmSetTypeDef 	Alarm_Struct;

u16 stm32Temp = 0;
int alarmFlag = 0;
int alarmHour,alarmMin;

int TimeArc_radius = 110;
GUI_RECT  windowRect = {75,100,355,380 };
GUI_RECT  windowHourRect = {155,200,225,270 };
GUI_RECT  windowMinRect = {225,200,290,270 };

 struct		
{ 
  GUI_AUTODEV_INFO AutoInfo;
  int arc_x;
  int arc_y;
}timeDraw ;

/*------------------------------ Adjusts ���� ------------------------------*/
WM_HWIN	Adjust_HWIN; //Adjust���ھ��

//extern GUI_CONST_STORAGE GUI_BITMAP bmp_ok;
//extern GUI_CONST_STORAGE GUI_BITMAP bmp_back;

u8 adjustWindow = 0;
GUI_COLOR  AdjustWindow_Back = 0x2C2C2C; //Adjust����ɫ
GUI_COLOR  AdjustText_Color  = 0xEFEFEF; //Adjust�ı�ɫ

//slider �ؼ��Ľṹ��
//������ ��Сֵ������ֵ�����ֵ�������ɫ������ѡ���������ɫ�����鱾�����ɫ
_SliderAttribute  Slider_Hour = {0,12,23,4,SliderColor_Shaft,SliderColor_Process,SliderColor_Thumb};
_SliderAttribute  SliderAttribute = {0,20,59,4,SliderColor_Shaft,SliderColor_Process,SliderColor_Thumb};

int  DrawSkinFlex_Slider(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);  // ����Ƥ���ػ溯��

static const GUI_WIDGET_CREATE_INFO _aAdjustWindow[] = 
{
    { WINDOW_CreateIndirect,"",0,			    0,  0,  350,350, 0				},
    { TEXT_CreateIndirect,      "hour:",	 GUI_ID_TEXT0,            52, 20,100,40, 0,0},
    { TEXT_CreateIndirect,      "min:",		 GUI_ID_TEXT1,            52, 80,100,40, 0,0},
    { TEXT_CreateIndirect,      "sec:",		 GUI_ID_TEXT2,            52,140,100,40, 0,0},

    { SLIDER_CreateIndirect,     NULL,       GUI_ID_SLIDER0,          147,30,180,20, 0,0},
    { SLIDER_CreateIndirect,     NULL,       GUI_ID_SLIDER1,          147,90,180,20, 0,0},
    { SLIDER_CreateIndirect,     NULL,       GUI_ID_SLIDER2,          147,150,180,20, 0,0},

    { BUTTON_CreateIndirect,    "       BACK",    GUI_ID_BUTTON0,        58,210, 150,55, 0,0},
    { BUTTON_CreateIndirect,    "   OK",          GUI_ID_BUTTON1,       240,210, 150,55, 0,0},
};       

void Adjust_Paint(WM_MESSAGE * pMsg);     // Adjust�����ػ�
void Adjust_Init(WM_MESSAGE * pMsg);      // Adjust���ڳ�ʼ��
static void _cbAdjustWindow(WM_MESSAGE * pMsg); // Adjust���ڻص�

/*------------------------------ Alarm ���� ------------------------------*/
WM_HWIN	Alarm_HWIN; //Alarm���ھ��
u8 alarmWindow = 0;

GUI_RECT  AlarmHourRect = {175,140,275,190 };
GUI_RECT  AlarmMinRect  = {300,140,400,190 };

GUI_COLOR  AlarmWindow_Back = 0x2C2C2C; //Alarm����ɫ
GUI_COLOR  AlarmText_Color  = 0xC9C9C9; //Alarm�ı�ɫ

//slider �ؼ��Ľṹ��
//������ ��Сֵ������ֵ�����ֵ�������ɫ������ѡ���������ɫ�����鱾�����ɫ
_SliderAttribute  Alarm_Hour_Attribute = {0,12,23,4,SliderColor_Shaft,SliderColor_Process,SliderColor_Thumb};
_SliderAttribute  Alarm_Min_Attribute = {0,20,59,4,SliderColor_Shaft,SliderColor_Process,SliderColor_Thumb};

int  DrawSkinFlex_Slider(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);  // ����Ƥ���ػ溯��

static const GUI_WIDGET_CREATE_INFO _aAlarmWindow[] = 
{
    { WINDOW_CreateIndirect,"",0,			    0,  0,  800,480, 0				},
    { TEXT_CreateIndirect,      "hour:",	 GUI_ID_TEXT0,            134,239,100,40, 0,0},
    { TEXT_CreateIndirect,      "min:",		 GUI_ID_TEXT1,            135,303,100,40, 0,0},

    { SLIDER_CreateIndirect,     NULL,       GUI_ID_SLIDER0,          229,249,180,20, 0,0},
    { SLIDER_CreateIndirect,     NULL,       GUI_ID_SLIDER1,          229,310,180,20, 0,0},


    { BUTTON_CreateIndirect,    "        BACK",    GUI_ID_BUTTON0,       531,155, 150,55, 0,0},
    { BUTTON_CreateIndirect,    "    ON",          GUI_ID_BUTTON1,       531,270, 150,55, 0,0},
};       

void Alarm_Paint(WM_MESSAGE * pMsg);     // Alarm�����ػ�
void Alarm_Init(WM_MESSAGE * pMsg);      // Alarm���ڳ�ʼ��
static void _cbAlarmWindow(WM_MESSAGE * pMsg); // Alarm���ڻص�


/*-------------------------timer ���� ---------------------------------*/
WM_HWIN Timer_HWIN;
GUI_RECT  TimerWindow_Rect  = {240,160,600,220 };
u8  timerWindow = 0;
u8  timerFalg = 0;
u8  timerMin = 0;
u8  timerSec = 0;
u16 subsecond = 0;
 
static const GUI_WIDGET_CREATE_INFO _aTimerWindow[] =  //window��Դ��
{
	{WINDOW_CreateIndirect,"",0,			    0,  0,  800,480, 0	},
    { BUTTON_CreateIndirect,    "        BACK",      GUI_ID_BUTTON0,          115,287,180,55, 0,0},
    { BUTTON_CreateIndirect,    "          RESET",   GUI_ID_BUTTON1,          335,290,180,55, 0,0},
    { BUTTON_CreateIndirect,    "         START",    GUI_ID_BUTTON2,          551,293,180,55, 0,0},
};
void Timer_init(WM_MESSAGE * pMsg);	//window��ʼ��
void TimerButton_Click(int ID);// button �¼�����
static void _cbTimerWindow(WM_MESSAGE * pMsg);	//window�Ļص�����

/*------------------------------���� �������� -----------------------------*/
 WM_HWIN Button_HWIN;

static const GUI_WIDGET_CREATE_INFO _ButtonDialog[] =  //window��Դ��
{
	{WINDOW_CreateIndirect,"",0,			    0,  0,  160,190, 0				},
    { BUTTON_CreateIndirect,    "      Alarm",      GUI_ID_BUTTON0,          5, 5, 150,40, 0,0},
    { BUTTON_CreateIndirect,    "      Timer",      GUI_ID_BUTTON1,          5, 75,150,40, 0,0},
    { BUTTON_CreateIndirect,    "      Adjust",     GUI_ID_BUTTON2,          5,145,150,40, 0,0},
};
void WM_Button_init(WM_MESSAGE * pMsg)	//window��ʼ��
{
	WM_HWIN hWin = pMsg->hWin;

	BUTTON_SetBitmapEx(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),BUTTON_BI_UNPRESSED, &Alarm32_Button_Bitmap, 4,5);
	BUTTON_SetBitmapEx(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),BUTTON_BI_UNPRESSED, &Timer_Button_Bitmap,		   4,5);
	BUTTON_SetBitmapEx(WM_GetDialogItem(hWin,GUI_ID_BUTTON2),BUTTON_BI_UNPRESSED, &Adjust_Button_Bitmap,		4,5);

}
// button �¼�����
void ButtonClick(int ID)
{
	switch (ID)
	{
		case GUI_ID_BUTTON0:
			alarmWindow = 1;
//			WM_HideWindow(Button_HWIN);
			Alarm_HWIN = GUI_CreateDialogBox(_aAlarmWindow, GUI_COUNTOF(_aAlarmWindow),&_cbAlarmWindow,WM_HBKWIN,0,0);			
			break;				
		case GUI_ID_BUTTON1:	
			timerWindow = 1;
//			WM_HideWindow(Button_HWIN);
			Timer_HWIN = GUI_CreateDialogBox(_aTimerWindow, GUI_COUNTOF(_aTimerWindow),&_cbTimerWindow,WM_HBKWIN,0,0);
			break;				
		case GUI_ID_BUTTON2:	
			adjustWindow = 1;
			WM_HideWindow(Button_HWIN);
			Adjust_HWIN = GUI_CreateDialogBox(_aAdjustWindow, GUI_COUNTOF(_aAdjustWindow),&_cbAdjustWindow,WM_HBKWIN,400,110);
			break;
		default:	break;	
	}
}
static void _cbButton(WM_MESSAGE * pMsg)	//window�Ļص�����
{
	int NCode;
	int ID;
		
	switch (pMsg->MsgId)
	{
		/* �ػ�window */
		case WM_PAINT: 
			GUI_SetBkColor(0x2C2C2C);	//���õ��ǵ�ǰwindow�ı�����ɫ������������ı���ɫ
			GUI_Clear();
		break;
		/*  ��ʼ��window */
		case WM_INIT_DIALOG:
			WM_Button_init(pMsg);
		break;
		/* �Ӵ�����Ϣ */
		case WM_NOTIFY_PARENT: 
			ID = WM_GetId(pMsg->hWinSrc); 
			NCode = pMsg->Data.v;        
			switch (NCode) 
			{
			case WM_NOTIFICATION_RELEASED:
				ButtonClick(ID);
				break;
			}			
		break;
		default: WM_DefaultProc(pMsg);	//Ĭ�ϴ�����
	}
}


/********************* ����	*************************/
void  Desktop_Iint(void)
{
	int x=160;
	int	y=205;

	GUI_SetFont(&GUI_FontD32); //��������
	GUI_SetBkColor(0xEFEFEF);
	GUI_SetColor(0x3B3B3B);
	GUI_DispCharAt(':', x+50,y);
	GUI_DispDecAt(Time_Struct.RTC_Hours,	x,y,2);
	GUI_DispDecAt(Time_Struct.RTC_Minutes, x+64,y,2);
}
void  DrawDesktop(void)
{
	GUI_SetBkColor(0x2C2C2C);	
	GUI_Clear();
	GUI_SetColor(0x797979);
	GUI_DrawLine(440,142,440,350);

	GUI_SetBkColor(0x2C2C2C);
	GUI_ClearRect( 75,100,355,380);

	GUI_SetColor(GUI_WHITE);
	GUI_AA_FillCircle(215,240,135);

	GUI_SetColor(0xEFEFEF);
	GUI_AA_FillCircle(215,240,110);

	GUI_SetColor(0x2C2C2C);
	GUI_AA_DrawArc(215,240,110,110,0,360);

	if(alarmFlag == 0)
	{
		GUI_SetColor(0xFF6633);		
		RTC_AlarmCmd(RTC_Alarm_A, DISABLE);
	}
	else
	{
		GUI_SetColor(0x3484FD); 
		RTC_AlarmCmd(RTC_Alarm_A, ENABLE);	//ʹ������
	}
	GUI_AA_FillCircle(timeDraw.arc_x,timeDraw.arc_y,4);
	
	Desktop_Iint();
	
	GUI_DrawBitmap(&Tianqi_Bitmap,165,260);
	GUI_SetFont(&GUI_Font24_ASCII); //��������
	GUI_SetBkColor(0xEFEFEF);
	GUI_SetColor(0x3B3B3B);
	GUI_DispDecAt(stm32Temp,218,263,2);		
	
	
}
void  _cbDesktop( WM_MESSAGE * pMsg)
{
	WM_HWIN hDlg;
	int NCode;
	int ID;

	hDlg = pMsg->hWin;
	switch (pMsg->MsgId)
	{
		case WM_PAINT: 
			DrawDesktop();
		break;		
	}
}

/******************************		Main����	*********************************/

void APP_Time(void)
{
	
	GUI_AA_SetFactor(4);	
	WM_SetCallback(WM_HBKWIN,_cbDesktop);
	
	Button_RedrawSkin(&ButtonRedrawColor);	//����Ƥ��
	Slider_RedrawSkin(&SliderRedrawColor);
	
	BUTTON_SetDefaultFont(&GUI_Font32_ASCII);
	BUTTON_SetDefaultTextColor(0xC9C9C9,BUTTON_CI_UNPRESSED);
	BUTTON_SetDefaultTextColor(0xC9C9C9,BUTTON_CI_PRESSED);	
	
	TEXT_SetDefaultFont(&GUI_Font32_ASCII);
	TEXT_SetDefaultTextColor(AdjustText_Color);	
	
	Button_HWIN = GUI_CreateDialogBox(_ButtonDialog,GUI_COUNTOF(_ButtonDialog),_cbButton,WM_HBKWIN,510,152);	//ʹ����Դ�����Ի���

	while(1)
	{		
		if(alarmWindow == 0 && timerWindow == 0 && adjustWindow == 0)		
		{
			RTC_GetTime(RTC_Format_BIN,&Time_Struct);			
			timeDraw.arc_x = 215 + TimeArc_radius * cos(1.5708 - Time_Struct.RTC_Seconds * 0.1047);
			timeDraw.arc_y = 240 - TimeArc_radius * sin(1.5708 - Time_Struct.RTC_Seconds * 0.1047);
			stm32Temp = (u16)ADC_GetTemp();
			WM_InvalidateRect(WM_HBKWIN,&windowRect);
			GUI_Delay(199);			
		}		
		if(timerFalg != 0)
		{
			WM_InvalidateRect(Timer_HWIN,&TimerWindow_Rect);
		}		
		GUI_Delay(1);
	}
}


/*------------------------------ timer ���� ------------------------------*/
void Timer_Paint(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

	GUI_SetBkColor(AlarmWindow_Back);
	GUI_Clear();

	GUI_SetFont(&GUI_FontD48); //��������
	GUI_SetBkColor(AlarmWindow_Back);
	GUI_SetColor(AlarmText_Color);

	GUI_DispDecAt(timerMin,240,160,2);
	GUI_DispCharAt(':',333,160);
	GUI_DispDecAt(timerSec,368,160,2);	
	GUI_DispCharAt(':',461,160);
	GUI_DispDecAt(subsecond,496,160,2);	

	if(timerFalg == 0)
		BUTTON_SetText(WM_GetDialogItem(hWin,GUI_ID_BUTTON2),"         START");
	else
		BUTTON_SetText(WM_GetDialogItem(hWin,GUI_ID_BUTTON2),"         STOP");
} 
void Timer_init(WM_MESSAGE * pMsg)	//window��ʼ��
{
	WM_HWIN hWin = pMsg->hWin;
	timerMin = 0;timerSec = 0;subsecond = 0;
	
	BUTTON_SetBitmapEx(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),BUTTON_BI_UNPRESSED,&Back_Button_Bitmap,4,0);
	BUTTON_SetBitmapEx(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),BUTTON_BI_UNPRESSED,&Reset_Button_Bitmap,4,0);
	BUTTON_SetBitmapEx(WM_GetDialogItem(hWin,GUI_ID_BUTTON2),BUTTON_BI_UNPRESSED,&Stop_Button_Bitmap,4,0);
}
void TimerButton_Click(int ID)// button �¼�����
{
	switch (ID)
	{
		case GUI_ID_BUTTON0:
			timerWindow = 0;
			timerFalg   = 0;		
//			WM_DeleteWindow(Timer_HWIN);
//			WM_ShowWindow(Button_HWIN);
			GUI_EndDialog(Timer_HWIN,0);
			break;				
		case GUI_ID_BUTTON1:	
			if(timerFalg == 0)
			{
				timerMin = 0;timerSec = 0;subsecond = 0;
				WM_InvalidateRect(Timer_HWIN,&TimerWindow_Rect);
			}
			break;				
		case GUI_ID_BUTTON2:	
			timerFalg = ~timerFalg;
			if(timerFalg == 0)
				TIM_Cmd(TIM3,DISABLE); //�رն�ʱ��	
			else
				TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��			
			break;
		default:	break;	
	}
}
static void _cbTimerWindow(WM_MESSAGE * pMsg)	//window�Ļص�����
{
	int NCode;
	int ID;
		
	switch (pMsg->MsgId)
	{
		/* �ػ�window */
		case WM_PAINT: 
			Timer_Paint(pMsg);
		break;
		/*  ��ʼ��window */
		case WM_INIT_DIALOG:
			Timer_init(pMsg);
		break;
		/* �Ӵ�����Ϣ */
		case WM_NOTIFY_PARENT: 
            ID = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;        
            switch (NCode) 
            {
				case WM_NOTIFICATION_RELEASED:
					TimerButton_Click(ID);
					break;
            }
		break;
		default: WM_DefaultProc(pMsg);	//Ĭ�ϴ�����
	}
}

/*------------------------------ Alarm ���� ------------------------------*/

//����������Ƥ���ػ溯��
//������pDrawItemInfo Ƥ�������ݽṹ��ָ��
int  DrawSkinFlex_Slider(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) 
{
	//float Active_Area;
	GUI_RECT Rect;

	switch (pDrawItemInfo->Cmd) 
	{
		//case WIDGET_ITEM_DRAW_SHAFT:		
		//	Active_Area = (float)SliderAttribute.Set / SliderAttribute.Max;
		//	Rect.x0   = pDrawItemInfo->x0,
		//	Rect.y0	= pDrawItemInfo->y0 + (pDrawItemInfo->y1 + pDrawItemInfo->y0)/2 - SliderAttribute.Width/2,
		//	Rect.x1	= pDrawItemInfo->x1,
		//	Rect.y1	= pDrawItemInfo->y1 - (pDrawItemInfo->y1 + pDrawItemInfo->y0)/2 + SliderAttribute.Width/2,						
		//	GUI_SetColor(SliderAttribute.ShaftColor);
		//	GUI_FillRectEx(&Rect);
		//	GUI_SetColor(SliderAttribute.ProcessColor);
		//	GUI_FillRect(Rect.x0,Rect.y0,Rect.x1 * Active_Area,Rect.y1);
		//break;
		case WIDGET_ITEM_DRAW_THUMB:
			GUI_SetColor(SliderAttribute.ThumbColor);
			Rect.x0 = pDrawItemInfo->x0;
			Rect.y0 = pDrawItemInfo->y0;
			Rect.x1 = pDrawItemInfo->x1;
			Rect.y1 = pDrawItemInfo->y1;
			GUI_FillRectEx(&Rect);
		break;
		default:	return SLIDER_DrawSkinFlex(pDrawItemInfo);
	}
	return 0;
}
     
//������Alarm�����ػ�
//������pMsg �ص���Ϣ 
void Alarm_Paint(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

	GUI_SetBkColor(AlarmWindow_Back);
	GUI_Clear();

	GUI_SetFont(&GUI_FontD48); //��������
	GUI_SetBkColor(AlarmWindow_Back);
	GUI_SetColor(AlarmText_Color);

	GUI_DispDecAt(Alarm_Struct.Hour,177,145,2);
	GUI_DispCharAt(':',270,145);
	GUI_DispDecAt(Alarm_Struct.Min,305,145,2);	

	if(alarmFlag == 0)
		BUTTON_SetText(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),"     ON") ;
	else	
		BUTTON_SetText(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),"     OFF") ;

} 
//������Alarm���ڳ�ʼ��
//������pMsg �ص���Ϣ 
void Alarm_Init(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
	//
	SLIDER_SetRange(WM_GetDialogItem(hWin,GUI_ID_SLIDER0),Alarm_Hour_Attribute.Min,Alarm_Hour_Attribute.Max);
	SLIDER_SetValue(WM_GetDialogItem(hWin,GUI_ID_SLIDER0),Alarm_Struct.Hour);
	SLIDER_SetSkin(WM_GetDialogItem(hWin, GUI_ID_SLIDER0),DrawSkinFlex_Slider);

	SLIDER_SetRange(WM_GetDialogItem(hWin,GUI_ID_SLIDER1),Alarm_Min_Attribute.Min,Alarm_Min_Attribute.Max);
	SLIDER_SetValue(WM_GetDialogItem(hWin,GUI_ID_SLIDER1),Alarm_Struct.Min);
	SLIDER_SetSkin(WM_GetDialogItem(hWin, GUI_ID_SLIDER1),DrawSkinFlex_Slider);

	BUTTON_SetBitmapEx(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),BUTTON_BI_UNPRESSED,&Back_Button_Bitmap,2,3);
	BUTTON_SetBitmapEx(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),BUTTON_BI_UNPRESSED,&Alarm50_Button_Bitmap,2,0);
}
//������Alarm���ڻص�
//������pMsg �ص���Ϣ 
void AlarmSlider_Changed(WM_HWIN hWin,int ID) 
{
    switch (ID) 
    {
		case GUI_ID_SLIDER0:
			Alarm_Struct.Hour = SLIDER_GetValue(WM_GetDialogItem(hWin,GUI_ID_SLIDER0)) ;
			WM_InvalidateRect(Alarm_HWIN,&AlarmHourRect);
			break;
		case GUI_ID_SLIDER1:
			Alarm_Struct.Min = SLIDER_GetValue(WM_GetDialogItem(hWin,GUI_ID_SLIDER1)) ;
			WM_InvalidateRect(Alarm_HWIN,&AlarmMinRect);
			break;
    }
}
// button �¼�����
void AlarmButton_Click(int ID)
{
	switch (ID)
	{
		case GUI_ID_BUTTON0:
			alarmWindow = 0;
			RTC_AlarmSet(&Alarm_Struct);	
//			WM_ShowWindow(Button_HWIN);		
//			WM_DeleteWindow(Alarm_HWIN);
			GUI_EndDialog(Alarm_HWIN,0);
			break;				
		case GUI_ID_BUTTON1:	
			alarmWindow = 0;
			RTC_AlarmSet(&Alarm_Struct);	
//			WM_DeleteWindow(Alarm_HWIN);
//			WM_ShowWindow(Button_HWIN);
			GUI_EndDialog(Alarm_HWIN,0);
			alarmFlag =~alarmFlag;
			break;				
		default:	break;	
	}
}
static void _cbAlarmWindow(WM_MESSAGE * pMsg) 
{
    int NCode, ID;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            Alarm_Paint(pMsg);
            break;
        case WM_INIT_DIALOG:
            Alarm_Init(pMsg);
            break;
        case WM_NOTIFY_PARENT:
            ID = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;   

			switch (NCode)
			{
				case WM_NOTIFICATION_RELEASED:	//button�¼�����
					AlarmButton_Click(ID);
				break;
				case WM_NOTIFICATION_VALUE_CHANGED:  //slider�¼�����
					AlarmSlider_Changed(hWin,ID);
				break;
			}
            break;
        default:	WM_DefaultProc(pMsg);           
    }
}

/*------------------------------ Adjust ���� ------------------------------*/
 
//������Adjust�����ػ�
//������pMsg �ص���Ϣ 
void AdjustWindow_Paint(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

	GUI_SetBkColor(AdjustWindow_Back);
	GUI_Clear();
	GUI_SetColor(0x797979);
	GUI_DrawLine(1,0,1,280);
} 
//������Adjust���ڳ�ʼ��
//������pMsg �ص���Ϣ 
void AdjustWindow_Init(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
	//
	SLIDER_SetRange(WM_GetDialogItem(hWin,GUI_ID_SLIDER0),Slider_Hour.Min,Slider_Hour.Max);
	SLIDER_SetValue(WM_GetDialogItem(hWin,GUI_ID_SLIDER0),Time_Struct.RTC_Hours);
	SLIDER_SetSkin(WM_GetDialogItem(hWin, GUI_ID_SLIDER0),DrawSkinFlex_Slider);

	SLIDER_SetRange(WM_GetDialogItem(hWin,GUI_ID_SLIDER1),SliderAttribute.Min,SliderAttribute.Max);
	SLIDER_SetValue(WM_GetDialogItem(hWin,GUI_ID_SLIDER1),Time_Struct.RTC_Minutes);
	SLIDER_SetSkin(WM_GetDialogItem(hWin, GUI_ID_SLIDER1),DrawSkinFlex_Slider);

	SLIDER_SetRange(WM_GetDialogItem(hWin,GUI_ID_SLIDER2),SliderAttribute.Min,SliderAttribute.Max);
	SLIDER_SetValue(WM_GetDialogItem(hWin,GUI_ID_SLIDER2),Time_Struct.RTC_Seconds);
	SLIDER_SetSkin(WM_GetDialogItem(hWin, GUI_ID_SLIDER2),DrawSkinFlex_Slider);

	BUTTON_SetBitmapEx(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),BUTTON_BI_UNPRESSED,&Back_Button_Bitmap,2,3);
	BUTTON_SetBitmapEx(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),BUTTON_BI_UNPRESSED,&OK_Button_Bitmap,2,2);
}
//������Adjust���ڻص�
//������pMsg �ص���Ϣ 
void AdjustSlider_Changed(WM_HWIN hWin,int ID) 
{
    switch (ID) 
    {
		case GUI_ID_SLIDER0:
			TimeSet.RTC_Hours = SLIDER_GetValue(WM_GetDialogItem(hWin,GUI_ID_SLIDER0)) ;
			Time_Struct.RTC_Hours = TimeSet.RTC_Hours;
			WM_InvalidateRect(WM_HBKWIN,&windowHourRect);
			break;
		case GUI_ID_SLIDER1:
			TimeSet.RTC_Minutes = SLIDER_GetValue(WM_GetDialogItem(hWin,GUI_ID_SLIDER1)) ;
			WM_InvalidateRect(WM_HBKWIN,&windowMinRect);
		   Time_Struct.RTC_Minutes = TimeSet.RTC_Minutes;
			break;
		case GUI_ID_SLIDER2:
			TimeSet.RTC_Seconds = SLIDER_GetValue(WM_GetDialogItem(hWin,GUI_ID_SLIDER2)) ;
			timeDraw.arc_x = 215 + TimeArc_radius * cos(1.5708 - TimeSet.RTC_Seconds * 0.1047);
			timeDraw.arc_y = 240 - TimeArc_radius * sin(1.5708 - TimeSet.RTC_Seconds * 0.1047);
			WM_InvalidateRect(WM_HBKWIN,&windowRect);
			break;
    }
}
// button �¼�����
void AdjustButton_Click(int ID)
{
	switch (ID)
	{
		case GUI_ID_BUTTON0:
			adjustWindow = 0;
			WM_DeleteWindow(Adjust_HWIN);
			WM_ShowWindow(Button_HWIN);
			break;				
		case GUI_ID_BUTTON1:	
			adjustWindow = 0;
			WM_DeleteWindow(Adjust_HWIN);
			WM_ShowWindow(Button_HWIN);
			RTC_SetTime(RTC_Format_BIN,&TimeSet);
			break;				
		default:	break;	
	}
}
static void _cbAdjustWindow(WM_MESSAGE * pMsg) 
{
    int NCode, ID;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            AdjustWindow_Paint(pMsg);
            break;
        case WM_INIT_DIALOG:
            AdjustWindow_Init(pMsg);
            break;
        case WM_NOTIFY_PARENT:
            ID = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;   

			switch (NCode)
			{
				case WM_NOTIFICATION_RELEASED:	//button�¼�����
					AdjustButton_Click(ID);
				break;
				case WM_NOTIFICATION_VALUE_CHANGED:  //slider�¼�����
					AdjustSlider_Changed(hWin,ID);
				break;
			}
            break;
        default:	WM_DefaultProc(pMsg);           
    }
}

