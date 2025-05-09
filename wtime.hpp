#pragma once

#ifdef USE_MPI
#include <mpi.h>

inline double wtime() {
    return MPI_Wtime();
}

#else
#include <chrono>

inline double wtime() {
    static auto start = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = now - start;
    return elapsed.count();
}
#endif
