#include <iostream>
#include <string>
#include <vector>
#include "console.hpp"
#include "card.hpp"
#include "player.hpp"
#include "game.hpp"

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
    game.deal() ;

    clearScreen() ;

    vector<Player> players = game.getPlayers() ;
    for (i = 0 ; i < players.size() ; i++) {
        clearScreen() ;
        showPlayer(players[i]) ;
        bool doSwap = requestSwapCards(players[i].getName()) ;
        while (doSwap) {
            int handChoice = requestHandChoice() ;
            int faceUpChoice = requestFaceUpChoice() ;
            game.swap(i, handChoice, faceUpChoice) ;
            clearScreen() ;
            players = game.getPlayers() ;
            showPlayer(players[i]) ;
            doSwap = requestSwapMore(players[i].getName()) ;
        }
    }

    game.firstMove() ;

    while (game.canContinue()) {
        clearScreen() ;
        showGame(game) ;
        vector<int> choices = requestMove(game.getCurrentPlayer().getName()) ;
        game.makeMove(choices) ;
    }
        
    return 0 ;
}
    
