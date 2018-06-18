
if(BUILD_TESTS)
    add_executable(system.xml.tests
        catch.cpp
        xml-tests.cpp
        )

    target_link_libraries(system.xml.tests
        system.xml
        )

    target_compile_features(system.xml.tests
        PRIVATE cxx_auto_type
        PRIVATE cxx_nullptr
        )
endif(BUILD_TESTS)
