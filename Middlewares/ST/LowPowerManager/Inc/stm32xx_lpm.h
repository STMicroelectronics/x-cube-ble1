/**
  ******************************************************************************
  * @file    stm32xx_lpm.h
  * @author  MCD Application Team
  * @brief   Header for stm32xx_lpm.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2014 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#ifndef __STM32xx_LPM_H
#define __STM32xx_LPM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32xx_lpm_conf.h"

/** @addtogroup Middlewares
 *  @{
 */

/** @addtogroup ST
 *  @{
 */
 
/** @addtogroup LowPowerManager
 *  @{
 */

/** @addtogroup STM32XX_LPM 
 * @{
 */

/** @defgroup STM32XX_LPM_Exported_Types
 * @{
 */
/* Exported types ------------------------------------------------------------*/

/**
  * MCU Low Power Mode supported
  */
typedef enum
{
  eLPM_Mode_Sleep   = 0x00,	/**< DEEPSLEEP=0, LPSDR=0, PDDS=0 */
  eLPM_Mode_Stop    = 0x04,	/**< DEEPSLEEP=1, LPSDR=0, PDDS=0 */
  eLPM_Mode_LP_Stop = 0x06,	/**< DEEPSLEEP=1, LPSDR=1, PDDS=0 */
  eLPM_Mode_StandBy = 0x07,	/**< DEEPSLEEP=1, LPSDR=1, PDDS=1 */
  eLPM_Mode_RUN     = 0x08
} eLPM_Mode;

/*
 * Supported requester to the MCU Low Power Manager - can be increased up  to 32
 */
typedef enum
{
  eLPM_SPI_TX,
  eLPM_SPI_RX,
  eLPM_MAIN_LOOP_PROCESSES
} eLPM_Id;

/**
 * @}
 */
 
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/

/** @defgroup STM32XX_LPM_Exported_Function_Prototypes
 * @{
 */
/* Exported functions ------------------------------------------------------- */
void LPM_Mode_Request(eLPM_Id eId, eLPM_Mode eMode);
void LPM_Enter_Mode(void);
void LPM_ExitStopMode(void);
void LPM_EnterStandbyMode(void);
void LPM_ExitStandbyMode(void);

/**
 * @}
 */
 
/* Compiler specific definition ------------------------------------------------------- */

 /*
 * Define the WEAK intrinsinc
  */
#if defined ( __CC_ARM )
#define WEAK __weak
#elif defined ( __ICCARM__ )
#define WEAK __weak
#elif defined ( __GNUC__ )
#define WEAK __attribute__((weak))
#endif

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

#endif /* __STM32xx_LPM_H */
