cmake_minimum_required(VERSION 3.10)

project(SisCtrlValve)

add_subdirectory(thermostat)
add_subdirectory(valve)

set_property(TARGET Thermostat Valve PROPERTY CXX_STANDARD 17)

install(TARGETS Thermostat Valve DESTINATION bin)
