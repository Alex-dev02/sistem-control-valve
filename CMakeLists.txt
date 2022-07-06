cmake_minimum_required(VERSION 3.10)

project(SisCtrlValve)

add_subdirectory(thermostat)
add_subdirectory(valve)
add_subdirectory(iot_node)

install(TARGETS Thermostat Valve IotNode DESTINATION bin)
