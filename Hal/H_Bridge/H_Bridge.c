/*
 * H_Bridge.c
 *
 * Created:  25/12/2022 22:51:57
 *  Author: Amero
 */ 
#include "StdTypes.h"
#include "H_Bridge.h"


void  H_H_Bridge_Init()
{
	M_Dio_PinMode(EN_H_1,OUTPUT);
	M_Dio_PinMode(EN_H_2,OUTPUT);
	M_Dio_PinMode(H_A1,OUTPUT);
	M_Dio_PinMode(H_A2,OUTPUT);
	M_Dio_PinMode(H_A3,OUTPUT);
	M_Dio_PinMode(H_A4,OUTPUT);

}


void  H_H_Bridge_CH1_EN()
{
	M_Dio_PinWrite(EN_H_1,HIGH);
	M_Dio_PinWrite(H_A1,HIGH);
	M_Dio_PinWrite(H_A2,LOW);

}

void  H_H_Bridge_CH1_Change_Direction(void)
{
	M_Dio_PinWrite(EN_H_1,HIGH);
	M_Dio_PinWrite(H_A1,LOW);
	M_Dio_PinWrite(H_A2,HIGH);
}

void  H_H_Bridge_CH1_Break(void)
{
	M_Dio_PinWrite(EN_H_1,LOW);
	M_Dio_PinWrite(H_A1,LOW);
	M_Dio_PinWrite(H_A2,LOW);
}

void  H_H_Bridge_CH2_EN(void)
{
	M_Dio_PinWrite(EN_H_2,HIGH);
	M_Dio_PinWrite(H_A3,HIGH);
	M_Dio_PinWrite(H_A4,LOW);
}
void  H_H_Bridge_CH2_Change_Direction(void)
{
	M_Dio_PinWrite(EN_H_2,HIGH);
	M_Dio_PinWrite(H_A3,LOW);
	M_Dio_PinWrite(H_A4,HIGH);
}
void  H_H_Bridge_CH2_Break(void)
{
	M_Dio_PinWrite(EN_H_2,LOW);
	M_Dio_PinWrite(H_A3,LOW);
	M_Dio_PinWrite(H_A4,LOW);
}