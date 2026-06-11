cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(HW2_servo C CXX ASM)
set(CMAKE_C_STANDARD 11)

pico_sdk_init()

add_executable(HW2_servo main.c)

target_link_libraries(HW2_servo
    pico_stdlib
    hardware_pwm
    hardware_clocks
)

pico_add_extra_outputs(HW2_servo)
