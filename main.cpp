#include <iostream>
#include "solver2d.hpp"
#ifdef USE_MPI
#include <mpi.h>  // ✅ Add this to declare MPI_Init, MPI_Finalize, etc.
#endif
int main() {
    #ifdef USE_MPI
    MPI_Init(nullptr, nullptr);
    #endif
    int N = 100;         // Grid size
    double dt = 1e-5;    // Time step
    double T = 0.1;      // Total simulation time
    int steps = 10;      // Number of snapshots

    runHeatEquation2D(N, dt, T, steps);
    #ifdef USE_MPI
    MPI_Finalize();
    #endif
    return 0;
}
