/**
  ******************************************************************************
  * @file    sample_service.h
  * @author  SRA Application Team
  * @brief   Header file for sample_service.c
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
#ifndef _SAMPLE_SERVICE_H_
#define _SAMPLE_SERVICE_H_

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32_bluenrg_ble.h"
#include "bluenrg_gatt_server.h"
#include "bluenrg_gap.h"
#include "bluenrg_gap_aci.h"
#include "bluenrg_gatt_aci.h"
#include "throughput_support.h"
#include "ble_clock.h"
#include "gp_timer.h"
#include "bluenrg_hal_aci.h"
#include "bluenrg_aci_const.h"
#include "hci_tl.h"
#include "hci_le.h"
#include "sm.h"
#include "bluenrg_conf.h"

#include "role_type.h"

#include "uart_support.h"

/** @addtogroup Applications
 *  @{
 */

/** @addtogroup SampleAppThT
 *  @{
 */
 
/** @addtogroup SAMPLE_SERVICE 
 * @{
 */

/** @addtogroup SAMPLE_SERVICE_Exported_Defines
 *  @{
 */
#define IDB04A1 0
#define IDB05A1 1
   
/** 
* @brief Handle of TX Characteristic on the Server. The handle should be
*        discovered, but it is fixed only for this demo.
*/ 
//#define TX_HANDLE 0x0011

/** 
* @brief Handle of RX Characteristic on the Client. The handle should be
*        discovered, but it is fixed only for this demo.
*/ 
//#define RX_HANDLE   0x0014

/**
 * @}
 */

/** @addtogroup SAMPLE_SERVICE_Exported_Functions
 *  @{
 */
tBleStatus Add_Sample_Service(void);
void Make_Connection(void);
void receiveData(uint8_t* data_buffer, uint8_t Nb_bytes);
void sendData(uint8_t* data_buffer, uint8_t Nb_bytes);
void startReadTXCharHandle(void);
void startReadRXCharHandle(void);
void enableNotification(void);
void Attribute_Modified_CB(uint16_t handle, uint8_t data_length,
                           uint8_t *att_data);
void GAP_ConnectionComplete_CB(uint8_t addr[6], uint16_t handle);
void GAP_DisconnectionComplete_CB(void);
void GATT_Notification_CB(uint16_t attr_handle, uint8_t attr_len,
                          uint8_t *attr_value);
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

#endif /* _SAMPLE_SERVICE_H_ */