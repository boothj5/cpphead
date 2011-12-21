#include <algorithm>
#include "player.h"
#include "card.h"

void Player::swap(int handCard, int faceUpCard)
{
    Card tmp = hand[handCard] ;
    hand[handCard] = faceUp[faceUpCard] ;
    faceUp[faceUpCard] = tmp ;
    sortHand() ;
}

void Player::removeFromHand(vector<int> indexes)
{
    // TODO write generic template function to remove indexes from vector
    // instead of copying
    vector<Card> newHand ;
    
    int i  ;
    int handSize = hand.size() ;
    for (i = 0 ; i < handSize ; i++) {
        vector<int>::iterator result = find(indexes.begin(), indexes.end(), i) ;
        if (result == indexes.end()) 
            newHand.push_back(hand[i]) ;
    }
    hand = newHand ;
    sortHand() ;
}

bool Player::hasCards()
{
    return hand.size() > 0 || faceUp.size() > 0 || faceDown.size() > 0 ;
}

