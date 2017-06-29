#ifndef __RTC_H
#define __RTC_H	 

#include "stm32f4xx.h"

//闹钟参数设置结构体
typedef struct
{
  u8	Date;	//日期
  u8 	Week;	//星期                                                
  u8  Hour; //小时                        
  u8  Min;  //分钟                        
  u8  Sec;  //秒  
                        
}RTC_AlarmSetTypeDef; 

void RTC_Initialize(void);
void RTC_AlarmSet(RTC_AlarmSetTypeDef *_AlarmStruct);

#endif
