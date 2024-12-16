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

target_link_libraries(unit_tests
    PRIVATE
    shop_lib
    gtest_main
    gmock_main
)

# Add tests to CTest
include(GoogleTest)
gtest_discover_tests(unit_tests)