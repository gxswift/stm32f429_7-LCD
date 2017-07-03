/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.32                          *
*        Compiled Oct  8 2015, 11:59:02                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_BUTTON_0 (GUI_ID_USER + 0x02)
#define ID_BUTTON_1 (GUI_ID_USER + 0x03)
#define ID_LISTWHEEL_0 (GUI_ID_USER + 0x04)
#define ID_LISTWHEEL_1 (GUI_ID_USER + 0x05)
#define ID_LISTWHEEL_2 (GUI_ID_USER + 0x06)
#define DATE_DIS (WM_USER+1)
// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 50, 800, 430, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "return", ID_BUTTON_0, 715, 346, 60, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "OK", ID_BUTTON_1, 615, 346, 60, 45, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, "Listwheel", ID_LISTWHEEL_0, 600, 60, 50, 200, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, "Listwheel", ID_LISTWHEEL_1, 650, 60, 50, 200, 0, 0x0, 0 },
  { LISTWHEEL_CreateIndirect, "Listwheel", ID_LISTWHEEL_2, 700, 60, 50, 200, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
static int _OwnerDraw(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
	switch (pDrawItemInfo->Cmd) {
	case WIDGET_DRAW_OVERLAY:
	/*	GUI_SetColor(GUI_RED);
		GUI_DrawHLine(125, 0, 130);
		GUI_DrawHLine(126, 0, 130);
		GUI_DrawHLine(127, 0, 130);
		GUI_DrawHLine(179, 0, 130);
		GUI_DrawHLine(180, 0, 130);
		GUI_DrawHLine(181, 0, 130);*/
	/*break;
	case WIDGET_DRAW_BACKGROUND:*/
		GUI_DrawGradientV(0, 0, 50, 80, GUI_DARKGRAY, 0xee000000 | GUI_BLUE);
		GUI_DrawGradientV(0, 120, 50, 200, 0xee000000 | GUI_BLUE,  GUI_DARKGRAY);
		break;
	default:
		return LISTWHEEL_OwnerDraw(pDrawItemInfo);
	}
	return 0;
}
// USER START (Optionally insert additional static code)
// USER END
extern WM_HWIN CreateWin1(void);
extern WM_HWIN WIN_Header;
CALENDAR_DATE Date;

	int Hour;
	int Min;
	int Sec;

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  static WM_HWIN hCalen;
  int    i;
  char   str[10];
  static int Select1,d1;
  static int Select2,d2;
  static int Select3,d3;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_PAINT:
	  GUI_DrawGradientV(0, 0, 799, 439, GUI_WHITE, GUI_CYAN);
	  GUI_SetTextMode(GUI_TM_TRANS);
	  GUI_SetColor(GUI_BLACK);
	  GUI_SetFont(&GUI_Font20B_1);
	  GUI_DispDecAt(d1,615,300,2);
	  GUI_DispDecAt(d2, 665, 300, 2);
	  GUI_DispDecAt(d3, 715, 300, 2);
	  GUI_DispStringAt(":", 640, 300);
	  GUI_DispStringAt(":", 690, 300);
	  break;
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Listwheel'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_0);
	LISTWHEEL_SetLineHeight(hItem, 40);
	LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_UNSEL, GUI_WHITE);
	LISTWHEEL_SetTextAlign(hItem, GUI_TA_VCENTER | GUI_TA_HCENTER);

	LISTWHEEL_SetFont(hItem, &GUI_Font32B_1);
	for (i = 0; i < 24; i++)
	{
		sprintf(str, "%d", i);
		LISTWHEEL_AddString(hItem, str);
	}
	LISTWHEEL_SetOwnerDraw(hItem, _OwnerDraw);
	LISTWHEEL_SetSel(hItem, Hour);
	if (Hour>2)
		LISTWHEEL_SetPos(hItem, Hour - 2);
	else
		LISTWHEEL_SetPos(hItem, Hour + 22);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_1);
	LISTWHEEL_SetLineHeight(hItem, 40);
	LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_UNSEL, GUI_WHITE);
	LISTWHEEL_SetTextAlign(hItem, GUI_TA_VCENTER | GUI_TA_HCENTER);

	LISTWHEEL_SetFont(hItem, &GUI_Font32B_1);
	for (i = 0; i < 60; i++)
	{
		sprintf(str, "%d", i);
		LISTWHEEL_AddString(hItem, str);
	}
	LISTWHEEL_SetOwnerDraw(hItem, _OwnerDraw);
	LISTWHEEL_SetSel(hItem, Min);
	if (Min>2)
		LISTWHEEL_SetPos(hItem, Min - 2);
	else
		LISTWHEEL_SetPos(hItem, Min + 58);


	hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_2);
	LISTWHEEL_SetLineHeight(hItem, 40);
	LISTWHEEL_SetBkColor(hItem, LISTWHEEL_CI_UNSEL, GUI_WHITE);
	LISTWHEEL_SetTextAlign(hItem, GUI_TA_VCENTER | GUI_TA_HCENTER);
	LISTWHEEL_SetFont(hItem, &GUI_Font32B_1);
	for (i = 0; i < 60; i++)
	{
		sprintf(str, "%d", i);
		LISTWHEEL_AddString(hItem, str);
	}
	LISTWHEEL_SetOwnerDraw(hItem, _OwnerDraw);
	LISTWHEEL_SetSel(hItem, Sec);
	if (Sec>2)
	LISTWHEEL_SetPos(hItem, Sec-2);
	else
	LISTWHEEL_SetPos(hItem, Sec+58);

	d1 = Hour;
	d2 = Min;
	d3 = Sec;

	CALENDAR_SetDefaultFont(CALENDAR_FI_CONTENT,&GUI_Font32B_1);
	CALENDAR_SetDefaultFont(CALENDAR_FI_HEADER, &GUI_Font32_1);

	CALENDAR_SetDefaultSize(CALENDAR_SI_HEADER,40);
	CALENDAR_SetDefaultSize(CALENDAR_SI_CELL_X,80);
	CALENDAR_SetDefaultSize(CALENDAR_SI_CELL_Y,50);

	hCalen = CALENDAR_Create(pMsg->hWin,20,20,Date.Year,Date.Month,Date.Day,0,0,0);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'return'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		  WM_DeleteWindow(pMsg->hWin);
		  CreateWin1();
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'OK'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
		  hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_0);
		  Select1 = LISTWHEEL_GetPos(hItem);

		  if (Select1 >21)d1 = Select1- 22;
		  else d1 = Select1 + 2;
		  LISTWHEEL_SetSel(hItem,d1);

		//  Select = Select2;

		  hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_1);
		  Select2 = LISTWHEEL_GetPos(hItem);

		  if (Select2 >57)d2 = Select2 - 58;
		  else d2 = Select2 + 2;
		  LISTWHEEL_SetSel(hItem, d2);

		  hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_2);
		  Select3 = LISTWHEEL_GetPos(hItem);

		  if (Select3 >57)d3 = Select3 - 58;
		  else d3 = Select3 + 2;
		  LISTWHEEL_SetSel(hItem, d3);

		  Hour = d1;
		  Min = d2;
		  Sec = d3;


		  // hCalen
		  CALENDAR_GetSel(hCalen, &Date);
		  CALENDAR_SetDate(hCalen, &Date);

		  WM_SendMessageNoPara(WIN_Header, DATE_DIS);
		  WM_InvalidateWindow(pMsg->hWin);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_LISTWHEEL_0: // Notifications sent by 'Listwheel'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
		  hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_0);
		  Select1 = LISTWHEEL_GetPos(hItem);
		  if (Select1 >21)d1 = Select1 - 22;
		  else d1 = Select1 + 2;

		  hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_1);
		  Select2 = LISTWHEEL_GetPos(hItem);
		  if (Select2 >57)d2 = Select2 - 58;
		  else d2 = Select2 + 2;

		  hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_2);
		  Select3 = LISTWHEEL_GetPos(hItem);
		  if (Select3 >57)d3 = Select3 - 58;
		  else d3 = Select3 + 2;
		  WM_InvalidateWindow(pMsg->hWin);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
	case ID_LISTWHEEL_1: // Notifications sent by 'Listwheel'
		switch (NCode) {
		case WM_NOTIFICATION_CLICKED:
			// USER START (Optionally insert code for reacting on notification message)
			// USER END
			break;
		case WM_NOTIFICATION_RELEASED:
			// USER START (Optionally insert code for reacting on notification message)
			// USER END
			break;
		case WM_NOTIFICATION_SEL_CHANGED:
			// USER START (Optionally insert code for reacting on notification message)
			hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_0);
			Select1 = LISTWHEEL_GetPos(hItem);
			if (Select1 >21)d1 = Select1 - 22;
			else d1 = Select1 + 2;

			hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_1);
			Select2 = LISTWHEEL_GetPos(hItem);
			if (Select2 >57)d2 = Select2 - 58;
			else d2 = Select2 + 2;

			hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_2);
			Select3 = LISTWHEEL_GetPos(hItem);
			if (Select3 >57)d3 = Select3 - 58;
			else d3 = Select3 + 2;
			WM_InvalidateWindow(pMsg->hWin);
			// USER END
			break;
			// USER START (Optionally insert additional code for further notification handling)
			// USER END
		}
		break;
		// USER START (Optionally insert additional code for further Ids)
		// USER END
	case ID_LISTWHEEL_2: // Notifications sent by 'Listwheel'
		switch (NCode) {
		case WM_NOTIFICATION_CLICKED:
			// USER START (Optionally insert code for reacting on notification message)
			// USER END
			break;
		case WM_NOTIFICATION_RELEASED:
			// USER START (Optionally insert code for reacting on notification message)
			// USER END
			break;
		case WM_NOTIFICATION_SEL_CHANGED:
			// USER START (Optionally insert code for reacting on notification message)
			hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_0);
			Select1 = LISTWHEEL_GetPos(hItem);
			if (Select1 >21)d1 = Select1 - 22;
			else d1 = Select1 + 2;

			hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_1);
			Select2 = LISTWHEEL_GetPos(hItem);
			if (Select2 >57)d2 = Select2 - 58;
			else d2 = Select2 + 2;

			hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_2);
			Select3 = LISTWHEEL_GetPos(hItem);
			if (Select3 >57)d3 = Select3 - 58;
			else d3 = Select3 + 2;
			WM_InvalidateWindow(pMsg->hWin);
			// USER END
			break;
			// USER START (Optionally insert additional code for further notification handling)
			// USER END
		}
		break;
		// USER START (Optionally insert additional code for further Ids)
		// USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateWindow
*/
WM_HWIN CreateWin3(void);
WM_HWIN CreateWin3(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
