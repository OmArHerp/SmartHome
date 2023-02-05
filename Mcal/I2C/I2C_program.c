/*
 * I2C.c
 *
 * Created: 12/4/2022 8:48:31 PM
 *  Author: Dell
 */ 
#include "I2C_interface.h"


void I2C_InitMaster(void)
{
	/*Setup the frequency(speed) 400KHz << Set Prescaler = 1*/
	ClrBit(TWSR,0);
	ClrBit(TWSR,1);
	TWBR = 12 ; 
	
	/*Enable Ack*/
	SetBit(TWCR,6);
	
	/*Enable I2C(TWI)*/
	SetBit(TWCR,2);
}
void I2C_InitSlave(u8 slaveAdd)
{
	
	if(slaveAdd<128)
	{
		/*Set Slave Address*/
		TWAR = slaveAdd<<1;
		
		
		
		/*Enable Ack*/
		SetBit(TWCR,6);
		
		/*Enable I2C(TWI)*/
		SetBit(TWCR,2);
	}
}
void I2C_SendStartCondition(void)
{
	/*Send Start Condition*/	/*NOTE -> This bit must be cleared afterwards to allow the I2C Send Data on the Data Bus*/
	SetBit(TWCR,5);
	
	/*Clear flag to start current Job*/
	SetBit(TWCR,7);
	
	/*Wait for the flag to rose up*/
	while(GetBit(TWCR,7) == 0);
	
	/*Check ACK = SC ACK*/
	while((TWSR & 0xF8) != 0x08);
}

void I2C_SendRepStartCondition(void)
{
	/*Send Start Condition*/
	SetBit(TWCR,5);
	
	/*Clear flag to start current Job*/
	SetBit(TWCR,7);
	
	/*Wait for the flag to rose up*/
	while(GetBit(TWCR,7) == 0);
	
	/*Check ACK = Repeated SC ACK*/
	while((TWSR & 0xF8) != 0x10);
}

void I2C_SendStopCondition(void)
{
	/*Send Stop Condition*/
	SetBit(TWCR,4);
	
	/*Clear flag to start current job*/
	SetBit(TWCR,7);
}
void I2C_SendSlaveAddWithWrite(u8 slaveAdd)
{
	/*Send Slave Address*/
	TWDR = slaveAdd<<1;
	
	/*Select write operation*/
	ClrBit(TWDR,0);
	
	/*Clear SC Bit*/
	ClrBit(TWCR,5);
	
	/*Clear flag to start current job*/
	SetBit(TWCR,7);
	
	/*Wait for the flag to rose up*/
	while(GetBit(TWCR,7) == 0);
	
	/*Check ACK = Master Transmit (Slave address + Write request) ACK*/
	while((TWSR & 0xF8) != 0x18);
}

void I2C_SendSlaveAddWithRead (u8 slaveAdd)
{
	/*Send Slave Address*/
	TWDR = slaveAdd<<1;
	
	/*Select read operation*/
	SetBit(TWDR,0);
	
	/*Clear SC Bit*/
	ClrBit(TWCR,5);
	
	/*Clear flag to start current job*/
	SetBit(TWCR,7);
	
	/*Wait for the flag to rose up*/
	while(GetBit(TWCR,7) == 0);
	
	/*Check ACK = Master Transmit (Slave address + Read request) ACK*/
	while((TWSR & 0xF8) != 0x40);
}

void I2C_SendMasterDataByte	  (u8 data)
{
	/*Write Data into data register*/
	TWDR = data;
	
	/*Clear flag to start current job*/
	SetBit(TWCR,7);
	
	/*Wait for the flag to rose up*/
	while(GetBit(TWCR,7));
	
	/*Check ACK = Master Transmit Data ACK */
	while((TWSR & 0xF8) != 0x28);
}

void I2C_ReadMasterDataByte	  (u8* returnedData)
{
	/*Clear flag to start current job*/
	SetBit(TWCR,7);
	
	/*Wait for the flag to rose up*/
	while(GetBit(TWCR,7));
	
	/*Check ACK = Master Received Data With ACK */
	while((TWSR & 0xF8) != 0x50);
	
	*returnedData = TWDR;
}
