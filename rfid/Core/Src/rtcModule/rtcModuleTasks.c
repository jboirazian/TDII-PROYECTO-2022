/*
 * rtcModuleTasks.c
 *
 *  Created on: Dec 12, 2021
 *      Author: kevin
 */
#include "main.h"

//RTC
extern _flagsRtc flagsRtc;

void taskRTC_Handler(void)
{
	//RTC
	RTC_Init();
	flagsRtc.bytes = 0;

	while(1)
	{
		RTC_GetTimeAndDate();
		vTaskDelay(1000 / portTICK_RATE_MS);
	}
}
