cmake_minimum_required(VERSION 3.16)


add_library(Valve
    src/Valve.cpp
    src/main.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Valve PRIVATE Threads::Threads)

target_include_directories(Valve PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src> 
)

