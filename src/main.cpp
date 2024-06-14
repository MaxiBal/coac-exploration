#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <random>
#include <algorithm>

#include <coac.hpp>

#include <chrono>

// Parameters


std::vector<std::vector<int>> grid = {
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1},
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0}
};



// Objective function to be minimized (Rosenbrock function example)
// double objectiveFunction(const std::vector<double>& coordinates) {
//     double sum = 0.0;

//     for (int i = 0; i < coordinates.size() - 1; ++i) {
//         sum += 100 * std::pow(coordinates[i + 1] - std::pow(coordinates[i], 2), 2) + std::pow(coordinates[i] - 1, 2);
//     }
//     return sum;
//}

double objectiveFunction(const std::vector<double>& coordinates)
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

    std::cout << "-------------\n";
    std::cout << "region data:\n[";
    for (const auto region : result.regions)
    {
        std::cout << "(";
        for (int i = 0; i < region.center.coordinates.size(); i++)
        {
            std::cout << region.center.coordinates[i] << ", ";
        }
        std::cout << "), ";
    }
    std::cout << "]\n";
}

void test_n_iters()
{
    // check runtime for `TEST_ITERS` coac algorithms
    const int TEST_ITERS = 1000;
    size_t total_runtime = 0;

    size_t total_iters = 0;

    for (int i = 0; i < TEST_ITERS; i++)
    {
        auto t1 = std::chrono::high_resolution_clock::now();
        auto result = coac(objectiveFunction, grid, generateInitialPositions());
        auto t2 = std::chrono::high_resolution_clock::now();

        total_iters += result.iters;
        total_runtime += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
    }

    std::cout << "For " << TEST_ITERS << " iterations:\n";
    std::cout << "Average iterations: " << total_iters / TEST_ITERS << ".\n";
    std::cout << "Average runtime: " << total_runtime / TEST_ITERS << ".\n";
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

