#include <algorithm>
#include <string>
#include "human_player.hpp"
#include "card.hpp"

HumanPlayer::HumanPlayer(string name) : Player(name) 
{
    // do nothing
}

bool HumanPlayer::isComputer() const
{
    return false ;
}
