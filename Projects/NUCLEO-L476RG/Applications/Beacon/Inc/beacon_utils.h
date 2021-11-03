/**
  ******************************************************************************
  * @file    beacon_utils.h
  * @author  SRA Application Team
  * @brief   Defines for Beacon application
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
#ifndef BEACON_UTILS_H
#define BEACON_UTILS_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define HTTP_WWW          (0x00u)
#define HTTPS_WWW         (0x01u)
#define HTTP              (0x02u)
#define HTTPS             (0x03u)

#define DOT_COM_SLASH     (0x00u)
#define DOT_ORG_SLASH     (0x01u)
#define DOT_EDU_SLASH     (0x02u)
#define DOT_NET_SLASH     (0x03u)
#define DOT_INFO_SLASH    (0x04u)
#define DOT_BIZ_SLASH     (0x05u)
#define DOT_GOV_SLASH     (0x06u)
#define DOT_COM           (0x07u)
#define DOT_ORG           (0x08u)
#define DOT_EDU           (0x09u)
#define DOT_NET           (0x0Au)
#define DOT_INFO          (0x0Bu)
#define DOT_BIZ           (0x0Cu)
#define DOT_GOV           (0x0Du)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* BEACON_UTILS_H */
