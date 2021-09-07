cmake_minimum_required(VERSION 3.10)

project(ip_filter CXX)

option(BUILD_TESTS "Build unittests" OFF)

include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(lib)

add_executable(ip_filter main.cpp)

target_link_libraries(ip_filter lib)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
