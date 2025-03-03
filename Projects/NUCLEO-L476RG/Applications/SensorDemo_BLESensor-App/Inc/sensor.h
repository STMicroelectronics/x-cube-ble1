/**
  ******************************************************************************
  * @file    sensor.h
  * @author  SRA Application Team
  * @brief   Header file for sensor.c
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>

#define IDB04A1 0
#define IDB05A1 1
#define SENSOR_DEMO_NAME   'B','l','u','e','N','R','G'
#define BDADDR_SIZE        6

void Set_DeviceConnectable(void);
void user_notify(void * pData);

extern uint8_t Application_Max_Attribute_Records[];

#endif /* SENSOR_H */
