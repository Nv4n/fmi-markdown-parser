add_library(cli STATIC
        Cli.cpp
        Cli.h
)

target_include_directories(cli
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(cli PUBLIC markdown)
target_link_libraries(cli PUBLIC global)
target_link_libraries(cli PUBLIC html)


target_compile_definitions(cli PRIVATE
        SUBDIR_ASSET_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/"
)

