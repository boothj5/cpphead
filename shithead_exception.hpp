#ifndef H_SHITHEAD_EXCEPTION
#define H_SHITHEAD_EXCEPTION

#include <string>

class ShitheadException
{
    std::string msg_;

    public:
    ShitheadException(std::string msg) : msg_(msg) {}
    std::string getMessage() const { return msg_; }
};

#endif
