cmake_minimum_required(VERSION 3.16)

add_library(Thermostat
    src/Thermostat.cpp
    src/main.cpp
)

target_include_directories(Thermostat PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src> 
)
