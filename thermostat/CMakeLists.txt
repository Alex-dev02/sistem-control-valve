cmake_minimum_required(VERSION 3.16)

add_library(libThermostat
    src/thermostat_router.cpp
    src/thermostat.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(libThermostat PRIVATE Threads::Threads)
target_link_libraries(libThermostat PRIVATE libNetworking)
target_link_libraries(libThermostat PRIVATE libSystem)

target_include_directories(libThermostat PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
)
