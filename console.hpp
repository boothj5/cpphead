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
std::string requestPlayerName(int);
char requestPlayerType(int);
void showPlayers(const std::vector<Player *>&);
void showPlayer(const Player&);
void showHand(std::string, const std::vector<Card>&, bool);
bool requestSwapCards(std::string);
int requestHandChoice();
int requestFaceUpChoice();
bool requestSwapMore(std::string);
void showGame(const Game&);
void showPile(const std::vector<Card>&);
std::vector<int> requestMove(std::string);
void showPickUpMessage(std::string);
void wait_user();
void showBadMove();
int requestFaceDownCard(std::string);
void showFaceDownWin(const Card&);
void showFaceDownFail(const Card&);
void showShithead(std::string);

} // namespace console
#endif
