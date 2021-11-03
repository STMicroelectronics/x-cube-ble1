/**
  ******************************************************************************
  * @file    hci_tl.h
  * @author  AMG RF FW team
  * @brief   Header file for hci_tl.c
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
#ifndef __HCI_TL_H_
#define __HCI_TL_H_

#include "bluenrg_types.h"
#include "link_layer.h"
#include "ble_list.h"

#define HCI_READ_PACKET_SIZE                    128 //71

/**
 * Maximum payload of HCI commands that can be sent. Change this value if needed.
 * This value can be up to 255.
 */
#define HCI_MAX_PAYLOAD_SIZE 128
 
/*** Data types ***/

/* structure used to read received data */
typedef struct _tHciDataPacket
{
  tListNode currentNode;
  uint8_t dataBuff[HCI_READ_PACKET_SIZE];
  uint8_t data_len;
} tHciDataPacket;

struct hci_request {
  uint16_t ogf;
  uint16_t ocf;
  int      event;
  void     *cparam;
  int      clen;
  void     *rparam;
  int      rlen;
};

typedef enum
{
  BUSY,
  AVAILABLE
} HCI_CMD_STATUS_t;

/**
 * This function must be used to pass the packet received from the HCI
 * interface to the BLE Stack HCI state machine.
 *
 * @param[in] hciReadPacket    The packet that is received from HCI interface.
 *
 */
void HCI_Input(tHciDataPacket *hciReadPacket);

/**
 * Initialization function. Must be done before any data can be received from
 * BLE controller.
 */
void HCI_Init(void);

/**
 * Callback used to pass events to application.
 *
 * @param[in] pckt    The event.
 *
 */
void HCI_Event_CB(void *pckt);

/**
 * Processing function that must be called after an event is received from
 * HCI interface. Must be called outside ISR. It will call HCI_Event_CB if
 * necessary.
*/
void HCI_Process(void);

/**
 * @brief Check if queue of HCI event is empty or not.
 * @note This function can be used to check if the event queue from BlueNRG is empty. This
 *       is useful when checking if it is safe to go to sleep. 
 * @return TRUE if event queue is empty. FALSE otherwise.
 */
BOOL HCI_Queue_Empty(void);
/**
 * Interrupt service routine that must be called when the BlueNRG 
 * reports a packet received or an event to the host through the 
 * BlueNRG interrupt line.
 */
#ifdef __DMA_LP__
void HCI_Isr(uint8_t *buffer, uint8_t event_payload_len);
void HCI_Process_Notification_Request(void);
void HCI_Cmd_Status(HCI_CMD_STATUS_t Hci_Cmd_Status);
void HCI_Wait_For_Response(void);
#else
void HCI_Isr(void);

int hci_send_req(struct hci_request *r, BOOL async);
#endif /* __DMA_LP__ */

extern tListNode hciReadPktPool;
extern tListNode hciReadPktRxQueue;
 
#endif /* __HCI_TL_H_ */
