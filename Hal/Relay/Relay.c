/*
 * Relay.c
 *
 * Created: 9/17/2022 7:08:37 AM
 *  Author: Dell
 */ 

#include "Relay.h"


void H_Relay_Init(void)
{
	M_Dio_PinMode(RELAY_PIN,OUTPUT);
}
void H_Relay_On(void)
{
	M_Dio_PinWrite(RELAY_PIN,HIGH);
}
void H_Relay_Off(void)
{
	M_Dio_PinWrite(RELAY_PIN,LOW);
}
void H_Relay_Tog(void)
{
	M_Dio_PinTog(RELAY_PIN);
}