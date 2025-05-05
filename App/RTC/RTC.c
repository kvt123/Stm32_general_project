#include "RTC.h"



uint8_t date;
uint8_t month;
uint16_t year;
uint8_t dow;
uint8_t hour;
uint8_t minute;
uint8_t second;
int8_t zone_hr;
uint8_t zone_min;

char buffer[100] = { 0 };
char buffer1[100] = { 0 };

const char *DAYS_OF_WEEK[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

void RTC_Init(RTC_InitDefaultTypeDef* DefaultValue)
{
  /* Start DS1307 timing. Pass user I2C handle pointer to function. */
	DS1307_Init(RTC_I2C);
	/* To test leap year correction. */
	DS1307_SetTimeZone(+7, 00);
	DS1307_SetDate(DefaultValue->RTC_Date);
	DS1307_SetMonth(DefaultValue->RTC_Month);
	DS1307_SetYear(DefaultValue->RTC_Year);
	DS1307_SetDayOfWeek(DefaultValue->RTC_DayOfWeek);
	DS1307_SetHour(DefaultValue->RTC_Hour);
	DS1307_SetMinute(DefaultValue->RTC_Minute);
	DS1307_SetSecond(DefaultValue->RTC_Second);
}

void GetValueDisplay_RTC(void)
{
    /* Get current date and time. */
    date = DS1307_GetDate();
    month = DS1307_GetMonth();
    year = DS1307_GetYear();
    dow = DS1307_GetDayOfWeek();
    hour = DS1307_GetHour();
    minute = DS1307_GetMinute();
    second = DS1307_GetSecond();
    zone_hr = DS1307_GetTimeZoneHour();
    zone_min = DS1307_GetTimeZoneMin();
    sprintf(buffer, "%04d-%02d-%02d %+03d:%02d",
            year, month, date, zone_hr, zone_min);

    sprintf(buffer1, "T%02d:%02d:%02d %s",
         hour, minute, second, DAYS_OF_WEEK[dow]);

}
