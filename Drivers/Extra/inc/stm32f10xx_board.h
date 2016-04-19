/***************************************************
* Module name: STM32F103C8T6 Board BSP
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
* General Board Support Package for minimum development
* board with STM32F103C8T6 MCU
*
***************************************************/
#ifndef __STM32F10XX_BOARD
#define __STM32F10XX_BOARD

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Exported types ------------------------------------------------------------*/


/* Defines -------------------------------------------------------------------*/
#define LED_PIN                         GPIO_PIN_13
#define LED_GPIO_PORT                   GPIOC
#define LED_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()  
#define LED_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOC_CLK_DISABLE()

/* Definition of ADC related resources ------------------------------------- */
/* Definition of ADCx clock resources ---------------------------------------*/
#define ADCx                            ADC1
#define ADCx_CLK_ENABLE()               __HAL_RCC_ADC1_CLK_ENABLE()

#define ADCx_FORCE_RESET()              __HAL_RCC_ADC1_FORCE_RESET()
#define ADCx_RELEASE_RESET()            __HAL_RCC_ADC1_RELEASE_RESET()

/* Definition of ADCx channels */
#define ADCx_CHANNELa                   ADC_CHANNEL_4

/* Definition of ADCx channels pins */
#define ADCx_CHANNELa_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define ADCx_CHANNELa_GPIO_PORT         GPIOA
#define ADCx_CHANNELa_PIN               GPIO_PIN_4

/* Definition of ADCx DMA resources */
#define ADCx_DMA_CLK_ENABLE()           __HAL_RCC_DMA1_CLK_ENABLE()
#define ADCx_DMA                        DMA1_Channel1

#define ADCx_DMA_IRQn                   DMA1_Channel1_IRQn
#define ADCx_DMA_IRQHandler             DMA1_Channel1_IRQHandler

/* Definition of ADCx NVIC resources */
#define ADCx_IRQn                       ADC1_2_IRQn
#define ADCx_IRQHandler                 ADC1_2_IRQHandler

#define TIMx                            TIM3
#define TIMx_CLK_ENABLE()               __HAL_RCC_TIM3_CLK_ENABLE()

#define TIMx_FORCE_RESET()              __HAL_RCC_TIM3_FORCE_RESET()
#define TIMx_RELEASE_RESET()            __HAL_RCC_TIM3_RELEASE_RESET()

#define TIMER_FREQUENCY                ((uint32_t) 1000)    /* Timer frequency (unit: Hz). With a timer 16 bits and time base freq min 1Hz, range is min=1Hz, max=32kHz. */
#define TIMER_FREQUENCY_RANGE_MIN      ((uint32_t)    1)    /* Timer minimum frequency (unit: Hz). With a timer 16 bits, maximum frequency will be 32000 times this value. */
#define TIMER_PRESCALER_MAX_VALUE      (0xFFFF-1)           /* Timer prescaler maximum value (0xFFFF for a timer 16 bits) */

/* Definition of TIMx clock resources ----------------------------------------*/
#define ADC_EXTERNALTRIGCONV_Tx_TRGO    ADC_EXTERNALTRIGCONV_T3_TRGO

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/**************************************************/
/* Function Prototype Section
* Add prototypes for all functions called by this
* module, with the exception of runtime routines.
*
***************************************************/
void BSP_LED_Init(void);
void BSP_LED_On(void);
void BSP_LED_Off(void);
void BSP_LED_Toggle(void);
void BSP_SystemClock_Config(void);
void BSP_ADC_Config(void);
void BSP_TIM_Config(void);
void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
