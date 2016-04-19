/***************************************************
* Module name: DEM 16216 LCD Driver
**
Copyright 2016 Company as an unpublished work.
* All Rights Reserved.
**
The information contained herein is confidential
* property of Company. The user, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Company.
**
First written on 10.02.2016 by BogTog.
**
Module Description:
* General driver for DEM16216 LCD display on STM32 ARM uControllers
**
**************************************************/
/* Include section
* Add all #includes here
**
**************************************************/
#include "dem16216_lcd.h"
/* Defines section
* Add all #defines here
**
**************************************************/
static GPIO_InitTypeDef  GPIO_InitStruct;
/* Function Prototype Section
* Add prototypes for all functions called by this
* module, with the exception of runtime routines.
**
**************************************************/
static void LCD__vSendCmdByte(uint8_t data);
static void LCD__vSendNibble(uint8_t data);
/**************************************************
* Function name : void LCD_vInit()
* returns : void
* Created by : BogTog
* Date created : 15.02.2016
* Description : Init function for executing the
*	initialisation sequence of display
* Notes : N/A
**************************************************/
void LCD_vInit()
{
	/* Enable LCD GPIO port Clock */
	LCD_GPIO_CLK_ENABLE();
	
	/* Set LCD Port pins as output */
	GPIO_InitStruct.Pin   = LCD_D4_PIN | LCD_D5_PIN | LCD_D6_PIN | LCD_D7_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_PARALEL_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin   = LCD_RS_PIN | LCD_RW_PIN | LCD_EN_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_CTRL_PORT, &GPIO_InitStruct);
	
	/* Begining of init sequence */
	HAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_PARALEL_PORT, LCD_D4_PIN | LCD_D5_PIN | LCD_D6_PIN | LCD_D7_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS_PIN | LCD_RW_PIN, GPIO_PIN_RESET);

	HAL_Delay(40);
	LCD__vSendCmdByte(0x3);
	LCD__vSendCmdByte(0x3);
	LCD__vSendCmdByte(0x3);
	LCD__vSendCmdByte(0x2);
	LCD__vSendCmdByte(0x28);
	HAL_Delay(1);
	LCD__vSendCmdByte(0x0C);
	HAL_Delay(1);
	LCD__vSendCmdByte(0x1);
	HAL_Delay(3);
	LCD__vSendCmdByte(0x6);
	HAL_Delay(1);
}

void LCD__vSendCmdByte(uint8_t data)
{
#ifdef IF_4BIT
	/* Set low RS for instruction writing */
	HAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS_PIN | LCD_RW_PIN, GPIO_PIN_RESET);
	
	LCD__vSendNibble(data >> 4);

	LCD__vSendNibble(data);
	
#else
  /* Set low RS and R/W for instruction writing */
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_RS_PIN | LCD_RW_PIN, GPIO_PIN_RESET);
	
	/* Set EN pin to high */
	HAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_PARALEL_PORT, ((data << 2) & 0x3FC), GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_PIN_RESET);
#endif
}

static void LCD__vSendNibble(uint8_t data)
{
	/* Set low R/W for writing */
	HAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RW_PIN, GPIO_PIN_RESET);
	
	/* Set EN pin to high */
	HAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_PIN_SET);
		
	/* Send first nibble */
	LCD_PARALEL_PORT->ODR &= ~(LCD_D4_PIN | LCD_D5_PIN | LCD_D6_PIN | LCD_D7_PIN); /* Clear port using mask */
	
	if (data & 0x1) HAL_GPIO_WritePin(LCD_PARALEL_PORT, LCD_D4_PIN, GPIO_PIN_SET);
	if (data & 0x2) HAL_GPIO_WritePin(LCD_PARALEL_PORT, LCD_D5_PIN, GPIO_PIN_SET);
	if (data & 0x4) HAL_GPIO_WritePin(LCD_PARALEL_PORT, LCD_D6_PIN, GPIO_PIN_SET);
	if (data & 0x8) HAL_GPIO_WritePin(LCD_PARALEL_PORT, LCD_D7_PIN, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_EN_PIN, GPIO_PIN_RESET);
}

void LCD_vSendChar(uint8_t data)
{
	/* Set RS high for data writing */
	HAL_GPIO_WritePin(LCD_CTRL_PORT, LCD_RS_PIN, GPIO_PIN_SET);
	
#ifdef IF_4BIT
	/* Send first nibble */
	LCD__vSendNibble(data >> 4);
	
	/* Send second nibble */
	LCD__vSendNibble(data);
#else
	
#endif
}

void LCD_vClrDisp()
{
	LCD__vSendCmdByte(0x1);
	HAL_Delay(2);
}

void LCD_vGoToPos(uint8_t line, uint8_t pos)
{
	if (pos < 16)
	{
		switch (line)
		{
			case 0x1:
				LCD__vSendCmdByte(0x80 + pos);
				break;
			case 0x2: 
				LCD__vSendCmdByte(0xC0 + pos);
				break;
			default: 
				LCD__vSendCmdByte(0x80 + pos);
				break;
		}
	}
}

void LCD_vRtrnCursHome()
{
	LCD__vSendCmdByte(0x02);
	HAL_Delay(2);
}

void LCD_vSendString(char *string)
{
	while (*string != '\0')
	{
		LCD_vSendChar(*string);
		string ++;
	}
}
