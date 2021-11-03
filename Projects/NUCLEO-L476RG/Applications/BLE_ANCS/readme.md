
## <b>BLE_ANCS Application Description</b>

This application implements the Apple Notification Center Service (ANCS) showing how to
configure the BlueNRG-MS/BlueNRG-M0 module as a Notification Consumer device.

Example Description:

The purpose of the ANCS profile (BLE Notification Consumer role)
is to give Bluetooth accessories a simple and convenient way to access
many kinds of notifications that are generated on a Notification Provider.
The BLE_ANCS demo, after the reset, puts the BlueNRG-MS/BlueNRG-M0 in advertising
with device name "ANCSdemo", and it sets the BlueNRG-MS/BlueNRG-M0 authentication
requirements for enabling bonding.
When the device is connected and bonded with a Notification Provider,
the demo configures the BlueNRG-MS/BlueNRG-M0 Notification Consumer device
to discover the service and the characteristics of the Notification Provider.
When the setup phase is completed, the BlueNRG-MS/BlueNRG-M0 device is configured
as a Notification Consumer and is able to receive every notification
sent from the Notification Provider.
 
## <b>Keywords</b>

BLE, Peripheral, ANCS, Profile, SPI, BlueNRG-M0, BlueNRG-MS

### <b>Directory contents</b>

 - BLE_ANCS_main.c        Main program body
 
 - cube_hal_**.c          System clock configuration
 
 - demo_application.c     Application init and start
 
 - gp_timer.c             General purpose timer utilities
  
 - hci_tl_interface.c     Interface to the BlueNRG HCI Transport Layer 
   
 - stm32**xx_hal_msp.c    Source code for MSP Initialization and de-Initialization

 - stm32**xx_it.c         Source code for interrupt Service Routines
 
 - system_stm32**xx.c     CMSIS Cortex-Mx Device Peripheral Access Layer
                          System Source File
						  
 - uart_support.c         Generic functions for UART communication
 
 - user_timer.c           User timer management

### <b>Hardware and Software environment</b>

  - This example runs on STM32 Nucleo boards with X-NUCLEO-IDB05A2 STM32 expansion board
    (the X-NUCLEO-IDB05A1 expansion board can be also used)
  - This example has been tested with STMicroelectronics:
    - NUCLEO-L476RG RevC board
    and can be easily tailored to any other supported device and development board.

ADDITIONAL_BOARD : X-NUCLEO-IDB05A2 https://www.st.com/content/st_com/en/products/ecosystems/stm32-open-development-environment/stm32-nucleo-expansion-boards/stm32-ode-connect-hw/x-nucleo-idb05a2.html
ADDITIONAL_COMP : BlueNRG-M0 https://www.st.com/content/st_com/en/products/wireless-connectivity/short-range/bluetooth-low-energy-network-co-processors/bluenrg-m0.html

### <b>How to use it?</b>

In order to make the program work, you must do the following:
 - WARNING: before opening the project with any toolchain be sure your folder
   installation path is not too in-depth since the toolchain may report errors
   after building.
 - Open STM32CubeIDE (this firmware has been successfully tested with Version 1.7.0).
   Alternatively you can use the Keil uVision toolchain (this firmware
   has been successfully tested with V5.32.0) or the IAR toolchain (this firmware has 
   been successfully tested with Embedded Workbench V8.50.9).
 - Rebuild all files and load your image into target memory.
 - Run the example.
 - Alternatively, you can download the pre-built binaries in "Binary" 
   folder included in the distributed package.

### <b>Author</b>

SRA Application Team

### <b>License</b>

Copyright (c) 2021 STMicroelectronics.
All rights reserved.

This software is licensed under terms that can be found in the LICENSE file
in the root directory of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.
