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
    Player(string) ;
    string getName() const ;
    vector<Card> getHand() const ;
    vector<Card> getFaceUp() const ;
    vector<Card> getFaceDown() const ;
    void addToHand(Card) ;
    void addToFaceUp(Card) ;
    void addToFaceDown(Card) ;
} ;

#endif
