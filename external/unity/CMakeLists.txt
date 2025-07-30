cmake_minimum_required(VERSION 3.14)
project(unity VERSION 2.4.1 LANGUAGES C)

include(FetchContent)

FetchContent_Declare(
    unity_repo
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG        v${PROJECT_VERSION}
)
FetchContent_MakeAvailable(unity_repo)

add_library(${PROJECT_NAME} STATIC
    ${unity_repo_SOURCE_DIR}/src/unity.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${unity_repo_SOURCE_DIR}/src
)
