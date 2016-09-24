cmake_minimum_required(VERSION 2.8)

project(SystemXml)

option(BUILD_TESTS "Build test programs" OFF)

set(info
    README.txt
    TODO.txt
    CHANGELOG.txt
)

set(SRC_CLIENT
    src/program.cpp
    src/xml.cpp
)

if(BUILD_TESTS)
    set(SRC_XML_TESTS
        src/xml.cpp
        src/test_framework.cpp
    )
endif(BUILD_TESTS)

add_executable(SystemXml ${SRC_CLIENT} ${info})
target_link_libraries(SystemXml wsock32.lib)

if(BUILD_TESTS)
    add_executable(xml-tests ${SRC_XML_TESTS} ${info})
endif(BUILD_TESTS)
