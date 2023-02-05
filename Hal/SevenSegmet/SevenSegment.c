/*
 * SevenSegment.c
 *
 * Created: 9/24/2022 8:49:05 PM
 *  Author: Dell
 */ 
#include "SevenSegment.h"


void H_Segment_Init(void)
{
	M_Dio_PinMode(ENABLE_FIRST_SEGMENT,OUTPUT);
	M_Dio_PinMode(ENABLE_SECOND_SEGMENT,OUTPUT);
	M_Dio_PinMode(Binary_A,OUTPUT);
	M_Dio_PinMode(Binary_B,OUTPUT);
	M_Dio_PinMode(Binary_C,OUTPUT);
	M_Dio_PinMode(Binary_D,OUTPUT);
}

void H_Segment_En(u8 Local_u8_Segment_Selection)
{
	switch(Local_u8_Segment_Selection)
	{
		case SegmentRight:
		M_Dio_PinWrite(ENABLE_FIRST_SEGMENT,HIGH);
		M_Dio_PinWrite(ENABLE_SECOND_SEGMENT,LOW);
		break;
		
		case SegmentLeft:
		M_Dio_PinWrite(ENABLE_FIRST_SEGMENT,LOW);
		M_Dio_PinWrite(ENABLE_SECOND_SEGMENT,HIGH);
		break;
		
		case Both_Segments:
		M_Dio_PinWrite(ENABLE_FIRST_SEGMENT,HIGH);
		M_Dio_PinWrite(ENABLE_SECOND_SEGMENT,HIGH);
		break;
	}
}

void H_Segment_Display1Number(u8 Local_u8_Number)
{
	switch(Local_u8_Number)
	{
		case 0:
			M_Dio_PinWrite(Binary_A,LOW);
			M_Dio_PinWrite(Binary_B,LOW);
			M_Dio_PinWrite(Binary_C,LOW);
			M_Dio_PinWrite(Binary_D,LOW);
			break;
		case 1:
			M_Dio_PinWrite(Binary_A,HIGH);
			M_Dio_PinWrite(Binary_B,LOW);
			M_Dio_PinWrite(Binary_C,LOW);
			M_Dio_PinWrite(Binary_D,LOW);
			break;
		case 2:
			M_Dio_PinWrite(Binary_A,LOW);
			M_Dio_PinWrite(Binary_B,HIGH);
			M_Dio_PinWrite(Binary_C,LOW);
			M_Dio_PinWrite(Binary_D,LOW);
			break;
		case 3:
			M_Dio_PinWrite(Binary_A,HIGH);
			M_Dio_PinWrite(Binary_B,HIGH);
			M_Dio_PinWrite(Binary_C,LOW);
			M_Dio_PinWrite(Binary_D,LOW);
			break;
		case 4:
			M_Dio_PinWrite(Binary_A,LOW);
			M_Dio_PinWrite(Binary_B,LOW);
			M_Dio_PinWrite(Binary_C,HIGH);
			M_Dio_PinWrite(Binary_D,LOW);
			break;
		case 5:
			M_Dio_PinWrite(Binary_A,HIGH);
			M_Dio_PinWrite(Binary_B,LOW);
			M_Dio_PinWrite(Binary_C,HIGH);
			M_Dio_PinWrite(Binary_D,LOW);
			break;
		case 6:
			M_Dio_PinWrite(Binary_A,LOW);
			M_Dio_PinWrite(Binary_B,HIGH);
			M_Dio_PinWrite(Binary_C,HIGH);
			M_Dio_PinWrite(Binary_D,LOW);
			break;
		case 7:
			M_Dio_PinWrite(Binary_A,HIGH);
			M_Dio_PinWrite(Binary_B,HIGH);
			M_Dio_PinWrite(Binary_C,HIGH);
			M_Dio_PinWrite(Binary_D,LOW);
			break;
		case 8:
			M_Dio_PinWrite(Binary_A,LOW);
			M_Dio_PinWrite(Binary_B,LOW);
			M_Dio_PinWrite(Binary_C,LOW);
			M_Dio_PinWrite(Binary_D,HIGH);
			break;
		case 9:
			M_Dio_PinWrite(Binary_A,HIGH);
			M_Dio_PinWrite(Binary_B,LOW);
			M_Dio_PinWrite(Binary_C,LOW);
			M_Dio_PinWrite(Binary_D,HIGH);
			break;
		default:
		break;		
	}
}

