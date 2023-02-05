/*
 * ADC.h
 *
 * Created: 11/11/2022 10:47:29 PM
 *  Author: Dell
 */ 


#ifndef ADC_H_
#define ADC_H_
/*****************************************************_INCLUDES_*****************************************************/
#include "ADCCfg.h"
#include "StdTypes.h"
#include "BitMath.h"
#include "Reg.h"

/*****************************************************_MACROS_*****************************************************/
#define ADMUX_REFS1						7	/*Reference Selection bit 1*/
#define ADMUX_REFS0						6	/*Reference Selection bit 0*/
#define ADMUX_ADLAR						5	/*Left Adjust Result*/


#define ADCSRA_ADEN						7	/*ADC Enable*/
#define ADCSRA_ADSC						6	/*ADC Start Conversion*/
#define ADCSRA_ADATE					5	/*Auto Trigger Enable*/
#define ADCSRA_ADIF						4	/*ADC Interrupt Flag*/
#define ADCSRA_ADIE						3	/*ADC Interrupt Enable*/


#define DIVISION_BY_2					1
#define DIVISION_BY_4					2
#define DIVISION_BY_8					3
#define DIVISION_BY_16					4
#define DIVISION_BY_32					5
#define DIVISION_BY_64					6
#define DIVISION_BY_128					7


/*Channel & gain selection*/
#define ADC_SINGLE_ENDED_CH0			0
#define ADC_SINGLE_ENDED_CH1			1
#define ADC_SINGLE_ENDED_CH2			2
#define ADC_SINGLE_ENDED_CH3			3
#define ADC_SINGLE_ENDED_CH4			4
#define ADC_SINGLE_ENDED_CH5			5
#define ADC_SINGLE_ENDED_CH6			6
#define ADC_SINGLE_ENDED_CH7			7

#define ADC_DIFFERENTIAL_CH8_G10		8
#define ADC_DIFFERENTIAL_CH9_G10		9
#define ADC_DIFFERENTIAL_CH10_G200		10
#define ADC_DIFFERENTIAL_CH11_G200		11
#define ADC_DIFFERENTIAL_CH12_G10		12
#define ADC_DIFFERENTIAL_CH13_G10		13
#define ADC_DIFFERENTIAL_CH14_G200		14
#define ADC_DIFFERENTIAL_CH15_G200		15
#define ADC_DIFFERENTIAL_CH16_G1		16
#define ADC_DIFFERENTIAL_CH17_G1		17
#define ADC_DIFFERENTIAL_CH18_G1		18
#define ADC_DIFFERENTIAL_CH19_G1		19
#define ADC_DIFFERENTIAL_CH20_G1		20
#define ADC_DIFFERENTIAL_CH21_G1		21
#define ADC_DIFFERENTIAL_CH22_G1		22
#define ADC_DIFFERENTIAL_CH23_G1		23
#define ADC_DIFFERENTIAL_CH24_G1		24
#define ADC_DIFFERENTIAL_CH25_G1		25
#define ADC_DIFFERENTIAL_CH26_G1		26
#define ADC_DIFFERENTIAL_CH27_G1		27
#define ADC_DIFFERENTIAL_CH28_G1		28
#define ADC_DIFFERENTIAL_CH29_G1		29

#define ADC_SINGLE_ENDED_1_22V			30
#define ADC_SINGLE_ENDED_0V				31

#define EIGHT_BIT						1
#define TEN_BIT							2


#define IDLE							0
#define BUSY							1
/*****************************************************_PROTOTYPES_*****************************************************/
void M_ADC_INIT(void);
u8   M_ADC_StartConversionSynch(u8 Channel, u16 *ptr_result);
u8	 M_ADC_StartConversionAsynch(u8 Channel, u16 *ptr_result, void (*NotificationFunc)(void));



#endif /* ADC_H_ */