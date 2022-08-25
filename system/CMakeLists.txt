cmake_minimum_required(VERSION 3.16)

add_library(libSystem
    system.cpp
    config_parser.cpp
)

target_link_libraries(libSystem
    libNetworking
)

target_include_directories(libSystem PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/>
)
