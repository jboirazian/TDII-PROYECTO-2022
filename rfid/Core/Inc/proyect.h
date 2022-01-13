/*
 * proyect.h
 *
 *  Created on: Aug 6, 2021
 *      Author: kevin
 */

#ifndef INC_PROYECT_H_
#define INC_PROYECT_H_

/************************************************************************************/
/*									Defines											*/
/************************************************************************************/
//Display
#define ILI9341_BGCOLOR				ILI9341_BLACK		//Color de fondo
#define ILI9341_REGULARCOLOR		ILI9341_WHITE		//Color de texto regular
#define ILI9341_SUCCESSCOLOR		ILI9341_GREEN		//Color de texto exitoso
#define ILI9341_ERRORCOLOR			ILI9341_RED			//Color de texto error
#define ILI9341_WARNINGCOLOR		ILI9341_YELLOW		//Color de texto advertencia

//RTC
#define RTC_START_SECONDS			49
#define RTC_START_MINUTES			59
#define RTC_START_HOURS				23
#define RTC_START_DATE				31
#define RTC_START_WEEKDAY			RTC_WEEKDAY_WEDNESDAY
#define RTC_START_MONTH				RTC_MONTH_DECEMBER
#define RTC_START_YEAR				69

//RFID
#define RFID_CONSECUTIVETIME		1000				//Tiempo que se deja entre dos tarjetas consecutivas

//Personal
#define MAXPERSONAL 				30				//Cantidad maxima de personal

#endif /* INC_PROYECT_H_ */
