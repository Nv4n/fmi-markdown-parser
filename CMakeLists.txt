cmake_minimum_required(VERSION 3.15)
project(MarkdownParser VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(cli)
add_subdirectory(markdown)
add_subdirectory(tests)
add_subdirectory(html)
add_subdirectory(global)

add_executable(md_parser main.cpp)

target_link_libraries(md_parser
        PRIVATE
        cli
)