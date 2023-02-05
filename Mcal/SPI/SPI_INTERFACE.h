/*
 * SPI_INTERFACE.h
 *
 * Created: 10/21/2022 8:35:42 PM
 *  Author: Dell
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

/*****************************************************_INCLUDES_*****************************************************/
#include "StdTypes.h"
#include "Reg.h"
#include "BitMath.h"
#include "Dio.h"
/*****************************************************_MACROS_*****************************************************/

/*****************************************************_PROTOTYPES_*****************************************************/
void M_SPI_InitMaster(void);
void M_SPI_InitSlave(void);
u8 SPI_Transieve(u8 TxData);



#endif /* SPI_INTERFACE_H_ */