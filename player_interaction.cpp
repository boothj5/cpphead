#include "player_interaction.hpp"
#include "player.hpp"
#include "game.hpp"
#include "console.hpp"
#include "player_helper.hpp"
#include "shithead_exception.hpp"

using namespace std;

void player_swap(Player *player, Game& game)
{
    if (!player->isComputer()) {
        console::clearScreen();
        console::showPlayer(*player);
        bool doSwap = console::requestSwapCards(player->name());
        while (doSwap) {
            int handChoice = console::requestHandChoice();
            int faceUpChoice = console::requestFaceUpChoice();
            game.swap(player, handChoice, faceUpChoice);
            console::clearScreen();
            console::showPlayer(*player);
            doSwap = console::requestSwapMore(player->name());
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
        if (!player->isComputer()) {
            vector<int> choices = console::requestMove(player->name());
            while (!game.validMove(choices)) {
                console::showBadMove();
                choices = console::requestMove(player->name());
            }
            game.makeMove(choices);
        }  else {
            // computer player
            PlayerHelper helper = game.getPlayerHelper();
            vector<int> choices = player->askMoveChoice(helper);
            if (!game.validMove(choices)) {
                throw new ShitheadException("Computer player is cheating!");
            } else {
                game.makeMove(choices);
            }            
        }
    } else {
        if (!player->isComputer()) {
            console::showPickUpMessage(player->name());
            game.pickUp();
        } else {
            game.pickUp();
        }
    }
}


void player_facedown_move(const Player *player, Game& game)
{
    int choice = 0;
    
    if (player->isComputer()) {
        choice = player->askFaceDownMoveChoice();
        if (game.validMoveFromFaceDown(choice)) {
            game.makeFaceDownMove(choice);
        }
        else {
            game.pickUpPileAndFaceDown(choice);
        }
    } else {
        choice = console::requestFaceDownCard(player->name());
        if (game.validMoveFromFaceDown(choice)) {
            console::showFaceDownWin(player->faceDown()[choice]);
            game.makeFaceDownMove(choice);
        }
        else {
            console::showFaceDownFail(player->faceDown()[choice]);
            game.pickUpPileAndFaceDown(choice);
        }
    }
}
