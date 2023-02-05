/*
 * Includes.h
 *
 * Created: 12/20/2022 12:31:55 AM
 *  Author: Dell
 */ 


#ifndef INCLUDES_H_
#define INCLUDES_H_

/*****************************************************_INCLUDES_*****************************************************/
#include "BitMath.h"
#include "StdTypes.h"
#include "Reg.h"
#include "Dio.h"
#include "Led.h"
#include "Buzzer.h"
#include "PushButton.h"
#include "Lcd.h"
#include "SevenSegment.h"
#include "KeyPad.h"
#include "SPI_INTERFACE.h"
#include "EXTI.h"
#include "GIE.h"
#include "ADC.h"
#include "TIMER.h"
#include "UART.h"
#include "HC05.h"
#include "EEPROM_interface.h"
#include "H_Bridge.h"
#include "Relay.h"
#define DigitNumbers	10
#define OperationNumber 5
#define F_CPU 16000000UL
#include <util/delay.h>
/*****************************************************_MACROS_*****************************************************/
#define ADMIN_MODE				20				
#define USER_MODE				21		
#define FIRST_BYTE				0
#define LAST_BYTE				255
#define LAST_PLACE				255
#define EMPTY					0xFF
#define NEXTLINE				13
#define ENTER					13
#define NO_ADMIN				0
#define ADMIN_EXISTS			1
#define DISPLAY_TIME			750
#define ERROR					0
#define NO_ERROR				1
#define END_OF_CREDENTIALS		'$'	
#define WATING_FOR_A			22	
#define TAKE_ID					1
#define STOP_TAKING_ID			0	
#define STOP_TAKING_PASS		1	
#define STILL_LOGGING_IN		1
#define START_TAKING_PASS		0
#define TWO_TRIALS				3
#define ONE_TRIAL				2
#define ZERO_TRIALS				1
#define NO_TRIALS				0
#define FIRST_EEPROM_PLACE		0
#define EMERGENCY				1
#define RESET					0
#define ADD_USER				1+48
#define REMOVE_USER				2+48
#define MENU					3+48
#define NONE					0
#define WAITING_FOR_CHOICE		1
#define ADDING_ID				1
#define ADDING_PASS				1
#define REMOVING_USER			1
#define TAKING_ID_PASS			1
#define CHECKING				1
#define YES						1
#define NO						0	
/*****************************************************_PROTOTYPES_*****************************************************/
void Door_Control(void);
void Light_Control(void);
void Dim_Light_Control(void);
void AirCond_control(void);
void AirCond_EN(void);



#endif /* INCLUDES_H_ */