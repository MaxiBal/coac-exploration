#include <path.hpp>

double path_fitness(const Path& path, const std::vector<double>& target)
{
    double score = 0.0;//path.path_length;

    // score should be evaluated on final point's distance to target
    for (int i = 0; i < target.size(); i++)
    {
        score += pow(path.waypoints[path.waypoints.size() - 1].coordinates[i] - target[i], 2);
    }

    // score should also be evaluated on cost map / function  
    for (int i = 0; i < path.waypoints.size(); i++)
    {
        score += path.waypoints[i].value;
    }
      
    return score;
}

double point_cost(
    const Path &path, 
    const Point &point,
    const std::vector<double>& target
)
{
    return 
        //path.fitness + 
        sqrt(distance_sq(path.waypoints[path.waypoints.size() - 1].coordinates, target)) + 
        costmap(point.coordinates);
}

double costmap(const std::vector<double>& coordinates)
{
    double sum = 0.0;

    for (int i = 0; i < coordinates.size() - 1; ++i) {
        sum += 100 * std::pow(coordinates[i + 1] - std::pow(coordinates[i], 2), 2) + std::pow(coordinates[i] - 1, 2);
    }
    return sum;

    // return 0.0;
}