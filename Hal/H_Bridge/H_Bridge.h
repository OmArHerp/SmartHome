/*
 * H_Bridge.h
 *
 * Created:  25/12/2022 22:51:57
 *  Author: Amero
 */ 


#ifndef H_BRIDGE_H_
#define H_BRIDGE_H_

//*********************************includes******************************
#include "Dio.h"
#include "H_BridgeCfg.h"
#include "StdTypes.h"

//***********************************MACROS******************************

//*********************************prototypes**************************
void  H_H_Bridge_Init(void);
void  H_H_Bridge_CH1_EN(void);
void  H_H_Bridge_CH1_Change_Direction(void);
void  H_H_Bridge_CH1_Break(void);

void  H_H_Bridge_CH2_EN(void);
void  H_H_Bridge_CH2_Change_Direction(void);
void  H_H_Bridge_CH2_Break(void);









#endif /* H_BRIDGE_H_ */