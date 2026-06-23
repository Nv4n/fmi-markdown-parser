add_library(tests STATIC
        test_lexer.cpp
        test_parser.cpp
)

target_include_directories(tests
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)