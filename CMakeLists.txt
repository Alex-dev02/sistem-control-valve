cmake_minimum_required(VERSION 3.10)

project(SisCtrlValve)

add_subdirectory(thermostat)
add_subdirectory(valve)

install(TARGETS Thermostat Valve DESTINATION bin)
