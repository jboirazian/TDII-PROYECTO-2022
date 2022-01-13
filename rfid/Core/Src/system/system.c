/*
 * system.c
 *
 *  Created on: Dec 12, 2021
 *      Author: kevin
 */
#include "main.h"



//SD
extern _flagsSd flagsSd;

//Personal
extern _flagsPersonal flagsPersonal;
extern __personal personal[MAXPERSONAL];


//Maquina de estados
enum __stateMachineGlobal state;

void initSystem(void)
{


	//Personal
	DATABASE_Init();
	flagsPersonal.bytes = 0;


}


void taskSystem_InOperation(void)
{
	//Maquina de estados
	state = __inOperation;

	while(1)
	{
		stateMachineInOperation();
		vTaskDelay(1 / portTICK_RATE_MS);
	}
}


void taskSystem_StateMachine(void)
{
	//Maquina de estados
	stateMachineInit();
	while(1)
	{
		stateMachineSystem();
		vTaskDelay(1 / portTICK_RATE_MS);
	}
}


