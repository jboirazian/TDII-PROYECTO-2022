/*
 * sdModule.h
 *
 *  Created on: Aug 4, 2021
 *      Author: kevin
 */

#ifndef INC_SDMODULE_H_
#define INC_SDMODULE_H_

/************************************************************************************/
/*									Structs											*/
/************************************************************************************/
typedef union
{
	uint16_t bytes;
	struct
	{
		uint8_t warningNoSd:1;				//Indica si se detecta tarjeta Sd
		uint8_t warningNoDatabaseFile:1;	//Indica si se encuentra el archivo 'database.txt'
		uint8_t flag2:1;
		uint8_t writeLog:1;
		uint8_t WriteDataBase:1;
		uint8_t loadDataBase:1;
		uint8_t flag5:1;
		uint8_t flag6:1;
		uint8_t flag7:1;
		uint8_t flag8:1;
		uint8_t flag9:1;
		uint8_t flag10:1;
		uint8_t flag11:1;
		uint8_t flag12:1;
		uint8_t flag13:1;
		uint8_t flag14:1;
		uint8_t flag15:1;
	} bits;
} _flagsSd;





/************************************************************************************/
/*									Functions										*/
/************************************************************************************/
/*
@Funcion:		SD_Init
@Argumentos:	void
@Retorno:		void
@Descripcion:	Realiza inicializaciones
*/
void SD_Init(void);

/*
@Funcion:		SD_Handler
@Argumentos:	void
@Retorno:		void
@Descripcion:	Maneja las rutinas de escritura, lectura y deteccion de la SD
*/
void SD_Handler(void);

/*
@Funcion:		SD_writeLog
@Argumentos:	void
@Retorno:		void
@Descripcion:	Habilita para escribir archivo log en la SD
*/
void SD_writeLog(void);

/*
@Funcion:		SD_getDataBase
@Argumentos:	void
@Retorno:		void
@Descripcion:	Habilita la carga en la estructura 'personal' el archivo database de la SD
*/
void SD_getDataBase(void);

/*
@Funcion:		SD_DBFile2Personal
@Argumentos:	textRead
@Retorno:		void
@Descripcion:	Carga en la estructura 'personal' el archivo database de la SD
*/
void SD_DBFile2Personal(uint8_t *textRead);

/*
@Funcion:		SD_IDString2Number
@Argumentos:	id
@Retorno:		idNum
@Descripcion:	Convierte string 'id' a decimal 'idNum'
*/
uint16_t SD_IDString2Number(uint8_t *id);


void SD_writeDB(void);
void SD_Personal2DBFile(uint16_t numPersonal);
#endif /* INC_SDMODULE_H_ */
