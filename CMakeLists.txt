cmake_minimum_required(VERSION 3.10)
project(HeatSolver)

set(CMAKE_CXX_STANDARD 17)

add_executable(main
    src/main.cpp
    src/Mesh.cpp
    src/Solver.cpp
)

target_include_directories(main PRIVATE include)