#include <iostream>
#include <string>
#include <vector>
#include "console.hpp"
#include "card.hpp"
#include "player.hpp"
#include "player_interaction.hpp"
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
        for (i = 0 ; i < players.size() ; i++)
            player_swap(players[i], game);

        game.firstMove();

        while (game.canContinue()) {
            const Player *currentPlayer = game.currentPlayer();
            clearScreen();
            showGame(game);
            if (game.playingFromFaceDown())
                player_facedown_move(currentPlayer, game);
            else
                player_move(currentPlayer, game);
        }

        showShithead(game.getCppHead());
            
        return 0 ;
    } catch (ShitheadException e) {
        cout << e.getMessage() << endl;
        return 1;
    }
}
    
