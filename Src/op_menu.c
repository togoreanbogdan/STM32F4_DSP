/***************************************************
* Module name: One Page LCD Menu
**
Copyright 2016 Company as an unpublished work.
* All Rights Reserved.
**
The information contained herein is confidential
* property of Company. The user, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Company.
**
First written on 07.04.2016 by BogTog.
**
Module Description:
* Module used to generate a one page menu. Navigation is done
* using one rotary encoder.
**
**************************************************/
/* Include section
* Add all #includes here
**
**************************************************/
#include "dem16216_lcd.h"
#include "op_menu.h"
#include "string.h"
/* Defines section
* Add all #defines here
**
**************************************************/
#define OPM__mToggleSel(x) (x == 1) ? (x = 0) : (x = 1);

uint8_t ItemSelected = 0;
uint8_t u8SelectedMenuItem = 0;

tstMenuInst arScreenDsplData[MENUS_NUMBER]=
{
	{MENU_LINES, {{"Fs", ""}, {"Type", ""}, {"Cut Freq", ""}, {"Gain", ""}, {"Q", ""}, {"CPU", ""}}},
};



static struct st_MenuSM
{
	tenMenuScreen nen_curr_state;
	tenMenuScreen nen_next_state;
	tenMenuScreen nen_prev_state;
	uint8_t u8FaultFlag;
	uint8_t u8MenuLine;
}menu1SM;


/* Function Prototype Section
* Add prototypes for all functions called by this
* module, with the exception of runtime routines.
**
**************************************************/
void MENU__vToggleSM(void);
void MENU__vUpdateLcdData(void);
void MENU__vPrintLn(char *text, char *data, uint8_t line);


/**************************************************
* Function name : void MENU_vInit()
* returns : void
* Created by : BogTog
* Date created : 22.02.2016
* Description : Init function for starting the menu
*	in the default state
* Notes : N/A
**************************************************/
void MENU_vInit()
{
	/* LCD init */
	LCD_INIT_FUNC();
	
	/* LCD Clear Command */
	LCD_CLR_FUNC();
	
	/* Go to the begining of the screen */
	LCD_GO_HOME();
	
	/* Menu State Maschine Init*/
	menu1SM.nen_curr_state = menu1;
	menu1SM.nen_next_state = menu1;
	menu1SM.nen_prev_state = menu1;
	menu1SM.u8FaultFlag = 0;
	menu1SM.u8MenuLine = 0;
	
	/* Display First screen on LCD */
	MENU__vUpdateLcdData();
}

/**************************************************
* Function name : void MENU_vUpdateMenu()
* returns : void
* Created by : BogTog
* Date created : 22.02.2016
* Description : Init function for starting the menu
*	in the default state
* Notes : N/A
**************************************************/
void MENU_vUpdateMenu()
{
	//MENU__vToggleSM();
	MENU__vUpdateLcdData();
}

/**************************************************
* Function name : void MENU_vUpdateLcdData()
*	param1 : 
* returns : void
* Created by : BogTog
* Date created : 22.02.2016
* Description : Write the data corresponding to current
*	menu on the LCD
* Notes : N/A
**************************************************/
void MENU__vUpdateLcdData()
{
	/* LCD Clear Command */
	LCD_CLR_FUNC();
	
	/* Go to the begining of the screen */
	LCD_GO_HOME();
	
	/* Write Current state data to LCD */
	MENU__vPrintLn(arScreenDsplData[menu1SM.nen_curr_state].arMenuDsplLines[menu1SM.u8MenuLine].text, 
								 arScreenDsplData[menu1SM.nen_curr_state].arMenuDsplLines[menu1SM.u8MenuLine].data, 1);
	
	MENU__vPrintLn(arScreenDsplData[menu1SM.nen_curr_state].arMenuDsplLines[menu1SM.u8MenuLine + 1].text, 
								 arScreenDsplData[menu1SM.nen_curr_state].arMenuDsplLines[menu1SM.u8MenuLine + 1].data, 2);
}

/**************************************************
* Function name : void MENU_vToggleSM()
* returns : void
* Created by : BogTog
* Date created : 22.02.2016
* Description : Public function used to got to the next
* 							state of the Menu State Machine.
* Notes : The wellcome screen is skipped
**************************************************/
void MENU__vToggleSM()
{
	if (menu1SM.nen_curr_state != menu1)
	{
		menu1SM.nen_prev_state = menu1SM.nen_curr_state;
		menu1SM.nen_curr_state = menu1SM.nen_next_state;
		menu1SM.nen_next_state = ++ menu1SM.nen_curr_state;
		menu1SM.u8MenuLine = 0;
		
		/* Write current menu data to LCD */
		MENU__vUpdateLcdData();
	} 
	else
	{
		menu1SM.nen_prev_state = menu1;
		menu1SM.nen_curr_state = menu1;
		menu1SM.nen_next_state = ++ menu1SM.nen_curr_state;
		menu1SM.u8MenuLine = 0;
		/* Write current menu data to LCD */
		MENU__vUpdateLcdData();
	}
}

/**************************************************
* Function name : void MENU__vPrintLn(char *text, char *data, uint8_t line)
* param1 : String data for the rightmost field
* param2 : String data for the leftmost field
* param3 : Select the LCD line on which to print the data
* returns : void
* Created by : BogTog
* Date created : 23.02.2016
* Description : Function used to print a menu line on one of the
* 							two lines.
* Notes : N/A
**************************************************/
void MENU__vPrintLn(char *text, char *data, uint8_t line)
{
	uint8_t u8TextLen = 0;
	uint8_t u8DataLen = 0;
	int8_t i8SpaceLen = 0;
	
	char *ptAuxPtr;
	
	ptAuxPtr = text;
	while (*ptAuxPtr != '\0')
	{
		u8TextLen ++;
		ptAuxPtr ++;
	}
	
	ptAuxPtr = data;
	while (*ptAuxPtr != '\0')
	{
		u8DataLen ++;
		ptAuxPtr ++;
	}
	
	i8SpaceLen = 16 - (u8DataLen + u8TextLen);
	if (i8SpaceLen >= 0)
	{
		LCD_vGoToPos(line, 0);
		LCD_vSendString(text);
		LCD_vGoToPos(line, u8TextLen+i8SpaceLen);
		LCD_vSendString(data);
	}
	else
	{
		LCD_vSendString("ERR str too long");
	}
}

/**************************************************
* Function name : void MENU_vScrollUp()
* returns : void
* Created by : BogTog
* Date created : 23.02.2016
* Description : Function for scrolling up the menu
* 							(callback for button or rotary encoder)
* Notes : N/A
**************************************************/
void MENU_vScrollUp()
{
	if (menu1SM.u8MenuLine > 0)
	{
		menu1SM.u8MenuLine --;
		MENU__vUpdateLcdData();
		u8SelectedMenuItem = menu1SM.u8MenuLine;
	}
}

/**************************************************
* Function name : void MENU_vScrollDown()
* returns : void
* Created by : BogTog
* Date created : 23.02.2016
* Description : Function for scrolling down the menu
* 							(callback for button or rotary encoder)
* Notes : N/A
**************************************************/
void MENU_vScrollDown()
{
	if ((menu1SM.u8MenuLine + 2) < arScreenDsplData[menu1SM.nen_curr_state].u8MenuLines)
	{
		menu1SM.u8MenuLine ++;
		MENU__vUpdateLcdData();
		u8SelectedMenuItem = menu1SM.u8MenuLine;
	}
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
  {
		OPM__mToggleSel(ItemSelected);
	}
}
