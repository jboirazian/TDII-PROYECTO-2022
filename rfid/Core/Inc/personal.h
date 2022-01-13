/*
 * personal.h
 *
 *  Created on: May 30, 2021
 *      Author: kevin
 */

#ifndef INC_PERSONAL_H_
#define INC_PERSONAL_H_

/************************************************************************************/
/*									Defines											*/
/************************************************************************************/
#define MAXLEN_NAME 	12
#define MAXLEN_SURNAME	15

//Tipo de movimiento
#define	INGRESO		1
#define EGRESO 		0





/************************************************************************************/
/*									Structs											*/
/************************************************************************************/
typedef struct __personal
{
	uint8_t 	tarjetaID[10];
	uint16_t 	personalID;
	uint8_t 	nombre[MAXLEN_NAME];
	uint8_t 	apellido[MAXLEN_SURNAME];
	uint8_t		movimiento;
} __personal;

typedef union
{
	uint16_t bytes;
	struct
	{
		uint8_t flag0:1;
		uint8_t flag1:1;
		uint8_t flag2:1;
		uint8_t flag3:1;
		uint8_t flag4:1;
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
} _flagsPersonal;





/************************************************************************************/
/*									Functions										*/
/************************************************************************************/
/*
@Funcion:		DATABASE_Init
@Argumentos:	void
@Retorno:		void
@Descripcion:	Realiza inicializaciones
*/
void DATABASE_Init(void);

/*
@Funcion:		DATABASE_checkID
@Argumentos:	rfidCard	Numero de tarjeta a chequear
@Retorno:		id			ID del personal
@Descripcion:	En base al numero de tarjeta, carga en las variables globales el ID, movimiento
				y nombre del personal
*/
uint16_t DATABASE_check(uint8_t *rfidCard);

/*
@Funcion:		DATABASE_load
@Argumentos:	void
@Retorno:		void
@Descripcion:	Carga los datos leidos de la SD en la base de datos
*/
void DATABASE_load(void);

/*
@Funcion:		PERSONAL_load
@Argumentos:	id			Numero de identificacion
				tarjeta		Numero de tarjeta
				nombre		Nombre del personal
				apellido	Apellido del personal
@Retorno:		void
@Descripcion:	Carga los datos del personal a la base de datos
*/
void PERSONAL_load(uint16_t id, uint8_t *rfidCard, uint8_t *nombre, uint8_t *apellido);

/*
@Funcion:		PERSONAL_delete
@Argumentos:	id			Numero de identificacion
@Retorno:		void
@Descripcion:	Borra al personal de la base de datos en base a su 'id'
*/
void PERSONAL_delete(uint16_t id);

/*
@Funcion:		DATABASE_getPersonalQuantity
@Argumentos:	void
@Retorno:		void
@Descripcion:	Devuelve la cantidad total de personal
*/
uint16_t DATABASE_getPersonalQuantity(void);

/*
@Funcion:		PERSONAL_getID
@Argumentos:	void
@Retorno:		void
@Descripcion:	Indica el ID registrado
*/
uint16_t PERSONAL_getID(void);

/*
@Funcion:		PERSONAL_getDetectedMovement
@Argumentos:	void
@Retorno:		void
@Descripcion:	Indica el tipo de movimiento registrado
*/
uint8_t PERSONAL_getDetectedMovement(void);

void DATABASE_clear(void);

#endif /* INC_PERSONAL_H_ */
