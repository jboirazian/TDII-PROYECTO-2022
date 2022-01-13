/*
 * displayModuleTasks.c
 *
 *  Created on: Dec 12, 2021
 *      Author: kevin
 */
#include "main.h"

void taskDiplay_Handler(void)
{
	//Display LCD
	ILI9341_Init();


	while(1)
	{
		ILI9341_Handler();
		vTaskDelay(10 / portTICK_RATE_MS);
	}
}
