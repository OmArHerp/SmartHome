/*
 * PushButton.h
 *
 * Created: 9/17/2022 3:22:42 PM
 *  Author: Dell
 */ 


#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_


/******************************************************_INCLUDES_*****************************************************/
#include "PushButtonCfg.h"
#include "Dio.h"
#include "StdTypes.h"
#define F_CPU 16000000UL
#include <util/delay.h>
/*****************************************************_MACROS_*****************************************************/
#define PUSH_BUTTON0		0
#define PUSH_BUTTON1		1
#define PUSH_BUTTON2		2

#define ACTIVE_HIGH			1
#define ACTIVE_LOW			2

#if  PUSH_BUTTON_MODE	==	ACTIVE_HIGH
#define RELEASED			0
#define PRESSED				1
#elif PUSH_BUTTON_MODE	==	ACTIVE_LOW
#define PRESSED				0
#define RELEASED			1
#endif
/*****************************************************_PROTOTYPES_*****************************************************/
void H_PushButton_Init(u8);
u8   H_PushButtonRead(u8);




#endif /* PUSHBUTTON_H_ */