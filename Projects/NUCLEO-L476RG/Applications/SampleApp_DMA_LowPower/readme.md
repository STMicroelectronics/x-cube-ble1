
## <b>SampleApp_DMA_LowPower Application Description</b>

This application shows how to simply use the BLE Stack creating a client and server connection.

Example Description:

To test this application you need two STM32 Nucleo boards with their
respective BlueNRG STM32 expansion boards. One board needs to be configured
as Server-Peripheral role, while the other needs to be configured as Client-Central
role.
Before flashing the boards, please make sure to select the right configuration (SERVER
or CLIENT) for each board from your IDE;

During the connection and characteristic discovery phase the LED2 on the CLIENT is ON.
Once the previous procedure (which lasts about 40 seconds) has completed, the LED2 on
the CLIENT gets OFF.
The connection phase can be shortened by reducing the connection interval, but in this case
the power consumption will increase.
After connection has been established, by pressing the USER button on one board,
the micro on the other one gets toggled from RUN to STOP mode and viceversa.
Also, the USER button sets the STOP mode locally.

If you have only one STM32 Nucleo board, you can program it as SERVER and use as CLIENT
the BLE IOT app for Android devices available on the Play Store at
https://play.google.com/store/apps/details?id=com.stmicro.bleiot 
   
Current consumption could be monitored through an amperemeter connected to JP6.
This sample application uses the STM32 Cube Low Level low power optimizations
along with the DMA module for offloading the MCU.
The communication is done using a vendor specific profile.

### <b>Keywords</b>

BLE, Master, Slave, Central, Peripheral, SPI, DMA, Low Power, BlueNRG-M0, BlueNRG-MS

### <b>Directory contents</b>

 - app_service.c           Manage services using a vendor specific profile
 
 - cube_hal_**.c           System clock configuration
  
 - gp_timer.c              General purpose timer utilities
 
 - hci_tl.c                Functions for managing the HCI interface
  
 - hci_tl_interface.c      Interface to the BlueNRG HCI Transport Layer
 
 - low_power_conf_xx.c     Configure the system for power optimization
 
 - main.c                  Main program body
   
 - stm32**xx_hal_msp.c     Source code for MSP Initialization and de-Initialization

 - stm32**xx_it.c          Source code for interrupt Service Routines
 
 - system_stm32**xx.c      CMSIS Cortex-Mx Device Peripheral Access Layer
                           System Source File
						   
 - stm32xx_hal_app_rtc.c   Application specific HAL implementation (set the Wakeup clock source)

### <b>Hardware and Software environment</b>

  - This example runs on STM32 Nucleo boards with X-NUCLEO-IDB05A2 STM32 expansion board
    (the X-NUCLEO-IDB05A1 expansion board can be also used)
  - This example has been tested with STMicroelectronics:
    - NUCLEO-L476RG RevC board
    and can be easily tailored to any 
    other supported device and development board.

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
