/**
  ******************************************************************************
  * @file    app_bluenrg_ms.c
  * @author  SRA Application Team
  * @brief   BlueNRG-M0 initialization and applicative code
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
#include "app_bluenrg_ms.h"

#include <string.h>
#include "hci_le.h"
#include "hci_tl.h"
#include "sensor_service.h"
#include "eddystone_beacon.h"
#include "bluenrg_utils.h"
#include "stm32l4xx_nucleo.h"
#include "bluenrg_gap_aci.h"
#include "bluenrg_gatt_aci.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/
/**
 * Define the beacon type here only if it is not already defined in the project
 * options.
 * For the URL beacon type uncomment the line below.
 * Otherwise, if it is not already defined in the project options, the UID
 * beacon type is set.
 */
//#define EDDYSTONE_BEACON_TYPE EDDYSTONE_URL_BEACON_TYPE

#ifndef EDDYSTONE_BEACON_TYPE
  #define EDDYSTONE_BEACON_TYPE EDDYSTONE_UID_BEACON_TYPE
#endif

#define IDB04A1 0
#define IDB05A1 1

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void EnterStopMode(void);
static void User_Init(void);
static void User_Process(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

#if PRINT_CSV_FORMAT
extern volatile uint32_t ms_counter;
/**
 * @brief  This function is a utility to print the log time
 *         in the format HH:MM:SS:MSS (DK GUI time format)
 * @param  None
 * @retval None
 */
void print_csv_time(void){
  uint32_t ms = HAL_GetTick();
  PRINT_CSV("%02ld:%02ld:%02ld.%03ld", (long)(ms/(60*60*1000)%24), (long)(ms/(60*1000)%60), (long)((ms/1000)%60), (long)(ms%1000));
}
#endif

void MX_BlueNRG_MS_Init(void)
{
  /* USER CODE BEGIN SV */

  /* USER CODE END SV */

  /* USER CODE BEGIN BlueNRG_MS_Init_PreTreatment */

  /* USER CODE END BlueNRG_MS_Init_PreTreatment */

  /* Initialize the peripherals and the BLE Stack */
  tBleStatus ret = BLE_STATUS_SUCCESS;

  uint16_t service_handle, dev_name_char_handle, appearance_char_handle;
  uint8_t SERVER_BDADDR[] = { MAC_ADDRESS };

  uint8_t  hwVersion;
  uint16_t fwVersion;
  uint8_t bnrg_expansion_board = IDB04A1; /* at startup, suppose the X-NUCLEO-IDB04A1 is used */

  User_Init();

  hci_init(user_notify, NULL);

  /* get the BlueNRG HW and FW versions */
  getBlueNRGVersion(&hwVersion, &fwVersion);

  /*
   * Reset BlueNRG again otherwise we won't
   * be able to change its MAC address.
   * aci_hal_write_config_data() must be the first
   * command after reset otherwise it will fail.
   */
  hci_reset();

  HAL_Delay(100);

  if (hwVersion > 0x30) { /* X-NUCLEO-IDB05A1 expansion board is used */
    bnrg_expansion_board = IDB05A1;
  }

  ret = aci_hal_write_config_data(CONFIG_DATA_PUBADDR_OFFSET,
                                  CONFIG_DATA_PUBADDR_LEN,
                                  SERVER_BDADDR);

  if (ret != BLE_STATUS_SUCCESS)
  {
    __asm("nop");
  }

  ret = aci_gatt_init();

  if (ret != BLE_STATUS_SUCCESS)
  {
    __asm("nop");
  }

  if (bnrg_expansion_board == IDB05A1) {
    ret = aci_gap_init_IDB05A1(GAP_PERIPHERAL_ROLE_IDB05A1, 0, 0x07, &service_handle, &dev_name_char_handle, &appearance_char_handle);
  }
  else {
    ret = aci_gap_init_IDB04A1(GAP_PERIPHERAL_ROLE_IDB04A1, &service_handle, &dev_name_char_handle, &appearance_char_handle);
  }

  if (ret != BLE_STATUS_SUCCESS)
  {
    __asm("nop");
  }

  ret = aci_hal_set_tx_power_level(1,4);

  if (ret != BLE_STATUS_SUCCESS)
  {
    __asm("nop");
  }

  /* Initialize beacon services */
  if (EDDYSTONE_BEACON_TYPE & EDDYSTONE_UID_BEACON_TYPE)
  {
    EddystoneUID_Start();
  }
  if (EDDYSTONE_BEACON_TYPE & EDDYSTONE_URL_BEACON_TYPE)
  {
    EddystoneURL_Start();
  }

  /* USER CODE BEGIN BlueNRG_MS_Init_PostTreatment */

  /* USER CODE END BlueNRG_MS_Init_PostTreatment */
}

/*
 * BlueNRG-MS background task
 */
void MX_BlueNRG_MS_Process(void)
{
  /* USER CODE BEGIN BlueNRG_MS_Process_PreTreatment */

  /* USER CODE END BlueNRG_MS_Process_PreTreatment */

  User_Process();
  hci_user_evt_proc();

  /* USER CODE BEGIN BlueNRG_MS_Process_PostTreatment */

  /* USER CODE END BlueNRG_MS_Process_PostTreatment */
}

/**
 * @brief  Initialize User process.
 *
 * @param  None
 * @retval None
 */
static void User_Init(void)
{
  BSP_COM_Init(COM1);
}

/**
 * @brief  User application process
 * @param  None
 * @retval None
 */
static void User_Process(void)
{
  EnterStopMode();
}

/**
 * @brief  Enter the STOP mode
 * @param  None
 * @retval None
 */
void EnterStopMode(void)
{
  /**
   * If needed, add in the following USER CODE section
   * the code for entering a low power mode.
   *
   * Here an example (to be adapted according to the used
   * STM32 family):
   *
   * __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
   * HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
   *
   */

  /* USER CODE BEGIN EnterStopMode */

  /* USER CODE END EnterStopMode */
}
