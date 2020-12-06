cmake_minimum_required(VERSION 3.9)
project(playground CXX)
set(CMAKE_CXX_STANDARD 17)

set(CARROT_DB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()
add_subdirectory(vendor)
add_subdirectory(cmd)
add_subdirectory(src)
add_subdirectory(test)