/*
 * stateMachine.h
 *
 *  Created on: May 30, 2021
 *      Author: kevin
 */

#ifndef INC_STATEMACHINE_H_
#define INC_STATEMACHINE_H_

/************************************************************************************/
/*									Enum											*/
/************************************************************************************/
enum __stateMachineGlobal {
	__inOperation = 0,
	__inConfiguration
};





/************************************************************************************/
/*									Functions										*/
/************************************************************************************/
void stateMachineInit(void);
void stateMachineSystem(void);
void stateMachineInOperation(void);
void stateMachineInConfiguration(void);





/************************************************************************************/
/*									Defines										*/
/************************************************************************************/
//Display
#define disp_APOYESUTARJETA 		0
#define disp_HOLA					1
#define disp_HASTALUEGO				2
#define disp_TARJETANOIDENTIFICADA	3
#define disp_CONFIGURANDO			4
#define disp_TUSB			5
#define disp_TAGREGADA 6
#define disp_PELIMINADA 7

#endif /* INC_STATEMACHINE_H_ */
