#ifndef H_COMPUTER_PLAYERS
#define H_COMPUTER_PLAYERS

#include <string>
#include "player.hpp"
#include "player_helper.hpp"
#include "card.hpp"

class ComputerPlayer: public Player {
    public:
    ComputerPlayer(std::string name);
    bool isComputer() const;
    virtual std::pair<int, int> askSwapChoice() const =0;
    virtual bool askSwapCards() const =0;
    virtual std::vector<int> askMoveChoice(const PlayerHelper helper) const =0;
    virtual int askFaceDownMoveChoice() const =0;
};

class SimplePlayer: public ComputerPlayer {
    public:
    SimplePlayer(std::string name);
    std::pair<int, int> askSwapChoice() const;
    bool askSwapCards() const;
    std::vector<int> askMoveChoice(const PlayerHelper helper) const;
    int askFaceDownMoveChoice() const;
};

class LowCardPlayer: public ComputerPlayer {
    public:
    LowCardPlayer(std::string name);
    std::pair<int, int> askSwapChoice() const;
    bool askSwapCards() const;
    std::vector<int> askMoveChoice(const PlayerHelper helper) const;
    int askFaceDownMoveChoice() const;
};

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
