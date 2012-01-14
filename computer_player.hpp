#ifndef H_COMPUTER_PLAYER
#define H_COMPUTER_PLAYER

#include <string>
#include "player.hpp"
#include "player_helper.hpp"

class ComputerPlayer: public Player {
    public:
    ComputerPlayer(std::string name);
    bool isComputer() const;
    virtual std::pair<int, int> askSwapChoice() const =0;
    virtual bool askSwapCards() const =0;
    virtual std::vector<int> askMoveChoice(const PlayerHelper helper) const =0;
    virtual int askFaceDownMoveChoice() const =0;
};

#endif
