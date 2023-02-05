/*
 * KeyPadCfg.h
 *
 * Created: 02/10/2022 21:17:47
 *  Author: Amero
 */ 


#ifndef KEYPADCFG_H_
#define KEYPADCFG_H_

//*********************************includes******************************

//***********************************SELECT_KEYPAD_PIN******************************
//option one [connecting key pad HardWare ] ->#define KEY_PAD_PINS  HardWare
//option two [connecting key pad to port B ] ->#define KEY_PAD_PINS  Software
#define PINS_HARDWARE  1
#define PINS_SOFTWARE  2
#define KEYPAD_PINS  PINS_HARDWARE

#if KEYPAD_PINS  == PINS_HARDWARE
#define KEYPAD_R0_PIN    PB4
#define KEYPAD_R1_PIN    PB5
#define KEYPAD_R2_PIN    PB6
#define KEYPAD_R3_PIN    PB7

#define KEYPAD_C0_PIN    PC0
#define KEYPAD_C1_PIN    PC1
#define KEYPAD_C2_PIN    PC2
#define KEYPAD_C3_PIN    PC3

#elif   KEYPAD_PINS  == PINS_SOFTWARE
#define KEYPAD_R0_PIN    PD0
#define KEYPAD_R1_PIN    PD1
#define KEYPAD_R2_PIN    PD2
#define KEYPAD_R3_PIN    PD3
						  
#define KEYPAD_C0_PIN    PD4
#define KEYPAD_C1_PIN    PD5
#define KEYPAD_C2_PIN    PD6
#define KEYPAD_C3_PIN    PD7
#endif

//*********************************KEYPAD_DELAY_TIME**************************

#define KEYPAD_DEBOUNCING_TIME         50




#endif /* KEYPADCFG_H_ */