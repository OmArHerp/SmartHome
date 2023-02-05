/*
 * EXTI.h
 *
 * Created: 10/24/2022 6:12:47 PM
 *  Author: Dell
 */ 


#ifndef EXTI_H_
#define EXTI_H_
/*****************************************************_INCLUDES_*****************************************************/
#include "EXTICfg.h"
#include "Reg.h"
#include "StdTypes.h"
#include "BitMath.h"
#include "Dio.h"
/*****************************************************_MACROS_*****************************************************/

#define INT0				  0
#define INT1				  1
#define INT2				  2
#define GICR_INT1			  7 /*PIE bits*/
#define GICR_INT0			  6
#define GICR_INT2			  5
#define MCUCR_ISC11			  3 /*Interrupt 1 sense control bit 1*/
#define MCUCR_ISC10			  2 /*Interrupt 1 sense control bit 0*/
#define MCUCR_ISC01			  1 /*Interrupt 0 sense control bit 1*/
#define MCUCR_ISC00			  0 /*Interrupt 0 sense control bit 0*/
#define MCUCSR_ISC2			  3 /*Interrupt 2 sense control bit*/

#define LOW_LEVEL			  1
#define ON_CHANGE			  2
#define FALLING_EDGE		  3
#define RISING_EDGE			  4
#define ENABLED				  1
#define DISABLED			  2

/*****************************************************_PROTOTYPES_*****************************************************/
void M_EXTI_Init(void);
void M_EXTI_PINMODE(void);
void M_EXTI_CallBack(u8 IntNum,void (*Copy_pvCallBackFunc)(void));
u8 M_EXTI_EnableInt(u8 IntNum);
u8 M_EXTI_DisableInt(u8 IntNum);
u8 M_EXTI_SetSenseControl(u8 IntNum,u8 Sense);


#endif /* EXTI_H_ */