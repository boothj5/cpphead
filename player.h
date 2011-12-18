#ifndef H_PLAYER
#define H_PLAYER

#include <string>
#include <vector>
#include "card.h"

using namespace std ;

class Player {
    string name ;
    vector<Card> hand ;
    vector<Card> faceUp ;
    vector<Card> faceDown ;
    
    public:
    Player() ;
    Player(string) ;
    string getName() ;
    vector<Card> getHand() ;
    vector<Card> getFaceUp() ;
    vector<Card> getFaceDown() ;
    void addToHand(Card) ;
    void addToFaceUp(Card) ;
    void addToFaceDown(Card) ;
} ;

#endif
