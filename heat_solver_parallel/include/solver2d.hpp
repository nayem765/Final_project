// inside include/solver2d.hpp
#pragma once
#include <vector>

void runHeatEquation2D(int N, double dt, double total_time, int snapshots);
void saveToFile(const std::vector<std::vector<double>>& u, int step);  // <--- only this line, no definition
