add_library(markdown STATIC
        MarkdownParser.cpp
        MarkdownParser.h
        Lexer.cpp
        Lexer.h
        GlobalLogger.cpp
        GlobalLogger.h
        Markdown.h
        Utility.cpp
        Utility.h
        Markdown.cpp
)

target_include_directories(markdown
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)


target_compile_definitions(markdown PRIVATE
        SUBDIR_ASSET_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/"
)