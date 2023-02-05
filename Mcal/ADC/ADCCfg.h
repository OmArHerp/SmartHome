/*
 * ADCCfg.h
 *
 * Created: 11/11/2022 10:47:48 PM
 *  Author: Dell
 */ 


#ifndef ADCCFG_H_
#define ADCCFG_H_

/*****************************************************_SELECT_PRESCALER_*****************************************************/

/*options are:
*				1-DIVISION_BY_2
*				2-DIVISION_BY_4
*				3-DIVISION_BY_8
*				4-DIVISION_BY_16
*				5-DIVISION_BY_32
*				6-DIVISION_BY_64
*				7-DIVISION_BY_128
*				*/
#define ADC_PRESCALER		DIVISION_BY_128	
#define ADC_TIMEOUT			50000

/*Options Are:
*				1- 8  BIT
*				2- 10 BIT
*/
#define ADC_RESOLUTION		TEN_BIT



#endif /* ADCCFG_H_ */