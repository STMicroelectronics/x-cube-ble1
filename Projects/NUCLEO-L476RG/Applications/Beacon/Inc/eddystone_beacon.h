/**
  ******************************************************************************
  * @file    eddystone_beacon.h
  * @author  SRA Application Team
  * @brief   Header file for eddystone_beacon.c
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
#ifndef EDDYSTONE_BEACON_H
#define EDDYSTONE_BEACON_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Applications
 *  @{
 */

/** @addtogroup Beacon
 *  @{
 */

/** @addtogroup EDDYSTONE_BEACON
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#if defined (__CC_ARM)
	#define ASSERT_CONCAT_(a, b) a##b
	#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a, b)
	/* These can't be used after statements in c89. */
	#ifdef __COUNTER__
		#define STATIC_ASSERT(e,m) \
			;enum { ASSERT_CONCAT(static_assert_, __COUNTER__) = 1/(!!(e)) }
	#else
		/* This can't be used twice on the same line so ensure if using in headers
		 * that the headers are not included twice (by wrapping in #ifndef...#endif)
		 * Note it doesn't cause an issue when used on same line of separate modules
		 * compiled with gcc -combine -fwhole-program.  */
		#define static_assert(e,m) \
			;enum { ASSERT_CONCAT(assert_line_, __LINE__) = 1/(!!(e)) }
	#endif
#endif

/** @addtogroup EDDYSTONE_BEACON_Exported_Types
 * @{
 */
/* Exported types ------------------------------------------------------------*/

/**
 * @brief Eddystone Beacon UID structure
 */
typedef struct
{
  uint16_t AdvertisingIntervalMin; /*!< Specifies the desired minimum advertising interval. */
  uint16_t AdvertisingIntervalMax; /*!< Specifies the desired maximum advertising interval. */
  uint8_t CalibratedTxPower;   /*!< Specifies the power at 0m. */
  uint8_t * NamespaceID;       /*!< Specifies the 10-byte namespace to which the beacon belongs. */
  uint8_t * BeaconID;          /*!< Specifies the unique 6-byte beacon ID within the specified namespace. */
} EddystoneUID_InitTypeDef;

/**
 * @brief Eddystone Beacon URL structure
 */
typedef struct
{
  uint16_t AdvertisingIntervalMin; /*!< Specifies the desired minimum advertising interval. */
  uint16_t AdvertisingIntervalMax; /*!< Specifies the desired maximum advertising interval. */
  uint8_t CalibratedTxPower;   /*!< Specifies the power at 0m. */
  uint8_t UrlScheme;           /*!< Specifies the URL Encoded Scheme Prefix. */
  uint8_t * Url;               /*!< Specifies the Encoded URL (max 17 characters). */
  uint8_t UrlLength;           /*!< Specifies the length of the Encoded URL (max 17 characters). */
} EddystoneURL_InitTypeDef;
/**
 * @}
 */

/** @addtogroup EDDYSTONE_BEACON_Exported_Constants
 * @{
 */
/* Exported constants --------------------------------------------------------*/
#define MAC_ADDRESS                 0x12, 0x34, 0x00, 0xE1, 0x80, 0x03

#define EDDYSTONE_UID_BEACON_TYPE   (0x01u)
#define EDDYSTONE_URL_BEACON_TYPE   (0x02u)

#define ADVERTISING_DATA_TYPE       ADV_DATA_TYPE
#define ADVERTISING_INTERVAL_MIN    ADV_INTERV_MIN
#define ADVERTISING_INTERVAL_MAX    ADV_INTERV_MAX
#define CALIBRATED_TX_POWER_AT_0_M  ((uint8_t) (-22))
#define NAMESPACE_ID                'w', 'w', 'w', '.', 's', 't', '.', 'c', 'o', 'm'
#define BEACON_ID                   0, 0, 0, 0, 0, 1
#define URL_PREFIX                  HTTP
#define PHYSICAL_WEB_URL            "www.st.com"

#if (0 != (EDDYSTONE_BEACON_TYPE & (EDDYSTONE_BEACON_TYPE - 1)))
  #error "Please select only a single beacon type!"
#endif

#if (ADVERTISING_DATA_TYPE != ADV_NONCONN_IND)
   #warning "The advertising data type should be of 'non-connectable and no scan response' type."
#endif
#if (ADVERTISING_INTERVAL_MIN > ADVERTISING_INTERVAL_MAX)
   #error "The min advertising interval cannot be greater than the max advertising interval."
#endif
#if ((ADVERTISING_INTERVAL_MIN <= 0) || (ADVERTISING_INTERVAL_MIN > 40959))
  #error "Invalid min advertising interval! Please select a value between 0 and 40959 ms."
#endif
#if ((ADVERTISING_INTERVAL_MAX <= 0) || (ADVERTISING_INTERVAL_MAX > 40959))
  #error "Invalid max advertising interval! Please select a value between 0 and 40959 ms."
#endif

#if (0 != (EDDYSTONE_BEACON_TYPE & EDDYSTONE_URL_BEACON_TYPE))
#if defined(__CC_ARM) | defined(__ICCARM__)
	 static_assert(sizeof(PHYSICAL_WEB_URL) < 17, "The URL must be less than 17 characters.");
#else
#warning Please check that sizeof(PHYSICAL_WEB_URL) < 17
#endif
#endif
/**
 * @}
 */

/* Exported Macros -----------------------------------------------------------*/

/** @addtogroup EDDYSTONE_BEACON_Exported_Functions
 *  @{
 */
/* Exported functions --------------------------------------------------------*/

void EddystoneUID_Start(void);

void EddystoneURL_Start(void);

tBleStatus EddystoneUID_Init(EddystoneUID_InitTypeDef *EddystoneUID_Init);

tBleStatus EddystoneURL_Init(EddystoneURL_InitTypeDef *EddystoneURL_Init);

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

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* EDDYSTONE_BEACON_H */
