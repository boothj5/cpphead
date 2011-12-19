#include "player.h"
#include "card.h"

void Player::swap(int handCard, int faceUpCard)
{
    Card tmp = hand[handCard] ;
    hand[handCard] = faceUp[faceUpCard] ;
    faceUp[faceUpCard] = tmp ;
    sortHand() ;
}


