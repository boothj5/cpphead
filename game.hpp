#ifndef H_GAME
#define H_GAME

#include <vector>
#include <string>
#include "player.hpp"
#include "card.hpp"

using namespace std ;

class Game {
    vector<Player> players ;
    vector<Card> deck ;
    vector<Card> pile ;
    int numCards ;
    int numPlayers ;
    int currentPlayer ;
    string lastMove ;

    static int calcNumDecks(int, int) ;
    static ptrdiff_t randomGen(ptrdiff_t) ;
    
    void playFromHand(const vector<int>&) ;
    void setLastHandMove(vector<int>) ;

    public:
    Game(string[], int, int) ;
    
    void deal() ;
    void swap(int, int, int) ;
    void firstMove() ;
    vector<Player> getPlayers() const { return players ; }
    Player getCurrentPlayer() const { return players[currentPlayer] ; }
    vector<Card> getDeck() const { return deck ; }
    vector<Card> getPile() const { return pile ; }
    string getLastMove() const { return lastMove ; }
    bool canContinue() ;
} ;

#endif
