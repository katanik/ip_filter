include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

configure_file( sort_test_result.txt ${CMAKE_BINARY_DIR}/tests/sort_test_result.txt )
configure_file( sort_test_result.txt ${CMAKE_BINARY_DIR}/tests/ip1_result.txt )
configure_file( sort_test_result.txt ${CMAKE_BINARY_DIR}/tests/ip2_result.txt )
configure_file( sort_test_result.txt ${CMAKE_BINARY_DIR}/tests/ip3_result.txt )
configure_file( sort_test_result.txt ${CMAKE_BINARY_DIR}/tests/ip_result.tsv )

add_executable(ip_filter-tests test_ip_filter.cpp)

target_link_libraries(ip_filter-tests gtest_main)
target_link_libraries(ip_filter-tests lib)

add_custom_target(
    test $<TARGET_FILE:ip_filter-tests> 
    DEPENDS ip_filter-tests
)
