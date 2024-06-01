# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
   set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(PICO_SDK_PATH ${USERHOME}/.pico-sdk/sdk/1.5.1)
set(PICO_TOOLCHAIN_PATH ${USERHOME}/.pico-sdk/toolchain/13_2_Rel1)
if(WIN32)
    set(pico-sdk-tools_DIR ${USERHOME}/.pico-sdk/tools/1.5.1)
    include(${pico-sdk-tools_DIR}/pico-sdk-tools-config.cmake)
    include(${pico-sdk-tools_DIR}/pico-sdk-tools-config-version.cmake)
endif()
# ====================================================================================
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
    battery.c
)

target_include_directories(stock-ticker PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        )

pico_enable_stdio_usb(stock-ticker 1)
pico_enable_stdio_uart(stock-ticker 1)

pico_add_extra_outputs(stock-ticker)
target_link_libraries(stock-ticker
        hardware_adc
        hardware_gpio
        pico_stdlib
        pico_cyw43_arch_lwip_poll
        pico_lwip_mbedtls
        pico_mbedtls
        epd
        )