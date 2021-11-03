/**
  ******************************************************************************
  * @file    hci_tl_interface.h
  * @author  SRA Application Team
  * @brief   Header file for hci_tl_interface.c
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
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HCI_TL_INTERFACE_H_
#define __HCI_TL_INTERFACE_H_

#ifdef __cplusplus
 extern "C" {
#endif 

/** 
 * @addtogroup LOW_LEVEL_INTERFACE LOW_LEVEL_INTERFACE
 * @{
 */
 
/** 
 * @defgroup LL_HCI_TL_INTERFACE HCI_TL_INTERFACE
 * @{
 */
 
/** 
 * @defgroup LL_HCI_TL_INTERFACE_TEMPLATE TEMPLATE
 * @{
 */
   
/* Includes ------------------------------------------------------------------*/
#include "cube_hal.h"
#include "bluenrg_types.h"

/* Exported Functions --------------------------------------------------------*/
void HCI_TL_SPI_Send(const void* data1, const void* data2, int32_t n_bytes1,
                     int32_t n_bytes2);
void Hal_Init_Event_Request(void);
void Hal_Event_Request(uint8_t *buffer, uint8_t buff_size);

/**
 * @brief HCI Transport Layer Low Level Interrupt Service Routine
 *
 * @param  None
 * @retval None
 */
void hci_tl_lowlevel_isr(void);

/**
 * @}
 */
 
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HCI_TL_INTERFACE_H_ */

