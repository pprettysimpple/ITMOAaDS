cmake_minimum_required(VERSION 3.14)
project(lab1 C)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -pedantic -std=c++11 -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector")
set(CMAKE_C_STANDARD 11)

add_executable(lab1 H.c)