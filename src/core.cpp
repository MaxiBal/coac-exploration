#include <core.hpp>

std::random_device RandomGenerator::rd;
std::mt19937 RandomGenerator::gen(RandomGenerator::rd());

bool is_in_obstacle(
    const std::vector<double>& coordinates
)
{
    for (int i = 0; i < coordinates.size(); i++)
    {
        if (coordinates[i] > -5 && coordinates[i] < 5) return true;
    }

    return false;
}

double distance_sq(const std::vector<double>& a, const std::vector<double>& b) {
    double sum = 0.0;
    for (int i = 0; i < a.size(); ++i) {
        sum += std::pow(a[i] - b[i], 2);
    }
    return sum;
}
