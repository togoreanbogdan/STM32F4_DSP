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
#ifndef __OP_MENU
#define __OP_MENU

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/

/* Defines -------------------------------------------------------------------*/
#define MENU_LINES 6
#define MENUS_NUMBER 1
	
/* LCD Interface to LL Driver */
#define LCD_INIT_FUNC() LCD_vInit()
#define LCD_CLR_FUNC()	LCD_vClrDisp()
#define LCD_GO_HOME() 	LCD_vRtrnCursHome()
/* Exported constants --------------------------------------------------------*/
typedef struct
{
	char text[16];
	char data[16];
}tstScreenLine;

typedef enum
{
	menu1 = 0,
}tenMenuScreen;

typedef struct 
{
	uint8_t u8MenuLines;
	tstScreenLine arMenuDsplLines[MENU_LINES];
}tstMenuInst;


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void MENU_vInit(void);
void MENU_vUpdateMenu(void);
void MENU_vScrollUp(void);
void MENU_vScrollDown(void);
void MENU_vGoBack(void);
void MENU_vEnter(void);
/**************************************************/
/* Function Prototype Section
* Add prototypes for all functions called by this
* module, with the exception of runtime routines.
*
***************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __OP_MENU */
