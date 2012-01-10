#include <algorithm>
#include <string>
#include "computer_player.hpp"
#include "card.hpp"
#include "shithead_exception.hpp"

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

