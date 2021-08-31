add_library(filter ip_filter.cpp)

#target_include_directories(filter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(filter PUBLIC cxx_std_14)