/*
 * UART.c
 *
 * Created: 11/24/2022 6:48:07 PM
 *  Author: Dell
 */ 
#include "UART.h"

void UART_Init(void)
{
	ClrBit(DDRD,0); //to Enable input circuit for Rx Pin
	SetBit(DDRD,1); //to Enable input circuit for Tx Pin
	u8  Local_u8_UCSRCValue = 0;
	u16 Local_u16_UBRRHValue = 0;
	/*Set bit 7 for UCSRC register select*/
	SetBit(Local_u8_UCSRCValue,UCSRC_URSEL);
	
	/*8 Data bits character size*/
	SetBit(Local_u8_UCSRCValue,UCSRC_UCSZ0);
	SetBit(Local_u8_UCSRCValue,UCSRC_UCSZ1);
	
	/*9600 bps on system frequency 16MHz*/
	UBRRL = ((u32)F_OSC * 1000000 / ((u32)16 * BAUD_RATE)) -1;
	Local_u16_UBRRHValue = ((u32)F_OSC * 1000000 / ((u32)16 * BAUD_RATE)) -1 >> 8;
	UBRRH = Local_u16_UBRRHValue;
	
	
	/*Select Asynch. Mode*/
	ClrBit(Local_u8_UCSRCValue,UCSRC_UMSEL);
	
	/*Select Parity Mode*/
	#if	  PARITY_MODE	==	PARITY_DISABLE
	ClrBit(Local_u8_UCSRCValue,UCSRC_UPM0);
	ClrBit(Local_u8_UCSRCValue,UCSRC_UPM1);
	#elif PARITY_MODE	==	PARITY_ODD
	SetBit(Local_u8_UCSRCValue,UCSRC_UPM0);
	SetBit(Local_u8_UCSRCValue,UCSRC_UPM1);
	#elif PARITY_MODE	==	PARITY_EVEN
	ClrBit(Local_u8_UCSRCValue,UCSRC_UPM0);
	SetBit(Local_u8_UCSRCValue,UCSRC_UPM1);
	#endif
	
	/*Select 1 stop bit*/
	ClrBit(Local_u8_UCSRCValue,3);
	
	/*Send The Value to the register*/
	UCSRC = Local_u8_UCSRCValue;
	
	/*RX Enable*/
	SetBit(UCSRB,UCSRB_RXEN);
	
	/*TX Enable*/
	SetBit(UCSRB,UCSRB_TXEN);
}
void UART_Tx(u8 Local_u8_Data)
{
	UDR = Local_u8_Data;
	while(GetBit(UCSRA,6) == 0); // wait till data get transmitted 
}
u8	 UART_Rx(void)
{
	while(GetBit(UCSRA,7) == 0) // wait till all data received  
	{
		extern u8  Local_u8_Variable13 ;
		if(Local_u8_Variable13 !=0)
		break;
	}
	return UDR;
}
void UART_TxString(u8 *String)
{
	if(String != NULL)
	{
		u8 counter =0;
		while(String[counter] != '\0')
		{
			UART_Tx(String[counter]);
			counter++;
			_delay_ms(10);
		}
	}
}
















/*
u8 UART_SendCharSync(u8 u8char)
{
	while(GetBit(UCSRA,UCSRA_UDRE) == 0);
	UDR = u8char;
}
u8   UART_ReceiveChar(void)
{
	while(GetBit(UCSRA,UCSRA_RXC) == 0);
	return UDR;
}*/