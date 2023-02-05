/*
 * TIMER.h
 *
 * Created: 11/17/2022 12:22:46 AM
 *  Author: Dell
 */ 


#ifndef TIMER_H_
#define TIMER_H_
/*****************************************************_INCLUDES_*****************************************************/
#include "TIMERCfg.h"
#include "StdTypes.h"
#include "Reg.h"
#include "BitMath.h"
/*****************************************************_MACROS_*****************************************************/
#define TCCR0_WGM00			6  /*Waveform Generation mode bit 0 & 1*/
#define TCCR0_WGM01			3
#define TIMSK_TOIE0			0  /*Timer0 overflow interrupt enable*/
#define TIMSK_TOIE1			2  /*Timer1 overflow interrupt enable*/
#define TIMSK_OCIE0			1  /*Timer0 Output compare interrupt enable*/
#define TCCR1A_COM1A1		7  /*ChannelA compare match output mode bit1*/
#define TCCR1A_COM1A0		6  /*ChannelA compare match output mode bit0*/
#define TCCR1A_WGM11		1  /*Waveform generation mode bit1*/
#define TCCR1A_WGM10		0  /*Waveform generation mode bit0*/
#define TCCR1B_WGM13		4  /*Waveform generation mode bit3*/
#define TCCR1B_WGM12		3  /*Waveform generation mode bit2*/
#define TCCR1B_CS12			2  /*Prescaler bit 2*/
#define TCCR1B_CS11			1  /*Prescaler bit 1*/
#define TCCR1B_CS10			0  /*Prescaler bit 0*/
#define TCCR0_COM00			4 /*Compare Modes (Seton on top clear on compare or reverse ((Non)Inverted)*/
#define TCCR0_COM01			5


#define TIMER_OVF_INT		0
#define TIMER_CTC_INT		1

/*****************************************************_PROTOTYPES_*****************************************************/
void TIMER0_Init(void);
void TIMER0_OVF_SetCallBack(void (*CallBackFunc) (void));
void TIMER1_Init(void);
void TIMER1_SetCompVal(u16 CompVal); //setting H.W PWM no need for ISR Callback or whatever this shit is
void TIMER0_SetCompVal(u8 CompVal);
void TIMER1_SetTimerVal(u16 Val);
u16 TIMER1_GetTimerReading(void);
void M_Timer1_CallBackFn(void (*Ptr_ToFn) (void) );

#endif /* TIMER_H_ */