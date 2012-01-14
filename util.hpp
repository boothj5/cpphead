#ifndef H_UTIL
#define H_UTIL

#include <vector>
#include <algorithm>

namespace util {

static std::ptrdiff_t randomGen(std::ptrdiff_t i)
{
    int seed = static_cast<int>(time(0));
    std::srand(seed) ;
    return std::rand() % i ;
}

template <class T>
void shuffle(std::vector<T>& vec)
{
    std::ptrdiff_t (*p_randomGen)(std::ptrdiff_t) = randomGen ;
    random_shuffle(vec.begin(), vec.end(), p_randomGen) ;
}

} // namespace util

#endif
