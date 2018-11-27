cmake_minimum_required(VERSION 3.3.2)

project(test-libexample)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME} "src/test-libexample.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE example)
set_target_properties(${PROJECT_NAME} PROPERTIES
    LANGUAGES CXX
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    )
