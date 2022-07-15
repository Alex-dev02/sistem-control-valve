cmake_minimum_required(VERSION 3.10)

add_executable(Valve 
../networking/socket/TcpListener.cpp
../networking/socket/TcpListener.hpp
../networking/socket/TcpClient.cpp
../networking/socket/TcpClient.hpp
src/Valve.hpp
src/Valve.cpp
src/main.cpp)