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
#include "hci_const.h"
#include "gp_timer.h"
#include "low_power_conf.h"
#include "stm32xx_lpm.h"

extern SPI_Context_t SPI_Context;

volatile uint8_t send_measurement = 0;
uint8_t * HCI_read_packet;

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
}

/**
 * @brief  Writes data to a serial interface.
 * @param  data1   :  1st buffer
 * @param  data2   :  2nd buffer
 * @param  n_bytes1: number of bytes in 1st buffer
 * @param  n_bytes2: number of bytes in 2nd buffer
 * @retval None
 */
void Hal_Write_Serial(const void* data1, const void* data2, int32_t n_bytes1,
                      int32_t n_bytes2)
{
  /* New implementation (with DMA write) */
  BlueNRG_SPI_Write((uint8_t *)data1,(uint8_t *)data2, n_bytes1, n_bytes2);
}

void Hal_Event_Request(uint8_t *buffer, uint8_t buff_size)
{
  HCI_read_packet = buffer;
  
  BlueNRG_SPI_Request_Events(((tHciDataPacket*)buffer)->dataBuff, buff_size);
  
}

/**
 * @brief  EXTI line detection callback.
 * @param  uint16_t GPIO_Pin Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  BlueNRG_SPI_IRQ_Callback();
}

/**
  * @brief HCI Transport Layer Low Level Interrupt Service Routine
  *
  * @param  None
  * @retval None
  */
void hci_tl_lowlevel_isr(void)
{      
  hci_notify_asynch_evt(HCI_read_packet, SPI_Context.SPI_Receive_Context.payload_len);

  /* USER CODE BEGIN hci_tl_lowlevel_isr */

  /* USER CODE END hci_tl_lowlevel_isr */ 
}
