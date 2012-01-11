#ifndef H_COMPUTER_PLAYER
#define H_COMPUTER_PLAYER

#include <string>
#include "player.hpp"

class ComputerPlayer: public Player {
    public:
    ComputerPlayer(std::string name);
    bool isComputer() const;
    std::pair<int, int> askSwapChoice() const;
    bool askSwapCards() const;
};

#endif
