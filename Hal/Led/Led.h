/*
 * Led.h
 *
 * Created: 9/13/2022 4:03:33 AM
 *  Author: Dell
 */ 


#ifndef LED_H_
#define LED_H_



/*****************************************************_INCLUDES_*****************************************************/
#include "LedCfg.h"
#include "Dio.h"
#include "StdTypes.h"
#define F_CPU 16000000UL
#include <util/delay.h> // -> Imports the delay function -> the delay function contains empty for loop I think
/*****************************************************_MACROS_*****************************************************/
#define LED0	0
#define LED1	1
#define LED2	2
#define LED3	3
#define LED4	4

/*****************************************************_PROTOTYPES_*****************************************************/
void H_Led_Init(u8);
void H_Led_On(u8);
void H_Led_Off(u8);
void H_Led_Tog(u8);
void H_Led_BlinkOnce(u8);
void H_Led_BlinkTwice(u8);

#endif /* LED_H_ */