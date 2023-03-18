#include <ag/util/Random.hpp>
namespace ag {
float Random::range(float min, float max)
{
    std::uniform_real_distribution<float> D(min, max);
    return D(getInstance().mt);
}
int Random::range(int min, int max)
{
    std::uniform_int_distribution<> D(min, max);
    return D(getInstance().mt);
}
// private
Random::Random()
    : device()
    , mt(device())
{
}

Random& Random::getInstance()
{
    static Random inst;
    return inst;
}
}