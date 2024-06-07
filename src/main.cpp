#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <random>
#include <algorithm>

#include <coac.hpp>

// Parameters


std::vector<std::vector<int>> grid = {
    {0, 0, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0},
    {1, 1, 0, 1, 0},
    {0, 0, 0, 0, 0}
};



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
    // distance to point (5, 5, ...)

    double dist = 0.0;

    for (auto d : coordinates)
    {
        dist += pow(4.65 - d, 2);
    }

    return sqrtl(dist);
}

std::vector<Point> generateInitialPositions() {
    std::vector<Point> initial_positions;
    std::uniform_real_distribution<> coord_dis(LOWER_BOUND, UPPER_BOUND);
    for (int i = 0; i < NUM_ANTS; ++i) {
        Point point;
        point.coordinates.resize(DIMENSIONS);
        bool valid = false;
        while (!valid) {
            for (int d = 0; d < DIMENSIONS; ++d) {
                point.coordinates[d] = coord_dis(RandomGenerator::gen);
            }
            valid = !is_in_obstacle(point.coordinates, grid);
        }
        point.value = objectiveFunction(point.coordinates);
        initial_positions.push_back(point);
    }
    return initial_positions;
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

    // std::cout << "-------------\n";
    // std::cout << "region data:\n";
    // for (const auto region : result.regions)
    // {
    //     std::cout << "(";
    //     for (int i = 0; i < region.center.coordinates.size(); i++)
    //     {
    //         std::cout << region.center.coordinates[i] << ", "
    //     }
    // }
}



int main() {

    auto initial_positions = generateInitialPositions();
    
    auto result = coac(
        objectiveFunction,
        grid,
        initial_positions
    );
    print_coac_results(result);
    
    return 0;
}

