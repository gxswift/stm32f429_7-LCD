#ifndef MY_EMWINSKIN_H
#define MY_EMWINSKIN_H

#include "GUI.h"
#include "WM.h"
#include "BUTTON.h"
#include "PROGBAR.h"
#include "SLIDER.h"

typedef struct 
{
	int         Radius;
	GUI_COLOR	Pressed;
	GUI_COLOR	UnPressed;

}_ButtonRedrawColor;
typedef struct 
{
	GUI_COLOR	progress;
	GUI_COLOR	background;

}_ProgbarRedrawColor;
typedef	struct 
{
	GUI_COLOR  ThumbColor;
	GUI_COLOR  ShaftColor;
	GUI_COLOR  FocusColor;
	int TickSize;
	int ShaftSize;

}_SliderRedrawColor;
typedef	struct 
{
	int  Min;
	int  Set;
	int  Max;
	char Width;
	GUI_COLOR ShaftColor;
	GUI_COLOR ProcessColor;
	GUI_COLOR ThumbColor;

}_SliderAttribute;

#define	  SliderColor_Shaft    0xB9B9B9
#define	  SliderColor_Process  0xA47611
#define	  SliderColor_Thumb    0x9D9D9F
#define	  SliderColor_Focus    0xebf0f3

void  Button_RedrawSkin(_ButtonRedrawColor * pRedrawColor);
void  Progbar_RedrawSkin(_ProgbarRedrawColor * pRedrawColor);
void  Slider_RedrawSkin(_SliderRedrawColor * pRedrawColor);

#endif

