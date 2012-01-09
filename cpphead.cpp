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

    vector<Player *> players = game.players() ;
    for (i = 0 ; i < players.size() ; i++) {
        clearScreen() ;
        showPlayer(*players[i]) ;
        bool doSwap = requestSwapCards(players[i]->name()) ;
        while (doSwap) {
            int handChoice = requestHandChoice() ;
            int faceUpChoice = requestFaceUpChoice() ;
            game.swap(i, handChoice, faceUpChoice) ;
            clearScreen() ;
            players = game.players() ;
            showPlayer(*players[i]) ;
            doSwap = requestSwapMore(players[i]->name()) ;
        }
    }

    game.firstMove() ;

    while (game.canContinue()) {
        const Player *currentPlayer = game.currentPlayer();
        clearScreen() ;
        showGame(game) ;
        if (game.playingFromFaceDown()) {
            int choice = requestFaceDownCard(currentPlayer->name()) ;
            if (game.validMoveFromFaceDown(choice)) {
                showFaceDownWin(currentPlayer->faceDown()[choice]) ;
                game.makeFaceDownMove(choice) ;
            }
            else {
                showFaceDownFail(currentPlayer->faceDown()[choice]) ;
                game.pickUpPileAndFaceDown(choice) ;
            }
        }
        else {
            if (game.currentPlayerCanMove()) {
                vector<int> choices = requestMove(currentPlayer->name()) ;
                while (!game.validMove(choices)) {
                    showBadMove() ;
                    choices = requestMove(currentPlayer->name()) ;
                }
                game.makeMove(choices) ;
            } else {
                showPickUpMessage(currentPlayer->name()) ;
                game.pickUp() ;
            }
        }
    }


    showShithead(game.getCppHead()) ;
        
    return 0 ;
}
    
