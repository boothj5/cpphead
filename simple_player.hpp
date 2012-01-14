#ifndef H_SIMPLE_PLAYER
#define H_SIMPLE_PLAYER

#include <string>
#include "computer_player.hpp"
#include "player_helper.hpp"

class SimplePlayer: public ComputerPlayer {
    public:
    SimplePlayer(std::string name);
    std::pair<int, int> askSwapChoice() const;
    bool askSwapCards() const;
    std::vector<int> askMoveChoice(const PlayerHelper helper) const;
    int askFaceDownMoveChoice() const;
};

#endif
