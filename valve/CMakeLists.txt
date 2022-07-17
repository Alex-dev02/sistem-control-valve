cmake_minimum_required(VERSION 3.10)

add_executable(Valve 
../networking/socket/TcpListener.cpp
../networking/socket/TcpListener.hpp
../networking/socket/TcpClient.cpp
../networking/socket/TcpClient.hpp
../networking/router/Router.cpp
../networking/router/Router.hpp
../networking/IotDCP/IotDCP.cpp
../networking/IotDCP/IotDCP.hpp
../networking/IotDCP/Payload.cpp
../networking/IotDCP/Payload.hpp
../networking/IotDCP/HttpResponses.hpp
../networking/IotDCP/HttpResponses.cpp
../networking/socket/NetworkStream.hpp
../networking/socket/NetworkStream.cpp
src/Valve.hpp
src/Valve.cpp
src/main.cpp)