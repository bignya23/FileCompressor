
cmake_minimum_required(VERSION 3.30)
project(filecompressor)

set(CMAKE_CXX_STANDARD 20)

add_executable(filecompressor src/main.cpp
        src/huffman.cpp
        src/rle.cpp
        src/deflate.cpp
        src/headers/huffman.hpp)
