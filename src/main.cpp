#include <iostream>

#include <random>
#include <vector>


#include <coac.hpp>
#include <path.hpp>


std::random_device rd;
std::mt19937 gen(rd());


void print_path(const Path& vec)
{
    for (const auto& points : vec.waypoints)
    {
        std::cout << "(";
        for (const auto c : points.coordinates)
        {
            std::cout << c << ", ";
        }
        std::cout << "), ";
    }
    std::cout << "\n";
}

void print_result(const COAC_Result& result)
{
    std::cout << "--------------\n";
    std::cout << "Iterations: " << result.iters << std::endl;
    std::cout << "Best path:" << std::endl;
    print_path(result.best_path);
}

const int NUM_AGENTS = 1;
const int DIMENSIONS = 2;
const double PROJECTED_LOWER_BOUND = 0;
const double PROJECTED_UPPER_BOUND = 50;


std::vector<std::vector<double>> generate_initial_positions()
{
    std::vector<std::vector<double>> initial_positions;
    for (int i = 0; i < NUM_AGENTS; ++i) {
        std::vector<double> point(DIMENSIONS);
        bool valid = false;
        while (!valid) {
            for (int d = 0; d < DIMENSIONS; ++d) {
                point[d] = 0;
            }
            valid = true;// !is_in_obstacle(point);
        }
        initial_positions.push_back(point);
    }
    return initial_positions;
} 

int main()
{
    auto result = coac(
        generate_initial_positions(),
        {45.0, 45.0},
        PROJECTED_LOWER_BOUND,
        PROJECTED_UPPER_BOUND,
        NUM_AGENTS,
        1000,
        DIMENSIONS
    ); 

    print_result(result);


    return 0;
}