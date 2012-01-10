#include <algorithm>
#include <string>
#include "computer_player.hpp"
#include "card.hpp"

ComputerPlayer::ComputerPlayer(string name) : Player(name) 
{
    // do nothing
}

bool ComputerPlayer::isComputer() const
{
    return true ;
}
