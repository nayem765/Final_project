cmake_minimum_required(VERSION 3.10)
project(heat_solver)

set(CMAKE_CXX_STANDARD 17)
enable_language(CXX)

add_executable(heat_solver
    main.cpp
    solver2d.cpp
)

