cmake_minimum_required(VERSION 3.10)


include_directories(src "../thermostat" "../valve")
add_executable(Room src/main.cpp src/room.cpp src/room.hpp) 