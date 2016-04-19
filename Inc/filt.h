/***************************************************
* Module name: Filter Implementation Header File
*
* Copyright 2016 Company as an unpublished work.
* All Rights Reserved.
*
* The information contained herein is confidential
* property of Company. The user, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Company.
*
* First written on 09.04.2016 by BogTog.
*
* Module Description:
* Module used to compute a second order filter (biquad)
* with specific parameters
*
***************************************************/
#ifndef __FILT
#define __FILT

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
	
/* Exported types ------------------------------------------------------------*/
typedef enum
{
	LPF = 0,
	BPF,
	HPF,
	NOTCH,
	APF,
}tenFiltType;

typedef struct{
	uint32_t u32SamplingFreq;
	tenFiltType enType;
	uint32_t u32CutFreq;
	float f32Gain;
	float f32Q;
	uint8_t u8CPU;
}tstFiltParamList;

/* Defines -------------------------------------------------------------------*/
#define FILT_ORDER 2
#define PI 3.141592653589793238462643383F
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/**************************************************/
/* Function Prototype Section
* Add prototypes for all functions called by this
* module, with the exception of runtime routines.
*
***************************************************/
uint16_t CalcFilt(float in);
void CalcFiltInternParam(void);
	
#ifdef __cplusplus
}
#endif

#endif /* __FILT */
