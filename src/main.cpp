#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <random>
#include <algorithm>

#include <coac.hpp>

// Parameters




// Objective function to be minimized (Rosenbrock function example)
// double objectiveFunction(const std::vector<double>& coordinates) {
//     double sum = 0.0;

//     for (int i = 0; i < coordinates.size() - 1; ++i) {
//         sum += 100 * std::pow(coordinates[i + 1] - std::pow(coordinates[i], 2), 2) + std::pow(coordinates[i] - 1, 2);
//     }
//     return sum;
// }

inline double objectiveFunction(const std::vector<double>& coordinates)
{
    // distance to point (100, 100, ...)
    // avoid circle with radius 5, centered around (0, 0)

    double dist = 0.0;
    bool exists_in_collision = false;
    for (auto d : coordinates)
    {
        dist += pow(100 - d, 2);
        if (d > -5 && d < 5)
        {
            exists_in_collision = true;
        }

        if (d > 80 && d < 85)
        {
            exists_in_collision = true;
        }
    }

    return sqrtl(dist) + (exists_in_collision ? 100000 : 0);
}





void print_coac_results(const COAC_Result& result)
{
    std::cout << "--------------\n";
    std::cout << "Iterations: " << result.iters << std::endl;
    std::cout << "Global Best Value: " << result.global_best << std::endl;
    std::cout << "Global Best Coordinates: ";
    for (const auto& coord : result.best_coords) {
        std::cout << coord << " ";
    }

    std::cout << "\nAnt Paths\n";
    for (const auto& path : result.ant_paths)
    {
        std::cout << "[";
        for (const auto region : path)
        {
            std::cout << "(";
            for (int i = 0; i < DIMENSIONS; i++)
            {
                std::cout << region.center.coordinates[i] << ",";
            }
            std::cout << "), ";
        }
        std::cout << "],\n";
    }

    std::cout << std::endl;
}



int main() {
    auto result = coac(objectiveFunction);
    print_coac_results(result);
    
    return 0;
}

