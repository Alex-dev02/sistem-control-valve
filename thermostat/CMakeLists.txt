cmake_minimum_required(VERSION 3.16)

add_library(libThermostat
    src/thermostat_router.cpp
    src/thermostat.cpp
)

target_link_libraries(libThermostat PRIVATE libNetworking)

target_include_directories(libThermostat PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)
