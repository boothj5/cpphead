#include <vector>
#include <algorithm>
#include "game.h"
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
    int i ;
    for (vector<Player>::iterator player = players.begin(); player != players.end(); 
            ++player) {
        for (i = 0 ; i < numCards ; i++) {
            player->addToHand(deck.back()) ;
            deck.pop_back() ;
            player->addToFaceUp(deck.back()) ;
            deck.pop_back() ;
            player->addToFaceDown(deck.back()) ;
            deck.pop_back() ;
        }
    }
}

Player Game::getCurrentPlayer(void)
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

