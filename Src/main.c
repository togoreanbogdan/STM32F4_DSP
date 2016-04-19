#include "stm32f4xx_hal.h"
#include <string.h>
#include "adc.h"
#include "dac.h"
#include "gpio.h"
#include "dem16216_lcd.h"
#include "filt.h"
#include "tim.h"
#include "rot_enc.h"
#include "op_menu.h"
#include "math.h"

/* Private defines ---------------------------------------------------------*/
# define FREQ_STEPS 50

/* Private variables ---------------------------------------------------------*/
extern tstFiltParamList Filt1Param;
extern uint8_t ItemSelected;
extern tstMenuInst arScreenDsplData[MENUS_NUMBER];
extern uint8_t u8SelectedMenuItem;
static uint8_t counter = 1;
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

int main(void)
{
  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
	LCD_vInit();
	ENC_vInit();
	CalcFiltInternParam();
  MX_ADC1_Init();
  MX_DAC_Init();
	MX_TIM2_Init();
	MENU_vInit();
	
	MENU_vUpdateMenu();
	
  while (1)
  {
  }
}

/* System Clock Configuration */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	
	/* Clock Speeds are:
	Core : 168Mhz
	APB1 : 42 Mhz
	Timer on APB1 : 84 Mhz
	APB2 : 84 Mhz
	Timer on APB2 : 168 Mhz */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void UpdateMenuData()
{
	sprintf(arScreenDsplData[0].arMenuDsplLines[0].data, "%d", Filt1Param.u32SamplingFreq);
	sprintf(arScreenDsplData[0].arMenuDsplLines[2].data, "%d", Filt1Param.u32CutFreq);
	sprintf(arScreenDsplData[0].arMenuDsplLines[3].data, "%4.2f", Filt1Param.f32Gain);
	sprintf(arScreenDsplData[0].arMenuDsplLines[4].data, "%4.2f", Filt1Param.f32Q);
	sprintf(arScreenDsplData[0].arMenuDsplLines[5].data, "%d", Filt1Param.u8CPU);
	
	switch (Filt1Param.enType)
	{
		case 0 : {
			strcpy(arScreenDsplData[0].arMenuDsplLines[1].data, "LPF");
			break;
		}
		
		case 1 : {
			strcpy(arScreenDsplData[0].arMenuDsplLines[1].data, "HPF");
			break;
		}
		
		case 2 : {
			strcpy(arScreenDsplData[0].arMenuDsplLines[1].data, "BPF");
			break;
		}
		
		case 3 : {
			strcpy(arScreenDsplData[0].arMenuDsplLines[1].data, "APF");
			break;
		}
		
		case 4 : {
			strcpy(arScreenDsplData[0].arMenuDsplLines[1].data, "Notch");
			break;
		}
		
		default :{
			strcpy(arScreenDsplData[0].arMenuDsplLines[1].data, "Err");
		}
	}
}

void ENC_vRotEnc_Handler(ENC_tenDir ENC__enDir)
{
	uint16_t increase;
	
	if (ItemSelected)
	{
		switch(u8SelectedMenuItem)
		{
			case 0 : {
				#if 0
				increase = (uint16_t)exp(log()/FREQ_STEPS * counterFs);
				if (ENC__enDir == left)
				{
					if ((Filt1Param.u32CutFreq + increase) < )
					{
						Filt1Param.u32CutFreq += increase;
						counter ++;
					}
				}
				else
				{
					if ((int32_t)(Filt1Param.u32CutFreq - increase) > 0)
					{
					Filt1Param.u32CutFreq -= increase;
					counter --;
					}
				}
				#endif
				break;
			}
			
			case 1 : {
				if (ENC__enDir == left)
				{
					if (Filt1Param.enType != APF)
						Filt1Param.enType +=1;
					else
						Filt1Param.enType = LPF;
				}
				else
					if (Filt1Param.enType != LPF)
						Filt1Param.enType -=1;
					else
						Filt1Param.enType = APF;
				break;
			}
			
			case 2 : {
				increase = (uint16_t)exp(log(Filt1Param.u32SamplingFreq/2)/FREQ_STEPS * counter);
				if (ENC__enDir == left)
				{
					if ((Filt1Param.u32CutFreq + increase) < Filt1Param.u32SamplingFreq/2)
					{
						Filt1Param.u32CutFreq += increase;
						counter ++;
					}
				}
				else
				{
					if ((int32_t)(Filt1Param.u32CutFreq - increase) > 0)
					{
					Filt1Param.u32CutFreq -= increase;
					counter --;
					}
				}
			}
			
			default : {
			}
		}
		CalcFiltInternParam();
		UpdateMenuData();
		MENU_vUpdateMenu();	
	}
	else
	{
		if (ENC__enDir == left)
			MENU_vScrollUp();
		else
			MENU_vScrollDown();
	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* Toggle PIN for measurement purposes */
	GPIO_SetPD0();
	GPIO_ToggleLedGreen();
  HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 1);
	DAC->DHR12R1 = CalcFilt((float)HAL_ADC_GetValue(&hadc1));
	/* Toggle PIN for measurement purposes */
	GPIO_ReSetPD0();
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
