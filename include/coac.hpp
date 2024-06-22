#ifndef COAC_HPP
#define COAC_HPP

#include <vector>

#include <core.hpp>
#include <region.hpp>
#include <path.hpp>

const double ALPHA = 0.1; // Pheromone decay parameter
const double INITIAL_PHEROMONE = 0.5; // Initial pheromone level
const double SHRINK = 0.8; // Shrinking factor
const double EXPAND = 1.2; // Expanding factor
const double TARGET_ERROR = 0.01; // Acceptable error level
const double PHEROMONE_EVAPORATION = 0.5; // Pheromone evaporation rate


namespace 
{

std::vector<Point> generate_orthogonal_points(
    const Point& center, 
    const std::vector<double>& radius, 
    const std::function<double(const std::vector<double>&)>& objective_function,
    int NUM_AGENTS,
    int DIMENSIONS
);

} // namespace 


struct COAC_Result
{
    unsigned int iters;
    unsigned int ants;
    double global_best;
    std::vector<Region> regions;
    Path best_path;
};

COAC_Result coac(
    const std::vector<std::vector<double>>& initial_positions,
    const std::vector<double>& target,
    double PROJECTED_LOWER_BOUND, double PROJECTED_UPPER_BOUND,
    int NUM_AGENTS,
    int MAX_ITERS,
    int DIMENSIONS
);



#endif