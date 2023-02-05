/*
 * SevenSegment.h
 *
 * Created: 9/24/2022 8:49:36 PM
 *  Author: Dell
 */ 


#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

/*****************************************************_INCLUDES_*****************************************************/
#include "SevenSegmentCfg.h"
#include "Dio.h"
#include "StdTypes.h"
#include "PushButton.h"
#define F_CPU 16000000UL
#include <util/delay.h>
/*****************************************************_MACROS_*****************************************************/
#define SegmentRight		0
#define	SegmentLeft			1
#define	Both_Segments		2
/*****************************************************_PROTOTYPES_*****************************************************/
void H_Segment_Init(void);
void H_Segment_En(u8);
void H_Segment_Display1Number(u8);
void H_Segment_CountNumber(u8);
void H_Segment_Display2Number(u8);
void H_Segment_PbCounting(void);





#endif /* SEVENSEGMENT_H_ */