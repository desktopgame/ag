#pragma once
#include <random>

namespace ag {
class Random {
public:
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;
    Random(Random&&) = delete;
    Random& operator=(Random&&) = delete;

    static float range(float min, float max);
    static int range(int min, int max);

private:
    Random();
    ~Random() = default;
    static Random& getInstance();
    std::random_device device;
    std::mt19937 mt;
};
}