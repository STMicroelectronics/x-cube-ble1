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
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _CUBE_HAL_H_
#define _CUBE_HAL_H_

/* Includes ------------------------------------------------------------------*/
#ifdef USE_STM32F4XX_NUCLEO
  #include "stm32f4xx_hal.h"
  #include "stm32f4xx_nucleo.h"
  #include "stm32f4xx_nucleo_bluenrg.h"
  #include "stm32f4xx_hal_conf.h"
#endif /* USE_STM32F4XX_NUCLEO */

#ifdef USE_STM32L0XX_NUCLEO
  #include "stm32l0xx_hal.h"
  #include "stm32l0xx_nucleo.h"
  #include "stm32l0xx_nucleo_bluenrg.h"
  #include "stm32l0xx_hal_conf.h"
#endif /* USE_STM32L0XX_NUCLEO */

#ifdef USE_STM32L4XX_NUCLEO
  #include "stm32l4xx_hal.h"
  #include "stm32l4xx_nucleo.h"
  #include "stm32l4xx_nucleo_bluenrg.h"
  #include "stm32l4xx_hal_conf.h"
#endif /* USE_STM32L4XX_NUCLEO */

void SystemClock_Config(void);

#endif /* _CUBE_HAL_H_ */
