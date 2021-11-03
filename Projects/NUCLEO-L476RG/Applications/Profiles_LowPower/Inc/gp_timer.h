/**
  ******************************************************************************
  * @file    gp_timer.h
  * @author  AMS - HEA&RF BU
  * @brief   General purpose timer library
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

#ifndef __GP_TIMER_H__
#define __GP_TIMER_H__

#include "ble_clock.h"
#include "bluenrg_def.h"
#ifdef __DMA_LP__
#include "stm32xx_timerserver.h"
#endif /* __DMA_LP__ */

/**
 * timer
 *
 * A structure that represents a timer. Use Timer_Set() to set the timer.
 *
 */
struct timer {
    
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    
  tClockTime start;
  tClockTime interval;
  
#endif
};

typedef void (* TIMER_HCI_TIMEOUT_NOTIFY_CALLBACK_TYPE)(void);

/**
 * Timer_Set
 *
 * @param[in] t             Pointer to a timer structure
 * @param[in] interval      timeout value
 *
 * This function sets the timeout value of a timer.
 *
 */
void Timer_Set(struct timer *t, tClockTime interval);

/**
 * Timer_Reset
 * 
 * @param[in] t     Pointer to a timer structure
 * 
 * This function resets the timer with the same interval given
 * with Timer_Set, starting from the time it previously expired.
 * 
 */ 
void Timer_Reset(struct timer *t);

/**
 * Timer_Restart
 * 
 * @param[in]  t   Pointer to a timer structure
 * 
 * This function resets the timer with the same interval given
 * with Timer_Set, starting from the current time.
 * 
 */ 
void Timer_Restart(struct timer *t);

/**
 * Timer_Expired
 *
 * @param[in] t    Pointer to a timer structure
 *
 * This function returns TRUE if timer is expired, FALSE otherwise.
 *
 */
int Timer_Expired(struct timer *t);

/**
 * Timer_Expired
 *
 * @param[in] t    Pointer to a timer structure
 *
 * This function returns the time needed for expiration.
 *
 * @return  Time before timer's expiration.
 */
tClockTime Timer_Remaining(struct timer *t);

#ifdef __DMA_LP__
tBleStatus Blue_NRG_HCI_Timer_Start(uint32_t expiryTime,
		TIMER_HCI_TIMEOUT_NOTIFY_CALLBACK_TYPE timercb,
					   uint8_t *timerID);

tBleStatus Blue_NRG_HCI_Timer_Stop(uint8_t timerID);
#endif /* __DMA_LP__ */

#endif /* __GP_TIMER_H__ */
