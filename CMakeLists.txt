cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(stock-ticker C CXX ASM)
set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_subdirectory(epd)

include_directories(epd/Config)
include_directories(epd/GUI)
include_directories(epd/e-Paper)

add_executable(stock-ticker
    main.c
    ticker.c
    ticker_display.c
)

pico_enable_stdio_usb(stock-ticker 1)
pico_enable_stdio_uart(stock-ticker 1)

pico_add_extra_outputs(stock-ticker)
target_link_libraries(stock-ticker pico_stdlib epd)