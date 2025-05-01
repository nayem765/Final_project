include_directories(/opt/homebrew/include)
enable_language(CXX)

find_package(xtensor REQUIRED)
cmake_minimum_required(VERSION 3.10)
project(heat_solver)

set(CMAKE_CXX_STANDARD 17)

include_directories(heat_solver_parallel/include)

add_executable(heat_solver
    heat_solver_parallel/src/main.cpp
    heat_solver_parallel/src/solver2d.cpp
)

