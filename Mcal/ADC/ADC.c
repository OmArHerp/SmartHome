/*
 * ADC.c
 *
 * Created: 11/11/2022 10:47:12 PM
 *  Author: Dell
 */ 
#include "ADC.h"

/*Global Variable to hold the ADC Asynchronous digital result*/
static u16 *Global_PointerResult = NULL;
/*Global Variable to hold the ADC Asynchronous notification function*/
static void(*Global_NotificationFunc)(void) = NULL;

/**/
static u8 Global_ADCBusyFlag = IDLE;

void M_ADC_INIT(void)
{
	/*Set AREF as reference Voltage*/
	ClrBit(ADMUX,ADMUX_REFS1);
	SetBit(ADMUX,ADMUX_REFS0);
	
#if ADC_RESOLUTION == EIGHT_BIT
	SetBit(ADMUX,ADMUX_ADLAR); //-> clear to use 10 bits /*Activate Left Adjust result for 8 bit resolution*/
#elif ADC_RESOLUTION == TEN_BIT
	ClrBit(ADMUX,ADMUX_ADLAR);
#else
#error "Wrong ADC_RESOLUTION Configuration Option"
#endif
	
	/*setting prescalar*/
	ADCSRA &= 0b11111000;
	ADCSRA |= ADC_PRESCALER;
	
	/*ADC ENABLE*/
	SetBit(ADCSRA,ADCSRA_ADEN);
}
u8 M_ADC_StartConversionSynch(u8 Channel, u16 *ptr_u16_result)
{
	
	u8 Local_u8_ErrorState = OK; //  -> u8 Local_u8_ErrorState = 1;
	u32 Local_32_Counter =0;
	
	if(ptr_u16_result != NULL)
	{
		/*Check ADC is idle*/
		if(Global_ADCBusyFlag == IDLE)
		{
			/*ADC is now busy*/
			Global_ADCBusyFlag = BUSY;
			
			/*Set The Required Channel*/
			ADMUX &= 0b11100000;
			ADMUX |= Channel;
			
			/*Start Conversion*/
			SetBit(ADCSRA, ADCSRA_ADSC);
			
			/*busy waiting (polling) on the conversion complete flag*/ // -> On the completion of the conversion it becomes 1 or as long as the timeout hasn't passed
			while((!GetBit(ADCSRA,ADCSRA_ADIF)) && (Local_32_Counter != ADC_TIMEOUT))
			{
				Local_32_Counter++;
			}
			
			/*check about the reason why the loop is finished*/
			if(Local_32_Counter == ADC_TIMEOUT)
			{
				/*Loop is finished because timeout period has passed*/
				Local_u8_ErrorState = TIMEOUT_ERROR;
			}
			else
			{
				/*Loop is finished because the conversion complete flag is raised*/
				/*clear the interrupt flag*/  //-> must be cleared if not it will always be set during all operations
				SetBit(ADCSRA,ADCSRA_ADIF);
				
				/*return the data*/
				
				#if ADC_RESOLUTION == EIGHT_BIT
				*ptr_u16_result = ADCH;  // left adjust
				#elif ADC_RESOLUTION == TEN_BIT
				*ptr_u16_result = ADC;
				#endif
				
			}
			/*ADC is now IDLE*/
			Global_ADCBusyFlag = IDLE;
		}
		else
		{
			Local_u8_ErrorState = BUSY_ERROR;
		}
	}
	else
	{
		Local_u8_ErrorState = NULL_POINTER; 
	}
	
	return Local_u8_ErrorState;
}

u8 M_ADC_StartConversionAsynch(u8 Channel, u16 *ptr_u16_result, void (*NotificationFunc)(void))
{
	u8 Local_u8_ErrorState = OK;
	
	if((ptr_u16_result != NULL) && (NotificationFunc !=NULL))
	{
		if(Global_ADCBusyFlag == IDLE)
		{
			/*ADC is now busy*/
			Global_ADCBusyFlag = BUSY;
			/*Initialize the ADC result pointer globally*/
			Global_PointerResult = ptr_u16_result;
			
			/*Initialize the ADC notification function pointer golbally*/
			Global_NotificationFunc = NotificationFunc;
			
			/*Set The Required Channel*/
			ADMUX &= 0b11100000;
			ADMUX |= Channel;
			
			/*Start Conversion*/
			SetBit(ADCSRA, ADCSRA_ADSC);
			/*ADC conversion complete interrupt enable*/
			SetBit(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_u8_ErrorState = BUSY;
		}
		
	}
	else
	{
		Local_u8_ErrorState = NULL_POINTER;
	}
	return Local_u8_ErrorState;
}

/*ADC ISR*/
void __vector_16 (void)		__attribute__((signal));
void __vector_16 (void)	
{
	/*read the result*/
#if ADC_RESOLUTION == EIGHT_BIT
	 *Global_PointerResult = ADCH;  // left adjust
#elif ADC_RESOLUTION == TEN_BIT
	 *Global_PointerResult = ADC;
#endif

	/*Disable ADC complete interrupt enable*/
	 ClrBit(ADCSRA,ADCSRA_ADIE);
	 
	 /*ADC is now IDLE*/
	 Global_ADCBusyFlag = IDLE;
	 
	 /*Invoke the call back notification function*/
	 if(Global_NotificationFunc != NULL)
	 {
		 Global_NotificationFunc();
	 }
	 else
	 {
		 /*Do Nothing*/
	 }
}