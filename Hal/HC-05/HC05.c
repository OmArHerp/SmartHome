/*
 * HC_05.c
 *
 * Created: 11/30/2022 1:16:05 PM
 *  Author: Dell
 */ 
#include "HC05.h"
void HC05_Init(void)
{
	UART_Init();
}
void HC05_Tx(u8 Local_u8_Tx)
{
	UART_Tx(Local_u8_Tx);
}
u8  HC05_Rx(void)
{
	return UART_Rx();
}