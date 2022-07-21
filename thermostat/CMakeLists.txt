cmake_minimum_required(VERSION 3.10)

add_executable(Thermostat 
../networking/tcp/TcpListener.cpp
../networking/tcp/TcpListener.hpp
../networking/tcp/TcpClient.cpp
../networking/tcp/TcpClient.hpp
../networking/tcp/NetworkStream.hpp
../networking/tcp/NetworkStream.cpp
../networking/router/Router.cpp
../networking/router/Router.hpp
../networking/IotDCP/IotDCP.cpp
../networking/IotDCP/IotDCP.hpp
../networking/IotDCP/Response.hpp
../networking/IotDCP/Response.cpp
../networking/IotDCP/Request.hpp
../networking/IotDCP/Request.cpp
src/Thermostat.cpp
src/Thermostat.hpp
src/main.cpp)

