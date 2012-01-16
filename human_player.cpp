#include <algorithm>
#include <string>
#include "player.hpp"
#include "player_helper.hpp"
#include "human_player.hpp"
#include "shithead_exception.hpp"

using namespace std;

HumanPlayer::HumanPlayer(const string name) : Player(name) {}

bool HumanPlayer::isComputer() const
{
    return false ;
}

const pair<int, int> HumanPlayer::askSwapChoice() const 
{
    throw ShitheadException("Cannot ask human player for swap choice");
}

bool HumanPlayer::askSwapCards() const
{
    throw ShitheadException("Cannot ask human player to swap cards");
}

const vector<int> HumanPlayer::askMoveChoice(const PlayerHelper& helper) const
{
    throw ShitheadException("Cannot ask human player to move");
}

int HumanPlayer::askFaceDownMoveChoice() const
{
    throw ShitheadException("Cannot ask human player to move");
}
