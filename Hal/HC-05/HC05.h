/*
 * HC_05.h
 *
 * Created: 11/30/2022 1:16:43 PM
 *  Author: Dell
 */ 


#ifndef HC05_H_
#define HC05_H_
/*****************************************************_INCLUDES_*****************************************************/
#include "UART.h"
#include "StdTypes.h"
/*****************************************************_PROTOTYPES_*****************************************************/
void HC05_Init(void);
void HC05_Tx(u8);
u8   HC05_Rx(void);



#endif /* HC-05_H_ */