/*
 * sdModule.c
 *
 *  Created on: Aug 4, 2021
 *      Author: kevin
 */

#include "main.h"
#include "fatfs.h"

/************************************************************************************/
/*									External Variables								*/
/************************************************************************************/
#define TIME_DETECTSD	5





/************************************************************************************/
/*									External Variables								*/
/************************************************************************************/
extern __personal personal[MAXPERSONAL];
extern uint8_t TickSD;

extern _flagsSd flagsSd;
extern _flagsDisplay flagsDisplay;
extern uint16_t personalQuantity;





/************************************************************************************/
/*									Private Variables								*/
/************************************************************************************/
_flagsSd flagsSd;
uint8_t textName[16] = "log_YY-MM-DD.txt";
uint8_t logSentence[17];
uint8_t databaseSentence[18+MAXLEN_NAME+MAXLEN_SURNAME];	//10+1+5+1+LEN_NAME+1+MAXLEN_SURNAME
FATFS fs;
FIL fil;
FRESULT fresult;

uint8_t textRead[10+5+MAXLEN_SURNAME+MAXLEN_NAME+4];
char *temp;

uint8_t t_detectSD;





/************************************************************************************/
/*									Functions										*/
/************************************************************************************/
void SD_Init(void)
{
	MX_FATFS_Init();

	flagsSd.bytes = 0;
	flagsSd.bits.loadDataBase = 1;
}

void SD_Handler(void)
{
	uint8_t numPersonal;
	//Deteccion de SD
	if(TickSD)
	{
		TickSD = 0;
		t_detectSD++;

		if(t_detectSD>=TIME_DETECTSD)
		{
			t_detectSD = 0;

			MX_FATFS_Init();
			FATFS_UnLinkDriver(USERPath);
			retUSER = FATFS_LinkDriver(&USER_Driver, USERPath);
			f_mount(&fs, "", 0);

			fresult = f_open(&fil, (TCHAR *) "database.txt", FA_READ );
			if(fresult == FR_OK)
			{
				flagsSd.bits.warningNoSd = 0;
				flagsSd.bits.warningNoDatabaseFile = 0;
				flagsDisplay.bits.eraseWarning = 1;
				f_close(&fil);
			}
			else if(fresult == FR_NO_FILE)
			{
				flagsDisplay.bits.eraseWarning = 1;

				flagsSd.bits.warningNoDatabaseFile = 1;
				flagsDisplay.bits.refreshWarning = 1;
			}
			else if(fresult == FR_DISK_ERR || fresult == FR_NOT_READY)
			{
				flagsDisplay.bits.eraseWarning = 1;

				flagsSd.bits.warningNoSd = 1;
				flagsDisplay.bits.refreshWarning = 1;
			}
		}
	}


	//Escritura de database
		if(flagsSd.bits.WriteDataBase)
		{
			flagsSd.bits.WriteDataBase = 0;

			FATFS_UnLinkDriver(USERPath);
			retUSER = FATFS_LinkDriver(&USER_Driver, USERPath);
			f_mount(&fs, "", 0);
			//f_unlink((TCHAR *) "database.txt");
			fresult = f_open(&fil, (TCHAR *) "database.txt", FA_CREATE_ALWAYS | FA_WRITE);
			if(fresult == FR_OK)
			{
				numPersonal = 0;

				while(numPersonal < personalQuantity)
				{

					SD_Personal2DBFile(numPersonal);
					f_lseek(&fil, fil.fptr);
				/// ACA
					fresult = f_puts((TCHAR *)databaseSentence, &fil);
					numPersonal++;
				}
				f_close(&fil);
			}
			else if(fresult == FR_DISK_ERR)
			{
				flagsSd.bits.warningNoSd = 1;
				flagsSd.bits.warningNoDatabaseFile = 1;
				flagsDisplay.bits.refreshWarning = 1;
			}
		}


	//Escritura en archivos log.txt
	if(flagsSd.bits.writeLog)
	{
		flagsSd.bits.writeLog = 0;


		FATFS_UnLinkDriver(USERPath);
		retUSER = FATFS_LinkDriver(&USER_Driver, USERPath);
		f_mount(&fs, "", 0);

		fresult = f_open(&fil, (TCHAR *) textName, FA_OPEN_ALWAYS | FA_WRITE | FA_OPEN_APPEND);
		if(fresult == FR_OK)
		{
			flagsSd.bits.warningNoSd = 0;
			flagsDisplay.bits.eraseWarning = 1;
///
			f_lseek(&fil, fil.fptr);
			fresult = f_puts((TCHAR *)logSentence, &fil);
			f_close(&fil);
		}
		else if(fresult == FR_DISK_ERR)
		{
			flagsSd.bits.warningNoSd = 1;
			flagsDisplay.bits.refreshWarning = 1;
		}
	}

	//Lectura de archivo database.txt
	if(flagsSd.bits.loadDataBase)
	{
		flagsSd.bits.loadDataBase = 0;

		FATFS_UnLinkDriver(USERPath);
		retUSER = FATFS_LinkDriver(&USER_Driver, USERPath);
		fresult = f_mount(&fs, "", 1);

		fresult = f_open(&fil, (TCHAR *) "database.txt", FA_READ );
		if(fresult == FR_OK)
		{
			flagsSd.bits.warningNoSd = 0;
			flagsSd.bits.warningNoDatabaseFile = 0;
			flagsDisplay.bits.eraseWarning = 1;

			DATABASE_clear();

			//Lee los renglones del archivo 'database.txt' y lo carga en 'personal'
			do
			{
				temp = f_gets((TCHAR *)textRead, sizeof(textRead), &fil);
				if(temp != NULL)
					SD_DBFile2Personal(textRead);
			} while (temp != NULL);

			f_close(&fil);
		}
		else if(fresult == FR_NO_FILE)
		{
			flagsSd.bits.warningNoDatabaseFile = 1;
			flagsDisplay.bits.refreshWarning = 1;
		}
		else if(fresult == FR_DISK_ERR || fresult == FR_NOT_READY)
		{
			flagsSd.bits.warningNoSd = 1;
			flagsDisplay.bits.refreshWarning = 1;
		}
	}


}




