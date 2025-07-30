cmake_minimum_required(VERSION 3.11)
project(ArduinoFake VERSION 0.1)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FetchContent_Declare(
    fakeit_repo
    GIT_REPOSITORY https://github.com/eranpeer/FakeIt.git
    GIT_TAG        2.4.0
)

FetchContent_Declare(
    unity_repo
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG        v2.4.1
)

FetchContent_MakeAvailable(fakeit_repo)
FetchContent_MakeAvailable(unity_repo)  

# Include external libs
add_library(fakeit STATIC
    ${unity_repo_SOURCE_DIR}/src/unity.c
)

target_include_directories(fakeit PUBLIC
    ${unity_repo_SOURCE_DIR}/src
)

add_library(unity INTERFACE)

target_include_directories(unity INTERFACE
    ${fakeit_repo_SOURCE_DIR}/single_header/standalone/
)


# Targets that we develop here
enable_testing()

add_subdirectory(src)
add_subdirectory(test)
