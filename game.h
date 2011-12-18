#ifndef H_GAME
#define H_GAME

#include <vector>
#include <string>
#include "player.h"
#include "card.h"

using namespace std ;

class Game {
    vector<Player> players ;
    int numCards ;
    int numPlayers ;
    int currentPlayer ;
    vector<Card> deck ;

    static int calcNumDecks(int, int) ;
    static ptrdiff_t randomGen(ptrdiff_t i) ;
    
    public:
    Game(string[], int, int) ;
    void deal() ;
    vector<Player> getPlayers() ;
    Player getCurrentPlayer() ;
    vector<Card> getDeck() ;
} ;

#endif
