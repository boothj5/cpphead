#include <algorithm>
#include <string>
#include "player.hpp"
#include "computer_players.hpp"

using namespace std;

ComputerPlayer::ComputerPlayer(const string name) : Player(name) {}

bool ComputerPlayer::isComputer() const
{
    return true;
}

