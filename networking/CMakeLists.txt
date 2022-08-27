cmake_minimum_required(VERSION 3.16)

add_library(libNetworking
    http.cpp
    utils.cpp
    iot_dcp.cpp
    request.cpp
    response.cpp
    router.cpp
    network_stream.cpp
    tcp_listener.cpp
    tcp_client.cpp
    endpoint.cpp
)

target_include_directories(libNetworking PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/> 
)

# install(TARGETS libNetworking DESTINATION usr/local/bin)
