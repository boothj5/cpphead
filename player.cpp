#include "player.h"
#include "card.h"

Player::Player()
{
    name = "" ;
}

Player::Player(string aName) 
{
    name = aName ;
}

string Player::getName(void) 
{
    return name ;
}

void Player::addToHand(Card card)
{
    hand.push_back(card) ;
}

void Player::addToFaceUp(Card card)
{
    faceUp.push_back(card) ;
}

void Player::addToFaceDown(Card card)
{
    faceDown.push_back(card) ;
}

