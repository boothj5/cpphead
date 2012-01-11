#include <algorithm>
#include <string>
#include "player.hpp"
#include "computer_player.hpp"

using namespace std;

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

