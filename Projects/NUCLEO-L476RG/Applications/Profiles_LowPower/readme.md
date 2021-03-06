
## Profiles_LowPower Application Description

This sample application implements the BLE Peripheral Standard Profiles.
   
Example Description:

This application uses the STM32 Cube High Level APIs to set the low power modes.
Current consumption could be monitored through an ampere meter connected to JP6.

To test this application you need:
- an STM32 Nucleo board with its BlueNRG STM32 expansion board
- a Smartphone with Bluetooth Low Energy (BLE) chip and Android
  OS ≥ v4.3 or iOS ≥ v8.0.
The ST BLE Profile app is available:
- on Google Play Store at https://play.google.com/store/apps/details?id=com.stm.bluetoothlevalidation&hl=it
- on Apple App Store at https://apps.apple.com/it/app/stm32-ble-toolbox/id1081331769

This sample application configures the board as Server-Peripheral, while the
smartphone plays the Client-Central role.

To set/change the BLE Profile to test, change the value of the macro BLE_CURRENT_PROFILE_ROLES
(in the "active profile" section) in file:
$PATH_TO_THIS_PACKAGE$\Middlewares\ST\BlueNRG-MS\profiles\Peripheral\Inc\host_config.h

For example, if the HEART_RATE profile is set, after the connection between the
board and the smartphone has been established, the STM32_BLE_Profiles App will
show the Heart Rate values in bpm (beats per minute) coming from the STM32 Nucleo
board.

HID Profile
The HID profile can be used to emulate a
- Bluetooth Low Energy keyboard (KEYBOARD_IP macro enabled in hid_profile_application.c)
- Bluetooth Low Energy mouse (MOUSE_IP macro enabled in hid_profile_application.c)
connected to a smartphone.
Once the BLE device (i.e., the STM32 Nucleo board with its BlueNRG STM32 expansion board)
has been selected through the Bluetooth settings on the smartphone,
the user will be requested to type the PIN ("111111") to encrypt the link.
Keyboard use case:
Once the BLE device and the device are connected, the user can choose an editing app
and the sequence "AB" will be displayed every time the USER button is pressed on the BLE device.
Mouse use case:
Once the BLE device and the device are connected, the user can see the pointer on the smartphone screen
every time the USER button is pressed on the BLE device.

### Keywords

BLE, Peripheral, Profiles, SPI, Low Power, BlueNRG-M0, BlueNRG-MS

### Directory contents

 - *_profile_application.c Specific peripheral profile utilities
 
 - cube_hal_**.c           System clock configuration
  
 - gp_timer.c              General purpose timer utilities
 
 - hci_tl.c                Functions for managing the HCI interface
  
 - hci_tl_interface.c      Interface to the BlueNRG HCI Transport Layer
 
 - low_power_conf_xx.c     Configure the system for power optimization
 
 - main.c                  Main program body
 
 - profile_application.c   Generic functions executing the BLE profile
   
 - stm32**xx_hal_msp.c     Source code for MSP Initialization and de-Initialization

 - stm32**xx_it.c          Source code for interrupt Service Routines
 
 - system_stm32**xx.c      CMSIS Cortex-Mx Device Peripheral Access Layer System Source File
						   
 - stm32xx_hal_app_rtc.c   Application specific HAL implementation (set the Wakeup clock source)

### Hardware and Software environment

  - This example runs on STM32 Nucleo boards with X-NUCLEO-IDB05A2 STM32 expansion board
    (the X-NUCLEO-IDB05A1 expansion board can be also used)
  - This example has been tested with STMicroelectronics:
    - NUCLEO-L476RG RevC board
    and can be easily tailored to any other supported device and development board.

ADDITIONAL_BOARD : X-NUCLEO-IDB05A2 https://www.st.com/content/st_com/en/products/ecosystems/stm32-open-development-environment/stm32-nucleo-expansion-boards/stm32-ode-connect-hw/x-nucleo-idb05a2.html
ADDITIONAL_COMP : BlueNRG-M0 https://www.st.com/content/st_com/en/products/wireless-connectivity/short-range/bluetooth-low-energy-network-co-processors/bluenrg-m0.html
    
### How to use it?

In order to make the program work, you must do the following:
 - WARNING: before opening the project with any toolchain be sure your folder
   installation path is not too in-depth since the toolchain may report errors
   after building.
 - WARNING: because the application is configured in low power mode, the
   debug feature of your toolchain cannot be used.
   For using debugging you must disable the low power configuration
   (set macro LOW_POWER_ENABLED to 0 in $PATH_TO_THIS_APPLICATION\Src\main.c).
 - Open STM32CubeIDE (this firmware has been successfully tested with Version 1.8.0).
   Alternatively you can use the Keil uVision toolchain (this firmware
   has been successfully tested with V5.32.0) or the IAR toolchain (this firmware has 
   been successfully tested with Embedded Workbench V8.50.9).
 - Rebuild all files and load your image into target memory.
 - Run the example.
 - Alternatively, you can download the pre-built binaries in "Binary" 
   folder included in the distributed package.

### Author

SRA Application Team

### License

Copyright (c) 2022 STMicroelectronics.
All rights reserved.

This software is licensed under terms that can be found in the LICENSE file
in the root directory of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.
