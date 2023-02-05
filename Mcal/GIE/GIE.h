/*
 * GIE.h
 *
 * Created: 10/24/2022 6:49:12 PM
 *  Author: Dell
 */ 


#ifndef GIE_H_
#define GIE_H_
/*****************************************************_INCLUDES_*****************************************************/
#include "StdTypes.h"
#include "BitMath.h"
#include "Reg.h"
/*****************************************************_MACROS_*****************************************************/
#define SREG_I		7			/*Global Interrupt Enable Bit*/
/*****************************************************_PROTOTYPES_*****************************************************/
void M_GIE_EnableGlobal(void);
void M_GIE_DisableGlobal(void);




#endif /* GIE_H_ */