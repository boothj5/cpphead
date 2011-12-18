#include <iostream>
#include <vector>
#include <algorithm>
#include "game.h"
#include "console.h"
#include "player.h"
#include "card.h"

#define DECK_SIZE 52

using namespace std ;

Game::Game(string names[], int length, int numCards) 
{
    int i ;
    int rank, suit ;
    this->numPlayers = length ;
    this->numCards = numCards ;
    for (i = 0 ; i < length ; i++) {
        Player player(names[i]) ;
        players.push_back(player) ;
    }
    this->currentPlayer = 0 ;

    int numDecks = calcNumDecks(numPlayers, numCards) ;
    for (i = 0 ; i < numDecks ; i++)
        for (suit = HEARTS ; suit <= CLUBS ; suit++)
            for (rank = TWO ; rank <= ACE ; rank++)
                this->deck.push_back(Card((cardrank)rank, (cardsuit)suit)) ;
    
    random_shuffle(this->deck.begin(), this->deck.end()) ;
}

void Game::deal()
{
    int i, j ;
    Card card ;
    for (i = 0 ; i < players.size() ; i++) {
        for (j = 0 ; j < numCards ; j++) {
            card = deck.back() ;
            players[i].addToHand(card) ;
            deck.pop_back() ;
            
            card = deck.back() ;
            players[i].addToFaceUp(card) ;
            deck.pop_back() ;
            
            card = deck.back() ;
            players[i].addToFaceDown(card) ;
            deck.pop_back() ;
        }
    }
}

vector<Player> Game::getPlayers() 
{
    return players ;
}

Player Game::getCurrentPlayer()
{
    return players[currentPlayer] ;
}

vector<Card> Game::getDeck() {
    return deck ;
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

