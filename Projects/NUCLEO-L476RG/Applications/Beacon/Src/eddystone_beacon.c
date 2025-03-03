/**
  ******************************************************************************
  * @file    eddystone_beacon.c
  * @author  SRA Application Team
  * @brief   Set beacon services
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

/* Includes ------------------------------------------------------------------*/
#include "beacon_utils.h"

#include "hci_const.h"
#include "hci_le.h"
#include "bluenrg_gap.h"
#include "bluenrg_gap_aci.h"
#include "bluenrg_gatt_aci.h"
#include "bluenrg_hal_aci.h"
#include "eddystone_beacon.h"

/** @addtogroup Applications
 *  @{
 */

/** @addtogroup Beacon
 *  @{
 */

/** @defgroup EDDYSTONE_BEACON
 * @{
 */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup EDDYSTONE_BEACON_Private_Constants
 * @{
 */
/* Private constants ---------------------------------------------------------*/
#define ADVERTISING_INTERVAL_INCREMENT (16)
/**
 * @}
 */
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/** @defgroup EDDYSTONE_BEACON_Exported_Functions
 * @{
 */
/* Exported functions --------------------------------------------------------*/

/**
  * @brief  This function starts the Eddystone UID device
  * @param  None
  * @retval None
  */
void EddystoneUID_Start(void)
{
  uint8_t NamespaceID[] = { NAMESPACE_ID };
  uint8_t BeaconID[] = { BEACON_ID };

  EddystoneUID_InitTypeDef EddystoneUID_InitStruct =
  {
    .AdvertisingIntervalMin = ADVERTISING_INTERVAL_MIN,
    .AdvertisingIntervalMax = ADVERTISING_INTERVAL_MAX,
    .CalibratedTxPower = CALIBRATED_TX_POWER_AT_0_M,
    .NamespaceID = NamespaceID,
    .BeaconID = BeaconID
  };

  EddystoneUID_Init(&EddystoneUID_InitStruct);
}

/**
  * @brief  This function starts the Eddystone URL device
  * @param  None
  * @retval None
  */
void EddystoneURL_Start(void)
{
  uint8_t UrlScheme = URL_PREFIX;
  uint8_t Url[] = PHYSICAL_WEB_URL;

  EddystoneURL_InitTypeDef EddystoneURL_InitStruct =
  {
    .AdvertisingIntervalMin = ADVERTISING_INTERVAL_MIN,
    .AdvertisingIntervalMax = ADVERTISING_INTERVAL_MAX,
    .CalibratedTxPower = CALIBRATED_TX_POWER_AT_0_M,
    .UrlScheme = UrlScheme,
    .Url = Url,
    .UrlLength = sizeof(Url) - 1
  };

  EddystoneURL_Init(&EddystoneURL_InitStruct);
}

/**
  * @brief  This function initializes the Eddystone UID Bluetooth services
  * @param  EddystoneUID_Init pointer to initialization structure
  * @retval None
  */
tBleStatus EddystoneUID_Init(EddystoneUID_InitTypeDef *EddystoneUID_Init)
{
  tBleStatus ret = BLE_STATUS_SUCCESS;

  /* Disable scan response. */
  hci_le_set_scan_resp_data(0, NULL);

  /* Put the device in a non-connectable mode. */
  ret = aci_gap_set_discoverable(ADVERTISING_DATA_TYPE,           /*< Advertise as non-connectable, undirected. */
                                 EddystoneUID_Init->AdvertisingIntervalMin, /*< Set the min advertising interval (0.625 us increment). */
                                 EddystoneUID_Init->AdvertisingIntervalMax, /*< Set the max advertising interval (0.625 us increment). */
                                 PUBLIC_ADDR, NO_WHITE_LIST_USE,  /*< Use the public address, with no white list. */
                                 0, NULL,                         /*< Do not use a local name. */
                                 0, NULL,                         /*< Do not include the service UUID list. */
                                 0, 0);                           /*< Do not set a slave connection interval. */

  if (ret != BLE_STATUS_SUCCESS)
  {
    return ret;
  }

  /* Remove the TX power level advertisement (this is done to decrease the packet size). */
  ret = aci_gap_delete_ad_type(AD_TYPE_TX_POWER_LEVEL);

  if (ret != BLE_STATUS_SUCCESS)
  {
    return ret;
  }

  uint8_t service_data[] =
  {
    23,                                                                      /*< Length. */
    AD_TYPE_SERVICE_DATA,                                                    /*< Service Data data type value. */
    0xAA, 0xFE,                                                              /*< 16-bit Eddystone UUID. */
    0x00,                                                                    /*< UID frame type. */
    EddystoneUID_Init->CalibratedTxPower,                                    /*< Ranging data. */
    EddystoneUID_Init->NamespaceID[0],                                       /*< 10-byte ID Namespace. */
    EddystoneUID_Init->NamespaceID[1],
    EddystoneUID_Init->NamespaceID[2],
    EddystoneUID_Init->NamespaceID[3],
    EddystoneUID_Init->NamespaceID[4],
    EddystoneUID_Init->NamespaceID[5],
    EddystoneUID_Init->NamespaceID[6],
    EddystoneUID_Init->NamespaceID[7],
    EddystoneUID_Init->NamespaceID[8],
    EddystoneUID_Init->NamespaceID[9],
    EddystoneUID_Init->BeaconID[0],                                         /*< 6-byte ID Instance. */
    EddystoneUID_Init->BeaconID[1],
    EddystoneUID_Init->BeaconID[2],
    EddystoneUID_Init->BeaconID[3],
    EddystoneUID_Init->BeaconID[4],
    EddystoneUID_Init->BeaconID[5],
    0x00,                                                                   /*< Reserved. */
    0x00                                                                    /*< Reserved. */
  };

  uint8_t service_uuid_list[] =
  {
    3,                                                                      /*< Length. */
    AD_TYPE_16_BIT_SERV_UUID_CMPLT_LIST,                                    /*< Complete list of 16-bit Service UUIDs data type value. */
    0xAA, 0xFE                                                              /*< 16-bit Eddystone UUID. */
  };

  uint8_t flags[] =
  {
    2,                                                                      /*< Length. */
    AD_TYPE_FLAGS,                                                          /*< Flags data type value. */
    (FLAG_BIT_LE_GENERAL_DISCOVERABLE_MODE | FLAG_BIT_BR_EDR_NOT_SUPPORTED) /*< BLE general discoverable, without BR/EDR support. */
  };

  /* Update the service data. */
  ret = aci_gap_update_adv_data(sizeof(service_data), service_data);

  if (ret != BLE_STATUS_SUCCESS)
  {
    return ret;
  }

  /* Update the service UUID list. */
  ret = aci_gap_update_adv_data(sizeof(service_uuid_list), service_uuid_list);

  if (ret != BLE_STATUS_SUCCESS)
  {
    return ret;
  }

  /* Update the adverstising flags. */
  ret = aci_gap_update_adv_data(sizeof(flags), flags);

  if (ret != BLE_STATUS_SUCCESS)
  {
    return ret;
  }

  return ret;
}

/**
  * @brief  This function initializes the Eddystone URL Bluetooth services
  * @param  EddystoneURL_Init pointer to initialization structure
  * @retval None
  */
tBleStatus EddystoneURL_Init(EddystoneURL_InitTypeDef *EddystoneURL_Init)
{
  tBleStatus ret;

  /* Disable scan response. */
  hci_le_set_scan_resp_data(0, NULL);

  /* Put the device in a non-connectable mode. */
  ret = aci_gap_set_discoverable(ADVERTISING_DATA_TYPE,           /*< Advertise as non-connectable, undirected. */
                                 EddystoneURL_Init->AdvertisingIntervalMin, /*< Set the min advertising interval (0.625 us increment). */
                                 EddystoneURL_Init->AdvertisingIntervalMax, /*< Set the max advertising interval (0.625 us increment). */
                                 PUBLIC_ADDR, NO_WHITE_LIST_USE,  /*< Use the public address, with no white list. */
                                 0, NULL,                         /*< Do not use a local name. */
                                 0, NULL,                         /*< Do not include the service UUID list. */
                                 0, 0);                           /*< Do not set a slave connection interval. */

  if (ret != BLE_STATUS_SUCCESS)
  {
    return ret;
  }

  /* Remove the TX power level advertisement (this is done to decrease the packet size). */
  ret = aci_gap_delete_ad_type(AD_TYPE_TX_POWER_LEVEL);

  if (ret != BLE_STATUS_SUCCESS)
  {
    return ret;
  }

  uint8_t service_data[24] =
  {
    6 + EddystoneURL_Init->UrlLength,                                       /*< Length. */
    AD_TYPE_SERVICE_DATA,                                                   /*< Service Data data type value. */
    0xAA, 0xFE,                                                             /*< 16-bit Eddystone UUID. */
    0x10,                                                                   /*< URL frame type. */
    EddystoneURL_Init->CalibratedTxPower,                                   /*< Ranging data. */
    EddystoneURL_Init->UrlScheme,                                           /*< URL Scheme Prefix is http://www. */
    0x00,                                                                   /*< URL */
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
  };

  for (uint8_t i = 0; i < EddystoneURL_Init->UrlLength; ++i)
  {
    service_data[7 + i] = EddystoneURL_Init->Url[i];
  }

  uint8_t service_uuid_list[] =
  {
    3,                                                                      /*< Length. */
    AD_TYPE_16_BIT_SERV_UUID_CMPLT_LIST,                                    /*< Complete list of 16-bit Service UUIDs data type value. */
    0xAA, 0xFE                                                              /*< 16-bit Eddystone UUID. */
  };

  uint8_t flags[] =
  {
    2,                                                                      /*< Length. */
    AD_TYPE_FLAGS,                                                          /*< Flags data type value. */
    (FLAG_BIT_LE_GENERAL_DISCOVERABLE_MODE | FLAG_BIT_BR_EDR_NOT_SUPPORTED) /*< BLE general discoverable, without BR/EDR support. */
  };

  /* Update the service data. */
  ret = aci_gap_update_adv_data(sizeof(service_data), service_data);

  if (ret != BLE_STATUS_SUCCESS)
  {
    return ret;
  }

  /* Update the service UUID list. */
  ret = aci_gap_update_adv_data(sizeof(service_uuid_list), service_uuid_list);

  if (ret != BLE_STATUS_SUCCESS)
  {
    return ret;
  }

  /* Update the adverstising flags. */
  ret = aci_gap_update_adv_data(sizeof(flags), flags);

  if (ret != BLE_STATUS_SUCCESS)
  {
    return ret;
  }

  return ret;
}
/**
 * @}
 */

/* Private functions ---------------------------------------------------------*/

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
