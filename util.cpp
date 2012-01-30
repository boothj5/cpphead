#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

namespace util {

ptrdiff_t randomGen(ptrdiff_t i)
{
    return rand() % i ;
}

string formatMillis(const double ms)
{
    stringstream result;

    // more than a minute
    if (ms >= 60000) {
        int minutes = ms / 60000;
        int seconds = (ms - (minutes * 60000)) / 1000;
        result << minutes << " minutes, ";
        result << seconds << " seconds";
    } else if (ms >= 1000) {
        int seconds = ms / 1000;
        result << seconds << " seconds";
    } else {
        result << ms << " milliseconds";
    }

    return result.str();
}


} // namespace util

