cmake_minimum_required(VERSION 3.10)

# Name of your project
project(CVM_Plus_Plus)

# Force the compiler to use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add all our .cpp files here to build the final executable named 'cvm'
add_executable(cvm main.cpp lexer.cpp)