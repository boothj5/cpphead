#include <vector>
#include <algorithm>

using namespace std;

namespace util {

ptrdiff_t randomGen(ptrdiff_t i)
{
    int seed = static_cast<int>(clock());
    srand(seed) ;
    return rand() % i ;
}

} // namespace util

