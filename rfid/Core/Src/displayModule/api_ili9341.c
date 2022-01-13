/*
 * api_ili9341.c
 *
 *  Created on: Aug 6, 2021
 *      Author: kevin
 */

#include "main.h"

/************************************************************************************/
/*									External Variables								*/
/************************************************************************************/
extern SPI_HandleTypeDef hspi1;

extern uint8_t detectedName[MAXLEN_NAME];		//Nombre del personal de la tarjeta ingresada
extern uint8_t detectedNameLen;					//Largo del nombre del personal de la tarjeta ingresada

extern _flagsSd flagsSd;						//Flags asociados a la SD





/************************************************************************************/
/*									Private Variables								*/
/************************************************************************************/
//Flags
_flagsDisplay flagsDisplay;						//Flags asociados al display

//Varibales
uint8_t indexMessage;							//Indica cual mensaje que se esta imprimiendo en el momento
uint8_t indexMessageAnt;						//Indica cual mensaje se imprimio anteriormente

display_Messages messages[8] =					//Mensajes a imprimir
{
	{(uint8_t *) "APOYE SUTARJETA"			, 15	, 8		, ILI9341_REGULARCOLOR	},
	{(uint8_t *) "HOLA!"						, 5		, 0		, ILI9341_SUCCESSCOLOR	},
	{(uint8_t *) "HASTA LUEGO!"				, 12	, 0		, ILI9341_SUCCESSCOLOR	},
	{(uint8_t *) "TARJETA NOIDENTIFICADA"	, 22	, 10	, ILI9341_ERRORCOLOR	},
	{(uint8_t *) "CONFIGURANDO..."			, 15	, 12	, ILI9341_REGULARCOLOR	},
	{(uint8_t *) "TARJETA   ENVIADA A PC!"	, 22	, 10	, ILI9341_SUCCESSCOLOR	},
	{(uint8_t *) "PERSONA AGREGADA!"						, 18		, 8	, ILI9341_SUCCESSCOLOR	},
	{(uint8_t *) "PERSONA BORRADA!"						, 18		, 8		, ILI9341_SUCCESSCOLOR	}
};



/************************************************************************************/
/*									Private Functions								*/
/************************************************************************************/
static void ILI9341_writeString(const uint8_t *str, uint8_t len);
static void ILI9341_writeStringCentered(const uint8_t *str, uint8_t len, uint16_t y);
static void ILI9341_display2LineText(const uint8_t *str, uint8_t len, uint8_t cut);
static void ILI9341_drawBorder(uint8_t pxWidth);
static void ILI9341_displayTime(uint16_t color);
static void ILI9341_displayDate(uint16_t color);
static void ILI9341_displayConfigurationAnimation(void);
static void ILI9341_displayWarning(uint16_t color);



void ILI9341_writeString(const uint8_t *str, uint8_t len)
{
	uint8_t i;

	for(i = 0; i < len; i++)
		ILI9341_write(str[i]);
}

void ILI9341_writeStringCentered(const uint8_t *str, uint8_t len, uint16_t y)
{
	ILI9341_setCursor((ILI9341_getWidth()-(len*ILI9341_getTextSize()*6))/2, y);
	ILI9341_writeString(str, len);
}

void ILI9341_display2LineText(const uint8_t *str, uint8_t len, uint8_t cut)
{
	uint8_t str2[len-cut];
	uint8_t i;

	if(cut == 0)
	{
		ILI9341_writeStringCentered(str, len, 100);
	}
	else
	{
		for(i = 0; i<len-cut ; i++)
			str2[i] = str[cut+i];

		ILI9341_writeStringCentered(str, cut, 100);
		ILI9341_writeStringCentered(str2, len-cut, 135);
	}
}

void ILI9341_drawBorder(uint8_t pxWidth)
{
	uint8_t i;

	for(i = 0; i< pxWidth; i++)
		ILI9341_drawRect(i,i,ILI9341_getWidth()-2*i,ILI9341_getHeight()-2*i,ILI9341_getTextColor());
}

void ILI9341_displayConfigurationAnimation(void)
{
	static uint32_t time;
	static uint16_t n;

	//1. Si recien empieza a animar los puntos suspensivos...
	if(flagsDisplay.bits.startConfigAnimation)
	{
		flagsDisplay.bits.startConfigAnimation = 0;
		time = 0;
		n = 0;
	}

	//2. Cada vez que vence el tiempo, cambia de animacion
	if(time >= CONFIG_ANIMATION_TIME)
	{
		time = 0;

		ILI9341_setTextSize(4);
		ILI9341_setTextColor(ILI9341_REGULARCOLOR);

		if(n == 0)
			ILI9341_writeStringCentered((uint8_t*) ".  ", 3, 135);
		else if(n == 1)
			ILI9341_writeStringCentered((uint8_t*) ".. ", 3, 135);
		else if(n == 2)
			ILI9341_writeStringCentered((uint8_t*) "...", 3, 135);

		n++;
		n%=3;
	}

	time++;
}

void ILI9341_displayTime(uint16_t color)
{
	uint8_t time[8];
	static uint8_t timeAnt[8];
	uint8_t i;

	//1. Obtiene el tiempo en ASCII
	RTC_getTime(time,0);

	//2. Verifica si hay que actualizar display
	for(i = 0; i< 8; i++)
		if(timeAnt[i] != time[i])
			flagsDisplay.bits.refreshTime = 1;


	//3. Si es necesario actualizarlo, lo hace
	if(flagsDisplay.bits.refreshTime)
	{
		flagsDisplay.bits.refreshTime = 0;

		//Escribe el horario
		ILI9341_setTextSize(2);
		ILI9341_setTextColor(color);
		ILI9341_setCursor(222, 10);
		ILI9341_writeString(time,8);

		//Guarda el tiempo obtenido para compararlo la proxima vez
		for(i = 0; i< 8; i++)
			timeAnt[i] = time[i];
	}
}

