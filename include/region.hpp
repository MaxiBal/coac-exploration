#ifndef SELECT_REGION_HPP
#define SELECT_REGION_HPP

#include <functional>
#include <vector>


#include <core.hpp>
#include <path.hpp>

const int INITIAL_NUM_REGIONS = 300; // Number of regions

const unsigned int REGION_DENSITY = static_cast<unsigned int>(VISIBILITY_RADIUS / VISIBILITY_RADIUS);
const double INITIAL_RADIUS_VALUE = 8.0;



namespace
{

int roulette_wheel_selection(
    const std::vector<Region>& regions
);


int max_pheromone(const std::vector<Region>& regions);

Region create_random_region(
    const std::vector<double>& random_center,
    const double dimensions,
    const double initial_pheromone,
    const std::function<double(std::vector<double>&)>& objective_function,
    std::uniform_real_distribution<>& coord_dis,
    int DIMENSIONS
);

}

// Initialize regions with random centers and radii
void initialize_regions(
    std::vector<Region>& regions, 
    const double initial_pheromone, 
    const double dimensions,
    const std::function<double(const std::vector<double>&)>& objective_function,
    double PROJECTED_LOWER_BOUND, double PROJECTED_UPPER_BOUND
);

// Select region based on pheromone levels
int selectRegion(
    Path& path,
    const std::vector<Region>& regions
    //const Path& best_path
);

void populate_space_with_regions(
    std::vector<Region>& regions, 
    std::vector<double>  position,
    const double dimensions,
    const double initial_pheromone,
    const std::function<double(std::vector<double>&)>& objective_function
);


#endif