/**
  ******************************************************************************
  * @file    stm32xx_hal_app_rtc.h
  * @author  MCD Application Team
  * @brief   Header for stm32xx_hal_app_rtc.c module
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
#ifndef __STM32XX_HAL_APP_RTC_H
#define __STM32XX_HAL_APP_RTC_H

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

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported defines --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
 void HAL_APP_RTC_Set_Wucksel(RTC_HandleTypeDef *localhrtc, uint32_t RTC_Wucksel_Value);


#ifdef __cplusplus
}
#endif

#endif /*__STM32XX_HAL_APP_RTC_H */
