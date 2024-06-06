#include <region.hpp>

#include <core.hpp>

#include <algorithm>

namespace 
{

int roulette_wheel_selection(const std::vector<Region>& regions)
{
    std::vector<double> probabilities;

    for (const auto& region : regions) {
        probabilities.push_back(region.pheromone);
    }

    std::discrete_distribution<> dist(probabilities.begin(), probabilities.end());
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
    std::function<double(std::vector<double>&)>& objectiveFunction
) {
    std::uniform_real_distribution<> coord_dis(LOWER_BOUND, UPPER_BOUND);
    for (int i = 0; i < NUM_REGIONS; ++i) {
        Region region;
        region.center.coordinates.resize(dimensions);
        for (int d = 0; d < dimensions; ++d) {
            region.center.coordinates[d] = coord_dis(RandomGenerator::gen);
            region.radius.push_back((UPPER_BOUND - LOWER_BOUND) / 2);
        }
        region.center.value = objectiveFunction(region.center.coordinates);
        region.pheromone = initial_pheromone;
        region.visits = 0;
        regions.push_back(region);
    }
}

int selectRegion(const std::vector<Region>& regions)
{
    // if random pull is less than q0, do max_pheromone
    // else, do RWS

    double q = dis(RandomGenerator::gen);

    if (q <= q0)
    {
        return max_pheromone(regions);
    }
    else
    {
        return roulette_wheel_selection(regions);
    }
}