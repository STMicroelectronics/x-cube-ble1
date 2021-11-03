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

void PRINT_MESG_UART(const char * format, ... );

#define PRINTF PRINT_MESG_UART

/* Exported constants --------------------------------------------------------*/

/* Size of Transmission buffer */
#define TXSTARTMESSAGESIZE                 (COUNTOF(aTxStartMessage) - 1)
#define TXENDMESSAGESIZE                   (COUNTOF(aTxEndMessage) - 1)

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
