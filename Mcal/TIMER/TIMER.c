/*
 * Timer.c
 *
 * Created: 11/17/2022 12:22:03 AM
 *  Author: Dell
 */ 
#include "TIMER.h"

static void (*TIMER0_OVFCallBackFunc) (void) = NULL;
//static void (*TIMER0_CTCCallBackFunc) (void) = NULL;
static void (*TIMER1_OVFCallBackFunc)(void) = NULL ;

void TIMER0_Init(void)
{
	/*Set fast pwm mode*/
	SetBit(TCCR0,TCCR0_WGM00);
	SetBit(TCCR0,TCCR0_WGM01);
	
	/*Preload Value*/
	TCNT0 = TIMER0_PRELOAD_VALUE;
	
	/*Interrupt Timer Enable*/
	//SetBit(TIMSK,TIMSK_TOIE0);
	
	
	
	/*Set Prescaler: Divison by 64*/
	TCCR0 &= 0b11111000;
	TCCR0 |=3;
	
	//set on top clr on comp
	ClrBit(TCCR0,TCCR0_COM00);
	SetBit(TCCR0,TCCR0_COM01);
	
	 /*OCR0 = 64 ;*/
	
}
void TIMER0_SetCompVal(u8 CompVal)
{
	OCR0 = CompVal;
}

void TIMER0_OVF_SetCallBack(void (*CallBackFunc) (void))
{
	if(CallBackFunc != NULL)
	{
		TIMER0_OVFCallBackFunc = CallBackFunc;
	}
}

/*ISR Function protoType for Timer0 OVF*/
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	static u16 counter =0;
	counter++;
	
	if(TIMER0_OVERFLOW_COUNTER == counter)
	{
		/*Set Preload Value*/
		TCNT0 = TIMER0_PRELOAD_VALUE;
		
		/*Set Preload Value*/
		counter = 0;
		
		/*call action*/
		if(TIMER0_OVFCallBackFunc != NULL)
		{
			TIMER0_OVFCallBackFunc();
		}
	}
}
void TIMER1_Init(void)
{
	
	
	/*Waveform Generation Mode: Normal Mode*/
	ClrBit(TCCR1A,TCCR1A_WGM10);
	ClrBit(TCCR1A,TCCR1A_WGM11);
	ClrBit(TCCR1B,TCCR1B_WGM12);
	ClrBit(TCCR1B,TCCR1B_WGM13);
	
	
	
	/*Prescaler: Divison by 1024*/
	SetBit(TCCR1B,TCCR1B_CS10);
	ClrBit(TCCR1B,TCCR1B_CS11);
	SetBit(TCCR1B,TCCR1B_CS12);
	
	//over flow interrupt En
	SetBit(TIMSK,TIMSK_TOIE1);
	
	

	
}
void TIMER1_SetCompVal(u16 CompVal)
{
	OCR1A = CompVal;
}
void TIMER1_SetTimerVal(u16 Val)
{
	TCNT1 = Val;
}
u16 TIMER1_GetTimerReading(void)
{
	return TCNT1;
}



void M_Timer1_CallBackFn(void (*Ptr_ToFn) (void) )
{
	TIMER1_OVFCallBackFunc = Ptr_ToFn;
}
void __vector_9(void)__attribute__((signal, used));
void __vector_9(void)
{
	if(TIMER1_OVFCallBackFunc != NULL)
	TIMER1_OVFCallBackFunc();
}