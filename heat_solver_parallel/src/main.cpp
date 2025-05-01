#include <iostream>
#include "../include/solver2d.hpp"  // ✅ This line must match your project structure

int main() {
    int N = 100;         // Grid size
    double dt = 1e-5;  // instead of 0.001
   // Time step
    double T = 0.1;      // Total simulation time
    int steps = 10;      // Number of snapshots

    runHeatEquation2D(N, dt, T, steps);  // ✅ Call the solver

    return 0;
}
