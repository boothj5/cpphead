#include "player.h"
#include "card.h"

Player::Player(string aName) 
{
    name = aName ;
}

string Player::getName() const
{
    return name ;
}

vector<Card> Player::getHand() const
{
    return hand ;
}

vector<Card> Player::getFaceUp() const
{
    return faceUp ;
}

vector<Card> Player::getFaceDown() const
{
    return faceDown ;
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

