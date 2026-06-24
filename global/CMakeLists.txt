add_library(global STATIC
        GlobalLogger.cpp
        GlobalLogger.h
        Markdown.h
        Markdown.cpp
)

target_include_directories(global PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})