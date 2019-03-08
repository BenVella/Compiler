# cmake_minimum_required(VERSION <specify CMake version here>)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(Compiler main.cpp Lexer.h cmake-build-debug/Lexer.cpp)