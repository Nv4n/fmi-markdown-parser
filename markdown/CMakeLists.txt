add_library(markdown STATIC
        MarkdownReader.h
        MarkdownReader.cpp
        MarkdownTree.h
        MarkdownTree.cpp
        Tokenizer.h
        Tokenizer.cpp
)

target_include_directories(markdown
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(markdown PRIVATE
        SUBDIR_ASSET_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/"
)