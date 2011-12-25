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

    vector<Player> players = game.players() ;
    for (i = 0 ; i < players.size() ; i++) {
        clearScreen() ;
        showPlayer(players[i]) ;
        bool doSwap = requestSwapCards(players[i].name()) ;
        while (doSwap) {
            int handChoice = requestHandChoice() ;
            int faceUpChoice = requestFaceUpChoice() ;
            game.swap(i, handChoice, faceUpChoice) ;
            clearScreen() ;
            players = game.players() ;
            showPlayer(players[i]) ;
            doSwap = requestSwapMore(players[i].name()) ;
        }
    }

    game.firstMove() ;

    while (game.canContinue()) {
        clearScreen() ;
        showGame(game) ;
        if (game.currentPlayerCanMove()) {
            vector<int> choices = requestMove(game.currentPlayer().name()) ;
            game.makeMove(choices) ;
        } else {
            showPickUpMessage(game.currentPlayer().name()) ;
            game.pickUp() ;
        }
            
    }
        
    return 0 ;
}
    
