#ifndef H_CONSOLE
#define H_CONSOLE

#include <string>
#include <vector>
#include "player.hpp"
#include "game.hpp"

#define CLEARSCREEN true

namespace console {

void clearScreen();
void showWelcomeMessage();
int requestNumPlayers(); 
int requestNumCards();
const std::string requestPlayerName(const int);
char requestPlayerType(const int);
void showPlayers(const std::vector<Player *>&);
void showPlayer(const Player&);
void showHand(const std::string, const std::vector<Card>&, const bool);
bool requestSwapCards(const std::string);
int requestHandChoice();
int requestFaceUpChoice();
bool requestSwapMore(const std::string);
void showGame(const Game&);
void showPile(const std::vector<Card>&);
const std::vector<int> requestMove(const std::string);
void showPickUpMessage(const std::string);
void wait_user();
void showBadMove();
int requestFaceDownCard(const std::string);
void showFaceDownWin(const Card&);
void showFaceDownFail(const Card&);
void showShithead(const std::string);

} // namespace console
#endif
