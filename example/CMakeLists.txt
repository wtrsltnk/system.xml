
add_executable(system.xml.example
    program.cpp
    )

target_include_directories(system.xml.example
    PUBLIC
        ../include
    )

target_link_libraries(system.xml.example
    wsock32.lib
    system.xml
    )
