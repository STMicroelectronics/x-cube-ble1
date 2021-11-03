/**
  ******************************************************************************
  * @file    cube_hal.h
  * @author  SRA Application Team
  * @brief   Header file for cube_hal_l4.c
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

#ifndef _CUBE_HAL_H_
#define _CUBE_HAL_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "stm32l4xx_hal.h"
#include "stm32l4xx_nucleo.h"
#include "stm32l4xx_hal_conf.h"
#include "stm32l4xx_nucleo_bluenrg_dma_lp.h"
#include "stm32_bluenrg_ble_dma_lp.h" 

void SystemClock_Config(void);

#endif /* _CUBE_HAL_H_ */
