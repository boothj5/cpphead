#ifndef H_PLAYER
#define H_PLAYER

#include <string>
#include <vector>
#include <algorithm>
#include "card.hpp"

using namespace std ;

class Player {
    string name_ ;
    vector<Card> hand_ ;
    vector<Card> faceUp_ ;
    vector<Card> faceDown_ ;
    
    public:
    Player(string name) ;
    string name() const ;
    vector<Card> hand() const ;
    vector<Card> faceUp() const ;
    vector<Card> faceDown() const ;
    void addToHand(Card card) ;
    void addAllToHand(const vector<Card>&) ;
    void addToFaceUp(Card card) ;
    void addToFaceDown(Card card) ;
    void sortHand() ;
    void swap(int, int) ;
    void removeFromHand(vector<int>) ; 
    void removeFromFaceUp(vector<int>) ; 
    void removeFromFaceDown(int) ; 
    bool hasCards() const ;
    bool hasCardsInHand() const ;
    bool hasCardsInFaceUp() const ;

    virtual bool isComputer() const =0;
} ;

#endif
