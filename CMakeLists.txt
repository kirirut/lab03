cmake_minimum_required(VERSION 3.10)
project(ParentChild C)

set(CMAKE_C_STANDARD 99)

include_directories(includes)

# Define the child executable
add_executable(child
    src/child.c
)

# Define the parent executable
add_executable(parent
    src/parent.c
)

# Ensure child is built before parent (since parent spawns child)
add_dependencies(parent child)