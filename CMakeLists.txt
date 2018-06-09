cmake_minimum_required(VERSION 3.0)

project(system.xml)

option(BUILD_TESTS "Build test programs" OFF)

add_library(system.xml
    src/XmlAttribute.cpp
    src/XmlAttributeCollection.cpp
    src/XmlCDataSection.cpp
    src/XmlCharacterData.cpp
    src/XmlComment.cpp
    src/XmlDocument.cpp
    src/XmlDocumentType.cpp
    src/XmlElement.cpp
    src/XmlException.cpp
    src/XmlLinkedNode.cpp
    src/XmlLoader.cpp
    src/XmlLoader.h
    src/XmlName.cpp
    src/XmlNode.cpp
    src/XmlNodeList.cpp
    src/XmlProcessingInstruction.cpp
    src/XmlText.cpp
    src/XmlWriter.cpp
    src/XmlWriter.h
    )

target_include_directories(system.xml
    PUBLIC include
    )

target_compile_features(system.xml
    PRIVATE cxx_auto_type
    PRIVATE cxx_nullptr
    PRIVATE cxx_range_for
    )

add_executable(system.xml.example
    README.md
    src/program.cpp
    )

target_include_directories(system.xml.example
    PUBLIC include
    )

target_link_libraries(system.xml.example
    wsock32.lib
    system.xml
    )

if(BUILD_TESTS)
    add_executable(system.xml.tests
        tests/catch.cpp
        tests/xml-tests.cpp
        )

    target_link_libraries(system.xml.tests
        system.xml
        )

    target_compile_features(system.xml.tests
        PRIVATE cxx_auto_type
        PRIVATE cxx_nullptr
        )
endif(BUILD_TESTS)
