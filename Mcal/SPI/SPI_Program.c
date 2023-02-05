/*
 * SPI_Program.c
 *
 * Created: 10/21/2022 8:35:12 PM
 *  Author: Dell
 */ 

#include "SPI_INTERFACE.h"

void M_SPI_InitMaster(void)
{
	//Select Data Order LSB transmitted first
	SetBit(SPI->SPCR,5);//LSB
	
	//Select MASTER MODE
	SetBit(SPI->SPCR,4);
	
	
	//Select Clk Polarity Rising, Select CLK Phase Setup => Sample
	SetBit(SPI->SPCR,3);
	SetBit(SPI->SPCR,2);
	
	//Select CLK Rate = FCPU/16
	SetBit(SPI->SPCR,0);
	ClrBit(SPI->SPCR,1);
	ClrBit(SPI->SPSR,0);
	
	//Setup MOSI & MISO Pins & SS
	M_Dio_PinMode(PB5,OUTPUT);
	M_Dio_PinMode(PB6,INPUT);
	M_Dio_PinMode(PB7,OUTPUT);
	M_Dio_PinMode(PB4,OUTPUT);
	M_Dio_PinWrite(PB4,LOW);
	
	SetBit(SPI->SPCR,6);//EN
}
void M_SPI_InitSlave(void)
{
	SetBit(SPI->SPCR,5);//LSB
	
	//Select Slave Mode
	ClrBit(SPI->SPCR,4);
	
	//Select Clk Polarity Rising, Select CLK Phase Setup => Sample
	SetBit(SPI->SPCR,3);
	SetBit(SPI->SPCR,2);
	
	//Setup MOSI & MISO Pins & SS
	M_Dio_PinMode(PB4,INPUT);
	M_Dio_PinMode(PB5,INPUT);
	M_Dio_PinMode(PB6,OUTPUT);
	M_Dio_PinMode(PB7,INPUT);
	
	
	SetBit(SPI->SPCR,6);//EN
}
u8 SPI_Transieve(u8 TxData)
{
	u8 RxData;
	
	SPI->SPDR = TxData;
	
	/*wait till All Data get transferred*/
	while(GetBit(SPI->SPSR,7) == 0);
	
	RxData = SPI->SPDR;
	return RxData;
}
