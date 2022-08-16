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
iot_dcp_test.cpp
http_test.cpp
request_test.cpp
response_test.cpp
utils_test.cpp
router_test.cpp
tcp_client_test.cpp
endpoint_test.cpp
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

