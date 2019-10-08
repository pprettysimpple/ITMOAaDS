cmake_minimum_required(VERSION 3.14)
project(lab2 C)

#set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -fsanitize=address -fsanitize=undefined ")
#set(CMAKE_C_FLAGS "-Wall -fsanitize=address -fsanitize=undefined ")

set(CMAKE_C_STANDARD 11)

add_executable(lab2 A.c)