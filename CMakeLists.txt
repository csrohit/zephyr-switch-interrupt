# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.20.0)
set(BOARD stm32_min_dev_blue)
set($ENV{ZEPHYR_BASE} /home/chin2/zephyrproject/zephyr)

# set variable before find_package line
find_package(Zephyr)
project(blink VERSION 0.0.1)

target_sources(app PRIVATE src/main.c)

    