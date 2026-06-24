add_library(markdown STATIC
        MarkdownParser.cpp
        MarkdownParser.h
        Lexer.cpp
        Lexer.h
        Utility.cpp
        Utility.h
)

target_include_directories(markdown
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(markdown PUBLIC global)