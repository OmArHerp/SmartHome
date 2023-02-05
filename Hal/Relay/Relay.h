/*
 * Relay.h
 *
 * Created: 9/17/2022 7:08:52 AM
 *  Author: Dell
 */ 


#ifndef RELAY_H_
#define RELAY_H_



/*****************************************************_INCLUDES_*****************************************************/
#include "RelayCfg.h"
#include "Dio.h"

/*****************************************************_MACROS_*****************************************************/


/*****************************************************_PROTOTYPES_*****************************************************/
void H_Relay_Init(void);
void H_Relay_On(void);
void H_Relay_Off(void);
void H_Relay_Tog(void);




#endif /* RELAY_H_ */