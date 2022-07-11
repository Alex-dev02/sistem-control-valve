cmake_minimum_required(VERSION 3.10)

project(SisCtrlValve)

add_subdirectory(thermostat)
add_subdirectory(valve)
add_subdirectory(sensor)
add_subdirectory(component)
add_subdirectory(room)
add_subdirectory(room_manager)
add_subdirectory(scheduler)

install(TARGETS Thermostat Valve Sensor Room RoomManager Scheduler DESTINATION bin)
