cmake_minimum_required(VERSION 3.10)

add_executable(Thermostat 
../networking/socket/TcpListener.cpp
../networking/socket/TcpListener.hpp
../networking/socket/TcpClient.cpp
../networking/socket/TcpClient.hpp
../networking/router/Router.cpp
../networking/router/Router.hpp
../networking/http/HTTP.cpp
../networking/http/HTTP.hpp
../networking/http/Payload.cpp
../networking/http/Payload.hpp
../networking/socket/NetworkStream.hpp
../networking/socket/NetworkStream.cpp
src/Thermostat.cpp
src/Thermostat.hpp
src/main.cpp)

