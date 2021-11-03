/**
  ******************************************************************************
  * @file    low_power_conf_l4.c
  * @author  AAS / CL
  * @brief   Configuration file for low power optimization
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "low_power_conf.h"

/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  Configure the system for power optimization
  *
  * @note	This API configures the system to be ready for low power mode
  * 		- Unused GPIO in Analog mode
  * 		- Fast Wakeup
  * 		- Verefint disabled in low power mode
  * 		- FLASH in low power mode
  *
  * @param  None
  * @retval None
  */
void SystemPower_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /**
  * Disable FLASH in SLEEP Mode
  */
  __HAL_FLASH_SLEEP_POWERDOWN_ENABLE();

  //SO: TO BE VERIFIED FOR L4
  /* Enable Power Clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /**
  * Enable Ultra low power and Fast wakeup as vrefint is not used in that project
  */
  //SO: TO BE VERIFIED FOR L4 (these APIs are not available for L4)
  //HAL_PWREx_EnableUltraLowPower();
  //HAL_PWREx_EnableFastWakeUp();

  /*
  * Select HSI as system clock source after Wake Up from Stop mode
  */
    //__HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_StopWakeUpClock_MSI); //SO: TO BE VERIFIED FOR L4 (why not this?)
  __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_StopWakeUpClock_HSI);
  
  /*
  * Disable all GPIOs clock in SLEEP mode
  */
  __GPIOA_CLK_SLEEP_DISABLE();
  __GPIOB_CLK_SLEEP_DISABLE();
  __GPIOC_CLK_SLEEP_DISABLE();
  __GPIOD_CLK_SLEEP_DISABLE();
  __GPIOE_CLK_SLEEP_DISABLE(); //SO: TO BE VERIFIED FOR L4
  __GPIOF_CLK_SLEEP_DISABLE(); //SO: TO BE VERIFIED FOR L4
  __GPIOG_CLK_SLEEP_DISABLE(); //SO: TO BE VERIFIED FOR L4
  __GPIOH_CLK_SLEEP_DISABLE();
  
  /*
  * Enable GPIOs clock
  */
  __GPIOA_CLK_ENABLE();
  __GPIOB_CLK_ENABLE();
  __GPIOC_CLK_ENABLE();
  __GPIOD_CLK_ENABLE();
  __GPIOE_CLK_ENABLE(); //SO: TO BE VERIFIED FOR L4
  __GPIOF_CLK_ENABLE(); //SO: TO BE VERIFIED FOR L4
  __GPIOG_CLK_ENABLE(); //SO: TO BE VERIFIED FOR L4
  __GPIOH_CLK_ENABLE();

  /*
  * Configure all GPIO port pins in Analog mode with no pull
  */
  GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStructure.Speed = GPIO_SPEED_HIGH; //SO: TO BE VERIFIED FOR L4
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Pin = GPIO_PIN_All;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
  HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
  HAL_GPIO_Init(GPIOE, &GPIO_InitStructure); //SO: TO BE VERIFIED FOR L4
  HAL_GPIO_Init(GPIOF, &GPIO_InitStructure); //SO: TO BE VERIFIED FOR L4
  HAL_GPIO_Init(GPIOG, &GPIO_InitStructure); //SO: TO BE VERIFIED FOR L4
  HAL_GPIO_Init(GPIOH, &GPIO_InitStructure);
  
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure); 
  
  /*
  * Disable GPIOs clock
  */
  __GPIOA_CLK_DISABLE();
  __GPIOB_CLK_DISABLE();
  __GPIOC_CLK_DISABLE();
  __GPIOD_CLK_DISABLE();
  __GPIOE_CLK_DISABLE(); //SO: TO BE VERIFIED FOR L4
  __GPIOF_CLK_DISABLE(); //SO: TO BE VERIFIED FOR L4
  __GPIOG_CLK_DISABLE(); //SO: TO BE VERIFIED FOR L4
  __GPIOH_CLK_DISABLE();
  
  return;
}

/**
 * @brief  Call procedure for configuring the system clock after wake-up
 *         from STOP
 * @param  None
 * @retval None
 */
void LPM_ExitStopMode(void)
{
#if (HCLK_80MHZ == 1)
  __HAL_RCC_PLL_ENABLE();                                     /**< Enable PLL */
  while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) == RESET);        /**< Wait till PLL is ready */
  __HAL_APP_RCC_SET_SYSCLK_SRC(RCC_CFGR_SW_PLL);              /**< Select PLL as system clock source */
  while (__HAL_RCC_GET_SYSCLK_SOURCE() != RCC_CFGR_SWS_PLL);  /**< Wait till PLL is used as system clock source */
#endif
  
  return;
}
