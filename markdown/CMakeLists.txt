add_library(markdown STATIC
        MarkdownParser.cpp
        MarkdownParser.h
        Lexer.cpp
        Lexer.h
        ../global/GlobalLogger.cpp
        ../global/GlobalLogger.h
        ../global/Markdown.h
        Utility.cpp
        Utility.h
        ../global/Markdown.cpp
        ../html/HtmlWriter.cpp
        ../html/HtmlWriter.h
)

target_include_directories(markdown
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(markdown PUBLIC global)