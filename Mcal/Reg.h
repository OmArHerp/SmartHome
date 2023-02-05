/*
 * Reg.h
 *
 * Created: 9/6/2022 9:53:24 PM
 *  Author: Dell
 */ 


#ifndef REG_H_
#define REG_H_
#include "StdTypes.h"
/*************************************************_DIO_REGISTERS_**************************************************/
#define PINA *(volatile u8*)0x39
#define DDRA *(volatile u8*)0x3A
#define PORTA *(volatile u8*)0x3B
#define PINB *(volatile u8*)0x36
#define DDRB *(volatile u8*)0x37
#define PORTB *(volatile u8*)0x38
#define PINC *(volatile u8*)0x33
#define DDRC *(volatile u8*)0x34
#define PORTC *(volatile u8*)0x35
#define PIND *(volatile u8*)0x30
#define DDRD *(volatile u8*)0x31
#define PORTD *(volatile u8*)0x32

/*************************************************_SPI_REGISTERS_**************************************************/
/*
#define SPCR *(volatile u8*)0x2D
#define SPSR *(volatile u8*)0x2E
#define SPDR *(volatile u8*)0x2F*/

typedef struct
{
	u8 SPCR;
	u8 SPSR;
	u8 SPDR;
}SPI_REGS;

#define SPI		((volatile SPI_REGS*)0x2D)
/*************************************************_EXTI_REGISTERS_**************************************************/
#define GICR *(volatile u8*)0x5B /*General Interrupt Control Register */
#define MCUCR *(volatile u8*)0x55 /* MCU Control Register*/
#define MCUCSR *(volatile u8*)0x54 /*MCU Control & status Register*/

/*************************************************_GIE_REGISTERS_**************************************************/
#define SREG *(volatile u8*)0x5F

/*************************************************_ADC_REGISTERS_**************************************************/
#define ADMUX *(volatile u8*)0x27  /*ADC Multiplexer selection register*/
#define ADCSRA *(volatile u8*)0x26 /*ADC Control and status register A*/
#define ADCH *(volatile u8*)0x25   /*Data High Register*/
#define ADCL *(volatile u8*)0x24   /*Data Low Register*/
#define ADC	 *(volatile u16*)0x24  /*Data Registers 16 bits*/

/*************************************************_TIMER_REGISTERS_***********************************************/
#define TCCR0	*(volatile u8*)0x53  /*Timer/Counter 0 control register*/
#define TCNT0	*(volatile u8*)0x52  /*Timer/Counter 0 Register*/
#define TIMSK	*(volatile u8*)0x59  /*Timer Mask Register*/
#define TIFR	*(volatile u8*)0x58 /*Timer Interrupt Flag Register*/
#define TCCR1A  *(volatile u8*)0x4F  /*Timer1 Control RegisterA*/
#define TCCR1B  *(volatile u8*)0x4E  /*Timer1 Control RegisterB*/
#define OCR1A	*(volatile u16*)0x4A /*Channel A Output compare match Register*/
#define ICR1	*(volatile u16*)0x46 /*Input Capture register*/
#define OCR0	*(volatile u8*)0x5C
#define TCNT1	*(volatile u16*)0x4C  /*Timer1 Register*/
/*************************************************_UART_REGISTERS_***********************************************/
#define UDR		*(volatile u8*)0x2C
#define UCSRA	*(volatile u8*)0x2B
#define UCSRB	*(volatile u8*)0x2A
#define UCSRC	*(volatile u8*)0x40
#define UBRRL	*(volatile u8*)0x29
#define UBRRH	*(volatile u8*)0x40
/*************************************************_I2C_REGISTERS_***********************************************/
#define TWBR	*(volatile u8*)0x20 //TWI Bit Rate	Register
#define TWCR	*(volatile u8*)0x56 //TWI Control	Register
#define TWSR	*(volatile u8*)0x21 //TWI Status	Register
#define TWDR	*(volatile u8*)0x23 //TWI Data		Register
#define TWAR	*(volatile u8*)0x22 //TWI(Slave)Add.Register
/*************************************************_EEPROM_REGISTERS_***********************************************/
#define EEARH	*(volatile u8*)0x3F //ADDRESS Register
#define EEARL	*(volatile u8*)0x3E
#define EEDR	*(volatile u8*)0x3D //Data Register
#define EECR	*(volatile u8*)0x3C //Ctrl Register
#define SPMCR	*(volatile u8*)0x57

#endif /* REG_H_ */