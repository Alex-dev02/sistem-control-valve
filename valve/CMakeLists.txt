cmake_minimum_required(VERSION 3.16)


add_library(libValve
    src/Valve.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(libValve PRIVATE Threads::Threads)

target_include_directories(libValve PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src> 
)

