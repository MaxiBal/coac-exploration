#ifndef CORE_HPP
#define CORE_HPP

#include <random>

class RandomGenerator
{
public:
    static std::random_device rd;
    static std::mt19937 gen; 
    RandomGenerator() { }
};

#endif