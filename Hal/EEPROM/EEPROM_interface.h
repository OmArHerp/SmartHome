/*
 * EEPROM_interface.h
 *
 * Created: 12/6/2022 1:19:57 AM
 *  Author: Dell
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_



/*****************************************************_INCLUDES_*****************************************************/
#include "StdTypes.h"
#include "BitMath.h"
#include "Reg.h"
#include "I2C_interface.h"
#define F_CPU 16000000UL
#include <util/delay.h>
/*****************************************************_MACROS_*****************************************************/
#define EEPROM_FIXED_ADDRESS		0x50
#define EEPROM_Delay				5

#define EERE						0
#define EEWE						1
#define EEMWE						2
#define EERIE						3

#define SPMEN						0
/*****************************************************_PROTOTYPES_*****************************************************/
void EEPROM_WriteByte(u16 byteAddress, u8 data);
void EEPROM_ReadByte(u16 byteAddress, u8* returnData);
void EEPROMINT_WriteByte(u16 byteAddress, u8 data);
u8	 EEPROMINT_ReadByte(u16 byteAddress);




#endif /* EEPROM_INTERFACE_H_ */