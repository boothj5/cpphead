#ifndef H_HIGHCARD_PLAYER
#define H_HIGHCARD_PLAYER

#include <string>
#include "card.hpp"
#include "computer_player.hpp"
#include "player_helper.hpp"

class HighCardPlayer: public ComputerPlayer {
    public:
    HighCardPlayer(std::string name);
    std::pair<int, int> askSwapChoice() const;
    bool askSwapCards() const;
    std::vector<int> askMoveChoice(const PlayerHelper helper) const;
    int askFaceDownMoveChoice() const;

    private:
    static bool reverseCompare(Card, Card);
};

#endif
