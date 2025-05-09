#include <iostream>
#include "solver2d.hpp"

int main() {
    int N = 100;         // Grid size
    double dt = 1e-5;    // Time step
    double T = 0.1;      // Total simulation time
    int steps = 10;      // Number of snapshots

    runHeatEquation2D(N, dt, T, steps);

    return 0;
}
