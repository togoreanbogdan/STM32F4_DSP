/**
  ******************************************************************************
  * File Name          : gpio.h
  * Description        : This file contains all the functions prototypes for 
  *                      the gpio  
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
	 
#define GPIO_SetPD0() 					GPIOD->BSRR = GPIO_PIN_0
#define GPIO_ReSetPD0() 				GPIOD->BSRR = (uint32_t)GPIO_PIN_0 << 16U
#define GPIO_TogglePD0()				GPIOD->ODR ^= GPIO_PIN_0
	 
#define GPIO_SetLedGreen() 			GPIOD->BSRR = GPIO_PIN_12
#define GPIO_ReSetLedGreen() 		GPIOD->BSRR = (uint32_t)GPIO_PIN_12 << 16U
#define GPIO_ToggleLedGreen() 	GPIOD->ODR ^= GPIO_PIN_12
	 
#define GPIO_SetLedOrange() 		GPIOD->BSRR = GPIO_PIN_13
#define GPIO_ReSetLedOrange() 	GPIOD->BSRR = (uint32_t)GPIO_PIN_13 << 16U
#define GPIO_ToggleLedOrange() 	GPIOD->ODR ^= GPIO_PIN_13
	 
#define GPIO_SetLedRed() 				GPIOD->BSRR = GPIO_PIN_14
#define GPIO_ReSetLedRed() 			GPIOD->BSRR = (uint32_t)GPIO_PIN_14 << 16U
#define GPIO_ToggleLedRed() 		GPIOD->ODR ^= GPIO_PIN_14
	 
#define GPIO_SetLedBlue() 			GPIOD->BSRR = GPIO_PIN_15
#define GPIO_ReSetLedBlue() 		GPIOD->BSRR = (uint32_t)GPIO_PIN_15 << 16U
#define GPIO_ToggleLedBlue() 		GPIOD->ODR ^= GPIO_PIN_15
	 
void MX_GPIO_Init(void);

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
