# Interrupts in Zephyr RTOS

![Build Passing](https://img.shields.io/badge/build-passing-brightgreen)
[![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/licenses/)

Interfacing push button with STM32 Blue Pill board and toggle a LED on button click by using interrupts.

## Run Locally

Clone the project

1. Using https

```bash
  git clone https://github.com/csrohit/zephyr-switch-interrupt
```

2. Using ssh

```bash
  git clone git@github.com:csrohit/zephyr-switch-interrupt.git
```

Go to the project directory

```bash
  cd zephyr-switch-interrupt
```

Compile Project

Setup zephyr environment on your machine from [Zephyr: Getting Started](https://docs.zephyrproject.org/latest/develop/getting_started/index.html)

```bash
  make all
```

Flash Binary

To flash you need to have

1. Openocd installed on your machine. You can do it from here: [Getting Openocd](https://openocd.org/pages/getting-openocd.html)
2. Connect Stlink to PC and blue pill board using swd headers.
3. Put blue pill board in programming mode

```bash
  make flash
```

* or you can flash the hex file using [STM32 Cube Programmer](https://docs.nanoframework.net/content/stm32/flash-cube-programmer.html)
