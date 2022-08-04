cmake_minimum_required(VERSION 3.16)

###############

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

################

enable_testing()

add_executable(Tests
IotDCPTest.cpp
HTTPTest.cpp
RequestTest.cpp
ResponseTest.cpp
UtilsTest.cpp
RouterTest.cpp
TcpClientTest.cpp
main.cpp)

target_include_directories(Tests PRIVATE ../networking/IotDCP)

target_link_libraries(Tests
    libNetworking
)

target_link_libraries(
    Tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Tests)

