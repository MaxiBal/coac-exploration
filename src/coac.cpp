#include <coac.hpp>

#include <algorithm>
#include <iostream>

const double OBSTACLE_PENALTY = 1e6; // Penalty for point existing in an obstacle

namespace 
{


// Generate orthogonal neighboring points
std::vector<Point> generate_orthogonal_points(
    const Point& center, 
    const std::vector<double>& radius, 
    const std::function<double(const std::vector<double>&)>& objective_function,
    int NUM_AGENTS,
    int DIMENSIONS
) 
{
    std::vector<Point> points;
    std::uniform_real_distribution<> level_dis(-1.0, 1.0);

    for (int i = 0; i < NUM_AGENTS; ++i) 
    {
        Point point;
        point.coordinates.resize(DIMENSIONS);

        bool valid = false;
        while (!valid) 
        {
            for (int d = 0; d < DIMENSIONS; ++d) 
            {
                point.coordinates[d] = center.coordinates[d] + level_dis(RandomGenerator::gen) * radius[d];
            }
            valid = !is_in_obstacle(point.coordinates);
        }
        
        point.value = objective_function(point.coordinates);
        points.push_back(point);
    }

    return points;
}

}; // namespace 


// COAC algorithm
COAC_Result coac(
    const std::vector<std::vector<double>>& initial_positions,
    const std::vector<double>& target,
    double PROJECTED_LOWER_BOUND, double PROJECTED_UPPER_BOUND,
    int NUM_AGENTS,
    int MAX_ITERS,
    int DIMENSIONS
) 
{
    std::vector<Region> regions;
    initialize_regions(regions, INITIAL_PHEROMONE, DIMENSIONS, std::function(costmap), PROJECTED_LOWER_BOUND, PROJECTED_UPPER_BOUND);

    double global_best_value = std::numeric_limits<double>::max();

    int iter = 0;

    std::vector<Point> current_positions(initial_positions.size());
    std::vector<Path> ant_paths(NUM_AGENTS);
    

    for (; iter < MAX_ITERS; ++iter) 
    {
        //std::cout << "Iteration " << iter << "\n" << std::endl;
        for (auto& region : regions) 
        {
            region.visits = 0;
        }

        for (int ant = 0; ant < NUM_AGENTS; ++ant) 
        {
            int selected_region_index = selectRegion(
                ant_paths[ant], regions
            );

            Region& selected_region = regions[selected_region_index];
            //std::cout << "region: (" << selected_region.center.coordinates[0] << ", " << selected_region.center.coordinates[1] << ");\n"; 
            
            ant_paths[ant].waypoints.push_back(selected_region.center);
            // ant_paths[ant].path_length += sqrt(
            //     distance_sq(current_positions[ant].coordinates, selected_region.center.coordinates)
            // );
            ant_paths[ant].fitness = path_fitness(ant_paths[ant], target);

            current_positions[ant] = selected_region.center;

            selected_region.visits++;

            auto points = generate_orthogonal_points(
                selected_region.center, 
                selected_region.radius, 
                std::function(costmap),
                NUM_AGENTS,
                DIMENSIONS
            );

            auto best_point_it = std::min_element(
                points.begin(), points.end(), 
                [&](const Point& a, const Point& b) {
                    return 
                        point_cost(ant_paths[ant], a, target) < point_cost(ant_paths[ant], a, target);
                }
            );

            // shrink / grow region radius depending on best_point_it value

            if (best_point_it->value < selected_region.center.value) 
            {
                selected_region.center = *best_point_it;
                for (auto& radius : selected_region.radius) 
                {
                    radius *= EXPAND;
                }
            } 
            else 
            {
                for (auto& radius : selected_region.radius) 
                {
                    radius *= SHRINK;
                }
            }

            // update global best if selected region is better than global best

            if (ant_paths[ant].fitness < global_best_value) 
            {
                global_best_value = ant_paths[ant].fitness;
                //best_path = ant_paths[ant];
            }

            // add another region in explored area
            populate_space_with_regions(
                regions,
                current_positions[ant].coordinates,
                DIMENSIONS,
                INITIAL_PHEROMONE,
                std::function(costmap)
            );
        }
        // global modulation phase
        // update each region's pheromone level
        
        for (auto& region : regions) 
        {
            region.pheromone = (1 - PHEROMONE_EVAPORATION) * region.pheromone + ALPHA * region.visits;
        }

        //std::cout << "global best value: " << global_best_value << "\n";

        if (global_best_value < TARGET_ERROR) 
        {
            break;
        }
    }


    return {
        static_cast<unsigned int>(iter),
        static_cast<unsigned int>(NUM_AGENTS),
        global_best_value,
        regions,
        *std::min_element(
            ant_paths.begin(), ant_paths.end(), [&](const Path& a, const Path& b)
            {
                return path_fitness(a, target) < path_fitness(b, target);
            }
        )
    };
    
}