#ifndef __RTC_H
#define __RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "RTC_Ds1307.h"



typedef struct
{
  uint8_t RTC_Date;                

  uint8_t RTC_Month;           

  uint8_t RTC_Year;

  uint8_t RTC_DayOfWeek;        

  uint8_t RTC_Hour;                

  uint8_t RTC_Minute; 

  uint8_t RTC_Second; 
}RTC_InitDefaultTypeDef;



void RTC_Init(RTC_InitDefaultTypeDef* DefaultValue);
void GetValueDisplay_RTC(void);

#ifdef __cplusplus
}
#endif

#endif