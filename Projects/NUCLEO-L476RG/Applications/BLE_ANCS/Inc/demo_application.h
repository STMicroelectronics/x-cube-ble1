/**
  ******************************************************************************
  * @file    demo_application.h
  * @author  AMG RF Application team
  * @brief   Header file for demo_application.c
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
#ifndef __DEMO_APPLICATION_H__
#define __DEMO_APPLICATION_H__

/* Includes *********************************************************************/
#include "stdint.h"

/* Macros *********************************************************************/
/* Little Endian buffer to host endianness conversion */
#define LE_TO_HOST_16(ptr)  (uint16_t) ( ((uint16_t) \
                                           *((uint8_t *)ptr)) | \
                                          ((uint16_t) \
                                           *((uint8_t *)ptr + 1) << 8 ) )

uint8_t application_init(void);
uint8_t application_ADV_Start(void);
void APP_Tick(void);

#endif /* __DEMO_APPLICATION_H__ */
