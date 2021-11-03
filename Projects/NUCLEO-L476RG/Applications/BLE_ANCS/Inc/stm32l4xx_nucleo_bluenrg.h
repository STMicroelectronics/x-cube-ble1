/**
  ******************************************************************************
  * @file    stm32l4xx_nucleo_bluenrg.h
  * @author  SRA Application Team
  * @brief   This file contains definitions for SPI communication from
  *          STM32L4xx on STM32L4XX-Nucleo to BlueNRG module on ST's
  *          Expansion Board (reference X-NUCLEO-IDB05A1/X-NUCLEO-IDB05A2)
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
#ifndef __STM32L4XX_NUCLEO_BLUENRG_H
#define __STM32L4XX_NUCLEO_BLUENRG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "stm32l4xx_nucleo.h"

/** @addtogroup Applications
 *  @{
 */

/** @addtogroup BLE_ANCS
 *  @{
 */
  
/** @defgroup STM32L4XX_NUCLEO_BLUENRG
  * @{
  */
  
/** @defgroup STM32L4XX_NUCLEO_BLUENRG_Exported_Defines 
  * @{
  */
  
/**
* @brief SPI communication details between Nucleo L4 and BlueNRG
*        Expansion Board.
*/
// SPI Instance
#define BNRG_SPI_INSTANCE		SPI1
#define BNRG_SPI_CLK_ENABLE()		__SPI1_CLK_ENABLE()

// SPI Configuration
#define BNRG_SPI_MODE			SPI_MODE_MASTER
#define BNRG_SPI_DIRECTION		SPI_DIRECTION_2LINES
#define BNRG_SPI_DATASIZE		SPI_DATASIZE_8BIT
#define BNRG_SPI_CLKPOLARITY		SPI_POLARITY_LOW
#define BNRG_SPI_CLKPHASE	        SPI_PHASE_1EDGE
#define BNRG_SPI_NSS			SPI_NSS_SOFT
#define BNRG_SPI_FIRSTBIT	        SPI_FIRSTBIT_MSB
#define BNRG_SPI_TIMODE		        SPI_TIMODE_DISABLED
#define BNRG_SPI_CRCPOLYNOMIAL	        7
#define BNRG_SPI_BAUDRATEPRESCALER      SPI_BAUDRATEPRESCALER_16
#define BNRG_SPI_CRCCALCULATION		SPI_CRCCALCULATION_DISABLED

// SPI Reset Pin: PA.8
#define BNRG_SPI_RESET_PIN	        GPIO_PIN_8
#define BNRG_SPI_RESET_MODE	        GPIO_MODE_OUTPUT_PP
#define BNRG_SPI_RESET_PULL	        GPIO_PULLUP 
#define BNRG_SPI_RESET_SPEED		GPIO_SPEED_LOW
#define BNRG_SPI_RESET_ALTERNATE	0
#define BNRG_SPI_RESET_PORT		GPIOA
#define BNRG_SPI_RESET_CLK_ENABLE()     __GPIOA_CLK_ENABLE()

// SCLK: PB.3
#define BNRG_SPI_SCLK_PIN		GPIO_PIN_3
#define BNRG_SPI_SCLK_MODE		GPIO_MODE_AF_PP
#define BNRG_SPI_SCLK_PULL		GPIO_PULLDOWN
#define BNRG_SPI_SCLK_SPEED		GPIO_SPEED_HIGH
#define BNRG_SPI_SCLK_ALTERNATE		GPIO_AF5_SPI1
#define BNRG_SPI_SCLK_PORT		GPIOB
#define BNRG_SPI_SCLK_CLK_ENABLE()	__GPIOB_CLK_ENABLE()

// MISO (Master Input Slave Output): PA.6
#define BNRG_SPI_MISO_PIN		GPIO_PIN_6
#define BNRG_SPI_MISO_MODE		GPIO_MODE_AF_PP
#define BNRG_SPI_MISO_PULL		GPIO_PULLUP
#define BNRG_SPI_MISO_SPEED		GPIO_SPEED_HIGH
#define BNRG_SPI_MISO_ALTERNATE		GPIO_AF5_SPI1
#define BNRG_SPI_MISO_PORT		GPIOA
#define BNRG_SPI_MISO_CLK_ENABLE()	__GPIOA_CLK_ENABLE()

