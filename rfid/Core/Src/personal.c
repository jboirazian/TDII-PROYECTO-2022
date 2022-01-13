/*
 * personal.c
 *
 *  Created on: May 30, 2021
 *      Author: kevin
 */

#include "main.h"

/************************************************************************************/
/*									External Variables								*/
/************************************************************************************/
__personal personal[MAXPERSONAL];





/************************************************************************************/
/*									Private Variables								*/
/************************************************************************************/
_flagsPersonal flagsPersonal;

uint16_t personalQuantity;			//Cantidad de personas en la base de datos

uint16_t detectedID;				//ID de la tarjeta ingresada
uint8_t detectedName[MAXLEN_NAME];	//Nombre del personal de la tarjeta ingresada
uint8_t detectedNameLen;			//Largo del nombre del personal de la tarjeta ingresada
uint8_t detectedMovement;			//Tipo de movimiento al apoyar la tarjeta





/************************************************************************************/
/*									Functions										*/
/************************************************************************************/
void DATABASE_Init(void)
{
	personalQuantity = 0;

	DATABASE_load();
}

void DATABASE_load(void)
{
	SD_getDataBase();
	//PERSONAL_load(10214	, (uint8_t *) "54002218E6"	, (uint8_t *) "Kevin"		, (uint8_t *) "Chon"			);
}

void DATABASE_clear(void)
{
	uint8_t i;
	uint16_t p;

	for(p = 0; p < personalQuantity; p++)
	{
		for(i = 0; i < 10; i++)
			personal[p].tarjetaID[i] = 0;

		personal[p].personalID = 0;

		for(i = 0; i < MAXLEN_NAME; i++)
			personal[p].nombre[i] = 0;

		for(i = 0; i < MAXLEN_SURNAME; i++)
			personal[p].apellido[i] = 0;

		personal[p].movimiento = 0;
	}

	personalQuantity = 0;
}

void PERSONAL_load(uint16_t id, uint8_t *rfidCard, uint8_t *nombre, uint8_t *apellido)
{
	uint8_t i;

	for(i = 0; i < 10; i++)
		personal[personalQuantity].tarjetaID[i] = rfidCard[i];

	personal[personalQuantity].personalID = id;

	for(i = 0; i < MAXLEN_NAME; i++)
		personal[personalQuantity].nombre[i] = nombre[i];

	for(i = 0; i < MAXLEN_SURNAME; i++)
		personal[personalQuantity].apellido[i] = apellido[i];

	personal[personalQuantity].movimiento = EGRESO;

	personalQuantity++;
}

void PERSONAL_delete(uint16_t id)
{
	uint8_t i, j;					//Contadores auxiliares
	uint8_t idFound = 0;			//Flag para indicar que se encontro el id a borrar

	i=0;
	j=0;
	//Busca mientras no haya encontrado al id y no haya superado a la maxima cantidad de personal
	while(!idFound && i < MAXPERSONAL)
	{
		if(personal[i].personalID == id)
		{
			//Relleno el vacio con el ultimo personal
			personal[i].personalID = personal[personalQuantity-1].personalID;
			for(j = 0; j < 10; j++)
				personal[i].tarjetaID[j] = personal[personalQuantity-1].tarjetaID[j];

			//Elimino el ultimo personal porque ahora esta rellenando el vacio del personal eliminado
			personal[personalQuantity-1].personalID = 0;
			for(j = 0; j < 10; j++)
				personal[personalQuantity-1].tarjetaID[j] = 0;
		}
		else
			i++;
	}
	//comment: habria que ordenar el espacio vacio. Pienso que como no importa el orden,
	//con solo traer la ultima persona y rellenarla en el espacio vacio esta bien
}

uint16_t DATABASE_check(uint8_t *rfidCard)
{
	uint8_t idOk = 0;		//Flag que indica que se encontro al personal en base a su numero de tarjeta
	uint16_t pIndex = 0;
	uint8_t i, endNameLen = 0;
	uint16_t id;

	while(!idOk && pIndex < MAXPERSONAL)
	{
		for(i = 0 ; i < 10 ; i++)
		{
			if(personal[pIndex].tarjetaID[i] != rfidCard[i] || !personal[pIndex].tarjetaID[i])
				i = 10;
			if(i == 9)
				idOk = 1;
		}
		pIndex++;
	}

	if(idOk)
	{
		//1. Almacena ID detectado
		id = personal[pIndex-1].personalID;
		detectedID = id;

		//2. Almacena el nombre detectado
		detectedNameLen = 0;
		for(i = 0 ; i < MAXLEN_NAME ; i++)
		{
			detectedName[i] = personal[pIndex-1].nombre[i];

			if(detectedName[i] == '\0')
				endNameLen = 1;
			if(!endNameLen)
				detectedNameLen++;
		}

		//3. Almancena el tipo de movimiento detectado
		if(personal[pIndex-1].movimiento == EGRESO)
		{
			personal[pIndex-1].movimiento = INGRESO;
			detectedMovement = INGRESO;
		}
		else if(personal[pIndex-1].movimiento == INGRESO)
		{
			personal[pIndex-1].movimiento = EGRESO;
			detectedMovement = EGRESO;
		}
	}
	else
		id = 0;

	return id;
}

uint16_t DATABASE_getPersonalQuantity(void)
{
	return personalQuantity;
}

uint16_t PERSONAL_getID(void)
{
	return detectedID;
}

uint8_t PERSONAL_getDetectedMovement(void)
{
	return detectedMovement;
}
