/**
  ******************************************************************************
  * @file    role_type.h
  * @author  SRA Application Team
  * @brief   Define BLE role
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ROLE_TYPE_H
#define ROLE_TYPE_H

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup Applications
 *  @{
 */

/** @addtogroup SampleApp
 *  @{
 */

/** @defgroup ROLE_TYPE
 * @{
 */

/** @defgroup ROLE_TYPE_Exported_Types
 *  @{
 */
/* Exported types ------------------------------------------------------------*/
/**
* @brief BlueNRG Role.
*/
typedef enum {
  CLIENT = 0, /**< CLIENT is for Central role. */
  SERVER = 1  /**< SERVER is for Peripheral role. */
} BLE_RoleTypeDef;
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

#endif /* ROLE_TYPE_H */
