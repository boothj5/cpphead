#include <iostream>
#include <string>
#include <vector>
#include "console.h"
#include "card.h"
#include "player.h"
#include "game.h"

using namespace std ;

int main()
{
    int i, numPlayers, numCardsEach ;
    string * names ;
    clearScreen() ;
    showWelcomeMessage() ;
    numPlayers = requestNumPlayers() ;
    numCardsEach = requestNumCards() ;
    names = requestPlayerNames(numPlayers) ;

    Game game(names, numPlayers, numCardsEach) ;
    
    cout << "Current player : " << game.getCurrentPlayer().getName() << endl ;

    vector<Card> deck = game.getDeck() ;

    cout << deck.size() << endl ;

    for (vector<Card>::iterator card = deck.begin(); card != deck.end(); ++card) {
        cout << card->toString() << endl ;
    }

    game.deal() ;

    deck = game.getDeck() ;
    cout << deck.size() << endl ;

    for (vector<Card>::iterator card = deck.begin(); card != deck.end(); ++card) {
        cout << card->toString() << endl ;
    }

    return 0 ;
}
    
