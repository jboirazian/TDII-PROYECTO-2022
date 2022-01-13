/*
 * rfidModule.c
 *
 *  Created on: May 30, 2021
 *      Author: kevin
 */
#include "main.h"

/************************************************************************************/
/*									External Variables								*/
/************************************************************************************/
extern UART_HandleTypeDef huart1;





/************************************************************************************/
/*									Private Variables								*/
/************************************************************************************/
_flagsRfid flagsRfid;

uint8_t rxByte;					//Byte que transmite el RFID y recibe el micro
uint8_t rxBuffer[RFID_NUMDATA];	//Buffer de datos de la tarjeta recibidos





/************************************************************************************/
/*									Functions										*/
/************************************************************************************/
void RFID_Init(void)
{
	HAL_UART_Receive_IT(&huart1,&rxByte,1);

	flagsRfid.bits.readyToRead = 1;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//1. Indica mediante un flag que hubo interrupcion
	flagsRfid.bits.rxInterrupted = 1;
	//2. Carga en 'rxByte' el byte recibido
	HAL_UART_Receive_IT(huart,&rxByte,1);
}

void RFID_Handler(uint8_t *rfidCard)
{
	static uint8_t numByteRecieving = 0;	//Cuantifica el numero de byte que esta recibiendo de la trama total
	static uint8_t recievedStartByte = 0;
	uint8_t i = 0;

	//Si hubo interrupcion...
	if(flagsRfid.bits.rxInterrupted)
	{
		//1. Limpia el flag
		flagsRfid.bits.rxInterrupted = 0;

		//2. Chequea STARTBYTE
		if(rxByte == RFID_STARTBYTE && recievedStartByte == 0)
		{
			recievedStartByte = 1;
			numByteRecieving = 0;
			rxBuffer[numByteRecieving] = rxByte;
		}
		//3. Empieza a cargar el resto del 'rxBuffer' si se recibio el startbyte
		else if (recievedStartByte)
		{
			numByteRecieving++;
			rxBuffer[numByteRecieving] = rxByte;
			// Cuando llega y se carga el ultimo byte
			if(numByteRecieving >= (RFID_NUMDATA-1))
			{
				recievedStartByte = 0;
				// Carga 'rfidID' si la tarjeta tiene una identificacion valida
				if(!flagsRfid.bits.rxBufferOk && RFID_verifyRxBuffer())
				{
					flagsRfid.bits.rxBufferOk = 1;
					for(i = 0 ; i < RFID_NUMID ; i++)
						rfidCard[i]=rxBuffer[i+1];
				}
			}
		}
	}
}

uint8_t RFID_check(void)
{
	return flagsRfid.bits.rxBufferOk;
}

void RFID_clear(void)
{
	flagsRfid.bits.rxBufferOk = 0;
}

uint8_t RFID_verifyRxBuffer(void)
{
	//Debe cumplir ambas condiciones para que el dato sea valido
	return (RFID_verifyStopByte() && RFID_verifyChecksum())? 1 : 0;
}

uint8_t RFID_verifyStopByte(void)
{
	//El stop byte debe ser 03h para que el dato sea valido
    return (rxBuffer[RFID_NUMDATA-1] == 3)? 1 : 0;
}

uint8_t RFID_verifyChecksum(void)
{
	//El checksum calculado debe ser igual al checksum recibido en la trama
    return (((ascii2hexa(rxBuffer[11])<<4)|(ascii2hexa(rxBuffer[12]))) == RFID_doChecksum())? 1 : 0;
}

uint8_t RFID_doChecksum(void)
{
    uint8_t i;								//Contador auxiliar
    uint8_t cs = 0;							//Checksum
    uint8_t dataByte = 0;					//Variable para convertir los bytes recibidos de ascii a hexa
    uint8_t parDataByte[5] = {0,0,0,0,0};	//Byte tomados de a dos nibbles de la trama

    for(i=0;i<10;i++)
    {
        //1. Convierto los caracteres ASCII de la tarjeta a un numero hexadecimal
    	dataByte = ascii2hexa(rxBuffer[i+1]);

        //2. Agrupo cada par de numeros hexadecimales (4bits) a un byte (8bits)
        //2a. Primer nibble es el mas significativo
    	if(i%2 == 0)
        	parDataByte[i/2] |= dataByte<<4;
    	//2b. Segundo nibble es el menos significativo
        else
        {
        	parDataByte[i/2] |= dataByte;
            //Cuando termina de agrupar el par de numeros, va realizando el checksum
            cs^=parDataByte[i/2];
        }
    }

    return cs;
}

uint8_t ascii2hexa(uint8_t a)
{
    if(a >= '0' && a <= '9')
             a -= 48;
    else if(a >= 'A' && a <= 'F')
             a -= 55;

    return a;
}
