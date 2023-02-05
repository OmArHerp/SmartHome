/*
 * PushButton.c
 *
 * Created: 9/17/2022 3:22:19 PM
 *  Author: Dell
 */ 

#include "PushButton.h"

void H_PushButton_Init(u8 Local_u8_PushButton)
{
	switch(Local_u8_PushButton)
	{
		case PUSH_BUTTON0 : M_Dio_PinMode(PUSH_BUTTON0_PIN,INPUT); break;
		case PUSH_BUTTON1 : M_Dio_PinMode(PUSH_BUTTON1_PIN,INPUT); break;
		case PUSH_BUTTON2 : M_Dio_PinMode(PUSH_BUTTON2_PIN,INPUT); break;
		default:												   break;
	}
}
u8   H_PushButtonRead(u8 Local_u8_PushButton)
{
	u8 Local_u8_Reading = RELEASED;
	switch(Local_u8_PushButton)
	{
		case PUSH_BUTTON0 :
		 if(M_Dio_PinRead(PUSH_BUTTON0_PIN) == PRESSED)
		 {
			 _delay_ms(PUSH_BUTTON_DEBOUNCING_TIME);
			 if(M_Dio_PinRead(PUSH_BUTTON0_PIN) == PRESSED)
			 {
				 while(M_Dio_PinRead(PUSH_BUTTON0_PIN) == PRESSED);
				 Local_u8_Reading = PRESSED;
			 }
		 }
		 break;
		case PUSH_BUTTON1 : 
		if(M_Dio_PinRead(PUSH_BUTTON1_PIN) == PRESSED)
		{
			_delay_ms(PUSH_BUTTON_DEBOUNCING_TIME);
			if(M_Dio_PinRead(PUSH_BUTTON1_PIN) == PRESSED)
			{
				while(M_Dio_PinRead(PUSH_BUTTON1_PIN) == PRESSED);
				Local_u8_Reading = PRESSED;
			}
		}
		break;
		case PUSH_BUTTON2 : 
		if(M_Dio_PinRead(PUSH_BUTTON2_PIN) == PRESSED)
		{
			_delay_ms(PUSH_BUTTON_DEBOUNCING_TIME);
			if(M_Dio_PinRead(PUSH_BUTTON2_PIN) == PRESSED)
			{
				while(M_Dio_PinRead(PUSH_BUTTON2_PIN) == PRESSED);
				Local_u8_Reading = PRESSED;
			}
		}
		break;
		default:						 break;
	}
	return Local_u8_Reading;
	
}