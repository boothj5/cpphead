#include "player.h"

Player::Player()
{
    name = "" ;
}

Player::Player(string aName) 
{
    name = aName ;
}

string Player::getName(void) 
{
    return name ;
}

