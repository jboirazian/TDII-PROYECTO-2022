/*
 * rfidModuleTasks.c
 *
 *  Created on: Dec 12, 2021
 *      Author: kevin
 */
#include "main.h"

//Modulo RFID
extern _flagsRfid flagsRfid;
uint8_t rfidCard[10];		//ID de tarjeta leida


void taskRfid_Handler(void)
{
	//RFID
	RFID_Init();
	flagsRfid.bytes = 0;

	while(1)
	{
		RFID_Handler(rfidCard);
		vTaskDelay(1 / portTICK_RATE_MS);
	}
}
