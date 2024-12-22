enable_testing()

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Add test executable
add_executable(unit_tests
    test_main.cpp
)

target_include_directories(unit_tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(unit_tests
    PRIVATE
    shop_lib
    gtest
    gtest_main
    gmock
)

# Copy SQL files to test binary directory
file(COPY ${CMAKE_SOURCE_DIR}/sql/schema.sql 
     DESTINATION ${CMAKE_BINARY_DIR}/bin/sql)

# Add tests to CTest
include(GoogleTest)
gtest_discover_tests(unit_tests 
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)