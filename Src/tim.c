#include "tim.h"
#include "filt.h"

#define u32TimPeriod(x) ((uint32_t)((SystemCoreClock /2) /x) - 1)


TIM_HandleTypeDef TimHandle;
extern tstFiltParamList Filt1Param;

/* TIM2 init function */
void MX_TIM2_Init(void)
{
  /* Set TIMx instance */
  TimHandle.Instance = TIM2;
	
  TimHandle.Init.Period = u32TimPeriod(Filt1Param.u32SamplingFreq);
  TimHandle.Init.Prescaler = 0;
  TimHandle.Init.ClockDivision = 0;
  TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
  HAL_TIM_Base_Init(&TimHandle);
  
  /*##-2- Start the TIM Base generation in interrupt mode ####################*/
  /* Start Channel1 */
  HAL_TIM_Base_Start_IT(&TimHandle);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{

  if(htim_base->Instance==TIM2)
  {
    /* Peripheral clock enable */
    __TIM2_CLK_ENABLE();

    /* Peripheral interrupt init*/
    HAL_NVIC_SetPriority(TIM2_IRQn, 10, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
		
		/* Start TIM2 in Interrupt mode */
		HAL_TIM_Base_Start_IT(&TimHandle);
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{

  if(htim_base->Instance==TIM2)
  {
    /* Peripheral clock disable */
    __TIM2_CLK_DISABLE();

    /* Peripheral interrupt Deinit*/
    HAL_NVIC_DisableIRQ(TIM2_IRQn);
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
