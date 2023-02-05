/*
 * EXTI.c
 *
 * Created: 10/24/2022 6:11:22 PM
 *  Author: Dell
 */ 
#include "EXTI.h"

/*Array of global pointer to functions to hold ISR addresses*/
 static void (*CallBackFunc[3])(void) = {NULL};

void M_EXTI_PINMODE(void)
{
	M_Dio_PinMode(PD2,INPUT);
	M_Dio_PinMode(PD3,INPUT);
 	M_Dio_PinPullRes(PD2,ENABLE);
	M_Dio_PinPullRes(PD2,ENABLE);
}

u8 M_EXTI_EnableInt(u8 IntNum)
{
	u8 Local_u8_ErrorState = OK;
	switch(IntNum)
	{
		case INT0: SetBit(GICR,GICR_INT0); break;
		case INT1: SetBit(GICR,GICR_INT1); break;
		case INT2: SetBit(GICR,GICR_INT2); break;
		default:   Local_u8_ErrorState = NOK; break;
	}
	return Local_u8_ErrorState;
}
u8 M_EXTI_DisableInt(u8 IntNum)
{
	u8 Local_u8_ErrorState = OK;
	switch(IntNum)
	{
		case INT0: ClrBit(GICR,GICR_INT0); break;
		case INT1: ClrBit(GICR,GICR_INT1); break;
		case INT2: ClrBit(GICR,GICR_INT2); break;
		default:   Local_u8_ErrorState = NOK; break;
	}
	return Local_u8_ErrorState;
}

void M_EXTI_Init(void)
{
	M_EXTI_PINMODE();
	/*Set INT0 Sense Control*/
	#if		INT0_SENSE == LOW_LEVEL
			ClrBit(MCUCR,MCUCR_ISC00);
			ClrBit(MCUCR,MCUCR_ISC01);
	#elif	INT0_SENSE == ON_CHANGE
			SetBit(MCUCR,MCUCR_ISC00);
			ClrBit(MCUCR,MCUCR_ISC01);
	#elif	INT0_SENSE == FALLING_EDGE
			ClrBit(MCUCR,MCUCR_ISC00);
			SetBit(MCUCR,MCUCR_ISC01);
	#elif	INT0_SENSE == RISING_EDGE
			SetBit(MCUCR,MCUCR_ISC00);
			SetBit(MCUCR,MCUCR_ISC01);
	#else
			#error "Wrong INT0_SENSE Config Option"
	#endif
	
	/*Set INT1 Sense Control*/
	#if		INT1_SENSE == LOW_LEVEL
			ClrBit(MCUCR,MCUCR_ISC10);
			ClrBit(MCUCR,MCUCR_ISC11);
	#elif	INT1_SENSE == ON_CHANGE
			SetBit(MCUCR,MCUCR_ISC10);
			ClrBit(MCUCR,MCUCR_ISC11);
	#elif	INT1_SENSE == FALLING_EDGE
			ClrBit(MCUCR,MCUCR_ISC10);
			SetBit(MCUCR,MCUCR_ISC11);
	#elif	INT1_SENSE == RISING_EDGE
			SetBit(MCUCR,MCUCR_ISC10);
			SetBit(MCUCR,MCUCR_ISC11);
	#else
			#error "Wrong INT1_SENSE Config Option"
	#endif
	
	/*Set INT2 Sense Control*/
	#if		INT2_SENSE == FALLING_EDGE
			ClrBit(MCUCSR,MCUCSR_ISC2);
	#elif	INT2_SENSE == RISING_EDGE
			SetBit(MCUCSR,MCUCSR_ISC2);
	#else
			#error "Wrong INT0_SENSE Config Option"
	#endif
	
	/*Set INT0 Initial state (PIE)*/
	#if		INT0_INITIAL_STATE == ENABLED
			SetBit(GICR,GICR_INT0);
	#elif	INT0_INITIAL_STATE == DISABLED
			ClrBit(GICR,GICR_INT0);
	#else
			#error "Wrong Initial State condition for INT0"
	#endif
			
	/*Set INT1 Initial state (PIE)*/
	#if		INT1_INITIAL_STATE == ENABLED
			SetBit(GICR,GICR_INT1);
	#elif	INT1_INITIAL_STATE == DISABLED
			ClrBit(GICR,GICR_INT1);
	#else
			#error "Wrong Initial State condition for INT1"
	#endif
	
	/*Set INT2 Initial state (PIE)*/
	#if		INT2_INITIAL_STATE == ENABLED
			SetBit(GICR,GICR_INT2);
	#elif	INT2_INITIAL_STATE == DISABLED
			ClrBit(GICR,GICR_INT2);
	#else
			#error "Wrong Initial State condition for INT2"
	#endif
}