void ILI9341_displayDate(uint16_t color)
{
	uint8_t date[12];
	static uint8_t dateAnt[12];
	uint8_t i;

	//1. Obtiene la fecha en ASCII
	RTC_getDateWeekday(date, 0);
	date[3] = ' ';
	RTC_getDate(date, 4);

	//2. Verifica si hay que actualizar display
	for(i = 0; i< 12; i++)
		if(dateAnt[i] != date[i])
			flagsDisplay.bits.refreshDate = 1;

	//3. Si es necesario actualizarlo, lo hace
	if(flagsDisplay.bits.refreshDate)
	{
		flagsDisplay.bits.refreshDate = 0;

		//Escribe la fecha
		ILI9341_setTextSize(2);
		ILI9341_setTextColor(color);
		ILI9341_setCursor(8, 10);
		ILI9341_writeString(date,12);

		//Guarda el tiempo obtenido para compararlo la proxima vez
		for(i = 0; i< 12; i++)
			dateAnt[i] = date[i];
	}
}

void ILI9341_displayWarning(uint16_t color)
{
	if(flagsDisplay.bits.refreshWarning)
	{
		flagsDisplay.bits.refreshWarning = 0;

		ILI9341_setTextSize(2);
		ILI9341_setTextColor(color);

		if(flagsSd.bits.warningNoSd)
		{
			ILI9341_setCursor(8,220);
			ILI9341_writeString((uint8_t*) "NO_SD", 5);
		}

		if(flagsSd.bits.warningNoDatabaseFile)
		{
			ILI9341_setCursor(90,220);
			ILI9341_writeString((uint8_t*) "NO_DB", 5);
		}
	}

	if(flagsDisplay.bits.eraseWarning)
	{
		flagsDisplay.bits.eraseWarning = 0;

		ILI9341_setTextSize(2);
		ILI9341_setTextColor(ILI9341_BGCOLOR);

		if(!flagsSd.bits.warningNoSd)
		{
			ILI9341_setCursor(8,220);
			ILI9341_writeString((uint8_t*) "NO_SD", 5);
		}

		if(!flagsSd.bits.warningNoDatabaseFile)
		{
			ILI9341_setCursor(90,220);
			ILI9341_writeString((uint8_t*) "NO_DB", 5);
		}
	}
}

/************************************************************************************/
/*									Public Functions								*/
/************************************************************************************/
void ILI9341_Init(void)
{
	//1. Setea configuraciones iniciales
	ILI9341_begin(&hspi1);

	//2. Rota display de forma horizontal
	ILI9341_setRotation(1);

	//3. Imprime fondo con color 'ILI9341_BGCOLOR'
	ILI9341_fillScreen(ILI9341_BGCOLOR);

	//4. Setea fondo de caracteres con color 'ILI9341_BGCOLOR'
	ILI9341_setTextBgColor(ILI9341_BGCOLOR);

	//5. Imprime primer mensaje IDLE
	ILI9341_LoadText(disp_APOYESUTARJETA);
	indexMessage 	= disp_APOYESUTARJETA;
	indexMessageAnt = disp_APOYESUTARJETA;

	flagsDisplay.bytes = 0;
	flagsDisplay.bits.refreshText = 1;
}

void ILI9341_LoadText(uint8_t index)
{
	//1. Indica cual mensaje se tiene que imprimir
	indexMessage = index;

	//2. Solicita refresco de display
	if(indexMessageAnt != indexMessage)
		flagsDisplay.bits.refreshText = 1;
}

void ILI9341_Handler(void)
{
	//1. Muestra tiempo y fecha en la parte superior
	ILI9341_displayTime(ILI9341_REGULARCOLOR);
	ILI9341_displayDate(ILI9341_REGULARCOLOR);

	//2. Imprime nuevo texto si se hace falta
	if(flagsDisplay.bits.refreshText)
	{
		flagsDisplay.bits.refreshText = 0;

		//Limpia el texto anterior
		ILI9341_setTextSize(4);
		ILI9341_setTextColor(ILI9341_BGCOLOR);
		ILI9341_display2LineText(messages[indexMessageAnt].text, messages[indexMessageAnt].len, messages[indexMessageAnt].cut);
		if(indexMessageAnt == disp_HOLA || indexMessageAnt == disp_HASTALUEGO)
			ILI9341_writeStringCentered(detectedName, detectedNameLen, 135);
		if(messages[indexMessage].color == ILI9341_REGULARCOLOR)
			ILI9341_drawBorder(2);

		//Imprime texto actual
		ILI9341_setTextColor(messages[indexMessage].color);
		if(messages[indexMessage].color != ILI9341_REGULARCOLOR)
			ILI9341_drawBorder(2);
		ILI9341_display2LineText(messages[indexMessage].text, messages[indexMessage].len, messages[indexMessage].cut);

		if(indexMessage == disp_HOLA || indexMessage == disp_HASTALUEGO)
			ILI9341_writeStringCentered(detectedName, detectedNameLen, 135);

		if(indexMessage == disp_CONFIGURANDO)
			flagsDisplay.bits.startConfigAnimation = 1;

		//Recuerda el mensaje que se acaba de imprimir
		indexMessageAnt = indexMessage;
	}

	//3. Animacion de Configuracion
	if(indexMessage == disp_CONFIGURANDO)
		ILI9341_displayConfigurationAnimation();

	//4. Imprime advertencias
	ILI9341_displayWarning(ILI9341_WARNINGCOLOR);
}
