#include <core.hpp>

std::random_device RandomGenerator::rd;
std::mt19937 RandomGenerator::gen(RandomGenerator::rd());

bool is_in_obstacle(
    const std::vector<double>& coordinates, 
    const std::vector<std::vector<int>>& grid
)
{
    int x = static_cast<int>(std::floor(coordinates[0]));
    int y = static_cast<int>(std::floor(coordinates[1]));
    return (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size() && grid[x][y] == 1);
}