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

string Player::getName() 
{
    return name ;
}

vector<Card> Player::getHand()
{
    return hand ;
}

vector<Card> Player::getFaceUp()
{
    return faceUp ;
}

vector<Card> Player::getFaceDown()
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

