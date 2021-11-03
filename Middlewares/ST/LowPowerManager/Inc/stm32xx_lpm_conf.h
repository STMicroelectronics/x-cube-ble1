/**
  ******************************************************************************
  * @file    stm32xx_lpm_conf.h
  * @author  MCD Application Team
  * @brief   Configuration file for low power manager
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2014 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#ifndef __STM32xx_LPM_CONF_H
#define __STM32xx_LPM_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

 /* Includes ------------------------------------------------------------------*/
#ifdef USE_STM32F4XX_NUCLEO
  #include "stm32f4xx_hal.h"  
#endif /* USE_STM32F4XX_NUCLEO */

#ifdef USE_STM32L0XX_NUCLEO
#include "stm32l0xx_hal.h"
#endif /* USE_STM32L0XX_NUCLEO */
   
#ifdef USE_STM32L4XX_NUCLEO
#include "stm32l4xx_hal.h"
#endif /* USE_STM32L4XX_NUCLEO */

#ifdef __cplusplus
}
#endif

#endif /* __STM32xx_LPM_CONF_H */
