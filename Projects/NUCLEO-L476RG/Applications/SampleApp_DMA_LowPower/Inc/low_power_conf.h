/**
  ******************************************************************************
  * @file    low_power_conf.h 
  * @author  CL
  * @brief   Header file for low_power_conf_l4.c
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
#ifndef __LOW_POWER_CONF_H_
#define __LOW_POWER_CONF_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32xx_lpm.h"
#include "stm32xx_hal_app_rcc.h"

#include "stm32l4xx_hal.h"
#include "stm32l4xx_nucleo.h"
#include "stm32l4xx_hal_rtc.h"
#include "stm32l4xx_hal_rtc_ex.h"
   
#define WAKE_UP_COUNTER 0x0802

/* Exported constants --------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Defines related to RTC Clock configuration */    
/* Uncomment to enable the adequate Clock Source */
#define RTC_CLOCK_SOURCE_LSI
/* #define RTC_CLOCK_SOURCE_LSE */

#ifdef RTC_CLOCK_SOURCE_LSI
  #define RTC_ASYNCH_PREDIV    0x7F
  #define RTC_SYNCH_PREDIV     0x0130
#endif

/* RTC Timer setting */
#define UPDATE_INTERVAL   1000.00 /* ms*/

/* Global variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void SystemPower_Config(void);
   
#ifdef __cplusplus
}
#endif

#endif /* __LOW_POWER_CONF_H_ */
