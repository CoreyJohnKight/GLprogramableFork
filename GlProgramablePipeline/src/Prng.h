#pragma once 
#include <cstdlib>
#include <ctime>
namespace Prng
{
    // Seed the PRNG using the current time
    inline void seedPRNG() {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

    // Generate a random integer in the specified range [min, max]
    inline int randomInt(int min, int max) {
        if (min > max) {
            std::swap(min, max);
        }
        return min + std::rand() % (max - min + 1);
    }

    // Generate a random float in the specified range [min, max)
    inline float randomFloat(float min, float max) {
        if (min > max) {
            std::swap(min, max);
        }
        float normalized = static_cast<float>(std::rand()) / RAND_MAX;
        return min + normalized * (max - min);
    }

    // Generate a random double in the specified range [min, max)
    inline double randomDouble(double min, double max) {
        if (min > max) {
            std::swap(min, max);
        }
        double normalized = static_cast<double>(std::rand()) / RAND_MAX;
        return min + normalized * (max - min);
    }

}