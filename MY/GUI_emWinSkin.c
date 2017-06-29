#include "GUI_emwinSkin.h"


void  Button_RedrawSkin(_ButtonRedrawColor * pRedrawColor)
{
	BUTTON_SKINFLEX_PROPS	Button_Skin;
	GUI_COLOR  ButtonColor = pRedrawColor->Pressed;
	int i;
	for(i=0;i<2;i++)
	{
		Button_Skin.aColorFrame[0] = ButtonColor;
		Button_Skin.aColorFrame[1] = ButtonColor;
		Button_Skin.aColorFrame[2] = ButtonColor;
		Button_Skin.aColorUpper[0] = ButtonColor;
		Button_Skin.aColorUpper[1] = ButtonColor;
		Button_Skin.aColorLower[0] = ButtonColor;
		Button_Skin.aColorLower[1] = ButtonColor;
		Button_Skin.Radius = pRedrawColor->Radius;

		switch (i)
		{
			case 0:
				BUTTON_SetSkinFlexProps(&Button_Skin,BUTTON_SKINFLEX_PI_ENABLED);
				BUTTON_SetSkinFlexProps(&Button_Skin,BUTTON_SKINFLEX_PI_FOCUSSED);
				ButtonColor = pRedrawColor->UnPressed;
			break;
			case 1:
				BUTTON_SetSkinFlexProps(&Button_Skin,BUTTON_SKINFLEX_PI_PRESSED);
			break;
		}
	}

}
void  Progbar_RedrawSkin(_ProgbarRedrawColor * pRedrawColor)
{
	PROGBAR_SKINFLEX_PROPS  Progbar_Skin;
	GUI_COLOR  Progbar_pro  = pRedrawColor->progress;
	GUI_COLOR  Progbar_Back = pRedrawColor->background;	

	Progbar_Skin.aColorLowerL[0] = Progbar_pro;
	Progbar_Skin.aColorLowerL[1] = Progbar_pro;
	Progbar_Skin.aColorUpperL[0] = Progbar_pro;
	Progbar_Skin.aColorUpperL[1] = Progbar_pro;

	Progbar_Skin.aColorLowerR[0] = Progbar_Back;
	Progbar_Skin.aColorLowerR[1] = Progbar_Back;
	Progbar_Skin.aColorUpperR[0] = Progbar_Back;
	Progbar_Skin.aColorUpperR[1] = Progbar_Back;

	PROGBAR_SetSkinFlexProps(&Progbar_Skin,0);		
}
void  Slider_RedrawSkin(_SliderRedrawColor * pRedrawColor)
{
	SLIDER_SKINFLEX_PROPS Slider_Skin;
	GUI_COLOR Color_Thumb = pRedrawColor->ThumbColor;
	GUI_COLOR Color_Shaft = pRedrawColor->ShaftColor;
	GUI_COLOR Color_Focus = pRedrawColor->FocusColor;

	Slider_Skin.aColorFrame[0] = Color_Thumb;
	Slider_Skin.aColorFrame[1] = Color_Thumb;
	Slider_Skin.aColorInner[0] = Color_Thumb;
	Slider_Skin.aColorInner[1] = Color_Thumb;
	Slider_Skin.aColorShaft[0] = Color_Shaft;
	Slider_Skin.aColorShaft[1] = Color_Shaft;
	Slider_Skin.aColorShaft[2] = Color_Shaft;
	Slider_Skin.ColorFocus     = Color_Focus;
	Slider_Skin.TickSize = pRedrawColor->TickSize;
	Slider_Skin.ShaftSize = pRedrawColor->ShaftSize;

	SLIDER_SetSkinFlexProps(&Slider_Skin,SLIDER_SKINFLEX_PI_UNPRESSED);
	SLIDER_SetSkinFlexProps(&Slider_Skin,SLIDER_SKINFLEX_PI_PRESSED);
}
