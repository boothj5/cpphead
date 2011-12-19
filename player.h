#ifndef H_PLAYER
#define H_PLAYER

#include <string>
#include <vector>
#include <algorithm>
#include "card.h"

using namespace std ;

class Player {
    string name ;
    vector<Card> hand ;
    vector<Card> faceUp ;
    vector<Card> faceDown ;
    
    public:
    Player(string name) { this->name = name ; }
    string getName() const { return name ; }
    vector<Card> getHand() const { return hand ; }
    vector<Card> getFaceUp() const { return faceUp ; } 
    vector<Card> getFaceDown() const { return faceDown ; }
    void addToHand(Card card) { hand.push_back(card) ; } 
    void addToFaceUp(Card card) { faceUp.push_back(card) ; }
    void addToFaceDown(Card card) { faceDown.push_back(card) ; }
    void sortHand() { sort(hand.begin(), hand.end(), Card::shCompare) ; }
    void swap(int, int) ;
    void removeFromHand(vector<int>) ; 
} ;

#endif
