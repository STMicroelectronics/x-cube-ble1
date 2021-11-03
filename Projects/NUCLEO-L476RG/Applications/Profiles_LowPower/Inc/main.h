/**
  ******************************************************************************
  * @file    main.h
  * @author  MCD Application Team
  * @brief   Header file for main.c
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "cube_hal.h"

/** @addtogroup Applications
 *  @{
 */

/** @addtogroup Profiles_LowPower
 *  @{
 */

/** @addtogroup MAIN
 *  @{
 */
 
/* Exported constants --------------------------------------------------------*/

/** @defgroup MAIN_Exported_Types
 *  @{
 */
/* Exported types ------------------------------------------------------------*/

/**
 * @}
 */

/** @defgroup MAIN_Exported_Defines
 *  @{
 */
/* Exported defines -----------------------------------------------------------*/
#define HCLK_32MHZ 0 /* can be set to 1 only for STM32L053xx */
#define HCLK_80MHZ 0 /* can be set to 1 only for STM32L476RG */ /* SO: TO BE VERIFIED FOR L4. Do not use by now. */
#define HCLK_84MHZ 0 /* can be set to 1 only for STM32F401xE */

/* USER CODE BEGIN Private defines */
/**
 * RTC cloc divider
 */
#define WUCKSEL_DIVIDER (3)		/**< Tick is (LSI speed clock/2) */
#define RTC_ASYNCH_PRESCALER (1)
#define RTC_SYNCH_PRESCALER (0xFFFF)
/* USER CODE END Private defines */
/**
 * @}
 */

/** @defgroup MAIN_Exported_Functions
 *  @{
 */
/* Exported functions ------------------------------------------------------- */

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

#endif /*__MAIN_H */
