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

/** @addtogroup Profiles_DMA_LowPower
 *  @{
 */

/** @addtogroup MAIN
 *  @{
 */
 
/* Exported constants --------------------------------------------------------*/
/**
 * bit mapping of event not requiring sending HCI event
 */
#define	EVENT_NOT_REQUIRING_SENDING_HCI_COMMAND	(~(uint32_t)((1<<eMAIN_HCI_THRESHOLD)-1))

/** @defgroup MAIN_Exported_Types
 *  @{
 */
/* Exported types ------------------------------------------------------------*/
/**
  * All enum after eMAIN_HCI_THRESHOLD shall not request sending HCI command
  */
typedef enum
{
  eMAIN_HCI_Process_Request_Id,
  eMAIN_Profile_Process_Request_Id,
  eMAIN_Profile_App_DeviceState_update_Id,
  eMAIN_Profile_StateMachine_update_Id,
  eMAIN_Profile_Measurement_update_Id,
  eMAIN_Profile_Event_Id,
  eMAIN_HCI_THRESHOLD  /**< Shall be in the list of enum and shall not be used by the application */
} eMAIN_Background_Task_Id_t;
/**
 * @}
 */

/** @defgroup MAIN_Exported_Defines
 *  @{
 */
/* Exported defines -----------------------------------------------------------*/
#define JTAG_SUPPORTED 0 /* if 1 keep debugger enabled while in any low power mode */

#define HCLK_80MHZ 0 /* can be set to 1 only for STM32L476xx */

#define LOW_POWER_MODE 1 /* 1 = Low Power mode ON, 0 = Low Power Mode OFF */

 /**
  * RTC cloc divider
  */
#define WUCKSEL_DIVIDER      (3) /**< Tick is  (LSI speed clock/2) */
#define RTC_ASYNCH_PRESCALER (1)
#define RTC_SYNCH_PRESCALER  (0x7FFF)
/**
 * @}
 */

/** @defgroup MAIN_Exported_Functions
 *  @{
 */
/* Exported functions ------------------------------------------------------- */
void TaskExecutionRequest(eMAIN_Background_Task_Id_t eMAIN_Background_Task_Id);
void TaskExecuted(eMAIN_Background_Task_Id_t eMAIN_Background_Task_Id);
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
