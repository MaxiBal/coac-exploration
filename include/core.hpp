#ifndef CORE_HPP
#define CORE_HPP

#include <random>

const int DIMENSIONS = 2; // Number of dimensions

class RandomGenerator
{
public:
    static std::random_device rd;
    static std::mt19937 gen; 
    RandomGenerator() { }
};

bool is_in_obstacle(
    const std::vector<double>& coordinates, 
    const std::vector<std::vector<int>>& grid
);

#endif