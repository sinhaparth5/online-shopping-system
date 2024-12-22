cmake_minimum_required(VERSION 3.10)
project(OnlineShop VERSION 1.0)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# C++ standard requirements
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use pkg-config to find SQLite3
find_package(OpenSSL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SQLite3 REQUIRED IMPORTED_TARGET sqlite3)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)

configure_file(${CMAKE_SOURCE_DIR}/sql/schema.sql ${CMAKE_BINARY_DIR}/sql/schema.sql COPYONLY)