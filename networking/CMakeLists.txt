cmake_minimum_required(VERSION 3.16)

add_library(Networking 
    IotDCP/IotDCP.cpp
    IotDCP/Request.cpp
    IotDCP/Response.cpp
    router/Router.cpp
    tcp/NetworkStream.cpp
    tcp/TcpListener.cpp
    tcp/TcpClient.cpp
)

target_include_directories(Networking PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/IotDCP> 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/router>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/tcp>
)
