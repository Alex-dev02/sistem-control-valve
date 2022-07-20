cmake_minimum_required(VERSION 3.10)

add_executable(Thermostat 
../networking/socket/TcpListener.cpp
../networking/socket/TcpListener.hpp
../networking/socket/TcpClient.cpp
../networking/socket/TcpClient.hpp
../networking/router/Router.cpp
../networking/router/Router.hpp
../networking/IotDCP/IotDCP.cpp
../networking/IotDCP/IotDCP.hpp
../networking/IotDCP/Response.hpp
../networking/IotDCP/Response.cpp
../networking/IotDCP/Request.hpp
../networking/IotDCP/Request.cpp
../networking/socket/NetworkStream.hpp
../networking/socket/NetworkStream.cpp
src/Thermostat.cpp
src/Thermostat.hpp
src/main.cpp)

