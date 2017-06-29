/***
	***************************************************************************
	*	@file  	lcd.c
	*	@brief   使用STM32F29本身的控制器驱动液晶屏，以下代码移植于官方 STM32F429I_DISCOVERY 
	*				实验板的例程，并作出相应的修改
   ******************************************************************************
   *  
	* 
	* 
	* 
	***************************************************************************
***/

#include "lcd_rgb.h"


//
//

void LCD_GPIO_Config(void)
{ 
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD |      
								   RCC_AHB1Periph_GPIOJ | RCC_AHB1Periph_GPIOK | RCC_AHB1Periph_GPIOI,ENABLE); 	
						
	GPIO_InitStruct.GPIO_Pin   = LTDC_R0_PIN;                             
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;

	// LCD 颜色 R 引脚配置 
	GPIO_PinAFConfig(LTDC_R0_PORT, LTDC_R0_PINSOURCE, LTDC_R0_AF);	
	GPIO_PinAFConfig(LTDC_R1_PORT, LTDC_R1_PINSOURCE, LTDC_R1_AF);	
	GPIO_PinAFConfig(LTDC_R2_PORT, LTDC_R2_PINSOURCE, LTDC_R2_AF);	
	GPIO_PinAFConfig(LTDC_R3_PORT, LTDC_R3_PINSOURCE, LTDC_R3_AF);	
	GPIO_PinAFConfig(LTDC_R4_PORT, LTDC_R4_PINSOURCE, LTDC_R4_AF);	
	GPIO_PinAFConfig(LTDC_R5_PORT, LTDC_R5_PINSOURCE, LTDC_R5_AF);	
	GPIO_PinAFConfig(LTDC_R6_PORT, LTDC_R6_PINSOURCE, LTDC_R6_AF);
	GPIO_PinAFConfig(LTDC_R7_PORT, LTDC_R7_PINSOURCE, LTDC_R7_AF);	

	GPIO_InitStruct.GPIO_Pin = LTDC_R0_PIN;	
	GPIO_Init(LTDC_R0_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R1_PIN;
	GPIO_Init(LTDC_R1_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R2_PIN;
	GPIO_Init(LTDC_R2_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R3_PIN;
	GPIO_Init(LTDC_R3_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R4_PIN;
	GPIO_Init(LTDC_R4_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R5_PIN;
	GPIO_Init(LTDC_R5_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R6_PIN;
	GPIO_Init(LTDC_R6_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_R7_PIN;
	GPIO_Init(LTDC_R7_PORT, &GPIO_InitStruct);

  
  // LCD 颜色 G 引脚配置 
  
	GPIO_PinAFConfig(LTDC_G0_PORT, LTDC_G0_PINSOURCE, LTDC_G0_AF);  
	GPIO_PinAFConfig(LTDC_G1_PORT, LTDC_G1_PINSOURCE, LTDC_G1_AF); 
	GPIO_PinAFConfig(LTDC_G2_PORT, LTDC_G2_PINSOURCE, LTDC_G2_AF); 
	GPIO_PinAFConfig(LTDC_G3_PORT, LTDC_G3_PINSOURCE, LTDC_G3_AF);  
	GPIO_PinAFConfig(LTDC_G4_PORT, LTDC_G4_PINSOURCE, LTDC_G4_AF);  
	GPIO_PinAFConfig(LTDC_G5_PORT, LTDC_G5_PINSOURCE, LTDC_G5_AF);  
	GPIO_PinAFConfig(LTDC_G6_PORT, LTDC_G6_PINSOURCE, LTDC_G6_AF);  
	GPIO_PinAFConfig(LTDC_G7_PORT, LTDC_G7_PINSOURCE, LTDC_G7_AF);  
  
	GPIO_InitStruct.GPIO_Pin = LTDC_G0_PIN;
	GPIO_Init(LTDC_G0_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G1_PIN;
	GPIO_Init(LTDC_G1_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G2_PIN;
	GPIO_Init(LTDC_G2_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G3_PIN;
	GPIO_Init(LTDC_G3_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G4_PIN;
	GPIO_Init(LTDC_G4_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G5_PIN;
	GPIO_Init(LTDC_G5_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G6_PIN;
	GPIO_Init(LTDC_G6_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_G7_PIN;
	GPIO_Init(LTDC_G7_PORT, &GPIO_InitStruct);

  
  // LCD 颜色 B 引脚配置 
  
	GPIO_PinAFConfig(LTDC_B0_PORT, LTDC_B0_PINSOURCE, LTDC_B0_AF);  
	GPIO_PinAFConfig(LTDC_B2_PORT, LTDC_B2_PINSOURCE, LTDC_B2_AF);  
	GPIO_PinAFConfig(LTDC_B3_PORT, LTDC_B3_PINSOURCE, LTDC_B3_AF);
	GPIO_PinAFConfig(LTDC_B4_PORT, LTDC_B4_PINSOURCE, LTDC_B4_AF);  
	GPIO_PinAFConfig(LTDC_B5_PORT, LTDC_B5_PINSOURCE, LTDC_B5_AF);  
	GPIO_PinAFConfig(LTDC_B6_PORT, LTDC_B6_PINSOURCE, LTDC_B6_AF);  
	GPIO_PinAFConfig(LTDC_B7_PORT, LTDC_B7_PINSOURCE, LTDC_B7_AF);  

	GPIO_InitStruct.GPIO_Pin = LTDC_B0_PIN;
	GPIO_Init(LTDC_B0_PORT, &GPIO_InitStruct);
	
//	GPIO_InitStruct.GPIO_Pin = LTDC_B1_PIN;
//	GPIO_Init(LTDC_B1_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LTDC_B2_PIN;
	GPIO_Init(LTDC_B2_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_B3_PIN;
	GPIO_Init(LTDC_B3_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_B4_PIN;
	GPIO_Init(LTDC_B4_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_B5_PIN;
	GPIO_Init(LTDC_B5_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_B6_PIN;
	GPIO_Init(LTDC_B6_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_B7_PIN;
	GPIO_Init(LTDC_B7_PORT, &GPIO_InitStruct);

  
  //信号线
	GPIO_PinAFConfig(LTDC_CLK_PORT, LTDC_CLK_PINSOURCE, LTDC_CLK_AF); 
	GPIO_PinAFConfig(LTDC_HSYNC_PORT, LTDC_HSYNC_PINSOURCE, LTDC_HSYNC_AF);  
	GPIO_PinAFConfig(LTDC_VSYNC_PORT, LTDC_VSYNC_PINSOURCE, LTDC_VSYNC_AF);  
	GPIO_PinAFConfig(LTDC_DE_PORT, LTDC_DE_PINSOURCE, LTDC_DE_AF);
    
	GPIO_InitStruct.GPIO_Pin = LTDC_CLK_PIN;
	GPIO_Init(LTDC_CLK_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_HSYNC_PIN;
	GPIO_Init(LTDC_HSYNC_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_VSYNC_PIN;
	GPIO_Init(LTDC_VSYNC_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LTDC_DE_PIN;
	GPIO_Init(LTDC_DE_PORT, &GPIO_InitStruct);
			
	//背光
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;

	GPIO_InitStruct.GPIO_Pin = LTDC_Black_PIN; 
	GPIO_Init(LTDC_Black_PORT, &GPIO_InitStruct);

	GPIO_SetBits(LTDC_Black_PORT,LTDC_Black_PIN);

}

void LCD_Init(void)
{ 
	LTDC_InitTypeDef       LTDC_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_LTDC, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2D, ENABLE); 

	LCD_GPIO_Config();  
	LCD_PWMinit(100);

	/* LTDC Configuration *********************************************************/  
	/* Polarity configuration */
	/* Initialize the horizontal synchronization polarity as active low */
	LTDC_InitStruct.LTDC_HSPolarity = LTDC_HSPolarity_AL;     
	/* Initialize the vertical synchronization polarity as active low */  
	LTDC_InitStruct.LTDC_VSPolarity = LTDC_VSPolarity_AL;     
	/* Initialize the data enable polarity as active low */
	LTDC_InitStruct.LTDC_DEPolarity = LTDC_DEPolarity_AL;     
	/* Initialize the pixel clock polarity as input pixel clock */ 
	LTDC_InitStruct.LTDC_PCPolarity = LTDC_PCPolarity_IPC;

	/* Configure R,G,B component values for LCD background color */                   
	LTDC_InitStruct.LTDC_BackgroundRedValue = 0;            
	LTDC_InitStruct.LTDC_BackgroundGreenValue = 0;          
	LTDC_InitStruct.LTDC_BackgroundBlueValue = 0;   

	//时钟配置

	#ifdef LCD_1024 
	RCC_PLLSAIConfig(330, 6, 4);
	RCC_LTDCCLKDivConfig(RCC_PLLSAIDivR_Div2);
	#else
	RCC_PLLSAIConfig(330, 7, 5);
	RCC_LTDCCLKDivConfig(RCC_PLLSAIDivR_Div2);
	#endif
	/* Enable PLLSAI Clock */
	RCC_PLLSAICmd(ENABLE);
	/* Wait for PLLSAI activation */
	while(RCC_GetFlagStatus(RCC_FLAG_PLLSAIRDY) == RESET)
	{
	}

	/* Timing configuration */  
	/* Configure horizontal synchronization width */
	LTDC_InitStruct.LTDC_HorizontalSync =HSW;
	/* Configure vertical synchronization height */
	LTDC_InitStruct.LTDC_VerticalSync = VSW;
	/* Configure accumulated horizontal back porch */
	LTDC_InitStruct.LTDC_AccumulatedHBP =HBP;
	/* Configure accumulated vertical back porch */
	LTDC_InitStruct.LTDC_AccumulatedVBP = VBP;
	/* Configure accumulated active width */
	LTDC_InitStruct.LTDC_AccumulatedActiveW = LCD_PIXEL_WIDTH+HBP;
	/* Configure accumulated active height */
	LTDC_InitStruct.LTDC_AccumulatedActiveH = LCD_PIXEL_HEIGHT+VBP;
	/* Configure total width */
	LTDC_InitStruct.LTDC_TotalWidth =LCD_PIXEL_WIDTH + HBP + HFP; 
	/* Configure total height */
	LTDC_InitStruct.LTDC_TotalHeigh =LCD_PIXEL_HEIGHT + VBP + VFP;

	LTDC_Init(&LTDC_InitStruct);

	LTDC_Cmd(ENABLE);
}  

