/**
  ******************************************************************************
  * @file    bluenrg_conf.h
  * @author  SRA Application Team
  * @brief   BLE configuration file
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
#ifndef BLUENRG_CONF_H
#define BLUENRG_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32l4xx_hal.h"
#include <string.h>

/*---------- Print messages from BLE1 files at user level -----------*/
#define BLE1_DEBUG      0
/*---------- Print the data travelling over the SPI in the .csv format compatible with the ST BlueNRG GUI -----------*/
#define PRINT_CSV_FORMAT      0
/*---------- Number of Bytes reserved for HCI Read Packet -----------*/
#define HCI_READ_PACKET_SIZE      128
/*---------- Number of Bytes reserved for HCI Max Payload -----------*/
#define HCI_MAX_PAYLOAD_SIZE      128

#define HCI_DEFAULT_TIMEOUT_MS        1000

#define BLUENRG_memcpy                memcpy
#define BLUENRG_memset                memset

#if (BLE1_DEBUG == 1)
#include <stdio.h>
#define PRINTF(...)                   printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

#if PRINT_CSV_FORMAT
#include <stdio.h>
#define PRINT_CSV(...)                printf(__VA_ARGS__)
void print_csv_time(void);
#else
#define PRINT_CSV(...)
#endif

#ifdef __cplusplus
}
#endif
#endif /* BLUENRG_CONF_H */
