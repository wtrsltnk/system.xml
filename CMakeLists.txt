cmake_minimum_required(VERSION 3.0)

project(system.xml)

option(BUILD_TESTS "Build test programs" OFF)

add_subdirectory(src)
add_subdirectory(example)
add_subdirectory(test)
