cmake_minimum_required(VERSION 3.10)
project(lab03 C)

set(CMAKE_C_STANDARD 99)

include_directories(includes)

add_executable(lab03
    src/main.c
    src/child.c
    src/parent.c
    src/common.c
)
