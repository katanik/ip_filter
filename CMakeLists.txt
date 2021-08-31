cmake_minimum_required(VERSION 3.10)

project(ip_filter CXX)

option(BUILD_TESTS "Build unittests" OFF)

include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(filter)

add_executable(ip_filter main.cpp)

target_compile_features(ip_filter PUBLIC cxx_std_14)
target_link_libraries(ip_filter filter)
