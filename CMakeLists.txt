cmake_minimum_required(VERSION 3.10)

project(SisCtrlValve)

add_subdirectory(thermostat)
add_subdirectory(valve)
add_subdirectory(sensor)
add_subdirectory(component)


install(TARGETS Thermostat Valve Sensor DESTINATION bin)
