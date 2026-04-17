cmake_minimum_required(VERSION 3.10)

project(CVM_Plus_Plus)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ADDED parser.cpp HERE
add_executable(cvm main.cpp lexer.cpp parser.cpp)