cmake_minimum_required(VERSION 3.11)
project(Hyper-Paddle-Tests)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Our Project
add_executable(runTests
    test_ball.cpp
    ../src/GameObjects/Ball/Ball.c
    ../src/Systems/deltaTime.c
)

# Include directories
target_include_directories(runTests PRIVATE ../include)
target_include_directories(runTests PRIVATE ../src)


# Link libraries
target_link_libraries(runTests gtest_main raylib)
