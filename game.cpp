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
    numPlayers = length ;
    this->numCards = numCards ;
    for (i = 0 ; i < numPlayers ; i++) {
        Player player(names[i]) ;
        players.push_back(player) ;
    }
    currentPlayer = 0 ;

    numDecks = calcNumDecks(numPlayers, numCards) ;
    for (i = 0 ; i < numDecks ; i++)
        for (suit = HEARTS ; suit <= CLUBS ; suit++)
            for (rank = TWO ; rank <= ACE ; rank++)
                deck.push_back(Card((cardrank)rank, (cardsuit)suit)) ;

    ptrdiff_t (*p_randomGen)(ptrdiff_t) = randomGen ;    
    random_shuffle(deck.begin(), deck.end(), p_randomGen) ;
}

void Game::deal()
{
    int i, j ;
    for (i = 0 ; i < players.size() ; i++) {
        for (j = 0 ; j < numCards ; j++) {
            players[i].addToHand(deck.back()) ;
            deck.pop_back() ;
            players[i].addToFaceUp(deck.back()) ;
            deck.pop_back() ;
            players[i].addToFaceDown(deck.back()) ;
            deck.pop_back() ;
        }
        players[i].sortHand() ;
    }
}

void Game::swap(int player, int handChoice, int faceUpChoice)
{
    players[player].swap(handChoice, faceUpChoice) ;
}

void Game::firstMove()
{
    // assumes hands are not empty and are sorted
    vector<Card> lowestByPlayer ;
    vector<int> toLay ;
    int i ;

    // find player with lowest card    
    currentPlayer = 0 ;
    for (i = 1 ; i < numPlayers ; i++) {
        Card playersLowest = players[i].getHand()[0] ;
        Card currentLowest = players[currentPlayer].getHand()[0] ;
        if (Card::shCompare(playersLowest, currentLowest))
            currentPlayer = i ;
    }
     
    // get indexes of cards with same rank in players hand
    for (i = 0 ; i < numCards ; i++) {
        Card first = players[currentPlayer].getHand()[0] ;
        Card current = players[currentPlayer].getHand()[i] ;
        if (current.equalsRank(first))
            toLay.push_back(i) ;
    }

    // play them
    setLastHandMove(toLay) ;
    playFromHand(toLay) ;
}

bool Game::canContinue()
{
    int playersWithCards = 0 ;
    int i ;

    for (i = 0 ; i < numPlayers ; i++)
        if (players[i].hasCards())
            playersWithCards++ ;

    return playersWithCards > 1 ;
}

// private

void Game::playFromHand(const vector<int>& toLay)
{
    int i ;
    for (i = 0 ; i < toLay.size() ; i++)
        pile.push_back(players[currentPlayer].getHand()[toLay[i]]) ;
    
    players[currentPlayer].removeFromHand(toLay) ;

    while (deck.size() > 0 && players[currentPlayer].getHand().size() < numCards) {
        players[currentPlayer].addToHand(deck.back()) ;
        deck.pop_back() ;
    }
}

void Game::setLastHandMove(vector<int> toLay) 
{
    Player player = getCurrentPlayer() ;
    lastMove = "" ;
    lastMove += player.getName() ;
    lastMove += " laid " ;
    int i ;
    for (i = 0 ; i < toLay.size() ; i++) {
        lastMove += player.getHand()[toLay[i]].toString() ;
        lastMove += ", " ;
    }
}

// static

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

