#ifndef H_HUMAN_PLAYER
#define H_HUMAN_PLAYER

#include <string>
#include <vector>
#include <algorithm>
#include "card.hpp"
#include "player.hpp"

using namespace std ;

class HumanPlayer: public Player {
    public:
    HumanPlayer(string name);
    bool isComputer() const;
} ;

#endif
