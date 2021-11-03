/**
  ******************************************************************************
  * @file    stm32l4xx_it.c
  * @author  MCD Application Team
  * @brief   Interrupt Service Routines
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

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_it.h"
#include "low_power_conf.h"
#include "debug.h"

/** @addtogroup Applications
 *  @{
 */

/** @addtogroup Profiles_DMA_LowPower
 *  @{
 */

/** @defgroup INTERRUPT_HANDLER
 *  @{
 */

 extern volatile uint8_t send_measurement;
 
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint32_t ms_counter = 0;
/* SPI handler declared in "main.c" file */
extern SPI_HandleTypeDef SpiHandle;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
  
  ms_counter++;
}

/******************************************************************************/
/*                 STM32L4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l4xx.s).                                               */
/******************************************************************************/
/**
  * @brief  This function handles RTC Auto wake-up interrupt request.
  * @param  None
  * @retval None
  */
void RTC_WAKEUP_IRQHandler(void)
{
  TIMER_RTC_Wakeup_Handler();
}

/**
  * @brief  This function handles External line
  *         interrupt request for BlueNRG.
  * @param  None
  * @retval None
  */
void BNRG_SPI_EXTI_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(BNRG_SPI_EXTI_PIN);
}

/**
  * @brief  This function handles External line
  *         interrupt request.
  * @param  None
  * @retval None
  */
void PUSH_BUTTON_EXTI_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(KEY_BUTTON_PIN);
  
  // FIXME: this should be moved in the proper callback called by Cube HAL
  send_measurement++;
}

/**
  * @brief  This function handles DMA Rx interrupt request.  
  * @param  None
  * @retval None    
  */
void DMA1_Channel2_IRQHandler(void)
{
  if(__HAL_DMA_GET_IT_SOURCE(SpiHandle.hdmarx, DMA_IT_TC)  && __HAL_DMA_GET_FLAG(SpiHandle.hdmarx, DMA_FLAG_TC2))
  {
    BlueNRG_DMA_RxCallback();
  }
}

/**
  * @brief  This function handles DMA Tx interrupt request.  
  * @param  None
  * @retval None    
  */
void DMA1_Channel3_IRQHandler(void)
{
  if(__HAL_DMA_GET_IT_SOURCE(SpiHandle.hdmatx, DMA_IT_TC)  && __HAL_DMA_GET_FLAG(SpiHandle.hdmatx, DMA_FLAG_TC3))
  {
    BlueNRG_DMA_TxCallback();
  }
}

/******************************************************************************/
/*                 STM32L4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*
void PPP_IRQHandler(void)
{
}
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
