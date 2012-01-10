#ifndef H_SHITHEAD_EXCEPTION
#define H_SHITHEAD_EXCEPTION

#include <string>

using namespace std;

class ShitheadException
{
    string msg_;

    public:
    ShitheadException(string msg) : msg_(msg) {}
    string getMessage() const { return msg_; }
};

#endif
