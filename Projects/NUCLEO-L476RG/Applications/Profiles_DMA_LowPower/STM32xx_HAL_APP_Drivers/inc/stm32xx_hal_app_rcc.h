/**
  ******************************************************************************
  * @file    stm32xx_hal_app_rcc.h
  * @author  MCD Application Team
  * @brief   Macro for System Clock Source
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
#ifndef __STM32XX_HAL_APP_RCC_H
#define __STM32XX_HAL_APP_RCC_H

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

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported defines --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
 /**
   * @brief  Set the System Clock Source
   *
   * @param  __SOURCE__: System clock source
   *
   * @retval None
   */
 #define __HAL_APP_RCC_SET_SYSCLK_SRC(__SOURCE__)   (RCC->CFGR |= (__SOURCE__))

/* Exported functions ------------------------------------------------------- */


#ifdef __cplusplus
}
#endif

#endif /*__STM32L0XX_HAL_APP_RCC_H */
