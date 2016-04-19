/***************************************************
* Module name: DEM 16216 LCD Driver
*
* Copyright 2016 Company as an unpublished work.
* All Rights Reserved.
*
* The information contained herein is confidential
* property of Company. The user, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Company.
*
* First written on 10.02.2016 by BogTog.
*
* Module Description:
* General driver for DEM16216 LCD display on STM32 ARM uControllers
*
***************************************************/
#ifndef __DEM16216_LCD
#define __DEM16216_LCD

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/
#define IF_4BIT	  //set interface to 4 bit

#define LCD_RS_PIN                      GPIO_PIN_15
#define LCD_RW_PIN                      GPIO_PIN_13
#define LCD_EN_PIN                      GPIO_PIN_11
	
/* Paralel LCD interface */
#define LCD_D4_PIN                      GPIO_PIN_15
#define LCD_D5_PIN                      GPIO_PIN_13
#define LCD_D6_PIN                      GPIO_PIN_11
#define LCD_D7_PIN                      GPIO_PIN_9
	
#define LCD_CTRL_PORT                   GPIOB
#define LCD_PARALEL_PORT                GPIOE
#define LCD_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOE_CLK_ENABLE(); __HAL_RCC_GPIOB_CLK_ENABLE()
#define LCD_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOE_CLK_DISABLE(); __HAL_RCC_GPIOB_CLK_ENABLE()

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/**************************************************/
/* Function Prototype Section
* Add prototypes for all functions called by this
* module, with the exception of runtime routines.
*
***************************************************/
void LCD_vInit(void);
void LCD_vClrDisp(void);
void LCD_vGoToPos(uint8_t line, uint8_t pos);
void LCD_vSendChar(uint8_t data);
void LCD_vSendString(char *string);
void LCD_vRtrnCursHome(void);
#ifdef __cplusplus
}
#endif

#endif /* __DEM16216_LCD */
