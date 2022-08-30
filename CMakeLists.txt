cmake_minimum_required(VERSION 3.16)

project(SisCtrlValve)

#set(CMAKE_CXX_FLAGS "--coverage")
#set(CMAKE_EXE_LINKER_FLAGS "--coverage")
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)
add_subdirectory(system)
add_subdirectory(networking)
add_subdirectory(thermostat)
add_subdirectory(valve)
add_subdirectory(tests)

target_link_libraries(libSystem nlohmann_json::nlohmann_json)

add_executable(sa_thermostat thermostat/src/main.cpp thermostat.conf)
add_executable(sa_valve valve/src/main.cpp valve.conf)

target_link_libraries(sa_thermostat libSystem)
target_link_libraries(sa_thermostat libNetworking)
target_link_libraries(sa_thermostat libThermostat)
target_link_libraries(sa_valve libSystem)
target_link_libraries(sa_valve libNetworking)
target_link_libraries(sa_valve libValve)

include(CTest)

#find_package(GTest REQUIRED CONFIG)

set_property(TARGET libNetworking libThermostat libValve sa_thermostat sa_valve PROPERTY CXX_STANDARD 17)

install(FILES thermostat.conf valve.conf DESTINATION /home/root COMPONENT config)
install(TARGETS sa_thermostat sa_valve DESTINATION bin)
