
## <b>SampleAppThT Application Description</b>

This application shows how to use BlueNRG Bluetooth Low Energy 
stack and to measure the application throughput.

Example Description:

To test this application you need two STM32 Nucleo boards with their
respective BlueNRG STM32 expansion boards. One board needs to be configured
as Server-Peripheral role, while the other needs to be configured as Client-Central
role.
Before flashing the boards, please make sure to use the right configuration by selecting
it from the menu options of the toolchain.

Selecting the "SampleApp_*" configurations allows to target the SampleApp.
 - Program the CLIENT on one STM32 Nucleo board, with BlueNRG STM32 expansion board,
   and reset it (configuration: SampleApp_CLIENT). 
 - Program the SERVER on a second STM32 Nucleo board, with BlueNRG STM32 expansion
   board, and reset it (configuration: SampleApp_SERVER). 
 - After establishing the connection between the two boards (when the LED2 on the
   CLIENT turns off),
   by pressing the USER button on one board, the LD2 LED on the other one gets toggled
   and viceversa.
   No serial terminal emulator must be open since no throughput test is performed.
 - If you have only one STM32 Nucleo board, you can program it as SERVER and use as CLIENT
   the BLE IOT app for Android devices available on the Play Store at
   https://play.google.com/store/apps/details?id=com.stmicro.bleiot 

Selecting the "ThroughputTest_*" configurations allows to perform a throughput test.
 - Program the CLIENT on one STM32 Nucleo board, with BlueNRG STM32 expansion board,
   and reset it (configuration: ThroughputTest_CLIENT).
   The platform will be seen on the PC as a virtual COM port. Open the port in a serial terminal emulator
   (Word Length = 8 Bits, Stop Bit = One Stop bit, Parity = ODD parity, BaudRate = 115200 baud,
   Hardware flow control disabled (RTS and CTS signals)).
 - Program the SERVER on a second STM32 Nucleo board, with BlueNRG STM32 expansion
   board, and reset it (configuration: ThroughputTest_SERVER).
   The two boards will try to establish a connection.
 - During the connection and characteristics discovery phase the LED2 on the CLIENT
   is ON.
   Once the connection between the two boards is established, the LED2 on the CLIENT turns OFF.
 - The throughput test can be started by pressing the USER button on the the Server-Peripheral board.
   The Server-Peripheral will continuously send notifications of 20 bytes to the Client-Central.
 - After every 500 packets, the measured application throughput will be displayed on the terminal emulator.  
 - IMPORTANT NOTE: To avoid issues with USB connection (mandatory if you have USB 3.0), it is   
   suggested to update the ST-Link/V2 firmware for STM32 Nucleo boards to the latest version.
 - WARNING: When using the NUCLEO-L053R8 boards the Throughput test may fails. No problem occurs
   when using NUCLEO-F401RE or NUCLEO-L476RG boards.

### <b>Keywords</b>

BLE, Master, Slave, Central, Peripheral, SPI, Throughput, BlueNRG-M0, BlueNRG-MS

### <b>Directory contents</b>

 - cube_hal_**.c           System clock configuration
  
 - gp_timer.c              General purpose timer utilities
 
 - hci_tl.c                Functions for managing the HCI interface
  
 - hci_tl_interface.c      Interface to the BlueNRG HCI Transport Layer
 
 - low_power_conf_xx.c     Configure the system for power optimization
 
 - main.c                  Main program body
 
 - sample_service.c        Manage services using a vendor specific profile
   
 - stm32**xx_hal_msp.c     Source code for MSP Initialization and de-Initialization

 - stm32**xx_it.c          Source code for interrupt Service Routines
 
 - system_stm32**xx.c      CMSIS Cortex-Mx Device Peripheral Access Layer
                           System Source File
 
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
