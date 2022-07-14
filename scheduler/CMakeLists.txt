cmake_minimum_required(VERSION 3.10)


include_directories(src "../date")
add_executable(Scheduler src/main.cpp src/scheduler.cpp src/scheduler.hpp) 