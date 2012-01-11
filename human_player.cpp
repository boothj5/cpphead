#include <algorithm>
#include <string>
#include "player.hpp"
#include "human_player.hpp"
#include "shithead_exception.hpp"

using namespace std;

HumanPlayer::HumanPlayer(string name) : Player(name) 
{
    // do nothing
}

bool HumanPlayer::isComputer() const
{
    return false ;
}

pair<int, int> HumanPlayer::askSwapChoice() const 
{
    throw ShitheadException("Cannot ask human player for swap choice");
}

bool HumanPlayer::askSwapCards() const
{
    throw ShitheadException("Cannot ask human player to swap cards");
}
