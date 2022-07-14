cmake_minimum_required(VERSION 3.10)


include_directories("../component" src)
add_executable(Valve src/main.cpp src/valve.cpp src/valve.hpp) 