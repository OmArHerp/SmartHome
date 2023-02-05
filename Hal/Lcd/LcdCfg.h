/*
 * LcdCfg.h
 *
 * Created: 9/21/2022 5:43:18 PM
 *  Author: Dell
 */ 


#ifndef LCDCFG_H_
#define LCDCFG_H_
/*****************************************************_SELECT_LCD_MODE_*****************************************************/
//option 1 --> [_4_BIT_MODE]
//option 2 --> [_8_BIT_MODE]
#define LCD_MODE			_4_BIT_MODE
/*****************************************************_SELECT_LCD_PIN_*****************************************************/
#define LCD_DATA_PORT		PORTA
#define LCD_DATA0_PIN		PA0
#define LCD_DATA1_PIN		PA1	
#define LCD_DATA2_PIN		PA2	
#define LCD_DATA3_PIN		PA3
#define LCD_DATA4_PIN		PA4
#define LCD_DATA5_PIN		PA5
#define LCD_DATA6_PIN		PA6
#define LCD_DATA7_PIN		PA7
#define LCD_RS_PIN			PB1
#define LCD_RW_PIN			PB2
#define LCD_EN_PIN			PD6

#endif /* LCDCFG_H_ */