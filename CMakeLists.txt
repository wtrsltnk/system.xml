cmake_minimum_required(VERSION 3.0)

project(system.xml)

option(BUILD_TESTS "Build test programs" OFF)

add_executable(system.xml
    README.md
    src/program.cpp
    src/xml.cpp
    )

target_include_directories(system.xml
    PUBLIC include
    )

target_link_libraries(system.xml
    wsock32.lib
    )

if(BUILD_TESTS)
    add_executable(xml-tests
        src/xml.cpp
        tests/catch.cpp
        tests/xml-tests.cpp
        )

    target_include_directories(xml-tests
        PUBLIC include
        )
endif(BUILD_TESTS)
