cmake_minimum_required(VERSION 3.16)

add_library(libNetworking
    communication/http.cpp
    communication/utils.cpp
    communication/iot_dcp.cpp
    communication/request.cpp
    communication/response.cpp
    router/router.cpp
    tcp/network_stream.cpp
    tcp/tcp_listener.cpp
    tcp/tcp_client.cpp
)

target_include_directories(libNetworking PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/communication> 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/router>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/tcp>
)
