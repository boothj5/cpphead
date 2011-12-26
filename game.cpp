#include <iostream>
#include <vector>
#include <algorithm>
#include "game.hpp"
#include "console.hpp"
#include "player.hpp"
#include "card.hpp"

#define DECK_SIZE 52

using namespace std ;

Game::Game(string names[], int length, int numCards) 
{
    int i, rank, suit, numDecks ;
    numPlayers_ = length ;
    numCards_ = numCards ;
    for (i = 0 ; i < numPlayers_ ; i++) {
        Player player(names[i]) ;
        players_.push_back(player) ;
    }
    currentPlayer_ = 0 ;

    numDecks = calcNumDecks(numPlayers_, numCards_) ;
    for (i = 0 ; i < numDecks ; i++)
        for (suit = HEARTS ; suit <= CLUBS ; suit++)
            for (rank = TWO ; rank <= ACE ; rank++)
                deck_.push_back(Card((cardrank)rank, (cardsuit)suit)) ;

    ptrdiff_t (*p_randomGen)(ptrdiff_t) = randomGen ;    
    random_shuffle(deck_.begin(), deck_.end(), p_randomGen) ;
}

void Game::deal()
{
    int i ;
    
    vector<Player>::iterator player ;
    for (player = players_.begin() ; player != players_.end() ; player++) {
        for (i = 0 ; i < numCards_ ; i++) {
            player->addToHand(deck_.back()) ;
            deck_.pop_back() ;
            player->addToFaceUp(deck_.back()) ;
            deck_.pop_back() ;
            player->addToFaceDown(deck_.back()) ;
            deck_.pop_back() ;
        }
        player->sortHand() ;
    }
}

void Game::swap(int player, int handChoice, int faceUpChoice)
{
    players_[player].swap(handChoice, faceUpChoice) ;
}

void Game::firstMove()
{
    // assumes hands are not empty and are sorted
    vector<Card> lowestByPlayer ;
    vector<int> toLay ;
    int i ;

    // find player with lowest card    
    currentPlayer_ = 0 ;
    for (i = 1 ; i < numPlayers_ ; i++) {
        Card playersLowest = players_[i].hand()[0] ;
        Card currentLowest = players_[currentPlayer_].hand()[0] ;
        if (Card::shCompare(playersLowest, currentLowest))
            currentPlayer_ = i ;
    }
     
    // get indexes of cards with same rank in players hand
    for (i = 0 ; i < numCards_ ; i++) {
        Card first = players_[currentPlayer_].hand()[0] ;
        Card current = players_[currentPlayer_].hand()[i] ;
        if (current.equalsRank(first))
            toLay.push_back(i) ;
    }

    // play them
    setLastHandMove(toLay) ;
    playFromHand(toLay) ;
    moveToNextPlayer() ;
}

vector<Player> Game::players() const 
{ 
    return players_ ; 
}

Player Game::currentPlayer() const 
{
    return players_[currentPlayer_] ; 
}

vector<Card> Game::deck() const 
{ 
    return deck_ ; 
}

vector<Card> Game::pile() const 
{ 
    return pile_ ; 
}

string Game::lastMove() const 
{ 
    return lastMove_ ; 
}

bool Game::canContinue() const
{
    int playersWithCards = 0 ;

    vector<Player>::const_iterator player ;
    for (player = players_.begin() ; player != players_.end() ; player++)
        if (player->hasCards())
            playersWithCards++ ;

    return playersWithCards > 1 ;
}

void Game::makeMove(const vector<int>& choices)
{
    setLastHandMove(choices) ;
    playFromHand(choices) ;
    moveToNextPlayer() ;
}

bool Game::validMove(const vector<int>& choices) const
{
    vector<Card> toLay ;
    vector<int>::const_iterator index ;
    for (index = choices.begin() ; index != choices.end() ; index++)
        if (players_[currentPlayer_].hasCardsInHand())
            toLay.push_back(players_[currentPlayer_].hand()[*index]) ;
        else
            toLay.push_back(players_[currentPlayer_].faceUp()[*index]) ;
    return validMove(toLay) ;
}

bool Game::validMove(const vector<Card>& cards) const
{
    if (!Card::allRanksEqual(cards)) 
        return false ;
    else
        return Game::canLay(cards.back(), pile_) ;
}

bool Game::currentPlayerCanMove() const
{
    if (pile_.empty())
        return true ;
    
    Player player = currentPlayer() ;    
    if (player.hasCardsInHand())
        return canMoveWithOneOf(player.hand()) ;
    else if (player.hasCardsInFaceUp())
        return canMoveWithOneOf(player.faceUp()) ;
    else
        return false ;
}

void Game::pickUp()
{
    vector<Card>::const_iterator card ;
    for (card = pile_.begin() ; card != pile_.end() ; card++)
        players_[currentPlayer_].addToHand(*card) ;
    pile_.clear() ;
    setLastMovePickUp() ;
    moveToNextPlayer() ;
}


void Game::playFromHand(const vector<int>& toLay)
{
    int i ;
    for (i = 0 ; i < toLay.size() ; i++)
        pile_.push_back(players_[currentPlayer_].hand()[toLay[i]]) ;
    
    players_[currentPlayer_].removeFromHand(toLay) ;

    while (deck_.size() > 0 && players_[currentPlayer_].hand().size() < numCards_) {
        players_[currentPlayer_].addToHand(deck_.back()) ;
        deck_.pop_back() ;
    }

    players_[currentPlayer_].sortHand() ;
}

void Game::setLastHandMove(const vector<int>& toLay) 
{
    Player player = currentPlayer() ;
    lastMove_ = "" ;
    lastMove_ += player.name() ;
    lastMove_ += " laid " ;
    int i ;
    for (i = 0 ; i < toLay.size() ; i++) {
        lastMove_ += player.hand()[toLay[i]].toString() ;
        lastMove_ += ", " ;
    }
}

void Game::setLastMovePickUp() 
{
    Player player = currentPlayer() ;
    lastMove_ = player.name() ; 
    lastMove_ += " picked up." ;
}

void Game::moveToNextPlayer()
{
    currentPlayer_++ ;
    if (currentPlayer_ == players_.size())
        currentPlayer_ = 0 ;
    while (!currentPlayer().hasCards()) 
        moveToNextPlayer() ;
}

bool Game::canMoveWithOneOf(const vector<Card>& cards) const
{
    int i ;
    for (i = 0 ; i < cards.size() ; i++)
        if (Game::canLay(cards[i], pile_))
            return true ;
    return false ;   

}

bool Game::canLay(const Card& card, const vector<Card>& cards)
{
    if (cards.empty())
        return true ;
    else if (card.special())
        return true ;
    else if (cards.back().isInvisible()) {
        vector<Card> newPile = cards ;
        newPile.pop_back() ;
        return canLay(card, newPile) ;
    }
    else if (card.rank() < cards.back().rank())
        return false ;
    else
        return true ;
}

int Game::calcNumDecks(int numPlayers, int numCards)
{
    int decksRequired, totalCards, div, add ;
    totalCards = numPlayers * (numCards * 3) ;
    div = totalCards / DECK_SIZE ;
    add = ((totalCards % DECK_SIZE) > 0) ;
    decksRequired = div + add ;
    return decksRequired ;
}

ptrdiff_t Game::randomGen(ptrdiff_t i)
{
    int seed = static_cast<int>(time(0));
    srand(seed) ;
    return rand() % i ; 
}

