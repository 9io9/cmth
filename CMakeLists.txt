cmake_minimum_required(VERSION 3.25.1)

project(cmth VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_library(cmth STATIC src/calc.c)

target_include_directories(cmth PRIVATE include)

enable_testing()
add_subdirectory(test)