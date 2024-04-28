cmake_minimum_required(VERSION 3.12)

# add a compilation subdirectory
add_subdirectory(Config)
add_subdirectory(e-Paper)
add_subdirectory(Fonts)
add_subdirectory(GUI)

# add a header directory
include_directories(Config)
include_directories(GUI)

add_library(epd)

target_link_libraries(epd ePaper GUI Fonts Config pico_stdlib hardware_spi)