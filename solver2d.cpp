#include "solver2d.hpp"
#include "wtime.hpp"  // Include the wtime header for timing
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <filesystem>  // C++17 filesystem support
#ifdef USE_MPI
#include <mpi.h>
#endif

namespace fs = std::filesystem;

// Save function for std::vector<std::vector<double>>
void saveToFile(const std::vector<std::vector<double>>& u, int step) {
    std::ostringstream filename;
    filename << "data/output/heat_" << std::setfill('0') << std::setw(4) << step << ".csv";
    std::ofstream out(filename.str());

    for (const auto& row : u) {
        for (size_t j = 0; j < row.size(); ++j) {
            out << row[j];
            if (j + 1 < row.size()) out << ",";
        }
        out << "\n";
    }
}

void runHeatEquation2D(int N, double dt, double total_time, int snapshots) {
        #ifdef USE_MPI
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double t_start = wtime();  // ✅ Start the timer

    if (N % size != 0) {
        if (rank == 0) {
            std::cerr << "Grid size N must be divisible by number of processes.\n";
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int local_N = N / size;        // Rows per process (not counting ghosts)
    int global_N = N;
    int start_row = rank * local_N;
    int end_row = start_row + local_N;

    // Add 2 extra rows for ghost cells
    std::vector<std::vector<double>> u(local_N + 2, std::vector<double>(N, 0.0));
    std::vector<std::vector<double>> u_new = u;
#else
    std::vector<std::vector<double>> u(N, std::vector<double>(N, 0.0));
    std::vector<std::vector<double>> u_new = u;
    #endif

    double alpha = 1.0;  // thermal diffusivity
    double dx = 1.0 / (N - 1);
    double dy = dx;
    double r = alpha * dt / (dx * dx);

    if (r >= 0.25) {
        std::cerr << "Warning: dt is too large for stability in Forward Euler method.\n";
    }

    int steps_per_snapshot = static_cast<int>(total_time / dt / snapshots);

    
    // Set initial condition: hot spot at center
    #ifdef USE_MPI
    for (int i = 1; i <= local_N; ++i) {  // skip ghost rows
        int global_i = start_row + (i - 1);  // global row index
        for (int j = 0; j < N; ++j) {
            double x = global_i * dx;
            double y = j * dy;
            if (std::abs(x - 0.5) < 0.1 && std::abs(y - 0.5) < 0.1) {
                u[i][j] = 100.0;
            }
        }
    }
#else
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            double x = i * dx;
            double y = j * dy;
            if (std::abs(x - 0.5) < 0.1 && std::abs(y - 0.5) < 0.1) {
                u[i][j] = 100.0;
            }
        }
    }
#endif


    // Ensure output directory exists
    fs::create_directories("data/output");

    int total_steps = static_cast<int>(total_time / dt);
    for (int step = 0; step <= total_steps; ++step) {
        #ifdef USE_MPI
    // 1. Send bottom real row to next rank, receive top ghost from previous rank
    if (rank < size - 1) {
        MPI_Send(u[local_N].data(), N, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD);
    }
    if (rank > 0) {
        MPI_Recv(u[0].data(), N, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // 2. Send top real row to previous rank, receive bottom ghost from next rank
    if (rank > 0) {
        MPI_Send(u[1].data(), N, MPI_DOUBLE, rank - 1, 1, MPI_COMM_WORLD);
    }
    if (rank < size - 1) {
        MPI_Recv(u[local_N + 1].data(), N, MPI_DOUBLE, rank + 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
#endif


        // Forward Euler update
        #ifdef USE_MPI
    for (int i = 1; i <= local_N; ++i) {
        for (int j = 1; j < N - 1; ++j) {
            u_new[i][j] = u[i][j] + r * (
                u[i+1][j] + u[i-1][j] +
                u[i][j+1] + u[i][j-1] -
                4 * u[i][j]
            );
        }
    }
#else
    for (int i = 1; i < N - 1; ++i) {
        for (int j = 1; j < N - 1; ++j) {
            u_new[i][j] = u[i][j] + r * (
                u[i+1][j] + u[i-1][j] +
                u[i][j+1] + u[i][j-1] -
                4 * u[i][j]
            );
        }
    }
#endif

        u.swap(u_new);

        if (step % steps_per_snapshot == 0) {
            #ifdef USE_MPI
                std::ostringstream filename;
                filename << "data/output/heat_rank" << rank << "_step" << std::setfill('0') << std::setw(4) << step << ".csv";
                std::ofstream out(filename.str());
            
                // Write only real rows (not ghost rows)
                for (int i = 1; i <= local_N; ++i) {
                    for (int j = 0; j < N; ++j) {
                        out << u[i][j];
                        if (j + 1 < N) out << ",";
                    }
                    out << "\n";
                }
            #else
                saveToFile(u, step);
            #endif
            }
            
    }
    #ifdef USE_MPI
    double t_end = wtime();
    std::cout << "Rank " << rank << " finished in " << (t_end - t_start) << " seconds.\n";
#endif

}
