#ifndef __GT9XX_H__
#define __GT9XX_H__

#include "stm32f4xx.h"

/*---------------------- IIC相关定义 ------------------------*/

#define Response_OK 1  //IIC响应
#define Response_ERR 0

#define Touch_DelayVaule 5  //通讯延时时间

// IO口相关宏
#define IIC_Touch_SCL_CLK     RCC_AHB1Periph_GPIOC 
#define IIC_Touch_SCL_PORT    GPIOC                   
#define IIC_Touch_SCL_PIN     GPIO_Pin_13   
         
#define IIC_Touch_SDA_CLK     RCC_AHB1Periph_GPIOB 
#define IIC_Touch_SDA_PORT    GPIOB                   
#define IIC_Touch_SDA_PIN     GPIO_Pin_2             

// IO口操作
#define SCL(a)	if (a)	\
					GPIO_SetBits(IIC_Touch_SCL_PORT,IIC_Touch_SCL_PIN);\
					else		\
					GPIO_ResetBits(IIC_Touch_SCL_PORT,IIC_Touch_SCL_PIN)

#define SDA(a)	if (a)	\
					GPIO_SetBits(IIC_Touch_SDA_PORT,IIC_Touch_SDA_PIN);\
					else		\
					GPIO_ResetBits(IIC_Touch_SDA_PORT,IIC_Touch_SDA_PIN)
	
/*---------------------- GT9XX芯片相关定义 ------------------------*/
					
#define TOUCH_MAX   5	//最大触摸点数

typedef struct 
{
	u8  flag;	//触摸标志位，为1时表示有触摸操作
	u8  num;		//触摸点数
	u16 x[TOUCH_MAX];	//x坐标
	u16 y[TOUCH_MAX];	//y坐标
}TouchStructure;

extern TouchStructure touchInfo;	//结构体声明

#define GT9XX_IIC_RADDR 0xBB	
#define GT9XX_IIC_WADDR 0xBA

#define GT9XX_READ_ADDR 0x814E	//信息寄存器

void Touch_Init(void);
u8 Touch_Scan(void);

#endif

