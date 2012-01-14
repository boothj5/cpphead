#ifndef H_LOWCARD_PLAYER
#define H_LOWCARD_PLAYER

#include <string>
#include "computer_player.hpp"
#include "player_helper.hpp"

class LowCardPlayer: public ComputerPlayer {
    public:
    LowCardPlayer(std::string name);
    std::pair<int, int> askSwapChoice() const;
    bool askSwapCards() const;
    std::vector<int> askMoveChoice(const PlayerHelper helper) const;
    int askFaceDownMoveChoice() const;
};

#endif
