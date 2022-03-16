/**
  ******************************************************************************
  * @file    sensor_service.c
  * @author  SRA Application Team
  * @brief   Module for processing ACI events
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "sensor_service.h"
#include "bluenrg_gap_aci.h"
#include "bluenrg_gatt_aci.h"

/** @addtogroup Applications
 *  @{
 */

/** @addtogroup Beacon
 *  @{
 */

/** @defgroup SENSOR_SERVICE
 * @{
 */

/** @addtogroup SENSOR_SERVICE_Exported_Functions
 * @{
 */
/**
 * @brief  Callback processing the ACI events.
 * @note   Inside this function each event must be identified and correctly
 *         parsed.
 * @param  void* Pointer to the ACI packet
 * @retval None
 */
void user_notify(void * pData)
{
  hci_uart_pckt *hci_pckt = pData;

  /* obtain event packet */
  hci_event_pckt *event_pckt = (hci_event_pckt*)hci_pckt->data;

  if(hci_pckt->type != HCI_EVENT_PKT)
  {
    return;
  }

  switch(event_pckt->evt)
  {

  case EVT_DISCONN_COMPLETE:
    {
      ;
    }
    break;

  case EVT_LE_META_EVENT:
    {
      evt_le_meta_event *evt = (void *)event_pckt->data;

      switch(evt->subevent)
      {
      case EVT_LE_CONN_COMPLETE:
        {
          ;
        }
        break;
      }
    }
    break;

  case EVT_VENDOR:
    {
      ;
    }
    break;
  }
}
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
