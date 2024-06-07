#include <region.hpp>

#include <core.hpp>

#include <algorithm>

namespace 
{

double distance(const std::vector<double>& a, const std::vector<double>& b) {
    double sum = 0.0;
    for (int i = 0; i < a.size(); ++i) {
        sum += std::pow(a[i] - b[i], 2);
    }
    return std::sqrt(sum);
}

int roulette_wheel_selection(
    const std::vector<Region>& regions, 
    const std::vector<double>& current_position,
    const std::vector<std::vector<int>>& grid
)
{
    std::vector<double> probabilities;

    for (const auto& region : regions) {
        probabilities.push_back(region.pheromone);
    }

    std::discrete_distribution<> dist(probabilities.begin(), probabilities.end());

    int selected_region_index;
    do {
        selected_region_index = dist(RandomGenerator::gen);
    } while (
        is_in_obstacle(regions[selected_region_index].center.coordinates, grid) || 
        distance(
            regions[selected_region_index].center.coordinates, 
            current_position
        ) > 2.0);

    return selected_region_index;

    return dist(RandomGenerator::gen);
}

int max_pheromone(const std::vector<Region>& regions)
{
    return std::distance(
        regions.begin(), 
        std::max_element(regions.begin(), regions.end(), [](const Region& r1, const Region& r2) { return r1.pheromone < r2.pheromone; })
    );
}


} // namespace 


// Initialize regions with random centers and radii
void initializeRegions(
    std::vector<Region>& regions, 
    const double initial_pheromone, 
    const double dimensions,
    std::function<double(std::vector<double>&)>& objectiveFunction,
    const std::vector<std::vector<int>>& grid
) 
{
    std::uniform_real_distribution<> coord_dis(LOWER_BOUND, UPPER_BOUND);
    
    for (int i = 0; i < NUM_REGIONS; ++i) {

        Region region;
        region.center.coordinates.resize(dimensions);

        bool valid = false;
        while (!valid) {
            for (int d = 0; d < DIMENSIONS; ++d) {
                region.center.coordinates[d] = coord_dis(RandomGenerator::gen);
            }
            valid = !is_in_obstacle(region.center.coordinates, grid);
        }

        for (int d = 0; d < DIMENSIONS; ++d) {
            region.radius.push_back((UPPER_BOUND - LOWER_BOUND) / 2);
        }

        region.center.value = objectiveFunction(region.center.coordinates);
        region.pheromone = initial_pheromone;
        region.visits = 0;
        regions.push_back(region);
    }
}

int selectRegion(
    const std::vector<Region>& regions, 
    const std::vector<double>& curr_pos, 
    const std::vector<std::vector<int>>& grid
)
{
    // if random pull is less than q0, do max_pheromone
    // else, do RWS

    // double q = dis(RandomGenerator::gen);

    // if (q <= q0)
    // {
    //     return max_pheromone(regions);
    // }
    // else
    // {
    return roulette_wheel_selection(regions, curr_pos, grid);
    // }
}