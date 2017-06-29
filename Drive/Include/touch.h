#ifndef __GT9XX_H__
#define __GT9XX_H__

#include "stm32f4xx.h"

/*---------------------- IIC��ض��� ------------------------*/

#define Response_OK 1  //IIC��Ӧ
#define Response_ERR 0

#define Touch_DelayVaule 5  //ͨѶ��ʱʱ��

// IO����غ�
#define IIC_Touch_SCL_CLK     RCC_AHB1Periph_GPIOC 
#define IIC_Touch_SCL_PORT    GPIOC                   
#define IIC_Touch_SCL_PIN     GPIO_Pin_13   
         
#define IIC_Touch_SDA_CLK     RCC_AHB1Periph_GPIOB 
#define IIC_Touch_SDA_PORT    GPIOB                   
#define IIC_Touch_SDA_PIN     GPIO_Pin_2             

// IO�ڲ���
#define SCL(a)	if (a)	\
					GPIO_SetBits(IIC_Touch_SCL_PORT,IIC_Touch_SCL_PIN);\
					else		\
					GPIO_ResetBits(IIC_Touch_SCL_PORT,IIC_Touch_SCL_PIN)

#define SDA(a)	if (a)	\
					GPIO_SetBits(IIC_Touch_SDA_PORT,IIC_Touch_SDA_PIN);\
					else		\
					GPIO_ResetBits(IIC_Touch_SDA_PORT,IIC_Touch_SDA_PIN)
	
/*---------------------- GT9XXоƬ��ض��� ------------------------*/
					
#define TOUCH_MAX   5	//���������

typedef struct 
{
	u8  flag;	//������־λ��Ϊ1ʱ��ʾ�д�������
	u8  num;		//��������
	u16 x[TOUCH_MAX];	//x����
	u16 y[TOUCH_MAX];	//y����
}TouchStructure;

extern TouchStructure touchInfo;	//�ṹ������

#define GT9XX_IIC_RADDR 0xBB	
#define GT9XX_IIC_WADDR 0xBA

#define GT9XX_READ_ADDR 0x814E	//��Ϣ�Ĵ���

void Touch_Init(void);
u8 Touch_Scan(void);

#endif

