/*
 * stateMachine.c
 *
 *  Created on: May 30, 2021
 *      Author: kevin
 */

#include "main.h"
#include "fatfs.h"
#include "usb_device.h"

/************************************************************************************/
/*									Variables										*/
/************************************************************************************/
//Systick
uint8_t Tick;				//Cada 1ms se setea este flag

//Display LCD
extern _flagsDisplay flagsDisplay;
extern USBD_HandleTypeDef hUsbDeviceFS;

//Modulo RFID
extern _flagsRfid flagsRfid;
uint8_t rfidCard[10];		//ID de tarjeta leida
uint8_t rfidCard_personal[11];


//RTC
extern _flagsRtc flagsRtc;
RTC_TimeTypeDef sTime;		//Estructura donde se guarda el horario
RTC_DateTypeDef sDate;		//Estructura donde se guarda la fecha

//SD
extern _flagsSd flagsSd;

//Personal
extern _flagsPersonal flagsPersonal;
extern __personal personal[MAXPERSONAL];
uint16_t personal_ID;
uint8_t personal_Movement;
extern uint16_t id_delete;

///USB
extern char buffer[0x40];
extern uint8_t USB_PC_STATUS;
extern uint8_t DATA_TO_SEND=0;

//Maquina de estados
enum __stateMachineGlobal state;





/************************************************************************************/
/*									Functions										*/
/************************************************************************************/
void stateMachineInit(void)
{
	//Maquina de estados
	state = __inOperation;
}

void stateMachineSystem(void)
{
	//El boton simula los cambios de estados
	//comment: Esto desp se realiza a traves de la PC
	if(USB_PC_STATUS==4)//// JUAN CAMBIO EL BOTON POR LA LOGICA
	{
		USB_PC_STATUS=0;
		ILI9341_LoadText(disp_CONFIGURANDO);
		state = __inConfiguration;
		HAL_Delay(100);
	}
	if(USB_PC_STATUS==5 )
	{
		ILI9341_LoadText(disp_APOYESUTARJETA);
		USB_PC_STATUS=0;
		flagsSd.bits.loadDataBase = 1;
		//Limpia por si se apoyo la tarjeta durante la configuracion
		RFID_clear();
		state = __inOperation;
	}


	switch(state)
	{
		case __inOperation:
			stateMachineInOperation();
			break;
		case __inConfiguration:
			stateMachineInConfiguration();
			break;
		default:
			state = __inOperation;
	}

	Tick = 0;
}

void stateMachineInOperation(void)
{
	static uint16_t t = 0;

	//Si esta habilitado para leer la tarjeta (para evitar mutiples lecturas)...
	if(flagsRfid.bits.readyToRead)
	{
		//Si se interrumpio y se cargo el buffer con datos ya verificados...
		if(RFID_check())
		{
			//Limpia el flag correspondiente
			RFID_clear();

			//Deshabilita la lectura de tarjeta por 1 seg
			flagsRfid.bits.readyToRead = 0;

			//Verifica si la tarjeta ingresada matchea con la base de datos
			personal_ID = DATABASE_check(rfidCard);
			if(!personal_ID)
			{
				ILI9341_LoadText(disp_TARJETANOIDENTIFICADA);
			}
			else
			{

				memcpy (rfidCard_personal, rfidCard, 10);
				DATA_TO_SEND=1;
				//Muestra tipo de movimiento y nombre de persona en el display
				personal_Movement = PERSONAL_getDetectedMovement();
				if(personal_Movement == INGRESO){
					ILI9341_LoadText(disp_HOLA);
					rfidCard_personal[10]=1+'0';///INGRESO
				}

				else if(personal_Movement == EGRESO){
					ILI9341_LoadText(disp_HASTALUEGO);
					rfidCard_personal[10]=2+'0';///EGRESO
				}


				//Escribe en el archivo log correspondiente
				SD_writeLog();
			}
		}
	}

	//Si se leyo una tarjeta, tiene que pasar 1.5 seg para poder realizar otra lectura
	if(!flagsRfid.bits.readyToRead)
	{
		if(t < RFID_CONSECUTIVETIME)
			t++;	//comment: en realidad se debe hacer en el interruptHandler del systick y ver cuando vencen el tiempo 'RFID_CONSECUTIVETIME'
		else
		{
			t = 0;

			//Rehabilita la lectura RFID y limpia el flag por si se apoyo durante el intervalo noReady
			flagsRfid.bits.readyToRead = 1;
			RFID_clear();

			ILI9341_LoadText(disp_APOYESUTARJETA);
		}
	}
}

void stateMachineInConfiguration(void)
{
	uint8_t PERSONAL_DATA[43]={0};/// A(10BITS TARJETA)(5BITS ID)(12BITS NOMBRE )(15BITS APELLIDO)
	//Si esta habilitado para leer la tarjeta (para evitar mutiples lecturas)...
	if(flagsRfid.bits.readyToRead)
	{
		//Si se interrumpio y se cargo el buffer con datos ya verificados...
		if(RFID_check())
		{
			//Limpia el flag correspondiente
			RFID_clear();

			//Deshabilita la lectura de tarjeta por 1 seg
			flagsRfid.bits.readyToRead = 0;

			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t*)rfidCard,0x0A);/// ENVIO EL NUMERO LEÍDO POR USB
			ILI9341_LoadText(disp_TUSB);///ESCRIBO QUE SE LEYÓ Y SE ENVÍO LA TARJETA.


		}

	}

	if(USB_PC_STATUS==1){// AGREGAR PERSONA A LA BASE DE DATOS DE LA SD
		memcpy (PERSONAL_DATA, buffer, 43);
		SD_DBFile2Personal(PERSONAL_DATA);
		SD_writeDB();
		ILI9341_LoadText(disp_TUSB);///SE AGREÓ A LA SD
		HAL_Delay(200);
		ILI9341_LoadText(disp_TAGREGADA);///MUESTRO POR PANTALLA QUE SE AGREÓ
		HAL_Delay(200);
		USB_PC_STATUS=0;
		state = __inOperation;
	}

	if(USB_PC_STATUS==3){// SE QUIERE ELIMINAR A UNA PERSONA DE BD
		PERSONAL_delete(id_delete);// BORRO UNA PERSONA DE LA BASE DE DATOS DE LA MEMORIA INTERNA
		SD_writeDB();// ACTUALIZO LA BASE DE DATOS
		id_delete=0;
		ILI9341_LoadText(disp_PELIMINADA);///MUESTRO POR PANTALLA QUE SE AGREÓ
		HAL_Delay(1000);
		ILI9341_LoadText(disp_APOYESUTARJETA);
		state = __inOperation;
	}


}
