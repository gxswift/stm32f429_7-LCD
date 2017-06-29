#ifndef __RTC_H
#define __RTC_H	 

#include "stm32f4xx.h"

//���Ӳ������ýṹ��
typedef struct
{
  u8	Date;	//����
  u8 	Week;	//����                                                
  u8  Hour; //Сʱ                        
  u8  Min;  //����                        
  u8  Sec;  //��  
                        
}RTC_AlarmSetTypeDef; 

void RTC_Initialize(void);
void RTC_AlarmSet(RTC_AlarmSetTypeDef *_AlarmStruct);

#endif
