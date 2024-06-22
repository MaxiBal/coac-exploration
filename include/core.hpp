#ifndef CORE_HPP
#define CORE_HPP

#include <random>

const constexpr double VISIBILITY_RADIUS = 16.00;

double distance_sq(const std::vector<double>& a, const std::vector<double>& b);

class RandomGenerator
{
public:
    static std::random_device rd;
    static std::mt19937 gen; 
    RandomGenerator() { }
};

bool is_in_obstacle(
    const std::vector<double>& coordinates
);

// Structure to represent a point in the search space
struct Point {
    std::vector<double> coordinates;
    double value;

};

// Structure to represent a region in the search space
struct Region {
    Point center;
    std::vector<double> radius;
    double pheromone;
    int visits;
};

struct Path {
    std::vector<Point> waypoints;
    double fitness;
    double path_length;
};

#endif