/**
  ******************************************************************************
  * @file    sensor_service.h
  * @author  SRA Application Team
  * @brief   Header file for sensor_service.c
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SENSOR_SERVICE_H
#define SENSOR_SERVICE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "bluenrg_gatt_server.h"
#include "bluenrg_gap.h"
#include "string.h"
#include "hci_const.h"
#include "bluenrg_hal_aci.h"
#include "bluenrg_aci_const.h"
#include "hci.h"
#include "sm.h"

#include <stdlib.h>

/** @defgroup SENSOR_SERVICE_Exported_Functions
 * @{
 */
/* Exported functions --------------------------------------------------------*/
void user_notify(void * pData);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* SENSOR_SERVICE_H */