void H_Segment_CountNumber(u8 Local_u8_Number)
{
	H_Segment_En(Both_Segments);
	H_Segment_Display1Number(0);
	_delay_ms(1000);
	u8 Local_u8_LeftNumber  = Local_u8_Number/10;
	u8 Local_u8_RightNumber = Local_u8_Number%10;
	u8 Local_u8_LeftCounter =0;
	u32 Local_u8_Counter=0;
	for(Local_u8_LeftCounter; Local_u8_LeftCounter<=Local_u8_LeftNumber ; Local_u8_LeftCounter++)
	{
		u8 Local_u8_RightCounter =0;
		for(Local_u8_RightCounter; Local_u8_RightCounter<=Local_u8_RightNumber ; Local_u8_RightCounter++)
		{
			while(Local_u8_Counter != DELAY_FREEZE)
			{
				Local_u8_Counter++;
				H_Segment_En(SegmentLeft);
				H_Segment_Display1Number(Local_u8_LeftCounter);
				_delay_ms(DELAY_HOLD1);
				H_Segment_En(SegmentRight);
				H_Segment_Display1Number(Local_u8_RightCounter);
				_delay_ms(DELAY_HOLD1);
			}
			Local_u8_Counter = 0;
			_delay_ms(DELAY_STEP);
		}
	}
	H_Segment_En(Both_Segments);
}

void H_Segment_Display2Number(u8 Local_u8_Number)
{
	u8 Local_u8_LeftNumber  = Local_u8_Number/10;
	u8 Local_u8_RightNumber = Local_u8_Number%10;
	while(1)
	{
		H_Segment_En(SegmentLeft);
		H_Segment_Display1Number(Local_u8_LeftNumber);
		_delay_ms(DELAY_HOLD2);
		H_Segment_En(SegmentRight);
		H_Segment_Display1Number(Local_u8_RightNumber);
		_delay_ms(DELAY_HOLD2);
	}
	
}
void H_Segment_PbCounting(void)
{ 
	H_PushButton_Init(PUSH_BUTTON0);
	H_PushButton_Init(PUSH_BUTTON1);
	H_PushButton_Init(PUSH_BUTTON2);
	
	u8  Local_u8_LeftNumber = 0;
	s8  Local_s8_RightNumber = 0;
	while(Local_u8_LeftNumber != 10 || Local_s8_RightNumber != 10)
	{
			H_Segment_En(SegmentLeft);
			H_Segment_Display1Number(Local_u8_LeftNumber);
			_delay_ms(DELAY_HOLD2);
			H_Segment_En(SegmentRight);
			H_Segment_Display1Number(Local_s8_RightNumber);
			_delay_ms(DELAY_HOLD2);
			
			if(H_PushButtonRead(PUSH_BUTTON2) == PRESSED)
			{
				Local_s8_RightNumber++;
				if(Local_s8_RightNumber>9)
				{
					Local_s8_RightNumber = 0;
					Local_u8_LeftNumber++;
				}
			}
			else if(H_PushButtonRead(PUSH_BUTTON1) == PRESSED)
			{
				Local_s8_RightNumber--;
				if( Local_s8_RightNumber == 0 && Local_u8_LeftNumber == 0)
				{
					Local_u8_LeftNumber = 9;
					Local_s8_RightNumber = 9;
				}
				if(Local_s8_RightNumber<0)
				{
					Local_u8_LeftNumber--;
					Local_s8_RightNumber = 9;
				}
			}
			else if(H_PushButtonRead(PUSH_BUTTON0) == PRESSED)
			{
				Local_u8_LeftNumber  = 0;
				Local_s8_RightNumber = 0;
			}
	}
	
}
