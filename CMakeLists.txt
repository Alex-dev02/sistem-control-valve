cmake_minimum_required(VERSION 3.10)

project(SisCtrlValve)

add_subdirectory(termostat)
add_subdirectory(valve)

install(TARGETS Termostat Valve DESTINATION bin)
