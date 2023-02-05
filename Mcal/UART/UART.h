/*
 * UART.h
 *
 * Created: 11/24/2022 6:48:23 PM
 *  Author: Dell
 */ 


#ifndef UART_H_
#define UART_H_
/*****************************************************_INCLUDES_*****************************************************/
#include "UARTCfg.h"
#include "BitMath.h"
#include "StdTypes.h"
#include "Reg.h"
#define F_CPU 16000000UL
#include <util/delay.h>
/*****************************************************_MACROS_*****************************************************/
#define UCSRA_RXC			7
#define UCSRA_TXC			6
#define UCSRA_UDRE			5
#define UCSRA_FE			4
#define UCSRA_DOR			3
#define UCSRA_PE			2
#define UCSRA_U2X			1
#define UCSRA_MPCM			0


#define UCSRB_RXEN			4
#define UCSRB_TXEN			3
#define UCSRB_UCSZ2			2
#define UCSRB_RXB			1
#define UCSRB_TXB			0


#define UCSRC_URSEL			7
#define UCSRC_UMSEL			6
#define UCSRC_UPM1			5
#define UCSRC_UPM0			4
#define UCSRC_USBS			3
#define UCSRC_UCSZ1			2
#define UCSRC_UCSZ0			1
#define UCSRC_UCPOL			0

#define UBRRH_URSEL			7




#define PARITY_DISABLE		1
#define PARITY_ODD			2
#define PARITY_EVEN			3


/*****************************************************_PROTOTYPES_*****************************************************/
void UART_Init(void);
void UART_Tx(u8);
u8	 UART_Rx(void);
void UART_TxString(u8 *);






/*
u8 UART_SendCharSynch(u8 u8char);
u8 UART_ReceiveCharSynch(u8* ReceivedData);
u8 UART_SendCharAsynch(u8 u8char, void (*NotificationFunc)(void));
u8 UART_ReceiveCharAsynch(u8* ReceivedData, void (*NotificationFunc)(void));

u8 UART_SendBufferSynch(u8* Buffer, u8 Size);
u8 UART_ReceiveBufferSynch(u8* ReceivedBuffer, u8 Size);

u8 UART_SendBufferAsynch(u8* Buffer , void (*NotificationFunc)(void) , u8 Size);
u8 UART_ReceiveBufferAsynch(u8* ReceivedBuffer , void (*NotificationFunc)(void), u8 Size);
*/




#endif /* UART_H_ */