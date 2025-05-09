cmake_minimum_required(VERSION 3.10)
project(heat_solver)

set(CMAKE_CXX_STANDARD 17)
enable_language(CXX)
if(USE_MPI)
    find_package(MPI REQUIRED)
    include_directories(${MPI_INCLUDE_PATH})
    add_definitions(-DUSE_MPI)
    set(CMAKE_CXX_COMPILER ${MPI_CXX_COMPILER})
endif()
add_executable(heat_solver
    main.cpp
    solver2d.cpp
)
if(USE_MPI)
    target_link_libraries(heat_solver ${MPI_LIBRARIES})
endif()

