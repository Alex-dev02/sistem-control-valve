cmake_minimum_required(VERSION 3.16)

add_library(libNetworking
    communication/HTTP.cpp
    communication/Utils.cpp
    communication/IotDCP.cpp
    communication/Request.cpp
    communication/Response.cpp
    router/Router.cpp
    tcp/NetworkStream.cpp
    tcp/TcpListener.cpp
    tcp/TcpClient.cpp
)

target_include_directories(libNetworking PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/communication> 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/router>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/tcp>
)
