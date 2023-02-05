/*
 * EEPROM_program.c
 *
 * Created: 12/6/2022 1:19:45 AM
 *  Author: Dell
 */ 
#include "EEPROM_interface.h"


void EEPROM_WriteByte(u16 byteAddress, u8 data)
{
	u8 Local_u8_Address = (u8)(EEPROM_FIXED_ADDRESS | (u8) (byteAddress>>8));
	/*Send Start Condition*/
	I2C_SendStartCondition();
	
	/*Send Slave address with write operation*/
	I2C_SendSlaveAddWithWrite(Local_u8_Address);
	
	/*Send byte address*/
	I2C_SendMasterDataByte(byteAddress);
	
	/*Send byte data*/
	I2C_SendMasterDataByte(data);
	
	/*Send stop condition*/
	I2C_SendStopCondition();
	
	_delay_ms(EEPROM_Delay);
}

void EEPROM_ReadByte(u16 byteAddress, u8* returnData)
{
	u8 Local_u8_Address = (u8)(EEPROM_FIXED_ADDRESS | (u8) (byteAddress>>8));
	
	/*Send Start Condition*/
	I2C_SendStartCondition();
	
	/*Send Slave address with write operation*/
	I2C_SendSlaveAddWithWrite(Local_u8_Address);
	
	/*Send byte address*/
	I2C_SendMasterDataByte(byteAddress);
	
	/*Send Repeated Start*/
	I2C_SendRepStartCondition();
	
	/*Send Slave address with read operation*/
	I2C_SendSlaveAddWithRead((u8) Local_u8_Address);
	
	/*Read byte data*/
	I2C_ReadMasterDataByte(returnData);
	
	/*Send stop condition*/
	I2C_SendStopCondition();
	
	_delay_ms(EEPROM_Delay);

}
void EEPROMINT_WriteByte(u16 byteAddress, u8 data)
{
	while(GetBit(EECR,EEWE));
	
	while(GetBit(SPMCR,SPMEN));
	
	/*Adjusting Address*/
	if(byteAddress <= 255)
	{
		EEARL = byteAddress;
	}
	else
	{
		EEARL = (u8) byteAddress;
		
		EEARH = (byteAddress>>8) & (0b00000011);
	}
	
	/*Preparing to write*/
	EEDR = data;
	SetBit(EECR,EEMWE);
	
	/*Write into EEPROM*/
	SetBit(EECR,EEWE);
	
	while(GetBit(EECR,EEWE));
}

u8  EEPROMINT_ReadByte(u16 byteAddress)
{
	u8 data;
	/*Make sure any writing operation is finished*/
	while(GetBit(EECR,EEWE) == 1);
	
	
	/*Adjusting Address*/
	if(byteAddress <= 255)
	{
		EEARL = byteAddress;
	}
	else
	{
		EEARL = (u8) byteAddress;
		
		EEARH = (byteAddress>>8) & (0b00000011);
	}
	
	SetBit(EECR,EERE);
	
	data = EEDR;
	
	return data;
	
}