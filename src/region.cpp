#include <region.hpp>
#include <iostream>

#include <core.hpp>

#include <algorithm>

namespace 
{



int max_pheromone(const std::vector<Region>& regions)
{
    return std::distance(
        regions.begin(), 
        std::max_element(regions.begin(), regions.end(), [](const Region& r1, const Region& r2) { return r1.pheromone < r2.pheromone; })
    );
}


Region create_random_region(
    const std::vector<double>& random_center,
    const double dimensions,
    const double initial_pheromone,
    const std::function<double(std::vector<double>&)>& objective_function,
    std::uniform_real_distribution<>& coord_dis,
    int DIMENSIONS
)
{
    Region region;
    region.center.coordinates.resize(dimensions);

    do {
        for (int d = 0; d < DIMENSIONS; ++d) {
            region.center.coordinates[d] = random_center[d] + coord_dis(RandomGenerator::gen);
        }
    } while(is_in_obstacle(region.center.coordinates));

    for (int d = 0; d < DIMENSIONS; ++d) {
        region.radius.push_back(INITIAL_RADIUS_VALUE);
    }

    region.center.value = objective_function(region.center.coordinates);
    region.pheromone = initial_pheromone;
    region.visits = 0;

    return region;
}


} // namespace 


// Initialize regions with random centers and radii
void initialize_regions(
    std::vector<Region>& regions, 
    const double initial_pheromone, 
    const double dimensions,
    const std::function<double(const std::vector<double>&)>& objective_function,
    double PROJECTED_LOWER_BOUND, double PROJECTED_UPPER_BOUND
) 
{
    std::uniform_real_distribution<> coord_dis(PROJECTED_LOWER_BOUND, PROJECTED_UPPER_BOUND);
    
    for (int i = 0; i < INITIAL_NUM_REGIONS; ++i) 
    {
        regions.push_back(
            create_random_region(
                std::vector<double>(dimensions, 0),
                dimensions, 
                initial_pheromone, 
                objective_function, 
                coord_dis,
                dimensions
            )
        );
    }
}

namespace 
{

inline double within_distance(double dist, double dist_threshold)
{
    return dist < dist_threshold ? 1 : 0;
}

inline int roulette_wheel_selection(
    const std::vector<Region>& regions
)
{
    std::vector<double> probabilities;

    for (const auto& region : regions) {
        probabilities.push_back(
            region.pheromone
        );
    }

    std::discrete_distribution<> dist(probabilities.begin(), probabilities.end());

    return dist(RandomGenerator::gen);
}

} // namespace 


int selectRegion(
    Path& path,
    const std::vector<Region>& regions
)
{

    return roulette_wheel_selection(regions);
}

std::uniform_real_distribution<> coord_dis(-VISIBILITY_RADIUS, VISIBILITY_RADIUS);

void populate_space_with_regions(
    std::vector<Region>& regions, 
    std::vector<double>  position,
    const double dimensions,
    const double initial_pheromone,
    const std::function<double(std::vector<double>&)>& objective_function
)
{

    const constexpr double min_region_radius_squared = VISIBILITY_RADIUS * VISIBILITY_RADIUS;

    // first check if there are no regions within visibility

    for (const auto& region : regions)
    {
        if (distance_sq(region.center.coordinates, position) < min_region_radius_squared)
        {
            return;
        }
    }

    for (unsigned int i = 0; i < REGION_DENSITY; i++)
    {
        regions.push_back(
            create_random_region(
                position,
                dimensions,
                initial_pheromone,
                objective_function,
                coord_dis,
                dimensions
            )
        );
    }
}
