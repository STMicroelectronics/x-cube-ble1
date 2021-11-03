/**
  ******************************************************************************
  * @file    stm32_bluenrg_ble.h
  * @author  SRA
  * @brief   Header file for stm32_bluenrg_ble.c
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
#ifndef __STM32_BLUENRG_BLE_H
#define __STM32_BLUENRG_BLE_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/ 
#ifdef USE_STM32F4XX_NUCLEO
  #include "stm32f4xx_hal.h"
  #include "stm32f4xx_nucleo.h"
  #include "stm32f4xx_nucleo_bluenrg.h"
  #define SYSCLK_FREQ 84000000
  #define SYSCLK_FREQ_SLEEP 32000
#endif
   
#ifdef USE_STM32L0XX_NUCLEO
  #include "stm32l0xx_hal.h"
  #include "stm32l0xx_nucleo.h"
  #include "stm32l0xx_nucleo_bluenrg.h"
  #define SYSCLK_FREQ 32000000
  #define SYSCLK_FREQ_SLEEP 32000
#endif

#ifdef USE_STM32L4XX_NUCLEO
  #include "stm32l4xx_hal.h"
  #include "stm32l4xx_nucleo.h"
  #include "stm32l4xx_nucleo_bluenrg.h"
  #define SYSCLK_FREQ 80000000
  #define SYSCLK_FREQ_SLEEP 32000
#endif

/** @addtogroup BSP
 *  @{
 */

/** @addtogroup X-NUCLEO-IDB0xA1
 *  @{
 */
 
/** @addtogroup STM32_BLUENRG_BLE
 *  @{
 */

/** @defgroup STM32_BLUENRG_BLE_Exported_Functions 
 * @{
 */
  
// FIXME: add prototypes for BlueNRG here
void BNRG_SPI_Init(void);
void BlueNRG_RST(void);
uint8_t BlueNRG_DataPresent(void);
void    BlueNRG_HW_Bootloader(void);
int32_t BlueNRG_SPI_Read_All(uint8_t *buffer,
                             uint8_t buff_size);
int32_t BlueNRG_SPI_Write(uint8_t* data1,
                          uint8_t* data2,
                          uint8_t Nb_bytes1,
                          uint8_t Nb_bytes2);
#ifdef OPTIMIZED_SPI
/* Optimized functions for throughput test */
/* Used by the server (L0 and F4, not L4) */
HAL_StatusTypeDef HAL_SPI_TransmitReceive_Opt(const uint8_t *pTxData, uint8_t *pRxData, uint8_t Size);
HAL_StatusTypeDef HAL_SPI_Transmit_Opt(const uint8_t *pTxData, uint8_t Size);
HAL_StatusTypeDef HAL_SPI_Receive_Opt(uint8_t *pRxData, uint8_t Size);
#endif /* OPTIMIZED_SPI */


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

#endif /* __STM32_BLUENRG_BLE_H */
