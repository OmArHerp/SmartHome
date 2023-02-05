/*
 * EXTICfg.h
 *
 * Created: 10/24/2022 6:12:23 PM
 *  Author: Dell
 */ 


#ifndef EXTICFG_H_
#define EXTICFG_H_



/*****************************************************_SELECT_SENSE_CONTROL_*****************************************************/
												/*Options: 1- LOW_LEVEL
												 *		   2- ON_CHANGE
												 *		   3- FALLING_EDGE
												 *		   4- RISING_EDGE
												 *		   */
												
#define INT0_SENSE			FALLING_EDGE

												/*Options: 1- LOW_LEVEL
												 *		   2- ON_CHANGE
												 *		   3- FALLING_EDGE
												 *		   4- RISING_EDGE
												 *		   */
#define INT1_SENSE			ON_CHANGE
											
												/*Options: 1- FALLING_EDGE
												 *		   2- RISING_EDGE
												 *		   */
#define INT2_SENSE			FALLING_EDGE
												
												/*Options: 1- ENABLED
												 *		   2- DISABLED
												 *		   */
#define INT0_INITIAL_STATE	ENABLED
												
												/*Options: 1- ENABLED
												 *		   2- DISABLED
												 *		   */

#define INT1_INITIAL_STATE	DISABLED
												
												/*Options: 1- ENABLED
												 *		   2- DISABLED
												 *		   */

#define INT2_INITIAL_STATE	DISABLED




#endif /* EXTICFG_H_ */