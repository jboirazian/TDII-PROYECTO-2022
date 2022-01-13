/*
 * sdModuleTasks.c
 *
 *  Created on: Dec 12, 2021
 *      Author: kevin
 */
#include "main.h"
#include "fatfs.h"

void taskSD_Handler(void)
{
	SD_Init();

	while(1)
	{
		SD_Handler();
		vTaskDelay(100 / portTICK_RATE_MS);
	}
}
