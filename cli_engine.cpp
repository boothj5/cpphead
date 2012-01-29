#include <vector>
#include "engines.hpp"
#include "game.hpp"
#include "console.hpp"
#include "player_interaction.hpp"

using namespace std;

CliEngine::CliEngine()
{}

CliEngine::~CliEngine()
{}

void CliEngine::run()
{
    int i, numPlayers, numCardsEach;
    vector<string> playerNames;
    vector<char> playerTypes;
    console::clearScreen();
    console::showWelcomeMessage();
    numPlayers = console::requestNumPlayers();
    numCardsEach = console::requestNumCards();

    for (i = 0; i < numPlayers; i++) {
        string name = console::requestPlayerName(i+1);
        playerNames.push_back(name);

        char type = console::requestPlayerType(i+1);
        playerTypes.push_back(type);
    }

    Game game(playerNames, playerTypes, numCardsEach);
    game.deal();

    console::clearScreen();

    vector<Player *> players = game.players();
    vector<Player *>::const_iterator piter;
    for (piter = players.begin(); piter!=players.end(); piter++)
        interact::swap(**piter, game);

    game.firstMove();

    while (game.canContinue()) {
        const Player *currentPlayer = game.currentPlayer();
        console::clearScreen();
        console::showGame(game);
        if (game.playingFromFaceDown())
            interact::facedown_move(*currentPlayer, game);
        else
            interact::move(*currentPlayer, game);
    }

    console::showShithead(game.getCppHead());

}

