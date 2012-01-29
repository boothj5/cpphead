#include <algorithm>
#include <string>
#include <map>
#include <iostream>
#include "card.hpp"
#include "player.hpp"

using namespace std;

Player::Player(const string name)
    : name_(name),
      hand_(0),
      faceUp_(0),
      faceDown_(0)
{}

Player::~Player()
{
    hand_.clear();
    faceUp_.clear();
    faceDown_.clear();
}

const string Player::name() const 
{
    return name_ ; 
}

const vector<Card> Player::hand() const 
{ 
    return hand_ ; 
}

const vector<Card> Player::faceUp() const 
{ 
    return faceUp_ ; 
}

const vector<Card> Player::faceDown() const 
{ 
    return faceDown_ ; 
}

void Player::addToHand(const Card& card) 
{ 
    hand_.push_back(card) ; 
}

void Player::addAllToHand(const vector<Card>& cards)
{
    copy(cards.begin(), cards.end(), back_inserter(hand_)) ;
}

void Player::addToFaceUp(const Card& card) 
{ 
    faceUp_.push_back(card) ; 
}

void Player::addToFaceDown(const Card& card) 
{ 
    faceDown_.push_back(card) ; 
}

void Player::sortHand() 
{ 
    sort(hand_.begin(), hand_.end(), card::shCompare) ; 
}

void Player::swap(const int handCard, const int faceUpCard)
{
    const Card tmp = hand_[handCard] ;
    hand_[handCard] = faceUp_[faceUpCard] ;
    faceUp_[faceUpCard] = tmp ;
}

void Player::removeFromHand(const vector<int>& indexes)
{
    vector<Card> newHand ;
    
    int i  ;
    for (i = 0 ; i < hand_.size() ; i++) {
        vector<int>::const_iterator result = 
            find(indexes.begin(), indexes.end(), i) ;
        if (result == indexes.end()) 
            newHand.push_back(hand_[i]) ;
    }
    hand_ = newHand ;
}

void Player::removeFromFaceUp(const vector<int>& indexes)
{
    vector<Card> newFaceUp ;
    
    int i  ;
    for (i = 0 ; i < faceUp_.size() ; i++) {
        const vector<int>::const_iterator result = 
            find(indexes.begin(), indexes.end(), i) ;
        if (result == indexes.end()) 
            newFaceUp.push_back(faceUp_[i]) ;
    }
    faceUp_ = newFaceUp ;
}

void Player::removeFromFaceDown(const int index)
{
    faceDown_.erase(faceDown_.begin() + index) ;
}

bool Player::hasCards() const
{
    return hand_.size() > 0 || faceUp_.size() > 0 || faceDown_.size() > 0 ;
}

bool Player::hasCardsInHand() const
{
    return hand_.size() > 0 ;
}

bool Player::hasCardsInFaceUp() const
{
    return faceUp_.size() > 0 ;
}
