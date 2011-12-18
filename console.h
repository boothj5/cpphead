#ifndef H_CONSOLE
#define H_CONSOLE
#include <string>
#include "player.h"

using namespace std ;

void clearScreen(void) ;
void showWelcomeMessage(void) ;
int requestNumPlayers(void) ; 
int requestNumCards(void) ;
string * requestPlayerNames(int) ;
void showPlayer(Player player) ;
#endif
