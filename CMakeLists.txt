cmake_minimum_required(VERSION 3.10)

project(SisCtrlValve)

add_subdirectory(thermostat)
add_subdirectory(valve)

set_property(TARGET Thermostat Valve PROPERTY CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

install(TARGETS Thermostat Valve DESTINATION bin)

enable_testing()

add_executable(
  first_test
  tests/first_test.cpp
)
target_link_libraries(
  first_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(first_test)

