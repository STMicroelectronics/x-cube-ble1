/**
  ******************************************************************************
  * @file    stm32xx_hal_app_rtc.c
  * @author  MCD Application Team
  * @brief   File for the Wakeup clock source setting
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
#include "stm32xx_hal_app_rtc.h"

/* External variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Set the Wakeup clock source
  *
  * @param  hrtc : RTC Handle
  *
  * @param  RTC_Wucksel_Value : The Wakeup clock selection source
  *
  * @retval None
  */
void HAL_APP_RTC_Set_Wucksel(RTC_HandleTypeDef *localhrtc, uint32_t RTC_Wucksel_Value)
{
  /**
  * This is a temporary register to avoid any unwanted transient state when performing read/modify/write
  * operation on the destination register
  */
  uint32_t uwTempRegister;
  
  uwTempRegister = localhrtc->Instance->CR;
  uwTempRegister &= (uint32_t)~RTC_CR_WUCKSEL;
  uwTempRegister |= RTC_Wucksel_Value;
  localhrtc->Instance->CR = uwTempRegister;
  
  return;
}

