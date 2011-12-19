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

ptrdiff_t Game::randomGen(ptrdiff_t i) 
{
    int seed = static_cast<int>(time(0));
    srand(seed) ;
    return rand() % i ; 
}

