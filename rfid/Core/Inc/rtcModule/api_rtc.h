/*
 * api_rtc.h
 *
 *  Created on: Aug 6, 2021
 *      Author: kevin
 */

#ifndef INC_RTCMODULE_API_RTC_H_
#define INC_RTCMODULE_API_RTC_H_

/************************************************************************************/
/*									Structs											*/
/************************************************************************************/
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
} _flagsRtc;





/************************************************************************************/
/*									Functions										*/
/************************************************************************************/
/*
@Funcion:		RTC_Init
@Argumentos:	void
@Retorno:		void
@Descripcion:	Realiza inicializaciones
*/
void RTC_Init(void);

/*
@Funcion:		RTC_GetTimeAndDate
@Argumentos:	void
@Retorno:		void
@Descripcion:	Almacena fecha y hora en variables globales
*/
void RTC_GetTimeAndDate(void);

/*
@Funcion:		RTC_getTime
@Argumentos:	void
@Retorno:		void
@Descripcion:	Carga tiempo en un determinado formato en un string
*/
void RTC_getTime(uint8_t *time, uint8_t pos);

/*
@Funcion:		RTC_getDate
@Argumentos:	void
@Retorno:		void
@Descripcion:	Carga fecha en un determinado formato en un string
*/
void RTC_getDate(uint8_t *date, uint8_t pos);

/*
@Funcion:		RTC_getDateWeekday
@Argumentos:	void
@Retorno:		void
@Descripcion:	Carga dia de la semana en un determinado formato en un string
*/
void RTC_getDateWeekday(uint8_t *dateWeekday, uint8_t pos);

#endif /* INC_RTCMODULE_API_RTC_H_ */
