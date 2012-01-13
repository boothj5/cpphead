#ifndef H_HUMAN_PLAYER
#define H_HUMAN_PLAYER

#include <string>
#include <vector>
#include "player.hpp"
#include "player_helper.hpp"

class HumanPlayer: public Player {
    public:
    HumanPlayer(std::string name);
    bool isComputer() const;
    std::pair<int, int> askSwapChoice() const;
    bool askSwapCards() const;
    std::vector<int> askMoveChoice(const PlayerHelper) const;
    int askFaceDownMoveChoice() const;
};

#endif
