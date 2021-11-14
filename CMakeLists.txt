cmake_minimum_required(VERSION 3.10)
project(flashcard)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(flc VERSION 0.1.0)

add_executable(flc src/main.cpp)
