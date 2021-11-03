/**
  ******************************************************************************
  * @file    throughput_support.h
  * @author  SRA Application Team
  * @brief   Defines for throughput test
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
#ifndef __THROUGHPUT_SUPPORT_H__
#define __THROUGHPUT_SUPPORT_H__

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "stm32l4xx_hal.h"

/******************************************************************************
 * Macros
 *****************************************************************************/
/* Store Value into a buffer in Little Endian Format */
#define HOST_TO_LE_32(buf, val)    (((buf)[0] = (uint8_t) (val)     ) , \
                                    ((buf)[1] = (uint8_t) (val>>8)  ) , \
                                    ((buf)[2] = (uint8_t) (val>>16) ) , \
                                    ((buf)[3] = (uint8_t) (val>>24) )) 

#define LE_TO_HOST_32(ptr)   (uint32_t) ( ((uint32_t) \
                                          *((uint8_t *)ptr)) | \
                                          ((uint32_t) \
                                          *((uint8_t *)ptr + 1) << 8)  | \
                                          ((uint32_t) \
                                          *((uint8_t *)ptr + 2) << 16) | \
                                          ((uint32_t) \
                                          *((uint8_t *)ptr + 3) << 24) )

/******************************************************************************
 * Types
 *****************************************************************************/

/******************************************************************************
 * Function Prototypes
 *****************************************************************************/

#endif /* __THROUGHPUT_SUPPORT_H__ */
