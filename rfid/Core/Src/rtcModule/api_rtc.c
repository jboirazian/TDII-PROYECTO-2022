/*
 * api_rtc.c
 *
 *  Created on: Aug 6, 2021
 *      Author: kevin
 */
#include "main.h"

/************************************************************************************/
/*									External Variables								*/
/************************************************************************************/
extern RTC_HandleTypeDef hrtc;
extern RTC_TimeTypeDef sTime;		//Estructura donde se guarda el horario
extern RTC_DateTypeDef sDate;		//Estructura donde se guarda la fecha





/************************************************************************************/
/*									Private Variables								*/
/************************************************************************************/
_flagsRtc flagsRtc;

uint8_t dateWeekdayList[7][3] = {"Lun", "Mar", "Mie", "Jue", "Vie", "Sab", "Dom"};





/************************************************************************************/
/*									Functions										*/
/************************************************************************************/
void RTC_Init(void)
{
	sTime.Seconds 	= RTC_START_SECONDS;
	sTime.Minutes 	= RTC_START_MINUTES;
	sTime.Hours 	= RTC_START_HOURS;
	sDate.Date 		= RTC_START_DATE;
	sDate.WeekDay	= RTC_START_WEEKDAY;
	sDate.Month 	= RTC_START_MONTH;
	sDate.Year		= RTC_START_YEAR;
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}


void RTC_SET(uint8_t DD, uint8_t MES , uint8_t AAAA , uint8_t HH , uint8_t MM,uint8_t SS , uint8_t DS)
{
	sTime.Seconds 	= SS;
	sTime.Minutes 	= MM;
	sTime.Hours 	= HH;
	sDate.Date 		= DD;
	sDate.WeekDay	= DS;
	sDate.Month 	= MES;
	sDate.Year		= AAAA;/// no tengo idea pero no me toma de manera correta el anio cuando se lo paso por USB , el resto de las cosas si
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}

void RTC_getTime(uint8_t *time, uint8_t pos)
{
	time[pos+0] = sTime.Hours/10	+'0';
	time[pos+1] = sTime.Hours%10	+'0';
	time[pos+2] = ':';
	time[pos+3] = sTime.Minutes/10	+'0';
	time[pos+4] = sTime.Minutes%10	+'0';
	time[pos+5] = ':';
	time[pos+6] = sTime.Seconds/10	+'0';
	time[pos+7] = sTime.Seconds%10	+'0';
}

void RTC_getDate(uint8_t *date, uint8_t pos)
{
	date[pos+7] = 1 +'0';
	date[pos+6] = 2 + '0';
	date[pos+5] = '/';
	date[pos+4] = sDate.Month%10	+'0';
	date[pos+3] = sDate.Month/10	+'0';
	date[pos+2] = '/';
	date[pos+1] = sDate.Date%10		+'0';
	date[pos+0] = sDate.Date/10		+'0';
}

void RTC_getDateWeekday(uint8_t *dateWeekday, uint8_t pos)
{
	uint8_t i;

	for(i = 0; i<3; i++)
		dateWeekday[i]=dateWeekdayList[sDate.WeekDay-1][i];
}

void RTC_GetTimeAndDate(void)
{
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}
