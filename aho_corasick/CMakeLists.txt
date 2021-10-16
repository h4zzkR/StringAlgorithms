cmake_minimum_required(VERSION 3.20)
project(aho_corasick)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        src/main.cpp
)

add_executable(aho_corasick ${SOURCES})
target_include_directories(aho_corasick
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)