cmake_minimum_required(VERSION 3.10)


include_directories(src "../component" "../sensor")
add_executable(Thermostat src/main.cpp src/thermostat.cpp src/thermostat.hpp) 