add_library(lib ip_list.cpp ip_data.cpp filter.cpp)

target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(lib PUBLIC cxx_std_14)