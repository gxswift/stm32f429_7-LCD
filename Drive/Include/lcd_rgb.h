#ifndef __LCD_H
#define	__LCD_H

#include "stm32f4xx.h"
#include "lcd_pwm.h"

#define HBP  46
#define VBP  23

#define HSW   1056
#define VSW   525

#define HFP  210
#define VFP   22

#define  LCD_PIXEL_WIDTH    ((uint16_t)800)
#define  LCD_PIXEL_HEIGHT   ((uint16_t)480)

#define LCD_FRAME_BUFFER       ((uint32_t)0xD0000000)
#define BUFFER_OFFSET          ((uint32_t)800*480*4)    //sdram为16位的,液晶RGB888
#define LCD_PIXCELS            ((uint32_t)800*480) 

/*---------------------- 引脚定义 ----------------------------*/

//红色数据线
#define LTDC_R0_PORT        	GPIOI
#define LTDC_R0_PIN         	GPIO_Pin_15
#define LTDC_R0_PINSOURCE     GPIO_PinSource15
#define LTDC_R0_AF			   GPIO_AF_LTDC

#define LTDC_R1_PORT        	GPIOJ
#define LTDC_R1_PIN         	GPIO_Pin_0
#define LTDC_R1_PINSOURCE     GPIO_PinSource0
#define LTDC_R1_AF			   GPIO_AF_LTDC

#define LTDC_R2_PORT        	GPIOJ
#define LTDC_R2_PIN         	GPIO_Pin_1
#define LTDC_R2_PINSOURCE     GPIO_PinSource1
#define LTDC_R2_AF			   GPIO_AF_LTDC

#define LTDC_R3_PORT        	GPIOJ
#define LTDC_R3_PIN         	GPIO_Pin_2
#define LTDC_R3_PINSOURCE     GPIO_PinSource2
#define LTDC_R3_AF			   GPIO_AF_LTDC

#define LTDC_R4_PORT        	GPIOJ
#define LTDC_R4_PIN         	GPIO_Pin_3
#define LTDC_R4_PINSOURCE     GPIO_PinSource3
#define LTDC_R4_AF			   GPIO_AF_LTDC

#define LTDC_R5_PORT        	GPIOJ
#define LTDC_R5_PIN         	GPIO_Pin_4
#define LTDC_R5_PINSOURCE     GPIO_PinSource4
#define LTDC_R5_AF			   GPIO_AF_LTDC

#define LTDC_R6_PORT        	GPIOJ
#define LTDC_R6_PIN         	GPIO_Pin_5
#define LTDC_R6_PINSOURCE     GPIO_PinSource5
#define LTDC_R6_AF			   GPIO_AF_LTDC

#define LTDC_R7_PORT        	GPIOJ
#define LTDC_R7_PIN         	GPIO_Pin_6
#define LTDC_R7_PINSOURCE     GPIO_PinSource6
#define LTDC_R7_AF			   GPIO_AF_LTDC

//绿色数据线
#define LTDC_G0_PORT        	GPIOJ
#define LTDC_G0_PIN         	GPIO_Pin_7
#define LTDC_G0_PINSOURCE     GPIO_PinSource7
#define LTDC_G0_AF			   GPIO_AF_LTDC

#define LTDC_G1_PORT        	GPIOJ
#define LTDC_G1_PIN         	GPIO_Pin_8
#define LTDC_G1_PINSOURCE     GPIO_PinSource8
#define LTDC_G1_AF			   GPIO_AF_LTDC

#define LTDC_G2_PORT        	GPIOJ
#define LTDC_G2_PIN         	GPIO_Pin_9
#define LTDC_G2_PINSOURCE     GPIO_PinSource9
#define LTDC_G2_AF			   GPIO_AF_LTDC

#define LTDC_G3_PORT        	GPIOJ
#define LTDC_G3_PIN         	GPIO_Pin_10
#define LTDC_G3_PINSOURCE     GPIO_PinSource10
#define LTDC_G3_AF			   GPIO_AF_LTDC

#define LTDC_G4_PORT        	GPIOJ
#define LTDC_G4_PIN         	GPIO_Pin_11
#define LTDC_G4_PINSOURCE     GPIO_PinSource11
#define LTDC_G4_AF			   GPIO_AF_LTDC

