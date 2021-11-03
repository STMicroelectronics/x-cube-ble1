/**
  ******************************************************************************
  * @file    stm32l4xx_it.h
  * @author  SRA Application Team
  * @brief   Header file for stm32l4xx_it.c
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
#ifndef __STM32xx_IT_H
#define __STM32xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "cube_hal.h"
#include "stm32xx_timerserver.h"

/** @addtogroup Applications
 *  @{
 */

/** @addtogroup Profiles_DMA_LowPower
 *  @{
 */
 
/** @addtogroup INTERRUPT_HANDLER
 * @{
 */
 
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void BNRG_SPI_EXTI_IRQHandler(void);
void PUSH_BUTTON_EXTI_IRQHandler(void);
void RTC_WAKEUP_IRQHandler(void);
void RTC_WKUP_IRQHandler(void);

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

#endif /* __STM32xx_IT_H */
