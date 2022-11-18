cmake_minimum_required(VERSION 3.24.3)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(maritime-testing)

# if you have an include directory, you can include it here
# target_include_directories(app PRIVATE include)

FILE(GLOB app_sources
     #src/main.c
     # src/uart_poll.c
     src/uart_dvl.c
)

target_sources(app PRIVATE ${app_sources})
