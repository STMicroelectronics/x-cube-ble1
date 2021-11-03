# X-CUBE-BLE1 Firmware Package

![latest tag](https://img.shields.io/github/v/tag/STMicroelectronics/x-cube-ble1.svg?color=brightgreen)

The X-CUBE-BLE1 is an expansion software package for STM32Cube. This software provides drivers running on STM32 for STM’s BlueNRG-M0 Bluetooth Low Energy device. It also includes the software library for BLE Profiles along with many sample applications. This software package is built on top of STM32Cube software technology that ease portability across different STM32 microcontrollers.

**X-CUBE-BLE1 software features**:

- Complete middleware to build applications using BlueNRG-M0 network processor, including BLE standard Central and Peripheral profiles.
- Easy portability across different MCU families thanks to STM32Cube.
- Sample applications that the developer can use to start experimenting with the code.
- References to free Android and iOS Apps that can be used along with the sample applications.
- Free, user-friendly license terms.
- Examples implementation available for X-NUCLEO-IDB05A2 STM32 expansion board plugged on top of one NUCLEO-F401RE, NUCLEO-L053R8 or NUCLEO-L476RG.

The figure below shows the overall architecture.

[![X-CUBE-BLE1 Block Diagram](_htmresc/X-CUBE-BLE1_BlockDiagram_2020.png)]()

- At the bottom layer there are the HW components: the STM32 MCU and the BlueNRG-M0 network processor.
- The drivers abstract low level details of the hardware and allow the middleware software to provide Bluetooth LE features in a hardware independent fashion.
- The applications provide examples of how to use the code.

**Related information and documentation**:

- [UM1873](https://www.st.com/content/st_com/en/products/embedded-software/mcu-mpu-embedded-software/stm32-embedded-software/stm32cube-expansion-packages/x-cube-BLE1.html): Getting started with the X-CUBE-BLE1 Bluetooth Low Energy software expansion for STM32Cube
- [AN4642](https://www.st.com/content/st_com/en/products/embedded-software/mcu-mpu-embedded-software/stm32-embedded-software/stm32cube-expansion-packages/x-cube-BLE1.html): Overview of the BLE Profiles application for X-CUBE-BLE1, expansion for STM32Cube
- [STM32Cube](http://www.st.com/stm32cube)
- [STM32 Nucleo boards](http://www.st.com/stm32nucleo)
- [STM32 Nucleo expansion boards](http://www.st.com/x-nucleo)
