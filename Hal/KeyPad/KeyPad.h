/*
 * KeyPad.h
 *
 * Created: 02/10/2022 21:17:20
 *  Author: Amero
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

//*********************************includes******************************
#include "KeyPadCfg.h"
#include "Dio.h"
#include "StdTypes.h"
# define F_CPU 16000000UL
#include <util/delay.h>
//***********************************MACROS******************************
#define KEYPAD_PRESSED                 0
#define KEYPAD_RELEASED                1
//*********************************prototypes**************************

void H_KeyPad_Init(void);
u8 H_KeyPad_Read(void);



#endif /* KEYPAD_H_ */