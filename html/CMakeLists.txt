add_library(html STATIC
        HtmlWriter.cpp
        HtmlWriter.h
)
target_include_directories(html
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(html PUBLIC global)

target_compile_definitions(html PRIVATE
        SUBDIR_ASSET_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/"
)