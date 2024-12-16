cmake_minimum_required(VERSION 3.10)
project(OnlineShop VERSION 1.0)

# C++ standard requirements
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use pkg-config to find SQLite3
find_package(PkgConfig REQUIRED)
pkg_check_modules(SQLite3 REQUIRED IMPORTED_TARGET sqlite3)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)