// MOSI (Master Output Slave Input): PA.7
#define BNRG_SPI_MOSI_PIN		GPIO_PIN_7
#define BNRG_SPI_MOSI_MODE		GPIO_MODE_AF_PP
#define BNRG_SPI_MOSI_PULL		GPIO_NOPULL 
#define BNRG_SPI_MOSI_SPEED		GPIO_SPEED_HIGH
#define BNRG_SPI_MOSI_ALTERNATE		GPIO_AF5_SPI1
#define BNRG_SPI_MOSI_PORT		GPIOA
#define BNRG_SPI_MOSI_CLK_ENABLE()	__GPIOA_CLK_ENABLE()

// NSS/CSN/CS: PA.1
#define BNRG_SPI_CS_PIN			GPIO_PIN_1
#define BNRG_SPI_CS_MODE		GPIO_MODE_OUTPUT_PP
#define BNRG_SPI_CS_PULL		GPIO_PULLUP 
#define BNRG_SPI_CS_SPEED		GPIO_SPEED_HIGH
#define BNRG_SPI_CS_ALTERNATE		0
#define BNRG_SPI_CS_PORT		GPIOA
#define BNRG_SPI_CS_CLK_ENABLE()	__GPIOA_CLK_ENABLE()

// IRQ: PA.0
#define BNRG_SPI_IRQ_PIN		GPIO_PIN_0
#define BNRG_SPI_IRQ_MODE		GPIO_MODE_IT_RISING
#define BNRG_SPI_IRQ_PULL		GPIO_NOPULL
#define BNRG_SPI_IRQ_SPEED		GPIO_SPEED_HIGH
#define BNRG_SPI_IRQ_ALTERNATE		0
#define BNRG_SPI_IRQ_PORT		GPIOA
#define BNRG_SPI_IRQ_CLK_ENABLE()	__GPIOA_CLK_ENABLE()

// EXTI External Interrupt for SPI
// NOTE: if you change the IRQ pin remember to implement a corresponding handler
// function like EXTI0_IRQHandler() in the user project
#define BNRG_SPI_EXTI_IRQn              EXTI0_IRQn
#define BNRG_SPI_EXTI_IRQHandler        EXTI0_IRQHandler
#define BNRG_SPI_EXTI_PIN               BNRG_SPI_IRQ_PIN
#define BNRG_SPI_EXTI_PORT              BNRG_SPI_IRQ_PORT
#define RTC_WAKEUP_IRQHandler           RTC_WKUP_IRQHandler
   
#define BNRG_SPI_FORCE_RESET()          __SPI1_FORCE_RESET()
#define BNRG_SPI_RELEASE_RESET()        __SPI1_RELEASE_RESET()
   
//#define BNRG_DMA_CLK_ENABLE()           __DMA1_CLK_ENABLE()
/* Definition for SPIx's DMA */
//#define BNRG_SPI_TX_DMA_CHANNEL         DMA1_Channel3
//#define BNRG_SPI_TX_DMA_REQUEST         DMA_REQUEST_1
//#define BNRG_SPI_TX_DMA_TC_FLAG         DMA_FLAG_TC3
//#define BNRG_SPI_RX_DMA_CHANNEL         DMA1_Channel2
//#define BNRG_SPI_RX_DMA_REQUEST         DMA_REQUEST_1
//#define BNRG_SPI_RX_DMA_TC_FLAG         DMA_FLAG_TC2
/* Definition for SPIx's NVIC */
//#define BNRG_SPI_DMA_TX_IRQn            DMA1_Channel3_IRQn
//#define BNRG_SPI_DMA_RX_IRQn            DMA1_Channel2_IRQn

//EXTI External Interrupt for user button
#define PUSH_BUTTON_EXTI_IRQHandler     EXTI15_10_IRQHandler

/**
  * @}
  */ 

/** @defgroup STM32L4XX_NUCLEO_BLUENRG_Exported_Functions
  * @{
  */
  
void Enable_SPI_IRQ(void);
void Disable_SPI_IRQ(void);
void Clear_SPI_IRQ(void);
void Clear_SPI_EXTI_Flag(void);

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

#endif /* __STM32L4XX_NUCLEO_BLUENRG_H */
