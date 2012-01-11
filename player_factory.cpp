#include <string>
#include "player.hpp"
#include "human_player.hpp"
#include "computer_player.hpp"
#include "shithead_exception.hpp"

using namespace std ;

Player * createPlayer(string name, char type)
{
    if (type == 'h')
        return new HumanPlayer(name);
    else if (type == 'c')
        return new ComputerPlayer(name);
    else
        throw ShitheadException("Unknown player type");
}
