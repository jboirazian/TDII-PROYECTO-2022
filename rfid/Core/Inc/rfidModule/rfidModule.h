/*
 * rfidModule.h
 *
 *  Created on: May 30, 2021
 *      Author: kevin
 */

#ifndef INC_RFIDMODULE_H_
#define INC_RFIDMODULE_H_

/************************************************************************************/
/*									Structs											*/
/************************************************************************************/
typedef union
{
	uint16_t bytes;
	struct
	{
		uint8_t rxInterrupted:1;	//Hubo interrupcion
		uint8_t rxBufferOk:1;		//'rxBuffer' con Cheksum chequeada y correcta
		uint8_t readyToRead:1;
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
} _flagsRfid;





/************************************************************************************/
/*									Defines											*/
/************************************************************************************/
#define RFID_STARTBYTE 	2
#define RFID_STOPBYTE 	3
#define	RFID_NUMDATA	14
#define	RFID_NUMID		10





/************************************************************************************/
/*									Functions										*/
/************************************************************************************/
/*
@Funcion:		RFID_Init
@Argumentos:	void
@Retorno:		void
@Descripcion:	Realiza inicializaciones
*/
void RFID_Init(void);

/*
@Funcion:		RFID_Handler
@Argumentos:	rfidCard	Numero de tarjeta leida
@Retorno:		void
@Descripcion:	Lee la UART 'huart' y carga el numero de tarjeta leida y ya validada en 'rfidCard'
*/
void RFID_Handler(uint8_t *rfidCard);

/*
@Funcion:		RFID_doChecksum
@Argumentos:	void
@Retorno:		cs			Checksum de los 10 datos de la tarjeta
@Descripcion:	Realiza el checksum de los 10 datos de la tarjeta
*/
uint8_t RFID_doChecksum(void);

/*
@Funcion:		RFID_verifyChecksum
@Argumentos:	void
@Retorno:		0			Checksum no coincide
				1			Checksum coincide
@Descripcion:	Verifica si el checksum recibido coincide con el checksum calculado
*/
uint8_t RFID_verifyChecksum(void);

/*
@Funcion:		RFID_verifyStopByte
@Argumentos:	void
@Retorno:		0			StopByte no coincide
				1			StopByte coincide
@Descripcion:	Verifica si el ultimo byte recibido es el correspondiente '03'
*/
uint8_t RFID_verifyStopByte(void);

/*
@Funcion:		RFID_verifyRxBuffer
@Argumentos:	void
@Retorno:		0			Cheksum o StopByte no coinciden
				1			Cheksum y StopByte coinciden
@Descripcion:	Verifica si el checksum recibido coincide con el checksum calculado,
				y si el ultimo byte recibido es el correspondiente '03'
*/
uint8_t RFID_verifyRxBuffer(void);

/*
@Funcion:		RFID_check
@Argumentos:	void
@Retorno:		0			Numero de tarjeta invalido
				1			Numero de tarjeta valido
@Descripcion:	Indica mediante el flag 'rxBufferOk' si el numero de tarjeta recibido
				es valido o invalido
*/
uint8_t RFID_check(void);

/*
@Funcion:		RFID_clear
@Argumentos:	void
@Retorno:		void
@Descripcion:	Limpia el flag 'rxBufferOk'
*/
void RFID_clear(void);

/*
@Funcion:		ascii2hexa
@Argumentos:	a			Caracter ascii
@Retorno:		h			Numero hexadecimal
@Descripcion:	Convierte caracter ascii en un numero hexadecimal
*/
uint8_t ascii2hexa(uint8_t a);

#endif /* INC_RFIDMODULE_H_ */
