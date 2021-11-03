/**
  ******************************************************************************
  * @file    user_timer.h
  * @author  AMS VMA Application Team
  * @brief   Header for user_timer.c module
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
#ifndef __USER_TIMER_H
#define __USER_TIMER_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "ble_clock.h"
#include "hci_tl_interface.h"


/* Definition for TIMx: TIM2/3 */
#ifdef STM32L053xx
#define TIMx                           TIM2
#define TIMx_CLK_ENABLE()              __HAL_RCC_TIM2_CLK_ENABLE()
#else
#define TIMx                           TIM3
#define TIMx_CLK_ENABLE()              __HAL_RCC_TIM3_CLK_ENABLE()
#endif /* STM32L053xx */

/* Definition for TIMx's NVIC */
#ifdef STM32L053xx
#define TIMx_IRQn                      TIM2_IRQn
#define TIMx_IRQHandler                TIM2_IRQHandler
#else
#define TIMx_IRQn                      TIM3_IRQn
#define TIMx_IRQHandler                TIM3_IRQHandler
#endif /* STM32L053xx */

#define USER_TIMER_PRESCALER    (64000-1)
/* Timeout in milliseconds. */
#define USER_TIMER_PERIOD_MSEC   200
#define USER_TIMER_PERIOD       (USER_TIMER_PERIOD_MSEC*(SYSCLK_FREQ/(USER_TIMER_PRESCALER+1))/1000)

#define USER_TIMER_PRESCALER_SLEEP  ((USER_TIMER_PRESCALER+1)/(SYSCLK_FREQ/SYSCLK_FREQ_SLEEP) - 1)

extern TIM_HandleTypeDef    TimHandle;
extern tClockTime user_timer_expired; 


void Init_User_Timer(void);
void Start_User_Timer(void);
void Stop_User_Timer(void);
void User_Timer_Enter_Sleep(void);
void User_Timer_Exit_Sleep(void);

 
#ifdef __cplusplus
}
#endif

#endif /*__USER_TIMER_H */
