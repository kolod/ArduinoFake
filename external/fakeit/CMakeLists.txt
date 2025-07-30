cmake_minimum_required(VERSION 3.14)
project(fakeit VERSION 2.4.0 LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    fakeit_repo
    GIT_REPOSITORY https://github.com/eranpeer/FakeIt.git
    GIT_TAG        ${PROJECT_VERSION}
)

FetchContent_MakeAvailable(fakeit_repo)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
    ${fakeit_repo_SOURCE_DIR}/single_header/standalone/
)
