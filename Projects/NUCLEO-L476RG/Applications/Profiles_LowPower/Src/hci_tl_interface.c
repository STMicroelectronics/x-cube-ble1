/**
  ******************************************************************************
  * @file    hci_tl_interface.c
  * @author  SRA Application Team
  * @brief   This file provides the implementation for all functions prototypes 
  *          for the STM32 BlueNRG HCI Transport Layer interface
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
#include "hci_tl_interface.h"

#include "debug.h"
#include "bluenrg_def.h"
#include "hci_tl.h"
#include "stm32_bluenrg_ble.h"
#include "gp_timer.h"
#include "stm32_bluenrg_ble.h"
#include "low_power_conf.h"
#include "stm32xx_lpm.h"

extern SPI_HandleTypeDef SpiHandle;

volatile uint8_t send_measurement = 0;

/**
  * @brief  RTC Wake Up callback
  * @param  RTC handle pointer
  * @retval None
  */
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
    uint32_t uwPRIMASK_Bit = __get_PRIMASK();	/**< backup PRIMASK bit */;
  
    /* Clear Wake Up Flag */
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
    __disable_irq();			/**< Disable all interrupts by setting PRIMASK bit on Cortex*/
    send_measurement++;
    __set_PRIMASK(uwPRIMASK_Bit);	/**< Restore PRIMASK bit*/
    LPM_Mode_Request(eLPM_MAIN_LOOP_PROCESSES, eLPM_Mode_RUN);
}

/**
 * @brief  EXTI line detection callback.
 * @param  uint16_t Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Clear Wake Up Flag */
  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
  
  HCI_Isr();
  
  LPM_Mode_Request(eLPM_MAIN_LOOP_PROCESSES, eLPM_Mode_RUN);  
}
