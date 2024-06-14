#ifndef SELECT_REGION_HPP
#define SELECT_REGION_HPP

#include <functional>
#include <vector>

#include <core.hpp>

// factor that determines how often the max pheromone path is taken versus the roulette wheel selection
const double q0 = 0.5;

const double LOWER_BOUND = 0.01; // Lower bound for search space
const double UPPER_BOUND = 4.99; // Upper bound for search space
const int NUM_REGIONS = 30; // Number of regions

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

namespace
{

std::uniform_real_distribution<> dis(0.0, 1.0);

int roulette_wheel_selection(
    const std::vector<Region>& regions,
    const std::vector<double>& current_position,
    const std::vector<std::vector<int>>& grid
);


int max_pheromone(const std::vector<Region>& regions);

}

// Initialize regions with random centers and radii
void initializeRegions(
    std::vector<Region>& regions, 
    const double initial_pheromone, 
    const double dimensions,
    std::function<double(std::vector<double>&)>& objectiveFunction,
    const std::vector<std::vector<int>>& grid
);

// Select region based on pheromone levels
int selectRegion(
    const std::vector<Region>& regions,
    const std::vector<double>& curr_pos, 
    const std::vector<std::vector<int>>& grid
);

void populate_space_with_regions(
    std::vector<Region>& regions,
    const std::vector<double>& discovered_space
);


#endif