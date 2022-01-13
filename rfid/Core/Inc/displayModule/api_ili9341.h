/*
 * api_ili9341.h
 *
 *  Created on: Aug 6, 2021
 *      Author: kevin
 */

#ifndef INC_DISPLAYMODULE_API_ILI9341_H_
#define INC_DISPLAYMODULE_API_ILI9341_H_

/************************************************************************************/
/*									Defines											*/
/************************************************************************************/
#define CONFIG_ANIMATION_TIME	500





/************************************************************************************/
/*									Structs											*/
/************************************************************************************/
typedef struct __display_Messages
{
	const uint8_t *text;
	uint8_t len;
	uint8_t cut;
	uint16_t color;
} display_Messages;

typedef union
{
	uint16_t bytes;
	struct
	{
		uint8_t refreshTime:1;
		uint8_t refreshDate:1;
		uint8_t refreshText:1;
		uint8_t startConfigAnimation:1;
		uint8_t refreshWarning:1;
		uint8_t eraseWarning:1;
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
} _flagsDisplay;





/************************************************************************************/
/*									Functions										*/
/************************************************************************************/
/*
@Funcion:		ILI9341_Init
@Argumentos:	void
@Retorno:		void
@Descripcion:	Realiza inicializaciones
*/
void ILI9341_Init(void);

/*
@Funcion:		ILI9341_LoadText
@Argumentos:	index
@Retorno:		void
@Descripcion:	Carga cual mensaje se tiene que imprimir
*/
void ILI9341_LoadText(uint8_t index);

/*
@Funcion:		ILI9341_Handler
@Argumentos:	void
@Retorno:		void
@Descripcion:	Realiza el manejo de las impresiones del display
*/
void ILI9341_Handler(void);

#endif /* INC_DISPLAYMODULE_API_ILI9341_H_ */
