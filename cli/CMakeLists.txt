add_library(cli STATIC
        Cli.cpp
        Cli.h
)

target_include_directories(cli
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(cli PRIVATE markdown)