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

/* Includes ------------------------------------------------------------------*/
#include "stm32_bluenrg_ble.h"
#include "bluenrg_types.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void Hal_Write_Serial(const void* data1, const void* data2, int32_t n_bytes1,
                      int32_t n_bytes2);

#endif /* __HCI_TL_INTERFACE_H_ */
