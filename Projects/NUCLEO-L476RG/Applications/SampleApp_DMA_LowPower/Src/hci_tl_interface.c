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

#include "bluenrg_conf.h"
#include "hci_const.h"
#include "cube_hal.h"

extern SPI_Context_t SPI_Context;

uint8_t *HCI_read_packet;

/**
 * @brief  Writes data to a serial interface.
 * @param  data1   :  1st buffer
 * @param  data2   :  2nd buffer
 * @param  n_bytes1: number of bytes in 1st buffer
 * @param  n_bytes2: number of bytes in 2nd buffer
 * @retval None
 */
void HCI_TL_SPI_Send(const void* data1, const void* data2, int32_t n_bytes1,
                      int32_t n_bytes2)
{
  /* New implementation (with DMA write) */
  BlueNRG_SPI_Write((uint8_t *)data1,(uint8_t *)data2, n_bytes1, n_bytes2);
}

/**
 * @brief  Init request for an event
 * @param  None
 * @retval None
 */
void Hal_Init_Event_Request(void)
{  
  Event_Request();
  
  return;
}

/**
 * @brief  Request for an event
 * @param  uint8_t*: the event packet
 * @param  uint8_t : the event packet size
 * @retval None
 */
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
  if(GPIO_Pin == BNRG_SPI_EXTI_PIN) {    
    BlueNRG_SPI_IRQ_Callback(); 
  }
  else {
    if(GPIO_Pin == KEY_BUTTON_PIN) {     
      LPM_Mode_Request(eLPM_MAIN_LOOP_PROCESSES, eLPM_Mode_RUN);
    }
  }  
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
