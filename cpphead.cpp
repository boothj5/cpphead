#include <iostream>
#include <string>
#include <vector>
#include "console.h"
#include "card.h"
#include "player.h"
#include "game.h"

using namespace std ;

int main()
{
    int i, numPlayers, numCardsEach ;
    string * names ;
    clearScreen() ;
    showWelcomeMessage() ;
    numPlayers = requestNumPlayers() ;
    numCardsEach = requestNumCards() ;
    names = requestPlayerNames(numPlayers) ;

    Game game(names, numPlayers, numCardsEach) ;
    game.deal() ;

    clearScreen() ;

    showPlayers(game.getPlayers()) ;

    return 0 ;
}
    
