cmake_minimum_required(VERSION 3.16)

project(SisCtrlValve)

add_subdirectory(networking)
add_subdirectory(thermostat)
add_subdirectory(valve)
add_subdirectory(tests)

include(CTest)

find_package(GTest REQUIRED CONFIG)

set_property(TARGET Thermostat Valve PROPERTY CXX_STANDARD 17)

install(TARGETS Thermostat Valve DESTINATION bin)
