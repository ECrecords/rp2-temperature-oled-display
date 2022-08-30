# Setting minimum version of CMake
cmake_minimum_required(VERSION 3.13)

# Include build function from Pico SDK
include(pico_sdk_import.cmake)

# Set project name and C/C++ standards
project(temp_visl C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Create a pico-sdk subdirectory in out project for the libraries
pico_sdk_init()

# find executable source file
add_executable(${PROJECT_NAME}
    main.c
    aht10.c
)

# enable/disable usb and uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# linking used libraries
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_i2c)