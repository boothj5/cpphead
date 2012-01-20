#ifndef H_PLAYER_HELPER
#define H_PLAYER_HELPER

#include <vector>
#include "card.hpp"

class PlayerHelper {
    std::vector<Card> pile_;
    
    public:
    explicit PlayerHelper(const std::vector<Card>&);
    const std::vector<Card> getPile() const;
};

#endif
