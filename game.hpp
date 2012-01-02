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
    int burnt_ ;
    int numCards_ ;
    int numPlayers_ ;
    vector<Player>::iterator currentPlayer_ ;
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
    int burnt() const ;
    string lastMove() const ;
    bool canContinue() const ;
    void makeMove(const vector<int>&) ;
    void makeFaceDownMove(int) ;
    bool currentPlayerCanMove() const ;
    bool playingFromFaceDown() const ;
    void pickUp() ;
    void pickUpPileAndFaceDown(int) ;
    bool validMove(const vector<int>&) const ;
    bool validMoveFromFaceDown(int) const ;
    string getCppHead() const ;

    private:
    void playFromHand(const vector<int>&) ;
    void setLastHandMove(const vector<int>&) ;
    void playFromFaceUp(const vector<int>&) ;
    void playFromFaceDown(int) ;
    void setLastFaceUpMove(const vector<int>&) ;
    void setLastFaceDownMove(int) ;
    void setLastMovePickUp() ;
    void setLastMoveMissAGo() ;
    void moveToNextPlayer() ;
    void processSpecialCards() ;
    bool canMoveWithOneOf(const vector<Card>&) const ;
    bool validMove(const vector<Card>&) const ;
    bool burnCardLaid() const ;
    bool missAGoLaid() const ;
    void burnPile() ;
    void missAGo() ;

    static bool canLay(const Card&, const vector<Card>&) ;
    static int calcNumDecks(int, int) ;
    static ptrdiff_t randomGen(ptrdiff_t) ;
} ;

#endif
