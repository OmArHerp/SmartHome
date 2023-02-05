/*
 * GIE.c
 *
 * Created: 10/24/2022 6:48:33 PM
 *  Author: Dell
 */ 
#include "GIE.h"

void M_GIE_EnableGlobal(void)
{
	//SetBit(SREG,SREG_I);
	 __asm volatile ("SEI"); /*Inline assembly syntax*/
}
void M_GIE_DisableGlobal(void)
{
	//ClrBit(SREG,SREG_I);
	 __asm volatile ("CLI"); /*Inline assembly syntax*/

}