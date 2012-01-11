#include <algorithm>
#include <string>
#include "computer_player.hpp"

ComputerPlayer::ComputerPlayer(string name) : Player(name) 
{
    // do nothing
}

bool ComputerPlayer::isComputer() const
{
    return true ;
}

pair<int, int> ComputerPlayer::askSwapChoice() const
{
    return pair<int, int>(0,0);
}

bool ComputerPlayer::askSwapCards() const
{
    return false;
}

