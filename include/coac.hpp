#ifndef COAC_HPP
#define COAC_HPP

#include <vector>

#include <region.hpp>

const int MAX_ITER = 1000; // Maximum iterations
const double ALPHA = 0.1; // Pheromone decay parameter
const double INITIAL_PHEROMONE = 0.0001; // Initial pheromone level
const int NUM_ANTS = 4; // Number of ants
const double SHRINK = 0.8; // Shrinking factor
const double EXPAND = 1.2; // Expanding factor
const int DIMENSIONS = 2; // Number of dimensions
const double TARGET_ERROR = 0.1; // Acceptable error level
const double PHEROMONE_EVAPORATION = 0.5; // Pheromone evaporation rate

struct COAC_Result
{
    unsigned int iters;
    unsigned int ants;
    double global_best;
    std::vector<double> best_coords;
    std::vector<std::vector<Region>> ant_paths;
};

COAC_Result coac(
    std::function<double(std::vector<double>&)> objective_function
);



#endif