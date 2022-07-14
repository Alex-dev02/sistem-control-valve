cmake_minimum_required(VERSION 3.10)


include_directories(src)
set(SOURCES src/date.cpp)
add_executable(Date src/main.cpp src/date.cpp src/date.hpp) 