/**
  ******************************************************************************
  * @file    uart_support.h
  * @author  SRA Application Team
  * @brief   Header file for uart_support.c
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
#ifndef __UART_SUPPORT_H
#define __UART_SUPPORT_H

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

#ifdef PRINTF
#undef PRINTF
#endif

#ifdef GETCHAR
#undef GETCHAR
#endif

void PRINT_MESG_UART(const char * format, ... );
uint8_t GETCHAR_UART(void);

#define PRINTF PRINT_MESG_UART
#define GETCHAR GETCHAR_UART

/* Exported constants --------------------------------------------------------*/
/** 
 * @brief User can use this section to tailor USARTx/UARTx instance used and 
 *        associated resources.
 */
/* Definition for USARTx clock resources */
#define USARTx                           USART2
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART2_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_FORCE_RESET()             __HAL_RCC_USART2_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART2_RELEASE_RESET()
/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_2
#define USARTx_TX_GPIO_PORT              GPIOA  
#define USARTx_TX_AF                     GPIO_AF7_USART2
#define USARTx_RX_PIN                    GPIO_PIN_3
#define USARTx_RX_GPIO_PORT              GPIOA 
#define USARTx_RX_AF                     GPIO_AF7_USART2
/* Definition for USARTx's NVIC */
#define USARTx_IRQn                      USART2_IRQn
#define USARTx_IRQHandler                USART2_IRQHandler

/* Size of Transmission buffer */
#define TXSTARTMESSAGESIZE              (COUNTOF(aTxStartMessage) - 1)
#define TXENDMESSAGESIZE                (COUNTOF(aTxEndMessage) - 1)

/* Size of Reception buffer */
#define UARTHEADERSIZE 4
#define RXBUFFERSIZE 255

/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

/* Exported functions ------------------------------------------------------- */
void notify_uart(uint8_t* payloadString, int n);

extern UART_HandleTypeDef UartHandle;
extern uint8_t uart_header[UARTHEADERSIZE];

#endif /* __UART_SUPPORT_H */
