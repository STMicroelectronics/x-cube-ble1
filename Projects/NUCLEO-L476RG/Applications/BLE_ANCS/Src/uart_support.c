/**
  ******************************************************************************
  * @file    uart_support.c
  * @author  SRA Application Team
  * @brief   This file implements the generic functions for UART communication
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
/*******************************************************************************
 * Include Files
*******************************************************************************/
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <bluenrg_types.h>
#include <hci_tl.h>
#include "bluenrg_conf.h"

#include "hci_tl_interface.h"
#include "uart_support.h"

/** @addtogroup Applications
 *  @{
 */

/** @defgroup SampleAppThT
 *  @{
 */
 
/** @defgroup UART_SUPPORT 
 * @{
 */
 
/*******************************************************************************
 * Macros
*******************************************************************************/

/******************************************************************************
 * Local Variable Declarations
******************************************************************************/

/** @defgroup UART_SUPPORT_Exported_Variables
 *  @{
 */
/******************************************************************************
 * Global Variable Declarations
******************************************************************************/

extern UART_HandleTypeDef UartHandle;
uint8_t uart_header[UARTHEADERSIZE];
uint8_t aRxBuffer[RXBUFFERSIZE];

void *profiledbgfile;
extern void _Error_Handler(char *, int);
/**
 * @}
 */
 
/******************************************************************************
 * Function Declarations
******************************************************************************/

/** @defgroup UART_SUPPORT_Functions
 *  @{
 */
/******************************************************************************
 * Function Definitions 
******************************************************************************/
uint8_t uartReceiveChar(void)
{
  uint8_t ch;
  HAL_UART_Receive(&UartHandle, &ch, 1, HAL_MAX_DELAY);
  
  /* Echo character back to console */
  HAL_UART_Transmit(&UartHandle, &ch, 1, HAL_MAX_DELAY);

  /* And cope with Windows */
  if(ch == '\r'){
    uint8_t ret = '\n';
    HAL_UART_Transmit(&UartHandle, &ret, 1, HAL_MAX_DELAY);
  }

  return ch;
}

/**
 * @brief
 * @param
 */
void PRINT_MESG_UART(const char * format, ... )
{
  va_list ap;
  uint8_t buffer [128];
  int n;
  
  va_start(ap, format);
  n = vsnprintf ((char*)buffer, 128, format, ap);
  va_end(ap);
  
  //notify_uart(buffer, n);
  if(HAL_UART_Transmit(&UartHandle, (uint8_t*)buffer, n, 300) != HAL_OK) {    
    _Error_Handler(__FILE__, __LINE__);
  }
}

uint8_t GETCHAR_UART(void)
{
  return uartReceiveChar();
}

void notify_uart(uint8_t* payloadString, int n)
{
  if(HAL_UART_Transmit(&UartHandle, (uint8_t*)payloadString, n, 300) != HAL_OK) {    
    _Error_Handler(__FILE__, __LINE__);
  }
}

static void wait(void)
{
  volatile uint32_t i;
  for (i=0; i<200000; i++) __NOP();
}

static void blink_led(void)
{
  BSP_LED_Toggle(LED2);
  wait();
  BSP_LED_Toggle(LED2); 
  wait();
}

/**
  * @brief  UART error callbacks
  * @note   This example shows a simple way to report transfer error, and you can
  *         add your own implementation.
  * @param  UART handle pointer  
  * @retval None
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
  blink_led();
  //PRINTF("HAL_UART_ErrorCallback\n");
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
