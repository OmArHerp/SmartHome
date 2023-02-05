/*
 * PushButtonCfg.h
 *
 * Created: 9/17/2022 3:22:58 PM
 *  Author: Dell
 */ 


#ifndef PUSHBUTTONCFG_H_
#define PUSHBUTTONCFG_H_
/*****************************************************_SELECT_PUSH_BUTTON_MODE_*********************************************/
// option 1 -> [ ACTIVE_HIGH ]
// option 2 -> [ ACTIVE_LOW ]
#define PUSH_BUTTON_MODE			  ACTIVE_HIGH
/*****************************************************_SELECT_PUSH_BUTTON_DEBOUNCING_TIME_***********************************/
#define PUSH_BUTTON_DEBOUNCING_TIME	  100
/*****************************************************_SELECT_PB_PIN_*****************************************************/
#define PUSH_BUTTON0_PIN			  PB0
#define PUSH_BUTTON1_PIN		      PD6
#define PUSH_BUTTON2_PIN			  PD2

#endif /* PUSHBUTTONCFG_H_ */