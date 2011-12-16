#ifndef H_GAME
#define H_GAME

#include "player.h"

using namespace std ;

class Game {
    Player * players ;
    int numPlayers ;
    int currentPlayer ;
    
    public:
    Game(string[], int) ;
    int getNumPlayers(void) ;
    Player getCurrentPlayer(void) ;
} ;

#endif
