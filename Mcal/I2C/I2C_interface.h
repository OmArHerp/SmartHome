/*
 * I2C_interface.h
 *
 * Created: 12/4/2022 8:49:19 PM
 *  Author: Dell
 */ 


#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_



/*****************************************************_INCLUDES_*****************************************************/
#include "StdTypes.h"
#include "BitMath.h"
#include "Reg.h"
/*****************************************************_MACROS_*****************************************************/

/*****************************************************_PROTOTYPES_*****************************************************/
void I2C_InitMaster			  (void);
void I2C_InitSlave			  (u8 slaveAdd);
void I2C_SendStartCondition	  (void);
void I2C_SendRepStartCondition(void);
void I2C_SendStopCondition	  (void);
void I2C_SendSlaveAddWithWrite(u8 slaveAdd);
void I2C_SendSlaveAddWithRead (u8 slaveAdd);
void I2C_SendMasterDataByte	  (u8 data);
void I2C_ReadMasterDataByte	  (u8* returnedData);


#endif /* I2C_INTERFACE_H_ */