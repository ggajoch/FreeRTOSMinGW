cmake_minimum_required(VERSION 3.3)
project(protocol)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB FreeRTOSSrc
FreeRTOS/*.c
FreeRTOS/include/*.h
FreeRTOS/portable/*.c
FreeRTOS/portable/*.h
)


set(SOURCE_FILES main.cpp ${FreeRTOSSrc})
include_directories(. FreeRTOS/include FreeRTOS/portable)


add_executable(protocol ${SOURCE_FILES})


find_library(LIBWMM winmm)
target_link_libraries(protocol ${LIBWMM})