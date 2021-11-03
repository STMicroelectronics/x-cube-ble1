/**
  ******************************************************************************
  * @file    hw_config.h
  * @author  MCD Application Team
  * @brief   Hardware Configuration & Setup
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
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "usb_type.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define PRINT_DATA_SIZE     2048
#define READ_DATA_SIZE      1024

/* Constants for user timer */
#define USER_TIMER_PRESCALER    64000-1 //TBR
/* Timeout in milliseconds. */
#define USER_TIMER_PERIOD_MSEC   200
#define USER_TIMER_PERIOD       USER_TIMER_PERIOD_MSEC*(SYSCLK_FREQ/(USER_TIMER_PRESCALER+1))/1000

#define USER_TIMER_PRESCALER_SLEEP  (USER_TIMER_PRESCALER+1)/(SYSCLK_FREQ/SYSCLK_FREQ_SLEEP) - 1

/* Exported functions ------------------------------------------------------- */
void RCC_Configuration(void);
void Init_GPIOs(void);
void Set_System(void);
void Set_USBClock(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void USB_Cable_Config (FunctionalState NewState);
void Handle_USBAsynchXfer (void);
void Get_SerialNum(void);
void USB_Send_Data(uint8_t byte);
void USB_Init(void);

/* External variables --------------------------------------------------------*/

#endif  /*__HW_CONFIG_H*/
