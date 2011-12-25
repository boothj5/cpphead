#ifndef H_GAME
#define H_GAME

#include <vector>
#include <string>
#include "player.hpp"
#include "card.hpp"

using namespace std ;

class Game {
    vector<Player> players_ ;
    vector<Card> deck_ ;
    vector<Card> pile_ ;
    int numCards_ ;
    int numPlayers_ ;
    int currentPlayer_ ;
    string lastMove_ ;

    public:
    Game(string[], int, int) ;
    
    void deal() ;
    void swap(int, int, int) ;
    void firstMove() ;
    vector<Player> players() const ;
    Player currentPlayer() const ;
    vector<Card> deck() const ;
    vector<Card> pile() const ;
    string lastMove() const ;
    bool canContinue() const ;
    void makeMove(const vector<int>&) ;
    bool currentPlayerCanMove() const ;
    void pickUp() ;

    private:
    void playFromHand(const vector<int>&) ;
    void setLastHandMove(const vector<int>&) ;
    void setLastMovePickUp() ;
    void moveToNextPlayer() ;
    bool canMoveWithOneOf(const vector<Card>&) const ;

    static bool canLay(const Card&, const vector<Card>&) ;
    static int calcNumDecks(int, int) ;
    static ptrdiff_t randomGen(ptrdiff_t) ;
} ;

#endif
