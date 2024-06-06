#include <coac.hpp>

#include <algorithm>

namespace 
{

// Generate orthogonal neighboring points
std::vector<Point> generateOrthogonalPoints(
    const Point& center, 
    const std::vector<double>& radius, 
    std::function<double(std::vector<double>&)>& objective_function
) 
{
    std::vector<Point> points;
    std::uniform_real_distribution<> level_dis(-1.0, 1.0);
    for (int i = 0; i < NUM_ANTS; ++i) {
        Point point;
        point.coordinates.resize(DIMENSIONS);

        for (int d = 0; d < DIMENSIONS; ++d) {
            point.coordinates[d] = center.coordinates[d] + level_dis(RandomGenerator::gen) * radius[d];
            point.coordinates[d] = std::clamp(point.coordinates[d], LOWER_BOUND, UPPER_BOUND);
        }
        
        point.value = objective_function(point.coordinates);
        points.push_back(point);
    }

    return points;
}

}; // namespace 


// COAC algorithm
COAC_Result coac(
    std::function<double(std::vector<double>&)> objective_function
) 
{
    std::vector<Region> regions;
    initializeRegions(regions, INITIAL_PHEROMONE, DIMENSIONS, objective_function);

    double global_best_value = std::numeric_limits<double>::max();
    std::vector<double> global_best_coordinates(DIMENSIONS);

    int iter = 0;

    std::vector<std::vector<Region>> ant_paths(NUM_ANTS, std::vector<Region>());

    for (; iter < MAX_ITER; ++iter) {
        for (auto& region : regions) {
            region.visits = 0;
        }

        for (int ant = 0; ant < NUM_ANTS; ++ant) {
            int selected_region_index = selectRegion(regions);
            Region& selected_region = regions[selected_region_index];

            ant_paths[ant].push_back(selected_region);

            selected_region.visits++;

            auto points = generateOrthogonalPoints(selected_region.center, selected_region.radius, objective_function);
            auto best_point_it = std::min_element(points.begin(), points.end(), [](const Point& a, const Point& b) {
                return a.value < b.value;
            });

            if (best_point_it->value < selected_region.center.value) {
                selected_region.center = *best_point_it;
                for (auto& radius : selected_region.radius) {
                    radius *= EXPAND;
                }
            } else {
                for (auto& radius : selected_region.radius) {
                    radius *= SHRINK;
                }
            }

            if (selected_region.center.value < global_best_value) {
                global_best_value = selected_region.center.value;
                global_best_coordinates = selected_region.center.coordinates;
            }
        }

        for (auto& region : regions) {
            region.pheromone = (1 - PHEROMONE_EVAPORATION) * region.pheromone + ALPHA * region.visits;
        }

        if (global_best_value < TARGET_ERROR) {
            break;
        }
    }

    return {
        static_cast<unsigned int>(iter),
        NUM_ANTS,
        global_best_value,
        global_best_coordinates,
        ant_paths
    };
    
}