#include <algorithm>
#include <string>
#include "player.hpp"
#include "computer_players.hpp"

using namespace std;

ComputerPlayer::ComputerPlayer(string name) : Player(name) 
{
    // do nothing
}

bool ComputerPlayer::isComputer() const
{
    return true;
}

