cmake_minimum_required(VERSION 3.10)

project(SisCtrlValve)

add_subdirectory(component)
add_subdirectory(thermostat)
add_subdirectory(valve)
add_subdirectory(sensor)
add_subdirectory(room)
add_subdirectory(room_manager)
add_subdirectory(scheduler)
add_subdirectory(date)

include_directories(component thermostat valve sensor room room_manager scheduler date)
link_directories(component thermostat valve sensor room room_manager scheduler date)

install(TARGETS Thermostat Valve Sensor Room RoomManager Scheduler Date DESTINATION bin)

