#ifndef H_COMPUTER_PLAYER
#define H_COMPUTER_PLAYER

#include <string>
#include <vector>
#include <algorithm>
#include "player.hpp"

using namespace std ;

class ComputerPlayer: public Player {
    public:
    ComputerPlayer(string name);
    bool isComputer() const;
    pair<int, int> askSwapChoice() const;
    bool askSwapCards() const;
};

#endif
