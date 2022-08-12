cmake_minimum_required(VERSION 3.16)

add_library(libSystem
    system.cpp
)

target_include_directories(libSystem PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/>
)
