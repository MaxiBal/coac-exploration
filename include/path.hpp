#ifndef PATH_HPP
#define PATH_HPP

#include <vector>


#include <core.hpp>
#include <region.hpp>


double costmap(const std::vector<double>& coordinates);

double path_fitness(const Path& path, const std::vector<double>& target);
double point_cost(
    const Path& path, 
    const Point& point,
    const std::vector<double>& target
);

#endif