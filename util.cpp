#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdint>

using namespace std;

namespace util {

static uint64_t rdtsc(void)
{
  uint32_t lo, hi;
  __asm__ __volatile__ (
  "xorl %%eax,%%eax \n        cpuid"
  ::: "%rax", "%rbx", "%rcx", "%rdx");
  __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
  return (uint64_t)hi << 32 | lo;
}


ptrdiff_t randomGen(ptrdiff_t i)
{
    srand(rdtsc()) ;
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