void SD_writeLog(void)
{
	uint8_t detectedMovement;
	uint16_t id;
	uint8_t i;

	//1. Arma la oracion del log
	//1a. Tiempo
	RTC_getTime(logSentence,0);
	logSentence[8] 	= ',';
	//1b. ID
	id = PERSONAL_getID();
	for(i = 13; i>= 9; i--)
	{
		logSentence[i] = id%10 +'0';
		id -= id%10;
		id /= 10;
	}
	logSentence[14] = ',';
	//1c. Movimiento
	detectedMovement = PERSONAL_getDetectedMovement();
	if(detectedMovement == INGRESO)		logSentence[15] = 'I';
	else if(detectedMovement == EGRESO)	logSentence[15] = 'E';
	logSentence[16] = '\n';

	//2. Escribe en el archivo log-fecha.txt
	RTC_getDate(textName,4);
	textName[6]		= '-';
	textName[9]		= '-';

	//Crea y abre el archivo 'log-fecha.txt' y escribe 'logSentence[]'
	flagsSd.bits.writeLog = 1;
}

void SD_getDataBase(void)
{
	flagsSd.bits.loadDataBase = 1;
}

uint16_t SD_IDString2Number(uint8_t *id)
{
	uint8_t i;
	uint16_t idNum = 0;

	for(i = 0; i< 5; i++)
	{
		idNum *= 10;
		idNum += id[i];
	}

	return idNum;
}

void SD_DBFile2Personal(uint8_t *textRead)
{
	uint8_t rfidCard[10];
	uint8_t idStr[5];
	uint16_t id;
	uint8_t name[12];
	uint8_t surname[15];

	uint8_t c;
	uint8_t i, n;
	uint8_t m;
	uint8_t z=0;

	while(z!=5){/// INICALIZO IDSTR
		idStr[z]=0;
		z++;
	}


	//1. Obtiene RFID CARD

	if(textRead[0]=='A'){
		m=1;
	}
	else
	{
		m=0;
	}

	////EDITADO POR JUAN
	rfidCard[0]=textRead[0+m];
	rfidCard[1]=textRead[1+m];
	rfidCard[2]=textRead[2+m];
	rfidCard[3]=textRead[3+m];
	rfidCard[4]=textRead[4+m];
	rfidCard[5]=textRead[5+m];
	rfidCard[6]=textRead[6+m];
	rfidCard[7]=textRead[7+m];
	rfidCard[8]=textRead[8+m];
	rfidCard[9]=textRead[9+m];

	i = 10+m;


	//2. Obtiene ID
	i++;
	n = 0;
	c = textRead[i];
	while(c != ',' && n < 5)
	{
		idStr[n] = textRead[i] - '0';
		i++;
		n++;
		c = textRead[i];
	}
	id = SD_IDString2Number(idStr);

	//3. Obtiene nombre
	i++;
	n = 0;
	c = textRead[i];
	while(c != ',' && n < 12)
	{
		name[n] = textRead[i];
		i++;
		n++;
		c = textRead[i];
	}
	name[n] = '\0';

	//4. Obtiene apellido
	i++;
	n = 0;
	while(c != '\0' && n < 15)
	{
		surname[n] = textRead[i];
		i++;
		n++;
		c = textRead[i];
	}
	surname[n] = '\0';

	//5. Carga a la base de datos solo si no hay ningun registro de dicha tarjeta
	if(!DATABASE_check(rfidCard))
		PERSONAL_load(id, rfidCard, name, surname);
	//comment: Si no hay una tarjeta en el database.txt pero si esta en la estructura personal, hay que eliminarlo
}


void SD_writeDB(void)
{
	flagsSd.bits.WriteDataBase = 1;
}


void SD_Personal2DBFile(uint16_t numPersonal)
{
	uint8_t i = 0, j = 0;
	uint16_t idNum = 0;
	uint16_t resto = 0;

	/// primero limpio la databaseSentence
	for(i = 0; i < 18+MAXLEN_NAME+MAXLEN_SURNAME; i++)
		databaseSentence[i] = 0;


	//1. Tarjeta ID


	for(i = 0; i < 10; i++)
		databaseSentence[i] = personal[numPersonal].tarjetaID[i];
	databaseSentence[10] = ',';

	//2. Personal ID
	idNum = personal[numPersonal].personalID;
	for(i = 0; i < 5; i++)
	{
		resto = idNum%10;
		databaseSentence[15-i] = resto + '0';
		idNum /= 10;
	}
	databaseSentence[16] = ',';

	//3. Nombre
	i = 0;
	while(personal[numPersonal].nombre[i]!=0)
	{
			databaseSentence[17+i] = personal[numPersonal].nombre[i];
			i++;
		}
		databaseSentence[17+i] = ',';

		//4. Apellido
		j = 0;
		while(personal[numPersonal].apellido[j]!=0)
		{
			databaseSentence[18+i] = personal[numPersonal].apellido[j];
			i++;
			j++;
		}
		databaseSentence[18+j+i] = '\n';
}