u8 M_EXTI_SetSenseControl(u8 IntNum,u8 Sense)
{
	u8 Local_u8_ErrorState = OK;
	
	switch(IntNum)
	{
		case INT0:
			if(Sense == LOW_LEVEL)
			{
				ClrBit(MCUCR,MCUCR_ISC00);
				ClrBit(MCUCR,MCUCR_ISC01);
			}
			else if(Sense == ON_CHANGE)
			{
				SetBit(MCUCR,MCUCR_ISC00);
				ClrBit(MCUCR,MCUCR_ISC01);
			}
			else if (Sense == FALLING_EDGE)
			{
				ClrBit(MCUCR,MCUCR_ISC00);
				SetBit(MCUCR,MCUCR_ISC01);
			}
			else if (Sense == RISING_EDGE)
			{
				SetBit(MCUCR,MCUCR_ISC00);
				SetBit(MCUCR,MCUCR_ISC01);
			}
			else
			{
				Local_u8_ErrorState = NOK;
			}
			break;
		case INT1:
			if(Sense == LOW_LEVEL)
			{
				ClrBit(MCUCR,MCUCR_ISC10);
				ClrBit(MCUCR,MCUCR_ISC11);
			}
			else if(Sense == ON_CHANGE)
			{
				SetBit(MCUCR,MCUCR_ISC10);
				ClrBit(MCUCR,MCUCR_ISC11);
			}
			else if (Sense == FALLING_EDGE)
			{
				ClrBit(MCUCR,MCUCR_ISC10);
				SetBit(MCUCR,MCUCR_ISC11);
			}
			else if (Sense == RISING_EDGE)
			{
				SetBit(MCUCR,MCUCR_ISC10);
				SetBit(MCUCR,MCUCR_ISC11);
			}
			else
			{
				Local_u8_ErrorState = NOK;
			}
			break;
		
		case INT2:
			if(Sense == FALLING_EDGE)
			{
				ClrBit(MCUCSR,MCUCSR_ISC2);
			}
			else if (Sense == RISING_EDGE)	
			{
				SetBit(MCUCSR,MCUCSR_ISC2);
			}
			else
			{
				Local_u8_ErrorState = NOK;
			}
			break;
		default: Local_u8_ErrorState = NOK; break;
	}
	return Local_u8_ErrorState;
}

void M_EXTI_CallBack(u8 IntNum,void (*Copy_pvCallBackFunc)(void))
{
	if(Copy_pvCallBackFunc != NULL)
	{
		if(IntNum < 3)
		{
			CallBackFunc[IntNum] = Copy_pvCallBackFunc;
		}
		
	}
}


/*INT0 ISR*/
void __vector_1 (void)		__attribute__((signal, used));
void __vector_1(void)
{
	if(CallBackFunc[INT0] != NULL)
	{
		CallBackFunc[INT0]();
	}
	
}

/*INT1 ISR*/
void __vector_2 (void)		__attribute__((signal, used));
void __vector_2(void)
{
	if(CallBackFunc[INT1] != NULL)
	{
		CallBackFunc[INT1]();
	}
}

/*INT2 ISR*/
void __vector_3 (void)		__attribute__((signal, used));
void __vector_3(void)
{
	if(CallBackFunc[INT2] != NULL)
	{
		CallBackFunc[INT2]();
	}

}