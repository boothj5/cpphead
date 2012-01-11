#include <iostream>
#include <string>
#include <vector>
#include "console.hpp"
#include "card.hpp"
#include "player.hpp"
#include "game.hpp"
#include "shithead_exception.hpp"

using namespace std;

int main()
{
    try {
        int i, numPlayers, numCardsEach;
        vector<string> playerNames;
        vector<char> playerTypes;
        clearScreen();
        showWelcomeMessage();
        numPlayers = requestNumPlayers();
        numCardsEach = requestNumCards();
        
        for (i = 0; i < numPlayers; i++) {
            string name = requestPlayerName(i+1);
            playerNames.push_back(name);

            char type = requestPlayerType(i+1);
            playerTypes.push_back(type);
        }

        Game game(playerNames, playerTypes, numCardsEach);
        game.deal();

        clearScreen();

        vector<Player *> players = game.players();
        for (i = 0 ; i < players.size() ; i++) {
            if (!players[i]->isComputer()) {
                clearScreen();
                showPlayer(*players[i]);
                bool doSwap = requestSwapCards(players[i]->name());
                while (doSwap) {
                    int handChoice = requestHandChoice();
                    int faceUpChoice = requestFaceUpChoice();
                    game.swap(i, handChoice, faceUpChoice);
                    clearScreen();
                    players = game.players();
                    showPlayer(*players[i]);
                    doSwap = requestSwapMore(players[i]->name());
                }
            } 
            else {
                bool doSwap = players[i]->askSwapCards();
                while (doSwap) {
                    pair<int, int> swapChoice = players[i]->askSwapChoice();
                    game.swap(i, swapChoice.first, swapChoice.second);
                    doSwap = players[i]->askSwapCards();
                }
            }
        }

        game.firstMove();

        while (game.canContinue()) {
            const Player *currentPlayer = game.currentPlayer();
            clearScreen();
            showGame(game);
            if (game.playingFromFaceDown()) {
                int choice = requestFaceDownCard(currentPlayer->name());
                if (game.validMoveFromFaceDown(choice)) {
                    showFaceDownWin(currentPlayer->faceDown()[choice]);
                    game.makeFaceDownMove(choice);
                }
                else {
                    showFaceDownFail(currentPlayer->faceDown()[choice]);
                    game.pickUpPileAndFaceDown(choice);
                }
            }
            else {
                if (game.currentPlayerCanMove()) {
                    vector<int> choices = requestMove(currentPlayer->name());
                    while (!game.validMove(choices)) {
                        showBadMove();
                        choices = requestMove(currentPlayer->name());
                    }
                    game.makeMove(choices);
                } else {
                    showPickUpMessage(currentPlayer->name());
                    game.pickUp();
                }
            }
        }


        showShithead(game.getCppHead());
            
        return 0 ;
    } catch (ShitheadException e) {
        cout << e.getMessage() << endl;
        return 1;
    }
}
    
