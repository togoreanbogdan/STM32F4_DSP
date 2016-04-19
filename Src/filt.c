/***************************************************
* Module name: Filter Implementation Source File
**
Copyright 2016 Company as an unpublished work.
* All Rights Reserved.
**
The information contained herein is confidential
* property of Company. The user, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Company.
**
First written on 09.04.2016 by BogTog.
**
Module Description:
* Module used to compute a second order filter (biquad)
* with specific parameters
**
**************************************************/
/* Include section
* Add all #includes here
**
**************************************************/
#include "filt.h"
#include "math.h"
#include "gpio.h"

/* Defines section
* Add all #defines here
**
**************************************************/

/* Variables section
* Add all variable definitions here
**
**************************************************/
struct InternFiltParam
{
	float a0;
	float a1;
	float a2;
	float b0;
	float b1;
	float b2;
}f1Param;

tstFiltParamList Filt1Param = {48000, LPF, 1, 0.0f, 1.0f, 0};
/* Function Prototype Section
* Add prototypes for all functions called by this
* module, with the exception of runtime routines.
**
**************************************************/

/**************************************************
* Function name : uint16_t CalcFilt(float in)
* input: Sample from ADC
* returns : Output sample for DAC
* Created by : BogTog
* Date created : 09.04.2016
* Description : Function used for computation
* the filter output
* Notes : N/A
**************************************************/
uint16_t CalcFilt(float in)
{
	static float y[3] = {0.0f, 0.0f, 0.0f};
	static float x[3] = {0.0f, 0.0f, 0.0f};
	
	/* Shift vector values */
	x[0] = x[1];
	x[1] = x[2];
	x[2] = in;
	y[0] = y[1];
	y[1] = y[2];
	/* Compute applying recursive formula */
	y[2] = (f1Param.b0)*x[2] + 
									(f1Param.b1)*x[1] + 
									(f1Param.b2)*x[0] - 
									(f1Param.a1)*y[1] - 
									(f1Param.a2)*y[0];
	/* Return result */
	
	return (uint16_t)y[2];
}

/**************************************************
* Function name : void CalcFiltIntParam()
* returns : void
* Created by : BogTog
* Date created : 09.04.2016
* Description : Function used for computation
* of the internal parameters of the digital filter
* Notes : N/A
**************************************************/
void CalcFiltInternParam()
{
	float w0;
	float A;
	float alpha;
	
	A = sqrt( pow(10,(Filt1Param.f32Gain/20)));
	w0 = 2*PI*Filt1Param.u32CutFreq/Filt1Param.u32SamplingFreq;
	alpha = sin(w0)/(2*Filt1Param.f32Q);
	
	switch(Filt1Param.enType)
	{
		case LPF : {
			f1Param.a0 =   1 + alpha;
			f1Param.b0 =  ((1 - cos(w0))/2)/f1Param.a0;
      f1Param.b1 =   (1 - cos(w0))/f1Param.a0;
      f1Param.b2 =  ((1 - cos(w0))/2)/f1Param.a0;
      
      f1Param.a1 =  (-2*cos(w0))/f1Param.a0;
      f1Param.a2 =   (1 - alpha)/f1Param.a0;
			break;
		}
		
		case HPF : {
			f1Param.b0 =  (1 + cos(w0))/2;
      f1Param.b1 =   -(1 + cos(w0));
      f1Param.b2 =  (1 + cos(w0))/2;
      f1Param.a0 =   1 + alpha;
      f1Param.a1 =  -2*cos(w0);
      f1Param.a2 =   1 - alpha;
			break;
		}

		case BPF : {
			f1Param.b0 =  alpha;
      f1Param.b1 =   0.0f;
      f1Param.b2 =  -alpha;
      f1Param.a0 =   1 + alpha;
      f1Param.a1 =  -2*cos(w0);
      f1Param.a2 =   1 - alpha;
			break;
		}

		case APF : {
			f1Param.b0 =   1.0f - alpha;
      f1Param.b1 =  -2*cos(w0);
      f1Param.b2 =   1 + alpha;
      f1Param.a0 =   1 + alpha;
      f1Param.a1 =  -2*cos(w0);
      f1Param.a2 =   1 - alpha;
		}
		
		case NOTCH : {
			f1Param.b0 =   1.0f;
      f1Param.b1 =  -2*cos(w0);
      f1Param.b2 =  -1.0f;
      f1Param.a0 =   1 + alpha;
      f1Param.a1 =  -2*cos(w0);
      f1Param.a2 =   1 - alpha;
			break;
		}
	}
}
