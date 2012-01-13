#ifndef H_COMPUTER_PLAYER
#define H_COMPUTER_PLAYER

#include <string>
#include "player.hpp"
#include "player_helper.hpp"

class ComputerPlayer: public Player {
    public:
    ComputerPlayer(std::string name);
    bool isComputer() const;
    std::pair<int, int> askSwapChoice() const;
    bool askSwapCards() const;
    std::vector<int> askMoveChoice(const PlayerHelper helper) const;
    int askFaceDownMoveChoice() const;
};

#endif
