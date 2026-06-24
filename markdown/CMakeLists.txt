add_library(markdown STATIC
        Parser.cpp
        Parser.h
        Lexer.cpp
        Lexer.h
        GlobalLogger.cpp
        GlobalLogger.h
        Markdown.h
        Utility.cpp
        Utility.h
)

target_include_directories(markdown
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)


target_compile_definitions(markdown PRIVATE
        SUBDIR_ASSET_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/"
)