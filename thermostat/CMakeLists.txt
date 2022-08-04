cmake_minimum_required(VERSION 3.16)

add_library(libThermostat
    src/thermostat.cpp
)

target_include_directories(libThermostat PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src> 
)