#define LTDC_G5_PORT        	GPIOK
#define LTDC_G5_PIN         	GPIO_Pin_0
#define LTDC_G5_PINSOURCE     GPIO_PinSource0
#define LTDC_G5_AF			   GPIO_AF_LTDC

#define LTDC_G6_PORT        	GPIOK
#define LTDC_G6_PIN         	GPIO_Pin_1
#define LTDC_G6_PINSOURCE     GPIO_PinSource1
#define LTDC_G6_AF			   GPIO_AF_LTDC

#define LTDC_G7_PORT        	GPIOK
#define LTDC_G7_PIN         	GPIO_Pin_2
#define LTDC_G7_PINSOURCE     GPIO_PinSource2
#define LTDC_G7_AF			   GPIO_AF_LTDC

//蓝色数据线
#define LTDC_B0_PORT        	GPIOJ
#define LTDC_B0_PIN         	GPIO_Pin_12
#define LTDC_B0_PINSOURCE     GPIO_PinSource12
#define LTDC_B0_AF			   GPIO_AF_LTDC

#define LTDC_B1_PORT       	GPIOJ
#define LTDC_B1_PIN           GPIO_Pin_13
#define LTDC_B1_PINSOURCE     GPIO_PinSource13
#define LTDC_B1_AF			   GPIO_AF_LTDC

#define LTDC_B2_PORT        	GPIOJ
#define LTDC_B2_PIN         	GPIO_Pin_14
#define LTDC_B2_PINSOURCE     GPIO_PinSource14
#define LTDC_B2_AF			   GPIO_AF_LTDC

#define LTDC_B3_PORT        	GPIOJ
#define LTDC_B3_PIN         	GPIO_Pin_15
#define LTDC_B3_PINSOURCE     GPIO_PinSource15
#define LTDC_B3_AF			   GPIO_AF_LTDC

#define LTDC_B4_PORT        	GPIOK
#define LTDC_B4_PIN         	GPIO_Pin_3
#define LTDC_B4_PINSOURCE     GPIO_PinSource3
#define LTDC_B4_AF			   GPIO_AF9_LTDC

#define LTDC_B5_PORT        	GPIOK
#define LTDC_B5_PIN         	GPIO_Pin_4
#define LTDC_B5_PINSOURCE     GPIO_PinSource4
#define LTDC_B5_AF			   GPIO_AF_LTDC

#define LTDC_B6_PORT        	GPIOK
#define LTDC_B6_PIN         	GPIO_Pin_5
#define LTDC_B6_PINSOURCE     GPIO_PinSource5
#define LTDC_B6_AF			   GPIO_AF_LTDC

#define LTDC_B7_PORT        	GPIOK
#define LTDC_B7_PIN         	GPIO_Pin_6
#define LTDC_B7_PINSOURCE     GPIO_PinSource6
#define LTDC_B7_AF			   GPIO_AF_LTDC

//控制信号线
#define LTDC_CLK_PORT         GPIOI
#define LTDC_CLK_PIN          GPIO_Pin_14
#define LTDC_CLK_PINSOURCE    GPIO_PinSource14
#define LTDC_CLK_AF			   GPIO_AF_LTDC

#define LTDC_HSYNC_PORT       GPIOI
#define LTDC_HSYNC_PIN        GPIO_Pin_12
#define LTDC_HSYNC_PINSOURCE  GPIO_PinSource12
#define LTDC_HSYNC_AF			GPIO_AF_LTDC

#define LTDC_VSYNC_PORT       GPIOI
#define LTDC_VSYNC_PIN        GPIO_Pin_13
#define LTDC_VSYNC_PINSOURCE  GPIO_PinSource13
#define LTDC_VSYNC_AF			GPIO_AF_LTDC


#define LTDC_DE_PORT          GPIOK
#define LTDC_DE_PIN           GPIO_Pin_7
#define LTDC_DE_PINSOURCE     GPIO_PinSource7
#define LTDC_DE_AF			   GPIO_AF_LTDC


#define LTDC_Black_PORT       GPIOD
#define LTDC_Black_PIN        GPIO_Pin_13



/*---------------------- 函数声明 ----------------------------*/ 

void     LCD_Init(void);

#endif 
