#include "player_interaction.hpp"
#include "player.hpp"
#include "game.hpp"
#include "console.hpp"

using namespace std;

void player_swap(Player *player, Game& game)
{
    if (!player->isComputer()) {
        clearScreen();
        showPlayer(*player);
        bool doSwap = requestSwapCards(player->name());
        while (doSwap) {
            int handChoice = requestHandChoice();
            int faceUpChoice = requestFaceUpChoice();
            game.swap(player, handChoice, faceUpChoice);
            clearScreen();
            showPlayer(*player);
            doSwap = requestSwapMore(player->name());
        }
    }
    else {
        bool doSwap = player->askSwapCards();
        while (doSwap) {
            pair<int, int> swapChoice = player->askSwapChoice();
            game.swap(player, swapChoice.first, swapChoice.second);
            doSwap = player->askSwapCards();
        }
    }
}

void player_move(const Player *player, Game& game)
{
    if (game.currentPlayerCanMove()) {
        vector<int> choices = requestMove(player->name());
        while (!game.validMove(choices)) {
            showBadMove();
            choices = requestMove(player->name());
        }
        game.makeMove(choices);
    } else {
        showPickUpMessage(player->name());
        game.pickUp();
    }
}


void player_facedown_move(const Player *player, Game& game)
{
    int choice = requestFaceDownCard(player->name());
    if (game.validMoveFromFaceDown(choice)) {
        showFaceDownWin(player->faceDown()[choice]);
        game.makeFaceDownMove(choice);
    }
    else {
        showFaceDownFail(player->faceDown()[choice]);
        game.pickUpPileAndFaceDown(choice);
    }
}
