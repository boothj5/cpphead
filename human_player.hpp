#ifndef H_HUMAN_PLAYER
#define H_HUMAN_PLAYER

#include <string>
#include <vector>
#include "player.hpp"
#include "player_helper.hpp"

class HumanPlayer: public Player {
    public:
    HumanPlayer(const std::string name);
    ~HumanPlayer() {};
    bool isComputer() const;
    const std::pair<int, int> askSwapChoice() const;
    bool askSwapCards() const;
    const std::vector<int> askMoveChoice(const PlayerHelper&) const;
    int askFaceDownMoveChoice() const;
};

#endif
