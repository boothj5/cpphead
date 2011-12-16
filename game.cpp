#include "game.h"
#include "player.h"

Game::Game(string names[], int length) 
{
    int i ;
    numPlayers = length ;
    players = new Player [length] ;
    for (i = 0 ; i < length ; i++) {
        Player player(names[i]) ;
        players[i] = player ;
    }
    currentPlayer = 0 ;
}

int Game::getNumPlayers(void) 
{
    return numPlayers ;
}

Player Game::getCurrentPlayer(void)
{
    return players[currentPlayer] ;
}
